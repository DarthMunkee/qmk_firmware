#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum layer_names {
  _QWERTY,
  _SYM,
  _RAISE,
  _ADJUST,
  _FN
};

enum custom_keycodes {	
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  BALL_HUI,//cycles hue
  BALL_WHT,//cycles white
  BALL_DEC,//decreased color
  BALL_SCR,//scrolls
  BALL_NCL,//left click
  BALL_RCL,//right click
  BALL_MCL,//middle click
  BALL_BCL,//mouse button 4 
  BALL_FCL,//mouse button 5
  BALL_HUE, //hold + scroll ball up and down to cycle hue
  BALL_SAT,//hold + scroll ball up and down to cycle saturation
  BALL_VAL,//hold + scroll ball up and down to cycle value
  BALL_DRG,
};

#define SYM  MO(_SYM)
#define RAISE  MO(_RAISE)
#define ADJUST MO(_ADJUST)
#define FN MO(_FN)
#define MOUSE MO(_MOUS)
#define WIN LGUI(KC_TAB)
#define CTRLTB LCTL_T(KC_TAB)
#define LSCL LSFT_T(KC_CAPS)
#define AHK LALT(KC_PSCR)
#define SEARCH LGUI(KC_SPC)
#define ESCFN LT(_FN, KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_all(
   ESCFN,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
   CTRLTB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   BALL_MCL, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, 
   LSCL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   BALL_RCL, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
   WIN,     SEARCH,  KC_LALT, KC_LGUI, SYM,     KC_ENT, KC_NO,    KC_SPC,  RAISE,   BALL_DRG, BALL_BCL, BALL_FCL, KC_RALT
),

[_SYM] = LAYOUT_all(
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,          KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
  _______,  KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, _______,  AHK,    _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
  _______, _______, _______, _______, _______, _______, _______, _______, S(KC_NUHS), S(KC_NUBS),_______, KC_UP, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   KC_LEFT , KC_DOWN, KC_RGHT
),

[_RAISE] = LAYOUT_all(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,             KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  _______,  KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  _______, KC_F18,  KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
  _______, KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  _______, KC_F24,  KC_NUHS, KC_NUBS, _______, _______,   _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_MPLY, KC_MNXT
),

[_ADJUST] =  LAYOUT_all(
  _______, RESET,   _______, _______, BALL_VAL, RGB_TOG,          _______, _______, _______, _______, _______, KC_DEL,
  _______, _______, _______, _______, BALL_SAT, RGB_HUI, RGB_MOD, RGB_SAI, RGB_VAI,  _______, _______,  _______, _______,
  _______, _______, _______, BALL_WHT, BALL_HUE, RGB_HUD, RGB_RMOD, RGB_SAD, RGB_VAD, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

[_FN] = LAYOUT_all(
  _______, KC_F1,   KC_F4,   KC_F7,   KC_F10,  KC_F13,           KC_F16,   KC_F19,  KC_F22, _______, _______, _______,
  _______, KC_F2,   KC_F5,   KC_F8,   KC_F11,  KC_F14,  _______, KC_F17,   KC_F20,  KC_F23, _______, _______, _______,
  _______, KC_F3,   KC_F6,   KC_F9,   KC_F12,  KC_F15,  _______, KC_F18,   KC_F21,  KC_F24, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),



};



layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _SYM, _RAISE, _ADJUST);
}
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
             }
             break;
/*		 case BALL_HUE:
        if (record->event.pressed) {
        hue_mode_enabled = 1;
        } else {
        hue_mode_enabled = 0;
        }
        break;
	case BALL_SAT:
		if (record->event.pressed) {
        saturation_mode_enabled = 1;
        } else {
        saturation_mode_enabled = 0;
        }
        break;
	case BALL_VAL:
		if (record->event.pressed) {
        value_mode_enabled = 1;
        } else {
        value_mode_enabled = 0;
        }
        break;
	case BALL_RCL:
	if (record->event.pressed) {
        right_click_mode_enabled = 1;
        } else {
        right_click_mode_enabled = 0;
        }
        break;
	case BALL_DRG:
	if (record->event.pressed) {
        drag_mode_enabled = 1;
        } else {
        drag_mode_enabled = 0;
        }
        break;*/
		
	case BALL_MCL:
		record->event.pressed?register_code(KC_BTN3):unregister_code(KC_BTN3);
		break;
	case BALL_RCL:
		record->event.pressed?register_code(KC_BTN2):unregister_code(KC_BTN2);
		break;
	case BALL_BCL:
		record->event.pressed?register_code(KC_BTN4):unregister_code(KC_BTN4);
		break;
	case BALL_FCL:
		record->event.pressed?register_code(KC_BTN5):unregister_code(KC_BTN5);
		break;
		

    } 
	
	return true;
}	


   


