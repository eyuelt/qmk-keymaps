// Handles RGB-related functionality.

#include "print.h"  // for debug output

// Save the rgb matrix mode in order to restore it later.
static uint8_t saved_rgb_matrix_mode_ = 0;
void set_saved_rgb_matrix_mode(uint8_t mode) {
  dprintf("set_saved_rgb_matrix_mode(%d)\n", mode);
  saved_rgb_matrix_mode_ = mode;
}
uint8_t get_saved_rgb_matrix_mode(void) {
  dprintf("get_saved_rgb_matrix_mode() => %d\n", saved_rgb_matrix_mode_);
  return saved_rgb_matrix_mode_;
}

// If the given rgb matrix mode is outside of the bounds, wrap around
uint8_t wrapped_rgb_matrix_mode(const uint8_t mode) {
  uint8_t wrapped = mode;
  if (wrapped <= RGB_MATRIX_NONE) {
    wrapped = RGB_MATRIX_EFFECT_MAX - 1;
  } else if (wrapped >= RGB_MATRIX_EFFECT_MAX) {
    wrapped = RGB_MATRIX_NONE + 1;
  }
  return wrapped;
}

static bool is_in_rgb_matrix_preview_ = false;
void begin_rgb_matrix_preview(void) {
  if (!is_in_rgb_matrix_preview_) {
    rgb_matrix_mode_noeeprom(get_saved_rgb_matrix_mode());
    is_in_rgb_matrix_preview_ = true;
  }
}
void end_rgb_matrix_preview(void) {
  if (is_in_rgb_matrix_preview_) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_null_effect);
    is_in_rgb_matrix_preview_ = false;
  }
}

// Define custom behavior for any RGB-related keys.
bool rgb_key_custom_behavior(uint16_t keycode, keyrecord_t *record) {
  const uint8_t mod_state = get_mods();
  switch (keycode) {
    case RGB_MOD:
      if (record->event.pressed) {
        if (mod_state & MOD_MASK_SHIFT) {
          set_saved_rgb_matrix_mode(
              wrapped_rgb_matrix_mode(get_saved_rgb_matrix_mode() - 1));
        } else {
          set_saved_rgb_matrix_mode(
              wrapped_rgb_matrix_mode(get_saved_rgb_matrix_mode() + 1));
        }
        begin_rgb_matrix_preview();
      } else {
        end_rgb_matrix_preview();
      }
      return false;
  }
  return true;
}

// Redefine the default behavior for the RGB_* keycodes, to do the same thing
// they normally do, except without writing to EEPROM.
// For brevity, we only define the behavior for the keys that we care about.
bool rgb_key_default_behavior(uint16_t keycode, keyrecord_t *record) {
  const uint8_t mod_state = get_mods();
  const bool is_shift_on = mod_state & MOD_MASK_SHIFT;
  if (record->event.pressed) {
    switch (keycode) {
      case RGB_HUI:
        is_shift_on ?
          rgb_matrix_decrease_hue_noeeprom() :
          rgb_matrix_increase_hue_noeeprom();
        return false;
      case RGB_SAI:
        is_shift_on ?
          rgb_matrix_decrease_sat_noeeprom() :
          rgb_matrix_increase_sat_noeeprom();
        return false;
      case RGB_VAI:
        is_shift_on ?
          rgb_matrix_decrease_val_noeeprom() :
          rgb_matrix_increase_val_noeeprom();
        return false;
      case RGB_MOD:
        is_shift_on ?
          rgb_matrix_step_reverse_noeeprom() :
          rgb_matrix_step_noeeprom();
        return false;
      case RGB_TOG:
        rgb_matrix_toggle_noeeprom();
        return false;
    }
  }
  // Don't continue to propagate the event to any other handlers.
  return false;
}
