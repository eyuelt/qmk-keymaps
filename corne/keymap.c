#include QMK_KEYBOARD_H

#include <stdio.h>

#include "layer.c"
#include "rgb.c"

enum layers {
  BASE,
  SYMBOLS,
  CONTROLS,
  MEDIA,
  WARP_ZONE
};

enum custom_keycodes {
  BSP_DEL = SAFE_RANGE,
};

#define MO_WARP MO(WARP_ZONE)
#define MO_SMBL MO(SYMBOLS)
#define MO_CTRL MO(CONTROLS)
#define CMD_LBRC LGUI(KC_LBRC)
#define CMD_RBRC LGUI(KC_RBRC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSLS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, MO_CTRL,  KC_SPC,     KC_ENT, MO_SMBL, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

  [SYMBOLS] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR,  KC_GRV,                      XXXXXXX,    KC_7,    KC_8,    KC_9, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_MINS,                      XXXXXXX,    KC_4,    KC_5,    KC_6, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_LPRN, KC_RPRN, KC_LBRC, KC_RBRC,  KC_EQL,                      XXXXXXX,    KC_1,    KC_2,    KC_3, XXXXXXX, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, MO_WARP, BSP_DEL,     KC_ENT, MO_WARP,    KC_0
                                      //`--------------------------'  `--------------------------'
  ),

  [CONTROLS] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, XXXXXXX, XXXXXXX,   KC_UP, XXXXXXX, XXXXXXX,                      KC_WH_D, KC_BTN1, KC_MS_U, KC_BTN2, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, KC_LEFT, KC_DOWN,KC_RIGHT, XXXXXXX,                      KC_WH_U, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX,CMD_LBRC,  KC_ESC,CMD_RBRC, XXXXXXX, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, MO_WARP,  KC_SPC,     KC_ENT, MO_WARP, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

  [MEDIA] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_MPLY, KC_MRWD, KC_MFFD, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, RGB_HUI, RGB_SAI, RGB_VAI, RGB_MOD, RGB_TOG,                      XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, KC_BRID, KC_BRIU, XXXXXXX, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, MO_WARP,  KC_SPC,     KC_ENT, MO_WARP, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

  [WARP_ZONE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX,   TO(1),   TO(2),   TO(3), XXXXXXX, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT, _______,   TO(0)
                                      //`--------------------------'  `--------------------------'
  )
};

// Called by the system for each key event.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  const uint8_t mod_state = get_mods();
  switch (keycode) {
    // regular backspace except it's treated as delete if shift is held
    case BSP_DEL:
      if (mod_state & MOD_MASK_SHIFT) {
        set_mods(mod_state & ~MOD_MASK_SHIFT);
        if (record->event.pressed) {
          register_code(KC_DEL);
        } else {
          unregister_code(KC_DEL);
        }
        set_mods(mod_state);
        return false;
      } else {
        if (record->event.pressed) {
          register_code(KC_BSPC);
        } else {
          unregister_code(KC_BSPC);
        }
        return false;
      }
    case RGB_TOG ... RGB_MODE_RGBTEST:
      return
        rgb_key_custom_behavior(keycode, record) &&
        rgb_key_default_behavior(keycode, record);
  }
  return true;
}


// ------------------------------ LEDs ------------------------------ //
// Note: changes here require a reflash of both halves of the keyboard.

#define OFF -1
#define HSV_DEGREES_TO_HSV_8BIT(deg) (uint8_t)(deg % 360 / 360.0 * 256)
#define BLU HSV_DEGREES_TO_HSV_8BIT(240)
#define GRN HSV_DEGREES_TO_HSV_8BIT(120)
#define MAG HSV_DEGREES_TO_HSV_8BIT(283)
#define YLW HSV_DEGREES_TO_HSV_8BIT( 60)
#define VIO HSV_DEGREES_TO_HSV_8BIT(253)
#define RED HSV_DEGREES_TO_HSV_8BIT(  0)
#define CYN HSV_DEGREES_TO_HSV_8BIT(180)
#define ORG HSV_DEGREES_TO_HSV_8BIT( 30)

const int16_t led_hues[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_split_3x6_3(
       BLU,  OFF,  OFF,  OFF,  OFF,  OFF,                OFF,  OFF,  OFF,  OFF,  OFF,  OFF,
       OFF,  OFF,  OFF,  OFF,  OFF,  OFF,                OFF,  OFF,  OFF,  OFF,  OFF,  OFF,
       OFF,  OFF,  OFF,  OFF,  OFF,  OFF,                OFF,  OFF,  OFF,  OFF,  OFF,  OFF,
                               OFF,  OFF,  OFF,    OFF,  OFF,  OFF
  ),

  [SYMBOLS] = LAYOUT_split_3x6_3(
       OFF,  BLU,  OFF,  OFF,  OFF,  OFF,                OFF,  MAG,  MAG,  MAG,  OFF,  OFF,
       OFF,  OFF,  OFF,  OFF,  OFF,  OFF,                OFF,  MAG,  MAG,  MAG,  OFF,  OFF,
       OFF,  OFF,  OFF,  OFF,  OFF,  OFF,                OFF,  MAG,  MAG,  MAG,  OFF,  OFF,
                               OFF,  OFF,  OFF,    OFF,  OFF,  MAG
  ),

  [CONTROLS] = LAYOUT_split_3x6_3(
       OFF,  OFF,  BLU,  VIO,  OFF,  OFF,                VIO,  OFF,  CYN,  OFF,  OFF,  OFF,
       OFF,  OFF,  VIO,  VIO,  VIO,  OFF,                VIO,  CYN,  CYN,  CYN,  OFF,  OFF,
       OFF,  OFF,  OFF,  OFF,  OFF,  OFF,                OFF,  OFF,  OFF,  OFF,  OFF,  OFF,
                               OFF,  OFF,  OFF,    OFF,  OFF,  OFF
  ),

  [MEDIA] = LAYOUT_split_3x6_3(
       OFF,  OFF,  OFF,  BLU,  OFF,  OFF,                OFF,  MAG,  MAG,  MAG,  OFF,  OFF,
       OFF,  ORG,  ORG,  ORG,  ORG,  OFF,                OFF,  RED,  BLU,  BLU,  OFF,  OFF,
       OFF,  OFF,  OFF,  OFF,  OFF,  OFF,                OFF,  OFF,  YLW,  YLW,  OFF,  OFF,
                               OFF,  OFF,  OFF,    OFF,  OFF,  OFF
  ),

  [WARP_ZONE] = LAYOUT_split_3x6_3(
       OFF,  OFF,  OFF,  OFF,  BLU,  OFF,                OFF,  OFF,  OFF,  OFF,  OFF,  OFF,
       OFF,  OFF,  OFF,  OFF,  OFF,  OFF,                OFF,  OFF,  OFF,  OFF,  OFF,  OFF,
       OFF,  OFF,  OFF,  OFF,  OFF,  OFF,                OFF,  GRN,  GRN,  GRN,  OFF,  OFF,
                               OFF,  OFF,  OFF,    OFF,  OFF,  GRN
  )
};

#undef OFF
#undef HSV_DEGREES_TO_HSV_8BIT
#undef BLU
#undef GRN
#undef MAG
#undef YLW
#undef VIO
#undef RED
#undef CYN
#undef ORG

// Called by the system to allow setting all LEDs on the keyboard.
void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
  const int16_t (*layer_led_hues)[MATRIX_COLS] =
    led_hues[get_highest_layer(layer_state)];
  for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
    for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
      const int16_t hue_for_key = layer_led_hues[row][col];
      if (hue_for_key >= 0 && hue_for_key < 256) {
        const uint8_t led_index = g_led_config.matrix_co[row][col];
        const HSV hsv = {hue_for_key, rgb_matrix_get_sat(), rgb_matrix_get_val()};
        const RGB rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color(led_index, rgb.r, rgb.g, rgb.b);  // Not written to EEPROM
      }
    }
  }
}

// Called every time the layers are changed.
layer_state_t layer_state_set_user(layer_state_t state) {
  if (leaving_layer(BASE, layer_state, state)) {
    set_saved_rgb_matrix_mode(rgb_matrix_get_mode());
    rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_null_effect);
  } else if (entering_layer(BASE, layer_state, state)) {
    rgb_matrix_mode_noeeprom(get_saved_rgb_matrix_mode());
    end_rgb_matrix_preview();
  }
  return state;
}

// Called at keyboard initialization.
void keyboard_post_init_user(void) {
#ifdef CONSOLE_ENABLE
  // enable debug output
  debug_enable = true;
  debug_matrix = true;
#endif
  // set initial color/mode for keyboard
  rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_null_effect);
}
