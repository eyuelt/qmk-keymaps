// Handles the logic for determining which half of the keyboard this is.

#include <stdio.h>

// Whether or not this half of the keyboard was initially incorrect about which
// side of the keyboard it is and should be inverted.
// Note: Does not affect keymap, as that is determined solely by the master.
bool should_invert_keyboard_ = false;

// Initial is_keyboard_left from qmk_firmware/quantum/split_common/split_util.c
bool OLD_is_keyboard_left(void) {
#if defined(SPLIT_HAND_PIN)
    // Test pin SPLIT_HAND_PIN for High/Low, if low it's right hand
    setPinInput(SPLIT_HAND_PIN);
#    ifdef SPLIT_HAND_PIN_LOW_IS_LEFT
    return !readPin(SPLIT_HAND_PIN);
#    else
    return readPin(SPLIT_HAND_PIN);
#    endif
#elif defined(SPLIT_HAND_MATRIX_GRID)
#    ifdef SPLIT_HAND_MATRIX_GRID_LOW_IS_RIGHT
    return peek_matrix_intersection(SPLIT_HAND_MATRIX_GRID);
#    else
    return !peek_matrix_intersection(SPLIT_HAND_MATRIX_GRID);
#    endif
#elif defined(EE_HANDS)
    return eeconfig_read_handedness();
#elif defined(MASTER_RIGHT)
    return !is_keyboard_master();
#endif
    return is_keyboard_master();
}

// Override is_keyboard_left from qmk_firmware/quantum/split_common/split_util.c
// to allow it to be changed programmatically based on should_invert_keyboard_..
bool is_keyboard_left(void) {
  const bool is_left = OLD_is_keyboard_left();
  return should_invert_keyboard_ ? !is_left : is_left;
}

