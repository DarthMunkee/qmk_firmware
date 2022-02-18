/* Copyright 2021 eye oh designs
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
#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST,
  _FN
};

enum custom_keycodes {	
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
};

#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
#define ADJUST MO(_ADJUST)
#define FN MO(_FN)
#define WIN LGUI(KC_TAB)
#define CTRLTB LCTL_T(KC_TAB)
#define LSCL LSFT_T(KC_CAPS)
#define AHK LALT(KC_PSCR)
#define SEARCH LGUI(KC_SPC)
#define ESCFN LT(_FN, KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_ortho1(
        KC_MUTE, KC_MUTE,                                                                                    KC_MPRV, KC_MPLY, KC_MNXT,
        KC_HOME,   ESCFN,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_PGUP,   CTRLTB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_PGDN,   LSCL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT ,
        KC_END,    WIN,     SEARCH,  KC_LALT, KC_LGUI, LOWER,      KC_SPACE,      RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
         ),

    [_LOWER] = LAYOUT_ortho1(
        RESET,   RGB_TOG,                                                                                     RGB_HUD,  RGB_VAD, RGB_SAD,
        _______,   KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,   KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_DEL,
        _______,   KC_DEL,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,   _______, KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE,
        _______,   _______, _______, _______, _______, _______, _______,   _______, S(KC_NUHS), S(KC_NUBS), _______, KC_UP, _______,
        _______,   _______, _______, _______, _______, _______,       KC_ENT,       _______, _______,    KC_LEFT,    KC_DOWN, KC_RGHT
         ),
    [_RAISE] = LAYOUT_ortho1(
        KC_MUTE, KC_GRAVE,                                                                                      RGB_HUI, RGB_VAI, RGB_SAI,
        _______,   KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        _______,  _______, _______, _______, _______, _______, _______,   _______, KC_MINS,  KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
        _______,  _______, _______, _______, _______, _______, _______,   _______, KC_NUHS,  KC_NUBS, _______, _______, _______,
        _______,   _______, _______, _______, _______, _______,       KC_BSPC,      _______, _______, _______, _______, _______
         ),
		 
	[_FN] = LAYOUT_ortho1(
        KC_MUTE, KC_GRAVE,                                                                                      RGB_HUI, RGB_VAI, RESET,
        _______,  _______,  KC_F1,   KC_F4,   KC_F7,   KC_F10,  KC_F13,   KC_F16,  KC_F19,  KC_F22,  _______, _______, _______,
        _______,  _______,  KC_F2,   KC_F5,   KC_F8,   KC_F11,  KC_F14,   KC_F17,  KC_F20,  KC_F23,  _______, _______, _______,
        _______,  _______,  KC_F3,   KC_F6,   KC_F9,   KC_F12,  KC_F15,   KC_F18,  KC_F21,  KC_F24,  _______, _______, _______,
        _______,  _______,  _______, _______, _______, _______, _______,  _______, _______, _______, _______,  _______
         ), 
		 
	[_ADJUST] = LAYOUT_ortho1(
        KC_MUTE, KC_GRAVE,                                                                                      RGB_HUI, RGB_VAI, RESET,
        KC_F9,   _______, RESET,   _______, _______, _______, RGB_TOG,          _______, _______, _______, _______, _______, KC_DEL,
        KC_F10,  _______, _______, _______, _______, RGB_HUI, RGB_MOD, RGB_SAI, RGB_VAI,  _______, _______,  _______, _______,
        KC_F11,  _______, _______, _______, _______, RGB_HUD, RGB_RMOD, RGB_SAD, RGB_VAD, _______, _______, _______, _______,
        KC_F12,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
         )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
             }
             break;
       
    }
    return true;
}

