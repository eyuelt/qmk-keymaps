#pragma once

//#define USE_MATRIX_I2C

/* Select hand configuration */

#include "conditional/master_left/config.h"
// #define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

//#define TAPPING_FORCE_HOLD
//#define TAPPING_TERM 100


// Sync layer changes across the split.
#define SPLIT_LAYER_STATE_ENABLE


#ifdef RGB_MATRIX_ENABLE
#  define RGB_MATRIX_KEYPRESSES  // enable effects that react to keypresses (as opposed to keyreleases)
#  define RGB_MATRIX_FRAMEBUFFER_EFFECTS  // enable framebuffer effects (i.e. heatmap, digital rain)
// #  define RGB_DISABLE_AFTER_TIMEOUT 0 // number of ticks to wait until disabling effects
#  define RGB_DISABLE_WHEN_USB_SUSPENDED  // turn off effects when suspended
// #  define RGB_MATRIX_LED_PROCESS_LIMIT (DRIVER_LED_TOTAL + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
// #  define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
#  define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150 // limit to 150 out of 255. Higher may cause controller to crash.
#  define RGB_MATRIX_HUE_STEP 8
#  define RGB_MATRIX_SAT_STEP 8
#  define RGB_MATRIX_VAL_STEP 8
#  define RGB_MATRIX_SPD_STEP 10
// RGB Matrix Animation modes.
// Note: These take up a lot of space.
// For full list of effects, see https://docs.qmk.fm/#/feature_rgb_matrix?id=rgb-matrix-effects.
// To add custom effects, see https://docs.qmk.fm/#/feature_led_matrix?id=custom-rgb-matrix-effects.
// TODO: add a custom effect that does nothing. otherwise the only way to have
// no effect is to turn off the LEDs altogether
#  ifndef CONSOLE_ENABLE  // debug mode needs the additional space
#    define ENABLE_RGB_MATRIX_BREATHING                    // sine-like oscillation of value
#    define ENABLE_RGB_MATRIX_BAND_VAL                     // horizontally travelling column of high value
//   Note: The problem with this one is that the keys hold their last value.
//   TODO: Only keep it if we can figure out how to limit effects to the BASE layer.
#    define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS          // random soft colors with keys changing color randomly
#    define ENABLE_RGB_MATRIX_PIXEL_FRACTAL                // looks kinda like conway's game of life
#    ifdef RGB_MATRIX_FRAMEBUFFER_EFFECTS  // required for these effects
#      define ENABLE_RGB_MATRIX_TYPING_HEATMAP             // typing heat map
#      define ENABLE_RGB_MATRIX_DIGITAL_RAIN               // matrix-like rain falling one-by-one from top to bottom
#    endif
#    if defined(RGB_MATRIX_KEYPRESSES) || defined(RGB_MATRIX_KEYRELEASES)  // required for these effects
//     TODO: these are broken. they are being mirrored for some reason
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


// Transaction IDs for sending messages across the split.
#define SPLIT_TRANSACTION_IDS_USER LAYER_SYNC, SIDE_SYNC
