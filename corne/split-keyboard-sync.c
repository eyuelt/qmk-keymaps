// Handles sending data between halves of the split keyboard.

#include <stdio.h>

#include "is_kb_left.c"
#include "print.h"  // for debug output
#include "transactions.h"

#define MAX_SYNC_RETRIES 5


// Declarations for helper functions.
bool _transaction_rpc_exec_with_retries(
    int8_t transaction_id, char *transaction_name,
    uint8_t m2s_buffer_size, const void *m2s_buffer,
    uint8_t s2m_buffer_size, void *s2m_buffer);


// LAYER_SYNC
// ==========
// Sync layer changes across the split. Otherwise, the slave half will not know
// when the master changes layers. This is required for addressing the LEDs of
// the slave half.
// Note: Although the state of the LED matrix is determined by each half's
// individual layer state, the keymap seems to be determined solely by the
// keymap of the master.

typedef struct _LayerSyncM2S {
  int layer_num;
} LayerSyncM2S;

typedef struct _LayerSyncS2M {
  int layer_num;
} LayerSyncS2M;

// Run on the slave when a LAYER_SYNC transaction is received.
void _layer_sync_slave_handler(
    uint8_t in_buflen, const void *in_data,
    uint8_t out_buflen, void *out_data) {
  const LayerSyncM2S *m2s = (const LayerSyncM2S *)in_data;
  layer_move(m2s->layer_num);
  LayerSyncS2M *s2m = (LayerSyncS2M *)out_data;
  s2m->layer_num = get_highest_layer(layer_state);
}

// Notify slave of layer change.
void layer_sync(const layer_state_t state) {
  if (is_keyboard_master()) {
    LayerSyncM2S m2s = {get_highest_layer(state)};
    LayerSyncS2M s2m = {0};
    _transaction_rpc_exec_with_retries(
            LAYER_SYNC, "LAYER_SYNC", sizeof(m2s), &m2s, sizeof(s2m), &s2m);
  }
}


// SIDE_SYNC
// =========
// Sometimes we flash the keyboards differently: one with MASTER_LEFT, the
// other with MASTER_RIGHT. In this case, the slave will be incorrect about
// whether it is the left or right half. As a result, it will end up displaying
// the LEDs inverted.
// Note: This does not affect the keymap, since keymap is determined solely by
// the master.

typedef struct _SideSyncM2S {
  bool master_is_left;
} SideSyncM2S;

typedef struct _SideSyncS2M {
  bool slave_is_right;
} SideSyncS2M;

// Run on the slave when a SIDE_SYNC transaction is received.
void _side_sync_slave_handler(
    uint8_t in_buflen, const void *in_data,
    uint8_t out_buflen, void *out_data) {
  const SideSyncM2S *m2s = (const SideSyncM2S *)in_data;
  SideSyncS2M *s2m = (SideSyncS2M *)out_data;
  should_invert_keyboard_ = m2s->master_is_left == OLD_is_keyboard_left();
  s2m->slave_is_right = !is_keyboard_left();
}

// Notify the slave of which side of the keyboard the master is, so that the
// slave can figure out which side it is on.
void side_sync(void) {
  if (is_keyboard_master()) {
    SideSyncM2S m2s = {is_keyboard_left()};
    SideSyncS2M s2m = {0};
    if (_transaction_rpc_exec_with_retries(
          SIDE_SYNC, "SIDE_SYNC", sizeof(m2s), &m2s, sizeof(s2m), &s2m)) {
      if (m2s.master_is_left != s2m.slave_is_right) {
        dprint("SIDE_SYNC error.\n");
      }
    }
  }
}


// Registration
// ============

void register_sync_transactions(void) {
  transaction_register_rpc(LAYER_SYNC, _layer_sync_slave_handler);
  transaction_register_rpc(SIDE_SYNC, _side_sync_slave_handler);
}


// Helpers
// =======

bool _transaction_rpc_exec_with_retries(
    int8_t transaction_id, char *transaction_name,
    uint8_t m2s_buffer_size, const void *m2s_buffer,
    uint8_t s2m_buffer_size, void *s2m_buffer) {
  int sync_attempt = 0;
  for (; sync_attempt <= MAX_SYNC_RETRIES; ++sync_attempt) {
    if (transaction_rpc_exec(
          transaction_id, m2s_buffer_size,
          m2s_buffer, s2m_buffer_size, s2m_buffer)) {
      break;
    } else {
      dprintf("%s failed attempt %d\n", transaction_name, sync_attempt);
      // Adding a 1ms delay here makes repeated failures much less likely.
      // Note: _delay_ms makes the whole keyboard hang, so use it sparingly.
      _delay_ms(1);
    }
  }
  if (sync_attempt > MAX_SYNC_RETRIES) {
    dprintf("%s failed all %d attempts!\n", transaction_name, sync_attempt);
    return false;
  }
  return true;
}
