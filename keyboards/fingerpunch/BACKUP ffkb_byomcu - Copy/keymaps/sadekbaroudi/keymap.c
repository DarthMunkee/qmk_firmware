/* Copyright 2021 Sadek Baroudi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "sadekbaroudi.h"
#ifdef PIMORONI_TRACKBALL_ENABLE
#include "drivers/sensors/pimoroni_trackball.h"
#include "pointing_device.h"
#include "color.h"
#endif
#include QMK_KEYBOARD_H

/*
 * The `LAYOUT_ffkb_base` macro is a template to allow the use of identical
 * modifiers for the default layouts (eg ALPHA_ALT, Colemak, Dvorak, etc), so
 * that there is no need to set them up for each layout, and modify all of
 * them if I want to change them.  This helps to keep consistency and ease
 * of use. K## is a placeholder to pass through the individual keycodes
 */

// clang-format off
#define LAYOUT_ffkb_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, \
              K33, K34, K35, K36, K37, K38 \
  ) \
  LAYOUT_wrapper( \
        KC_MS_BTN3,      K01,            K02,            K03,            LT(_FUNCTION, K04),     K05,                      K06,                   LT(_FUNCTION, K07),    K08,              K09,            K0A,          KC_BSLS, \
        KC_MS_BTN1,      LCTL_T(K11),    LGUI_T(K12),    LALT_T(K13),    LSFT_T(K14),            K15,                      LT(_MOUSE, K16),       RSFT_T(K17),           RALT_T(K18),      RGUI_T(K19),    RCTL_T(K1A),  LCTL(KC_V), \
        KC_MS_BTN2,      K21,            K22,            K23,            K24,                    K25,                      K26,                   K27,                   K28,              K29,            K2A,          S_ALT_TAB, \
                                 KC_MUTE,                K33,            LT(_NAVIGATION,K34),    LT(_FUNCTION,K35),        LT(_MEDIA,K36),        LT(_SYMBOLS,K37),      K38,              LCTL(KC_BSPC), \
                                                                                                           N_DEL_LINE \
    )

/* Re-pass though to allow templates to be used */
#define LAYOUT_ffkb_byomcu_base_wrapper(...)       LAYOUT_ffkb_base(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_ALPHA_ALT] = LAYOUT_ffkb_byomcu_base_wrapper(
        _________________ALPHA_ALT_L1_________________, _________________ALPHA_ALT_R1_________________,
        _________________ALPHA_ALT_L2_________________, _________________ALPHA_ALT_R2_________________,
        _________________ALPHA_ALT_L3_________________, _________________ALPHA_ALT_R3_________________,
                                             __ALPHA_ALT_THUMBS_6__
    ),

    [_ALPHA] = LAYOUT_ffkb_byomcu_base_wrapper(
        __________________ALPHA_L1____________________, __________________ALPHA_R1____________________,
        __________________ALPHA_L2____________________, __________________ALPHA_R2____________________,
        __________________ALPHA_L3____________________, __________________ALPHA_R3____________________,
                                              __ALPHA_THUMBS_6__
    ),

    [_NAVIGATION] = LAYOUT_wrapper(
        _______, ________________NAVIGATION_1_______________, _________________NUMPAD_1__________________, _______, 
        _______, ________________NAVIGATION_2_______________, _________________NUMPAD_2__________________, _______, 
        _______, ________________NAVIGATION_3_______________, _________________NUMPAD_3__________________, _______, 
                           _______, _______, _______, KC_TAB, KC_BSPC, KC_SPACE, KC_DOT, _______, 
                                                         _______
    ),

    [_SYMBOLS] = LAYOUT_wrapper(
        _______, ________________SYMBOLS_L1_________________, ________________SYMBOLS_R1_________________, _______, 
        _______, ________________SYMBOLS_L2_________________, ________________SYMBOLS_R2_________________, _______, 
        _______, ________________SYMBOLS_L3_________________, ________________SYMBOLS_R3_________________, _______, 
                           _______, _______, KC_ENT, KC_DEL,  KC_BSPC, _______, _______, _______,
                                                         _______
    ),

    [_FUNCTION] = LAYOUT_wrapper(
        _______, ________________SHIFTNAV_1_________________, ________________FUNCTION_1_________________, _______, 
        _______, ________________SHIFTNAV_2_________________, ________________FUNCTION_2_________________, _______, 
        _______, ________________SHIFTNAV_3_________________, ________________FUNCTION_3_________________, _______, 
                          _______, _______, _______, _______, N_DEL_LINE, KC_SPACE, _______, _______, 
                                                         _______
    ),

    [_MEDIA] = LAYOUT_wrapper(
        _______, ___________________RGB_1___________________, _________________MACROS_1__________________, _______, 
        _______, ___________________RGB_2___________________, _________________MACROS_2__________________, _______, 
        _______, ___________________RGB_3___________________, _________________MACROS_3__________________, _______, 
                          _______, _______, _______, _______, _______, _______, _______, _______,
                                                         _______
    ),
    
    [_MOUSE] = LAYOUT_wrapper(
        _______, __________________MOUSE_1__________________, ___________________BLANK___________________, _______, 
        _______, __________________MOUSE_2__________________, ___________________BLANK___________________, _______, 
        _______, __________________MOUSE_3__________________, ___________________BLANK___________________, _______, 
                    _______, _______, KC_MS_BTN1, KC_MS_BTN3, KC_MS_BTN3, KC_MS_BTN2, _______, _______,
                                                         _______
    )
};


#ifdef OLED_ENABLE


oled_rotation_t oled_init_user(oled_rotation_t rotation) {
      return OLED_ROTATION_180;
} 


static void render_logo(void) {
    // ffkb logo, 128x32px
    static const char PROGMEM ffkb_logo[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 
    0xf0, 0x10, 0x10, 0x10, 0x90, 0x30, 0x30, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xf0, 0xf8, 0xfc, 0x3c, 0x3c, 0x38, 0x70, 
    0x70, 0xe0, 0xe0, 0xc0, 0xc0, 0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 
    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0xc0, 0xc0, 0xe0, 0xe0, 0x70, 
    0x70, 0x38, 0x3c, 0x3c, 0xfc, 0xf8, 0xf0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0x10, 0x00, 
    0x80, 0x90, 0xd0, 0xf0, 0x30, 0x30, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 
    0x3f, 0x21, 0x01, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0xe7, 0xff, 0x7f, 0x7f, 0xbc, 0x9e, 0x8e, 0x8f, 
    0x87, 0x87, 0x83, 0x83, 0x81, 0x81, 0x81, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x81, 0x81, 0x81, 0x83, 0x83, 0x87, 0x87, 
    0x8f, 0x8e, 0x9e, 0xbc, 0x7f, 0x7f, 0xff, 0xe7, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x23, 0x07, 
    0x0f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3e, 0x3c, 0x38, 0x30, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 
    0xfc, 0x44, 0x44, 0x44, 0xe4, 0x0c, 0x0c, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x02, 0x06, 0x06, 0x07, 0x0f, 0x0f, 0x0f, 0x1f, 0x1f, 0x1b, 0x3b, 0x3b, 0x73, 0x73, 0x73, 0xe3, 
    0xe3, 0xdf, 0xdf, 0xdf, 0x8b, 0x83, 0x03, 0x03, 0x07, 0x1f, 0xfe, 0xfc, 0xf8, 0xe0, 0x00, 0x00, 
    0x00, 0x00, 0xe0, 0xf8, 0xfc, 0xfe, 0x1f, 0x07, 0x03, 0x03, 0x83, 0x8b, 0xdf, 0xdf, 0xdf, 0xe3, 
    0xe3, 0x73, 0x73, 0x73, 0x3b, 0x3b, 0x1b, 0x1f, 0x1f, 0x0f, 0x0f, 0x0f, 0x07, 0x06, 0x06, 0x02, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0x44, 0x44, 
    0x44, 0xfc, 0xfc, 0xfc, 0xfc, 0xf8, 0xb8, 0xb8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 
    0x0f, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x01, 0x01, 0x03, 0x03, 0x07, 0x07, 0x0f, 0x0e, 0x1f, 0x3f, 0x3f, 0x3f, 0x36, 0x36, 
    0x36, 0x36, 0x3f, 0x3f, 0x3f, 0x1f, 0x0e, 0x0f, 0x07, 0x07, 0x03, 0x03, 0x01, 0x01, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x08, 0x08, 
    0x08, 0x0f, 0x0f, 0x0f, 0x07, 0x07, 0x07, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    // ffkb logo, 128x64px
    // static const char PROGMEM ffkb_logo[] = {
    // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0xf0, 0xe0, 0xc0, 0x80, 
    // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // 0x80, 0xc0, 0xe0, 0xf0, 0xe0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 
    // 0xfe, 0x02, 0x02, 0x02, 0x82, 0x06, 0x0e, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xfe, 0xff, 0xff, 0x0f, 0x07, 0x0f, 0x1f, 
    // 0x3e, 0x7c, 0xf8, 0xf0, 0xe0, 0xc0, 0xe0, 0xe0, 0xe0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 
    // 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xe0, 0xe0, 0xe0, 0xc0, 0xe0, 0xf0, 0xf8, 0x7c, 0x3e, 
    // 0x1f, 0x0f, 0x07, 0x0f, 0xff, 0xff, 0xfe, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0x02, 0x82, 
    // 0x82, 0xc2, 0xe2, 0xde, 0x0e, 0x0e, 0x06, 0x02, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    // 0xff, 0x02, 0x02, 0x07, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xe0, 0xf8, 0xfc, 0x7e, 
    // 0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x03, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x03, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 
    // 0x7e, 0xfc, 0xf8, 0xe0, 0xff, 0xff, 0xff, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x1f, 
    // 0x7f, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xf0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 
    // 0x07, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xf0, 0xf8, 0xff, 0x7f, 0x1f, 0x87, 0x83, 0x80, 0x80, 
    // 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
    // 0x80, 0x80, 0x83, 0x87, 0x1f, 0x7f, 0xff, 0xf8, 0xf0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x04, 0x04, 
    // 0x04, 0x05, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x06, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 
    // 0xe0, 0x20, 0x20, 0x20, 0x20, 0x60, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // 0x08, 0x18, 0x3c, 0x3e, 0x7f, 0xff, 0xff, 0xff, 0xef, 0xcf, 0x8f, 0x87, 0x07, 0x07, 0x07, 0x07, 
    // 0x07, 0xe7, 0xe7, 0xe7, 0xc7, 0x07, 0x07, 0x0f, 0x3f, 0xfe, 0xfc, 0xf0, 0xc0, 0x00, 0x00, 0x00, 
    // 0x00, 0x00, 0x00, 0xc0, 0xf0, 0xfc, 0xfe, 0x3f, 0x0f, 0x07, 0x07, 0xc7, 0xe7, 0xe7, 0xe7, 0x07, 
    // 0x07, 0x07, 0x07, 0x07, 0x87, 0x8f, 0xcf, 0xef, 0xef, 0xff, 0xff, 0x7f, 0x3e, 0x3c, 0x18, 0x08, 
    // 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0x20, 0x20, 
    // 0x60, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    // 0xff, 0x20, 0x20, 0x70, 0xf8, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x07, 0x0f, 0x1f, 0x1e, 0x3e, 0x7c, 
    // 0xf8, 0xf1, 0xf1, 0xe1, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 
    // 0x00, 0x00, 0xfc, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe1, 0xf1, 0xf1, 0xf8, 
    // 0x7c, 0x3e, 0x1e, 0x1f, 0x0f, 0x07, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x20, 0x20, 
    // 0x20, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xcf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 
    // 0x7f, 0x40, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // 0x00, 0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7e, 0xfc, 0xff, 0xff, 0xff, 0xff, 0x3c, 0x3c, 
    // 0x3c, 0x3c, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x7e, 0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x01, 0x00, 0x00, 
    // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // 0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x40, 0x40, 
    // 0x40, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x3f, 0x3f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x07, 0x0f, 0x0f, 0x0e, 
    // 0x0e, 0x0f, 0x0f, 0x07, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    // };
    oled_write_raw_P(ffkb_logo, sizeof(ffkb_logo));

}


/*
static void render_status(void) {
    oled_write_P(PSTR("    Layer: "), false);
    switch (get_highest_layer(layer_state|default_layer_state)) {
        case _ALPHA_ALT:
            oled_write_P(PSTR("Alphalt   "), false);
            break;
        case _ALPHA:
            oled_write_P(PSTR("Alpha     "), false);
            break;
        case _NAVIGATION:
            oled_write_P(PSTR("Nav       "), false);
            break;
        case _SYMBOLS:
            oled_write_P(PSTR("Symbols   "), false);
            break;
        case _FUNCTION:
            oled_write_P(PSTR("Function  "), false);
            break;
        case _MEDIA:
            oled_write_P(PSTR("Media     "), false);
            break;
        case _MOUSE:
            oled_write_P(PSTR("Mouse     "), false);
            break;
        default:
            oled_write_P(PSTR("Unkn      "), false);
            break;
    }

    // // Write host Keyboard LED Status to OLEDs
    // led_t led_usb_state = host_keyboard_led_state();
    // oled_write_P(led_usb_state.num_lock    ? PSTR("NUMLCK ") : PSTR("       "), false);
    // oled_write_P(led_usb_state.caps_lock   ? PSTR("CAPLCK ") : PSTR("       "), false);
    // oled_write_P(led_usb_state.scroll_lock ? PSTR("SCRLCK ") : PSTR("       "), false);

    // ffkb logo, 128x48px
    static const char ffkb_logo_small [] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x40, 0x40, 
    0x40, 0x40, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 0x40, 0x40, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 
    0xc0, 0x40, 0x40, 0x40, 0x40, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0xf8, 0xfe, 0x8e, 0xdc, 0xf0, 0x70, 0x60, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 
    0x30, 0x70, 0xf0, 0xd8, 0x9c, 0x9e, 0xfc, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 
    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x40, 0x40, 0x00, 0x40, 0x40, 0xc0, 0xc0, 0xc0, 
    0x40, 0x40, 0x40, 0x40, 0x00, 0x00, 0x40, 0x40, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 
    0x40, 0x40, 0x40, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x10, 0x10, 
    0x18, 0x3c, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0x10, 0x10, 0x18, 0x3c, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x20, 0x30, 0x78, 0x7c, 
    0xff, 0xd7, 0x9b, 0x18, 0x78, 0x78, 0x18, 0x30, 0x70, 0xe0, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0x30, 
    0x18, 0x58, 0x78, 0x18, 0x99, 0x9b, 0xf7, 0xfc, 0x78, 0x30, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x38, 0x78, 0xfc, 0xfc, 0xfe, 0xff, 0xf8, 0xf0, 
    0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0x10, 0x10, 0x10, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0xe7, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x08, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 
    0x0f, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x01, 0x01, 0x01, 0x03, 0x07, 0x0e, 0x0c, 0x18, 0x3f, 0x7f, 0x68, 0x68, 0x3f, 0x3f, 0x0c, 
    0x0c, 0x06, 0x03, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 
    0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x08, 0x00, 0x01, 0x0b, 0x0f, 0x0f, 0x0f, 0x0f, 
    0x0f, 0x0f, 0x0e, 0x0c, 0x00, 0x00, 0x00, 0x08, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 
    0x08, 0x08, 0x0c, 0x0f, 0x0f, 0x0f, 0x07, 0x07, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    oled_write_raw_P(ffkb_logo_small, sizeof(ffkb_logo_small));
}
*/

/*
static void render_logo_text(void) {
    oled_write_P(PSTR("ffkb"), false);
}
*/

bool oled_task_user(void) {
    // If you don't want to display the logo, switch
    if (false) {
        //render_status();
    } else if (true) {
        render_logo();
    } else {
        //render_logo_text();
    }
    return true;
}

#endif


#if !defined(RGBLIGHT_ENABLE) && defined(PIMORONI_TRACKBALL_ENABLE)
layer_state_t layer_state_set_keymap(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _ALPHA_ALT:
        if (is_caps_lock_on) {
            pimoroni_trackball_set_rgbw(RGB_CYAN, 0x00);
        } else {
            pimoroni_trackball_set_rgbw(RGB_BLUE, 0x00);
        }
        break;
    case _NAVIGATION:
        pimoroni_trackball_set_rgbw(RGB_GREEN, 0x00);
        break;
    case _SYMBOLS:
        pimoroni_trackball_set_rgbw(RGB_PURPLE, 0x00);
        break;
    case _FUNCTION:
        pimoroni_trackball_set_rgbw(RGB_YELLOW, 0x00);
        break;
    case _MEDIA:
        pimoroni_trackball_set_rgbw(RGB_ORANGE, 0x00);
        break;
    case _MOUSE:
        pimoroni_trackball_set_rgbw(RGB_WHITE, 0x00);
        break;
    default: //  for any other layers, or the default layer
        if (is_caps_lock_on) {
            pimoroni_trackball_set_rgbw(RGB_CYAN, 0x00);
        } else {
            pimoroni_trackball_set_rgbw(RGB_BLUE, 0x00);
        }
        break;
    }
  return state;
}
#endif
