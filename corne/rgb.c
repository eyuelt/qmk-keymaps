// Handles RGB-related functionality.

// Define custom behavior for any RGB-related keys.
bool rgb_key_custom_behavior(uint16_t keycode, keyrecord_t *record) {
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
