/*
Copyright 2021 Sadek Baroudi <sadekbaroudi@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#include "config_common.h"


/* USB Device descriptor parameter */
#define DEVICE_VER      0x0001
#define VENDOR_ID       0xFEFE
#define PRODUCT_ID      0xFFBB
#define MANUFACTURER    sadekbaroudi
#define PRODUCT         sadekbaroudi ffkb_byomcu
#define DESCRIPTION     sadekbaroudi ffkb_byomcu

/* key matrix size */
/* Rows are doubled up */
#define MATRIX_ROWS 6
#define MATRIX_COLS 8

// SHIFT REGISTER
// Only needed for matrix_fingerpunch.c
// #define SHIFTREG_MATRIX_COL_LATCH B6
// #define SHIFTREG_MATRIX_COL_CLK B1
// #define SHIFTREG_MATRIX_COL_DATA B2
// Only needed for matrix_74hc595_spi.c
#define SHIFTREG_MATRIX_COL_CS B6
#define SHIFTREG_DIVISOR 8 // needs to be the same as the PMW33XX_CS_DIVISOR below
/* Row pin definitions */
#define MATRIX_ROW_PINS_SR { D2, F4, F5, F6, F7, D4 }

#define UNUSED_PINS

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

#define RGB_DI_PIN D3 // 41
#ifdef RGBLIGHT_ENABLE
  // Use twinkle as the default rgb mode for the layers
  #define DEFAULT_RGB_LAYER_MODE RGBLIGHT_MODE_TWINKLE+2
  #define RGBLED_NUM 42
  #define RGBLIGHT_HUE_STEP 16
  #define RGBLIGHT_SAT_STEP 16
  #define RGBLIGHT_VAL_STEP 16
  #define RGBLIGHT_LIMIT_VAL 112 /* The maximum brightness level for RGBLIGHT_ENABLE */
  #define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
// /*== all animations enable ==*/
  #define RGBLIGHT_ANIMATIONS
// /*== or choose animations ==*/
//   #define RGBLIGHT_EFFECT_BREATHING
//   #define RGBLIGHT_EFFECT_RAINBOW_MOOD
//   #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
//   #define RGBLIGHT_EFFECT_SNAKE
//   #define RGBLIGHT_EFFECT_KNIGHT
//   #define RGBLIGHT_EFFECT_CHRISTMAS
//   #define RGBLIGHT_EFFECT_STATIC_GRADIENT
//   #define RGBLIGHT_EFFECT_RGB_TEST
//   #define RGBLIGHT_EFFECT_ALTERNATING
// /*== customize breathing effect ==*/
//   /*==== (DEFAULT) use fixed table instead of exp() and sin() ====*/
//   #define RGBLIGHT_BREATHE_TABLE_SIZE 256      // 256(default) or 128 or 64
//   /*==== use exp() and sin() ====*/
//   #define RGBLIGHT_EFFECT_BREATHE_CENTER 1.85  // 1 to 2.7
//   #define RGBLIGHT_EFFECT_BREATHE_MAX    255   // 0 to 255
#endif

#ifdef RGB_MATRIX_ENABLE
  #define DRIVER_LED_TOTAL 42
  #define RGB_MATRIX_CENTER {100, 32}
  #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 112  /* The maximum brightness level for RGB_MATRIX */
  #define RGB_MATRIX_STARTUP_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS // Sets the default brightness value, if none has been set
  #define RGB_MATRIX_KEYPRESSES
  #define RGB_MATRIX_FRAMEBUFFER_EFFECTS
  #define RGB_MATRIX_KEYREACTIVE_ENABLED
  #define ENABLE_RGB_MATRIX_ALPHAS_MODS
  // #define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
  // #define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
  #define ENABLE_RGB_MATRIX_BREATHING
  #define ENABLE_RGB_MATRIX_BAND_SAT
  #define ENABLE_RGB_MATRIX_BAND_VAL
  // #define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
  // #define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
  // #define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
  // #define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
  // #define ENABLE_RGB_MATRIX_CYCLE_ALL
  #define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
  #define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
  // #define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
  #define ENABLE_RGB_MATRIX_DUAL_BEACON
  // #define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
  // #define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
  // #define ENABLE_RGB_MATRIX_RAINBOW_BEACON
  // #define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
  // #define ENABLE_RGB_MATRIX_RAINDROPS
  // #define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
  // #define ENABLE_RGB_MATRIX_DIGITAL_RAIN
  #define ENABLE_RGB_MATRIX_SOLID_REACTIVE
  #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
  // #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
  // #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
  // #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
  // #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
  // #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
  // #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
  // #define ENABLE_RGB_MATRIX_SPLASH
  // #define ENABLE_RGB_MATRIX_MULTISPLASH
  // #define ENABLE_RGB_MATRIX_SOLID_SPLASH
  // #define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
#endif

#define ENCODERS_PAD_A {D7, B4}
#define ENCODERS_PAD_B {C6, E6}

#define ENCODER_RESOLUTION 2
// Per encoder settings
//#define ENCODER_RESOLUTIONS { 2, 2 }

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#ifdef PIMORONI_TRACKBALL_ENABLE
#define PIMORONI_TRACKBALL_ROTATE
#define PIMORONI_TRACKBALL_CLICK
#endif

// cirque trackpad config
#define CIRQUE_PINNACLE_ADDR 0x2A
#define POINTING_DEVICE_TASK_THROTTLE_MS 5
#define I2C1_CLOCK_SPEED  400000
#define I2C1_DUTY_CYCLE FAST_DUTY_CYCLE_2

// If using encoder type 2, uncomment this
// #define ENCODERS_B_REVERSE

#define DYNAMIC_KEYMAP_LAYER_COUNT 5

// Trackball config
// Move into pwm3360 feature directory
#define PMW33XX_CS_PIN B5
#define PMW33XX_CPI 800
#define PMW33XX_CS_DIVISOR 8 // needs to be the same as the SHIFTREG_DIVISOR above
#define POINTING_DEVICE_INVERT_Y

/* SPI config for pmw3360 sensor. */
#define SPI_DRIVER SPID1
#define SPI_SCK_PIN B1
#define SPI_SCK_PAL_MODE 5
#define SPI_MOSI_PIN B2
#define SPI_MOSI_PAL_MODE 5
#define SPI_MISO_PIN B3
#define SPI_MISO_PAL_MODE 5
// end Trackball config
