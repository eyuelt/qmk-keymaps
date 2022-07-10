#pragma once


// Determine hand configuration from data flashed on keyboard halves.
#define EE_HANDS

// Sync layer changes across the split.
#define SPLIT_LAYER_STATE_ENABLE

// This allows keypress-triggered effects that affect multiple LEDs to be able
// to affect LEDs across the split.
// Note: This is already defined in crkbd/rev1/config.h. We redefine it here
// just to make it explicit.
#define SPLIT_TRANSPORT_MIRROR

// Disable control of the RGB matrix by the normal RGB_* keycodes.
// We will redefine these keycodes to not write to EEPROM.
#define RGB_MATRIX_DISABLE_KEYCODES


#ifdef RGB_MATRIX_ENABLE
#  define RGB_MATRIX_KEYPRESSES  // enable effects that react to keypresses (as opposed to keyreleases)
#  define RGB_MATRIX_FRAMEBUFFER_EFFECTS  // enable framebuffer effects (i.e. heatmap, digital rain)
#  define RGB_DISABLE_WHEN_USB_SUSPENDED  // turn off effects when suspended
#  define RGB_MATRIX_LED_FLUSH_LIMIT 16  // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
#  define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150 // limit to 150 out of 255. Higher may cause controller to crash.
#  define RGB_MATRIX_HUE_STEP 8
#  define RGB_MATRIX_SAT_STEP 8
#  define RGB_MATRIX_VAL_STEP 8
#  define RGB_MATRIX_SPD_STEP 10
// RGB Matrix Animation modes.
// Note: These take up a lot of space.
// For full list of effects, see https://docs.qmk.fm/#/feature_rgb_matrix?id=rgb-matrix-effects.
// To add custom effects, see https://docs.qmk.fm/#/feature_led_matrix?id=custom-rgb-matrix-effects.
#  define ENABLE_RGB_MATRIX_BREATHING                      // sine-like oscillation of value
#  define ENABLE_RGB_MATRIX_BAND_VAL                       // horizontally travelling column of high value
#  ifndef CONSOLE_ENABLE  // disable most effects in debug mode to conserve space
#    define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS          // random soft colors with keys changing color randomly
#    define ENABLE_RGB_MATRIX_PIXEL_FRACTAL                // looks kinda like conway's game of life
#    ifdef RGB_MATRIX_FRAMEBUFFER_EFFECTS  // required for these effects
#      define ENABLE_RGB_MATRIX_TYPING_HEATMAP             // typing heat map
#      define ENABLE_RGB_MATRIX_DIGITAL_RAIN               // matrix-like rain falling one-by-one from top to bottom
#    endif
#    if defined(RGB_MATRIX_KEYPRESSES) || defined(RGB_MATRIX_KEYRELEASES)  // required for these effects
#      define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE      // simple glow on keypress
#      define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE        // big glow on keypress
#      define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE   // big glow on keypress of multiple keys
#    endif
#  endif
#endif


#ifdef RGBLIGHT_ENABLE
#  ifndef CONSOLE_ENABLE  // debug mode needs the additional space
#    define RGBLIGHT_LIMIT_VAL 120
#    define RGBLIGHT_HUE_STEP 10
#    define RGBLIGHT_SAT_STEP 17
#    define RGBLIGHT_VAL_STEP 17
#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#    define RGBLIGHT_EFFECT_TWINKLE
#  endif
#endif
