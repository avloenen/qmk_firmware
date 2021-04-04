// Copyright (C) 2019, 2020  Keyboard.io, Inc
//
// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include QMK_KEYBOARD_H

#include "../../../../../users/avloenen/oneshot.h"
#include "../../../../../users/avloenen/swapper.h"

enum layers { _QWERTY, _COLEMAK, _LOWER, _RAISE, _ADJUST, _NUM };

// Keycodes for special combinations, useful for navigation and layer change
//#define HOME G(KC_LEFT)
#define HOME KC_HOME
//#define END G(KC_RGHT)
#define END KC_END
#define FWD G(KC_RBRC)
#define BACK G(KC_LBRC)
#define TABL G(S(KC_LBRC))
#define TABR G(S(KC_RBRC))
#define SPACEL A(G(KC_LEFT))
#define SPACER A(G(KC_RGHT))

//#define LA_SYM MO(_RAISE)
#define LA_SYM LT(_RAISE, KC_SPC)
//#define LA_NAV MO(_LOWER)
#define LA_NAV LT(_LOWER, KC_BSPC)
#define LA_NUM MO(_NUM)
#define OSM_SFT OSM(MOD_LSFT)
#define CMD_BS LGUI_T(KC_BSPC)
#define ENT_ALT LALT_T(KC_ENT)
#define NUM_SPC LT(_NUM, KC_SPC)

// Thumb keys
#define LTHMB1 OSM_SFT  // Shift is useful on thumb
#define LTHMB2 LA_NAV   // Navigation layer or access to stacking one shot mods
#define LTHMB3 CMD_BS   // Backspace is good here, command is very useful for one handed paste etc.
#define RTHMB1 ENT_ALT  // Enter is good here, alt is useful to have
#define RTHMB2 LA_SYM   // Symbols layer
#define RTHMB3 NUM_SPC  // Space is good here, number layer

// Leftmost column
#define HYP_TAB HYPR_T(KC_TAB)
#define MEH_ESC MEH_T(KC_ESC)
#define CTL_GRV CTL_T(KC_GRV)

// Window Manager keys
#define KC_TWM1 MEH_ESC
#define KC_TWM2 HYP_TAB

// Left-hand home row mods QWERTY
#define CTL_A LCTL_T(KC_A)
#define ALT_S LALT_T(KC_S)
#define SFT_D LSFT_T(KC_D)
#define SUP_F LGUI_T(KC_F)

// Right-hand home row mods QWERTY
#define SUP_J RGUI_T(KC_J)
#define SFT_K RSFT_T(KC_K)
#define ALT_L LALT_T(KC_L)
#define CTL_SCL RCTL_T(KC_SCLN)

// Left-hand home row mods COLEMAK
//#define CTL_A LCTL_T(KC_A)
#define ALT_R LALT_T(KC_R)
#define SFT_S LSFT_T(KC_S)
#define SUP_T LGUI_T(KC_T)

// Right-hand home row mods COLEMAK
#define SUP_N RGUI_T(KC_N)
#define SFT_E RSFT_T(KC_E)
#define ALT_I LALT_T(KC_I)
#define CTL_O RCTL_T(KC_O)

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    COLEMAK,
    ADJUST,
    SPECIAL,

    // Custom stacking oneshot mod implementation without timers.
    OS_SHFT,
    OS_CTRL,
    OS_ALT,
    OS_CMD,
    OS_RCMD,

    SW_WIN,           // Switch to next window         (cmd-tab)
    SW_APP,           // Switch to next window of app  (cmd-grv)
    SW_LANG,          // Switch to next input language (ctl-spc)
};

/*
 * Als layer shift met linkerduim gaat zijn de wijzigingen rechts en vice versa.
 * Modifiers op home row.
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
  //,---------------------------------------.                          ,---------------------------------------.
        KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                              KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,
  //|-------+-------+-------+-------+-------|                          |-------+-------+-------+-------+-------|
       CTL_A,  ALT_S,  SFT_D,  SUP_F,   KC_G,                              KC_H,  SUP_J,  SFT_K,  ALT_L,CTL_SCL,
  //|-------+-------+-------+-------+-------+-------.          ,-------|-------+-------+-------+-------+-------|
        KC_Z,   KC_X,   KC_C,   KC_V,   KC_B, KC_GRV,           KC_BSLS,   KC_N,   KC_M,KC_COMM, KC_DOT,KC_SLSH,
  //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
     KC_TWM2,KC_LCTL,KC_LALT, LTHMB1, LTHMB2, LTHMB3,            RTHMB1, RTHMB2, RTHMB3,KC_MINS,KC_QUOT,KC_TWM1
  //`-----------------------------------------------'          `-----------------------------------------------'
  ),

  [_COLEMAK] = LAYOUT(
  //,---------------------------------------.                          ,---------------------------------------.
        KC_Q,   KC_W,   KC_F,   KC_P,   KC_B,                              KC_J,   KC_L,   KC_U,   KC_Y,KC_SCLN,
  //|-------+-------+-------+-------+-------|                          |-------+-------+-------+-------+-------|
       CTL_A,  ALT_R,  SFT_S,  SUP_T,   KC_G,                              KC_M,  SUP_N,  SFT_E,  ALT_I,  CTL_O,
  //|-------+-------+-------+-------+-------+-------.          ,-------|-------+-------+-------+-------+-------|
        KC_Z,   KC_X,   KC_C,   KC_D,   KC_V, KC_GRV,           KC_BSLS,   KC_K,   KC_H,KC_COMM, KC_DOT,KC_SLSH,
  //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
     KC_TWM2,KC_LCTL,KC_LALT, LTHMB1, LTHMB2, LTHMB3,            RTHMB1, RTHMB2, RTHMB3,KC_MINS,KC_QUOT,KC_TWM1
  //`-----------------------------------------------'          `-----------------------------------------------'
  ),

  [_LOWER] = LAYOUT(
  //,---------------------------------------.                          ,---------------------------------------.
      SW_APP, SW_WIN,   TABL,   TABR,KC_VOLU,                           KC_BRIU,   HOME,  KC_UP,   END,  KC_DEL,
  //|-------+-------+-------+-------+-------|                          |-------+-------+-------+-------+-------|
     OS_CTRL, OS_ALT,OS_SHFT, OS_CMD,KC_VOLD,                           KC_BRID,KC_LEFT,KC_DOWN,KC_RGHT,KC_BSPC,
  //|-------+-------+-------+-------+-------+-------.          ,-------|-------+-------+-------+-------+-------|
      SPACEL, SPACER,   BACK,    FWD,KC_MUTE, KC_ENT,             KC_NO,  KC_NO,KC_PGDN,KC_PGUP,SW_LANG, KC_ENT,
  //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
     KC_TWM2,KC_LCTL,KC_LALT, LTHMB1, LTHMB2, LTHMB3,            RTHMB1, RTHMB2, RTHMB3,  KC_NO,  KC_NO,KC_TWM1
  //`-----------------------------------------------'          `-----------------------------------------------'
  ),

  [_RAISE] = LAYOUT(
  //,---------------------------------------.                          ,---------------------------------------.
        KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                              KC_6,   KC_7,   KC_8,   KC_9,   KC_0,
  //|-------+-------+-------+-------+-------|                          |-------+-------+-------+-------+-------|
     KC_LBRC,KC_RBRC,KC_LCBR,KC_RCBR,KC_LPRN,                           KC_RPRN,OS_RCMD,OS_SHFT, OS_ALT,OS_CTRL,
  //|-------+-------+-------+-------+-------+-------.          ,-------|-------+-------+-------+-------+-------|
     KC_EXLM,  KC_AT,KC_HASH, KC_DLR,KC_PERC,KC_TILD,           KC_PIPE,KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,
  //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
     KC_TWM2,KC_LCTL,KC_LALT, LTHMB1, LTHMB2, LTHMB3,            RTHMB1, RTHMB2, RTHMB3,  KC_NO,  KC_NO,KC_TWM1
  //`-----------------------------------------------'          `-----------------------------------------------'
  ),

  [_ADJUST] = LAYOUT(
  //,---------------------------------------.                          ,---------------------------------------.
        KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                              KC_6,   KC_7,   KC_8,   KC_9,   KC_0,
  //|-------+-------+-------+-------+-------|                          |-------+-------+-------+-------+-------|
     OS_CTRL, OS_ALT,OS_SHFT, OS_CMD, QWERTY,                           COLEMAK,OS_RCMD,OS_SHFT, OS_ALT,OS_CTRL,
  //|-------+-------+-------+-------+-------+-------.          ,-------|-------+-------+-------+-------+-------|
       KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,             KC_F7,  KC_F8,  KC_F9, KC_F10, KC_F11, KC_F12,
  //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
     KC_TWM2,KC_LCTL,KC_LALT, LTHMB1, LTHMB2, LTHMB3,            RTHMB1, RTHMB2, RTHMB3,  RESET,  KC_NO,KC_TWM1
  //`-----------------------------------------------'          `-----------------------------------------------'
  ),

  [_NUM] = LAYOUT(
  //,---------------------------------------.                          ,---------------------------------------.
     KC_BRID,KC_BRIU,  KC_NO,  KC_NO,KC_LCBR,                           KC_RCBR,   KC_7,   KC_8,   KC_9,KC_BSPC,
  //|-------+-------+-------+-------+-------|                          |-------+-------+-------+-------+-------|
     OS_CTRL, OS_ALT,OS_SHFT, OS_CMD,KC_LPRN,                           KC_RPRN,   KC_4,   KC_5,   KC_6,KC_MINS,
  //|-------+-------+-------+-------+-------+-------.          ,-------|-------+-------+-------+-------+-------|
     KC_MSTP,KC_MPLY,  KC_NO,  KC_NO,KC_LBRC,KC_UNDS,            KC_EQL,KC_RBRC,   KC_1,   KC_2,   KC_3,KC_PLUS,
  //|-------+-------+-------+-------+-------+-------|          |-------+-------+-------+-------+-------+-------|
     KC_TWM2,KC_LCTL,KC_LALT, LTHMB1, LTHMB2, LTHMB3,            RTHMB1, RTHMB2, RTHMB3,   KC_0, KC_DOT,KC_COMM
  //`-----------------------------------------------'          `-----------------------------------------------'
  )
};

/*
 * Multiple tri-layers possible with multiple state = ...
 */
layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
    return state;
}

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
        case LA_SYM:
        // case SYM_SPC:
        case LA_NAV:
            return true;
        default:
            return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
        case LA_SYM:
        // case SYM_SPC:
        case LA_NAV:
        case KC_LSFT:
        case OS_SHFT:
        case OS_CTRL:
        case OS_ALT:
        case OS_CMD:
	case OS_RCMD:
            return true;
        default:
            return false;
    }
}

bool sw_win_active     = false;
bool sw_app_active     = false;
bool sw_lang_active    = false;

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state  = os_up_unqueued;
oneshot_state os_cmd_state  = os_up_unqueued;
oneshot_state os_rcmd_state = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_swapper(&sw_win_active, KC_LGUI, KC_TAB, SW_WIN, keycode, record, SW_APP);
    update_swapper(&sw_app_active, KC_LGUI, KC_GRV, SW_APP, keycode, record, SW_WIN);
    update_swapper(&sw_lang_active, KC_LCTL, KC_SPC, SW_LANG, keycode, record, SW_LANG);        

    update_oneshot(&os_shft_state, KC_LSFT, OS_SHFT, keycode, record);
    update_oneshot(&os_ctrl_state, KC_LCTL, OS_CTRL, keycode, record);
    update_oneshot(&os_alt_state, KC_LALT, OS_ALT, keycode, record);
    update_oneshot(&os_cmd_state, KC_LCMD, OS_CMD, keycode, record);
    update_oneshot(&os_rcmd_state, KC_RCMD, OS_RCMD, keycode, record);

    if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
        oled_timer = timer_read32();
#endif
        // set_timelog();
    }
    static uint16_t my_special_timer;

    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            break;
        case COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
            }
            break;
        case SPECIAL:
            if (record->event.pressed) {
                my_special_timer = timer_read();
                register_code(KC_RALT);
            } else {
                unregister_code(KC_RALT);
                if (timer_elapsed(my_special_timer) < TAPPING_TERM) {
                    SEND_STRING(SS_TAP(X_ENT));  // Change the character(s) to be sent on tap here
                }
            }
            return false;
        break;
    }
    return true;
}

// Thumb keys for Backspace, Space and Enter
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CMD_BS:
            return true;
        case NUM_SPC:
            return true;
        case LALT_T(KC_ENT):
            return true;
        default:
            return false;
    }
}

// Home-row mods + Hyper/Tab and Meh/Esc
bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MEH_ESC:
            return true;
        case HYP_TAB:
            return true;
        case CTL_A:
            return true;
        case ALT_S:
            return true;
        case SFT_D:
            return true;
        case SUP_F:
            return true;
        case SUP_J:
            return true;
        case SFT_K:
            return true;
        case ALT_L:
            return true;
        case CTL_SCL:
            return true;
        case ALT_R:
            return true;
        case SFT_S:
            return true;
        case SUP_T:
            return true;
        case SUP_N:
            return true;
        case SFT_E:
            return true;
        case ALT_I:
            return true;
        case CTL_O:
            return true;
        default:
            return false;
    }
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CTL_A:
            return TAPPING_TERM + 30;
        case CTL_SCL:
            return TAPPING_TERM + 30;
        case CTL_O:
            return TAPPING_TERM + 30;
        default:
            return TAPPING_TERM;
    }
}
