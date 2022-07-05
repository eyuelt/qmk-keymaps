// Handles sending data between halves of the split keyboard.

#include <stdio.h>

#include "transactions.h"

#define MAX_LAYER_SYNC_ATTEMPTS 10

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
  // Set the layer on the slave half. Note that the keymap seems to be
  // determined solely by the keymap of the master, however the state of the LED
  // matrix is determined by each half's individual layer state.
  layer_move(m2s->layer_num);
  LayerSyncS2M *s2m = (LayerSyncS2M *)out_data;
  s2m->layer_num = get_highest_layer(layer_state);
}

void notify_slave_of_layer_change(const layer_state_t state) {
  if (is_keyboard_master()) {
    LayerSyncM2S m2s = {get_highest_layer(state)};
    LayerSyncS2M s2m = {0};
    int sync_attempt = 0;
    for (; sync_attempt < MAX_LAYER_SYNC_ATTEMPTS; ++sync_attempt) {
      if (transaction_rpc_exec(
            LAYER_SYNC, sizeof(m2s), &m2s, sizeof(s2m), &s2m)) {
        break;
      }
    }
  }
}

void register_sync_transactions(void) {
  transaction_register_rpc(LAYER_SYNC, _layer_sync_slave_handler);
}
