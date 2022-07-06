#pragma once

//#define USE_MATRIX_I2C

/* Select hand configuration */

#include "conditional/master_left/config.h"
// #define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

//#define TAPPING_FORCE_HOLD
//#define TAPPING_TERM 100

#ifdef RGBLIGHT_ENABLE
    #define RGBLIGHT_EFFECT_BREATHING
    #define RGBLIGHT_EFFECT_RAINBOW_MOOD
    #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
    #define RGBLIGHT_EFFECT_SNAKE
    #define RGBLIGHT_EFFECT_KNIGHT
    #define RGBLIGHT_EFFECT_CHRISTMAS
    #define RGBLIGHT_EFFECT_STATIC_GRADIENT
    #define RGBLIGHT_EFFECT_RGB_TEST
    #define RGBLIGHT_EFFECT_ALTERNATING
    #define RGBLIGHT_EFFECT_TWINKLE
    #define RGBLIGHT_LIMIT_VAL 120
    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 17
#endif

#ifdef RGB_MATRIX_ENABLE
#  ifndef CONSOLE_ENABLE  // debug mode needs the additional memory
#    define RGB_MATRIX_KEYPRESSES // reacts to keypresses
// #   define RGB_MATRIX_KEYRELEASES // reacts to keyreleases (instead of keypresses)
// #   define RGB_DISABLE_AFTER_TIMEOUT 0 // number of ticks to wait until disabling effects
#    define RGB_DISABLE_WHEN_USB_SUSPENDED // turn off effects when suspended
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
// #   define RGB_MATRIX_LED_PROCESS_LIMIT (DRIVER_LED_TOTAL + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
// #   define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150 // limits maximum brightness of LEDs to 150 out of 255. Higher may cause the controller to crash.
#    define RGB_MATRIX_HUE_STEP 8
#    define RGB_MATRIX_SAT_STEP 8
#    define RGB_MATRIX_VAL_STEP 8
#    define RGB_MATRIX_SPD_STEP 10

/* Enable the animations you want/need.  You may need to enable only a small number of these because       *
 * they take up a lot of space.  Enable and confirm that you can still successfully compile your firmware. */
// RGB Matrix Animation modes. Explicitly enabled
// For full list of effects, see:
// https://docs.qmk.fm/#/feature_rgb_matrix?id=rgb-matrix-effects
//
// Custom effects can also be added. See https://docs.qmk.fm/#/feature_led_matrix?id=custom-led-matrix-effects.

#    define ENABLE_RGB_MATRIX_ALPHAS_MODS                  // modifier keys are all a different color
#    define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT          // horizontal rainbow gradient
#    define ENABLE_RGB_MATRIX_BREATHING                    // sine-like oscillation of value
#    define ENABLE_RGB_MATRIX_BAND_VAL                     // horizontally travelling column of high value
#    define ENABLE_RGB_MATRIX_RAINDROPS                    // random colors with individual keys changing color randomly
#    define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS          // same as above but with soft, baby-like colors
#    define ENABLE_RGB_MATRIX_HUE_BREATHING                // sine-like oscillation of hue
#    define ENABLE_RGB_MATRIX_HUE_WAVE                     // horizontally travelling column of changed hue
#    define ENABLE_RGB_MATRIX_PIXEL_RAIN                   // same as raindrops, but with more neutral colors and OFF is a valid color
#    define ENABLE_RGB_MATRIX_PIXEL_FLOW                   // various colors move around the keys in a snake-like pattern
#    define ENABLE_RGB_MATRIX_PIXEL_FRACTAL                // looks kinda like conway's game of life
// enabled only if RGB_MATRIX_FRAMEBUFFER_EFFECTS is defined
#    define ENABLE_RGB_MATRIX_TYPING_HEATMAP               // typing heat map
#    define ENABLE_RGB_MATRIX_DIGITAL_RAIN                 // matrix-like rain falling slowly from top to bottom of keyboard, one key at a time
// enabled only if RGB_MATRIX_KEYPRESSES or RGB_MATRIX_KEYRELEASES is defined
// TODO: these are broken. they are being mirrored for some reason
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE        // simple glow on keypress
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE               // hue change on keypress
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE          // big glow (R=1) on keypress
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE     // big glow (R=2) on keypress
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS         // cross-shaped glow on keypress
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS    // can't tell difference from above
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS         // cross-shaped glow emanating out from center
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS    // can't tell difference from above
#    define ENABLE_RGB_MATRIX_SPLASH                       // rainbow puke emanating from keypress
#    define ENABLE_RGB_MATRIX_MULTISPLASH                  // can't tell difference from above
#    define ENABLE_RGB_MATRIX_SOLID_SPLASH                 // solid color puke emanting from keypress
#    define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH            // can't tell difference from above
#  endif
#endif


// Transaction IDs for sending messages across the split.
#define SPLIT_TRANSACTION_IDS_USER LAYER_SYNC, SIDE_SYNC
