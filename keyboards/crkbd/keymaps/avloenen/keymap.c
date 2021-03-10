#include QMK_KEYBOARD_H

#include "../../../../users/avloenen/oneshot.h"
#include "../../../../users/avloenen/swapper.h"

extern keymap_config_t keymap_config;

#ifdef OLED_DRIVER_ENABLE
static uint32_t oled_timer = 0;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layers { _QWERTY, _COLEMAK, _LOWER, _RAISE, _ADJUST, _NUM };

// Keycodes for special combinations, useful for navigation and layer change
#define HOME G(KC_LEFT)
#define END G(KC_RGHT)
#define FWD G(KC_RBRC)
#define BACK G(KC_LBRC)
#define TABL G(S(KC_LBRC))
#define TABR G(S(KC_RBRC))
#define SPACEL A(G(KC_LEFT))
#define SPACER A(G(KC_RGHT))

#define LA_SYM MO(_RAISE)
#define LA_NAV MO(_LOWER)
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

    SW_WIN,           // Switch to next window         (cmd-tab)
    SW_APP,           // Switch to next window of app  (cmd-grv)
    SW_LANG,          // Switch to next input language (ctl-spc)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
  //,-----------------------------------------------.                  ,-----------------------------------------------.
     KC_TWM2,   KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                      KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,KC_MINS,
  //|-------+-------+-------+-------+-------+-------|                  |-------+-------+-------+-------+-------+-------|
     KC_TWM1,  CTL_A,  ALT_S,  SFT_D,  SUP_F,   KC_G,                      KC_H,  SUP_J,  SFT_K,  ALT_L,CTL_SCL,KC_QUOT,
  //|-------+-------+-------+-------+-------+-------|                  |-------+-------+-------+-------+-------+-------|
      KC_GRV,   KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,                      KC_N,   KC_M,KC_COMM, KC_DOT,KC_SLSH,KC_BSLS,
  //|-------+-------+-------+-------+-------+-------+-------|  |-------+-------+-------+-------+-------+-------+-------|
                                      LTHMB1, LTHMB2, LTHMB3,    RTHMB1, RTHMB2, RTHMB3
                                  //`-----------------------'  `-----------------------'
  ),

  [_COLEMAK] = LAYOUT(
  //,-----------------------------------------------.                  ,-----------------------------------------------.
     KC_TWM2,   KC_Q,   KC_W,   KC_F,   KC_P,   KC_B,                      KC_J,   KC_L,   KC_U,   KC_Y,KC_SCLN,KC_MINS,
  //|-------+-------+-------+-------+-------+-------|                  |-------+-------+-------+-------+-------+-------|
     KC_TWM1,  CTL_A,  ALT_R,  SFT_S,  SUP_T,   KC_G,                      KC_M,  SUP_N,  SFT_E,  ALT_I,  CTL_O,KC_QUOT,
  //|-------+-------+-------+-------+-------+-------|                  |-------+-------+-------+-------+-------+-------|
      KC_GRV,   KC_Z,   KC_X,   KC_C,   KC_D,   KC_V,                      KC_K,   KC_H,KC_COMM, KC_DOT,KC_SLSH,KC_BSLS,
  //|-------+-------+-------+-------+-------+-------+-------|  |-------+-------+-------+-------+-------+-------+-------|
                                      LTHMB1, LTHMB2, LTHMB3,    RTHMB1, RTHMB2, RTHMB3
                                  //`-----------------------'  `-----------------------'
  ),

  [_LOWER] = LAYOUT(
  //,-----------------------------------------------.                  ,-----------------------------------------------.
     KC_TWM2, SW_APP, SW_WIN,   TABL,   TABR,KC_VOLU,                   KC_BRIU,   HOME,  KC_UP,   END,  KC_DEL, KC_DEL,
  //|-------+-------+-------+-------+-------+-------|                  |-------+-------+-------+-------+-------+-------|
     KC_TWM1,OS_CTRL, OS_ALT,OS_SHFT, OS_CMD,KC_VOLD,                   KC_BRID,KC_LEFT,KC_DOWN,KC_RGHT,KC_BSPC,KC_BSPC,
  //|-------+-------+-------+-------+-------+-------|                  |-------+-------+-------+-------+-------+-------|
      KC_GRV, SPACEL, SPACER,   BACK,    FWD,KC_MUTE,                     KC_NO,KC_PGDN,KC_PGUP,SW_LANG, KC_ENT, KC_ENT,
  //|-------+-------+-------+-------+-------+-------+-------|  |-------+-------+-------+-------+-------+-------+-------|
                                      LTHMB1, LTHMB2, LTHMB3,    RTHMB1, RTHMB2, RTHMB3
                                  //`-----------------------'  `-----------------------'
  ),

  [_RAISE] = LAYOUT(
  //,-----------------------------------------------.                  ,-----------------------------------------------.
     KC_TWM2,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                      KC_6,   KC_7,   KC_8,   KC_9,   KC_0,KC_BSPC,
  //|-------+-------+-------+-------+-------+-------|                  |-------+-------+-------+-------+-------+-------|
     KC_TWM1,KC_LBRC,KC_RBRC,KC_LCBR,KC_RCBR,KC_LPRN,                   KC_RPRN, OS_CMD,OS_SHFT, OS_ALT,OS_CTRL, KC_ENT,
  //|-------+-------+-------+-------+-------+-------|                  |-------+-------+-------+-------+-------+-------|
     KC_TILD,KC_EXLM,  KC_AT,KC_HASH, KC_DLR,KC_PERC,                   KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_PIPE,
  //|-------+-------+-------+-------+-------+-------+-------|  |-------+-------+-------+-------+-------+-------+-------|
                                      LTHMB1, LTHMB2, LTHMB3,    RTHMB1, RTHMB2, RTHMB3
                                  //`-----------------------'  `-----------------------'
  ),

  [_ADJUST] = LAYOUT(
  //,-----------------------------------------------.                  ,-----------------------------------------------.
     KC_TWM2,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                      KC_6,   KC_7,   KC_8,   KC_9,   KC_0,  RESET,
  //|-------+-------+-------+-------+-------+-------|                  |-------+-------+-------+-------+-------+-------|
     KC_TWM1,OS_CTRL, OS_ALT,OS_SHFT, OS_CMD, QWERTY,                   COLEMAK, OS_CMD,OS_SHFT, OS_ALT,OS_CTRL,KC_EXEC,
  //|-------+-------+-------+-------+-------+-------|                  |-------+-------+-------+-------+-------+-------|
       KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,                     KC_F7,  KC_F8,  KC_F9, KC_F10, KC_F11, KC_F12,
  //|-------+-------+-------+-------+-------+-------+-------|  |-------+-------+-------+-------+-------+-------+-------|
                                      LTHMB1, LTHMB2, LTHMB3,    RTHMB1, RTHMB2, RTHMB3
                                  //`-----------------------'  `-----------------------'
  ),

  [_NUM] = LAYOUT(
  //,-----------------------------------------------.                  ,-----------------------------------------------.
     KC_TWM2,KC_BRID,KC_BRIU,  KC_NO,  KC_NO,KC_LCBR,                   KC_RCBR,   KC_7,   KC_8,   KC_9,   KC_0,KC_BSPC,
  //|-------+-------+-------+-------+-------+-------|                  |-------+-------+-------+-------+-------+-------|
     KC_TWM1,OS_CTRL, OS_ALT,OS_SHFT, OS_CMD,KC_LPRN,                   KC_RPRN,   KC_4,   KC_5,   KC_6,KC_MINS,KC_PLUS,
  //|-------+-------+-------+-------+-------+-------|                  |-------+-------+-------+-------+-------+-------|
      KC_GRV,KC_MSTP,KC_MPLY,  KC_NO,  KC_NO,KC_LBRC,                   KC_RBRC,   KC_1,   KC_2,   KC_3, KC_DOT, KC_EQL,
  //|-------+-------+-------+-------+-------+-------+-------|  |-------+-------+-------+-------+-------+-------+-------|
                                      LTHMB1, LTHMB2, LTHMB3,    RTHMB1, RTHMB2, RTHMB3
                                  //`-----------------------'  `-----------------------'
  )
};


#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

void render_space(void) { oled_write_P(PSTR("     "), false); }

void render_mod_status_gui_alt(uint8_t modifiers) {
    static const char PROGMEM gui_off_1[] = {0x85, 0x86, 0};
    static const char PROGMEM gui_off_2[] = {0xa5, 0xa6, 0};
    static const char PROGMEM gui_on_1[]  = {0x8d, 0x8e, 0};
    static const char PROGMEM gui_on_2[]  = {0xad, 0xae, 0};

    static const char PROGMEM alt_off_1[] = {0x87, 0x88, 0};
    static const char PROGMEM alt_off_2[] = {0xa7, 0xa8, 0};
    static const char PROGMEM alt_on_1[]  = {0x8f, 0x90, 0};
    static const char PROGMEM alt_on_2[]  = {0xaf, 0xb0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[]  = {0xc7, 0};
    static const char PROGMEM on_off_2[]  = {0xc8, 0};
    static const char PROGMEM off_on_1[]  = {0xc9, 0};
    static const char PROGMEM off_on_2[]  = {0xca, 0};
    static const char PROGMEM on_on_1[]   = {0xcb, 0};
    static const char PROGMEM on_on_2[]   = {0xcc, 0};

    if (modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_1, false);
    } else {
        oled_write_P(gui_off_1, false);
    }

    if ((modifiers & MOD_MASK_GUI) && (modifiers & MOD_MASK_ALT)) {
        oled_write_P(on_on_1, false);
    } else if (modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_1, false);
    } else if (modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if (modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_1, false);
    } else {
        oled_write_P(alt_off_1, false);
    }

    if (modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_2, false);
    } else {
        oled_write_P(gui_off_2, false);
    }

    if (modifiers & MOD_MASK_GUI & MOD_MASK_ALT) {
        oled_write_P(on_on_2, false);
    } else if (modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_2, false);
    } else if (modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if (modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_2, false);
    } else {
        oled_write_P(alt_off_2, false);
    }
}

void render_mod_status_ctrl_shift(uint8_t modifiers) {
    static const char PROGMEM ctrl_off_1[] = {0x89, 0x8a, 0};
    static const char PROGMEM ctrl_off_2[] = {0xa9, 0xaa, 0};
    static const char PROGMEM ctrl_on_1[]  = {0x91, 0x92, 0};
    static const char PROGMEM ctrl_on_2[]  = {0xb1, 0xb2, 0};

    static const char PROGMEM shift_off_1[] = {0x8b, 0x8c, 0};
    static const char PROGMEM shift_off_2[] = {0xab, 0xac, 0};
    static const char PROGMEM shift_on_1[]  = {0xcd, 0xce, 0};
    static const char PROGMEM shift_on_2[]  = {0xcf, 0xd0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[]  = {0xc7, 0};
    static const char PROGMEM on_off_2[]  = {0xc8, 0};
    static const char PROGMEM off_on_1[]  = {0xc9, 0};
    static const char PROGMEM off_on_2[]  = {0xca, 0};
    static const char PROGMEM on_on_1[]   = {0xcb, 0};
    static const char PROGMEM on_on_2[]   = {0xcc, 0};

    if (modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_1, false);
    } else {
        oled_write_P(ctrl_off_1, false);
    }

    if ((modifiers & MOD_MASK_CTRL) && (modifiers & MOD_MASK_SHIFT)) {
        oled_write_P(on_on_1, false);
    } else if (modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_1, false);
    } else if (modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if (modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_1, false);
    } else {
        oled_write_P(shift_off_1, false);
    }

    if (modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_2, false);
    } else {
        oled_write_P(ctrl_off_2, false);
    }

    if (modifiers & MOD_MASK_CTRL & MOD_MASK_SHIFT) {
        oled_write_P(on_on_2, false);
    } else if (modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_2, false);
    } else if (modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if (modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_2, false);
    } else {
        oled_write_P(shift_off_2, false);
    }
}

void render_logo(void) {
    static const char PROGMEM corne_logo[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0};
    oled_write_P(corne_logo, false);
    oled_write_P(PSTR("corne"), false);
}

void render_layer_state(void) {
    static const char PROGMEM default_layer[] = {0x20, 0x94, 0x95, 0x96, 0x20, 0x20, 0xb4, 0xb5, 0xb6, 0x20, 0x20, 0xd4, 0xd5, 0xd6, 0x20, 0};
    static const char PROGMEM raise_layer[]   = {0x20, 0x97, 0x98, 0x99, 0x20, 0x20, 0xb7, 0xb8, 0xb9, 0x20, 0x20, 0xd7, 0xd8, 0xd9, 0x20, 0};
    static const char PROGMEM lower_layer[]   = {0x20, 0x9a, 0x9b, 0x9c, 0x20, 0x20, 0xba, 0xbb, 0xbc, 0x20, 0x20, 0xda, 0xdb, 0xdc, 0x20, 0};
    static const char PROGMEM adjust_layer[]  = {0x20, 0x9d, 0x9e, 0x9f, 0x20, 0x20, 0xbd, 0xbe, 0xbf, 0x20, 0x20, 0xdd, 0xde, 0xdf, 0x20, 0};
    if (layer_state_is(_ADJUST) | layer_state_is(_NUM)) {
        oled_write_P(adjust_layer, false);
    } else if (layer_state_is(_LOWER)) {
        oled_write_P(lower_layer, false);
    } else if (layer_state_is(_RAISE)) {
        oled_write_P(raise_layer, false);
    } else {
        oled_write_P(default_layer, false);
    }
}

void render_status_main(void) {
    render_logo();
    render_space();
    render_space();
    render_layer_state();
    render_space();
    render_space();
    render_mod_status_gui_alt(get_mods() | get_oneshot_mods());
    render_mod_status_ctrl_shift(get_mods() | get_oneshot_mods());
}

void render_status_secondary(void) {
    render_logo();
    render_space();
    render_space();
    render_layer_state();
    render_space();
    render_space();
    render_mod_status_gui_alt(get_mods() | get_oneshot_mods());
    render_mod_status_ctrl_shift(get_mods() | get_oneshot_mods());
}

void oled_task_user(void) {
    if (timer_elapsed32(oled_timer) > 30000) {
        oled_off();
        return;
    }
#    ifndef SPLIT_KEYBOARD
    else {
        oled_on();
    }
#    endif

    if (is_master) {
        render_status_main();
    } else {
        render_status_secondary();
    }
}

#endif

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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_swapper(&sw_win_active, KC_LGUI, KC_TAB, SW_WIN, keycode, record, SW_APP);
    update_swapper(&sw_app_active, KC_LGUI, KC_GRV, SW_APP, keycode, record, SW_WIN);
    update_swapper(&sw_lang_active, KC_LCTL, KC_SPC, SW_LANG, keycode, record, SW_LANG);        

    update_oneshot(&os_shft_state, KC_LSFT, OS_SHFT, keycode, record);
    update_oneshot(&os_ctrl_state, KC_LCTL, OS_CTRL, keycode, record);
    update_oneshot(&os_alt_state, KC_LALT, OS_ALT, keycode, record);
    update_oneshot(&os_cmd_state, KC_LCMD, OS_CMD, keycode, record);

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
