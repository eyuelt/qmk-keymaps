// !!! DO NOT ADD #pragma once !!! //

// Declare custom effects here (note the lack of semicolon after the macro!)
RGB_MATRIX_EFFECT(null_effect)

// Define effects inside this ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// This effect just turns all of the non-indicator LEDs off.
static bool null_effect(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  for (uint8_t i = led_min; i < led_max; i++) {
    const HSV hsv = {0x00, 0x00, 0x00};
    const RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
  }
  return rgb_matrix_check_finished_leds(led_max);
}

#endif  // RGB_MATRIX_CUSTOM_EFFECT_IMPLS

