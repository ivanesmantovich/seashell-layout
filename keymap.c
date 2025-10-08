#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif
#include "os_detection.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_NO, LALT(KC_SPC), KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, HYPR(KC_NO), LALT_T(KC_Z), KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, LGUI(KC_SPC), LCTL(KC_NO), MO(1), LGUI_T(KC_SPC), LALT(KC_NO)),
    [1] = LAYOUT(KC_TRNS, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_CIRC, KC_LPRN, KC_RPRN, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, KC_UP, KC_TAB, KC_COLN, KC_TRNS, KC_TRNS, KC_BSLS, KC_PIPE, KC_SLSH, KC_EQL, KC_MINS, KC_BSPC, KC_LEFT, KC_DOWN, KC_RGHT, KC_ENT, KC_TRNS, KC_TRNS, KC_GRV, KC_DQUO, KC_QUOT, KC_UNDS, KC_PLUS, KC_LT, KC_GT, KC_AMPR, KC_ASTR, KC_TILD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};

// Emacs-style key overrides
// Enter, tab, backspace, delete
const key_override_t ctrl_m_enter = ko_make_basic(MOD_MASK_CTRL, KC_M, KC_ENT);
const key_override_t ctrl_i_tab = ko_make_basic(MOD_MASK_CTRL, KC_I, KC_TAB);
const key_override_t ctrl_h_backspace = ko_make_basic(MOD_MASK_CTRL, KC_H, KC_BSPC);
const key_override_t ctrl_d_del = ko_make_basic(MOD_MASK_CTRL, KC_D, KC_DEL);
// Movement
const key_override_t ctrl_n_down = ko_make_basic(MOD_MASK_CTRL, KC_N, KC_DOWN);
const key_override_t ctrl_p_up = ko_make_basic(MOD_MASK_CTRL, KC_P, KC_UP);
const key_override_t ctrl_f_right = ko_make_basic(MOD_MASK_CTRL, KC_F, KC_RIGHT);
const key_override_t ctrl_b_left = ko_make_basic(MOD_MASK_CTRL, KC_B, KC_LEFT);
// Cut, copy, paste
const key_override_t ctrl_w_cut = ko_make_basic(MOD_MASK_CTRL, KC_W, LGUI(KC_X));
const key_override_t ctrl_y_paste = ko_make_basic(MOD_MASK_CTRL, KC_Y, LGUI(KC_V));
const key_override_t alt_w_copy = ko_make_basic(MOD_MASK_ALT, KC_W, LGUI(KC_C));
// Scroll
const key_override_t ctrl_v_pgdn = ko_make_basic(MOD_MASK_CTRL, KC_V, KC_PGDN);
const key_override_t alt_v_pgup = ko_make_basic(MOD_MASK_ALT, KC_V, KC_PGUP);

const key_override_t *key_overrides[] = {
    &ctrl_m_enter,
    &ctrl_i_tab,
    &ctrl_h_backspace,
    &ctrl_d_del,
    &ctrl_n_down,
    &ctrl_p_up,
    &ctrl_f_right,
    &ctrl_b_left,
    &ctrl_w_cut,
    &ctrl_y_paste,
    &alt_w_copy,
    &ctrl_v_pgdn,
    &alt_v_pgup,
    NULL
};

// For Alt+F/B → Alt+Arrows
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint8_t mod_state = get_mods();

    // Ctrl+A/E for home/end (OS-aware)
    if (mod_state & MOD_MASK_CTRL) {
      if (record->event.pressed) {
	switch (keycode) {
	case KC_A:
	  unregister_mods(MOD_MASK_CTRL);
	  if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS) {
	    register_code16(LGUI(KC_LEFT));
	  } else {
	    register_code(KC_HOME);
	  }
	  set_mods(mod_state);
	  return false;
	case KC_E:
	  unregister_mods(MOD_MASK_CTRL);
	  if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS) {
	    register_code16(LGUI(KC_RIGHT));
	  } else {
	    register_code(KC_END);
	  }
	  set_mods(mod_state);
	  return false;
	}
      } else {
	switch (keycode) {
	case KC_A:
	  if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS) {
	    unregister_code16(LGUI(KC_LEFT));
	  } else {
	    unregister_code(KC_HOME);
	  }
	  return false;
	case KC_E:
	  if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS) {
	    unregister_code16(LGUI(KC_RIGHT));
	  } else {
	    unregister_code(KC_END);
	  }
	  return false;
	}
      }
    }
    
    // Alt+F/B to word movement (OS-aware)
    if (mod_state & MOD_MASK_ALT) {
      if (record->event.pressed) {
        switch (keycode) {
	case KC_F:
	  unregister_mods(MOD_MASK_ALT);
	  if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS) {
	    register_code16(LALT(KC_RIGHT));
	  } else {
	    register_code16(LCTL(KC_RIGHT));
	  }
	  set_mods(mod_state);
	  return false;
	case KC_B:
	  unregister_mods(MOD_MASK_ALT);
	  if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS) {
	    register_code16(LALT(KC_LEFT));
	  } else {
	    register_code16(LCTL(KC_LEFT));
	  }
	  set_mods(mod_state);
	  return false;
        }
      } else {
        switch (keycode) {
	case KC_F:
	  if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS) {
	    unregister_code16(LALT(KC_RIGHT));
	  } else {
	    unregister_code16(LCTL(KC_RIGHT));
	  }
	  return false;
	case KC_B:
	  if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS) {
	    unregister_code16(LALT(KC_LEFT));
	  } else {
	    unregister_code16(LCTL(KC_LEFT));
	  }
	  return false;
        }
      }
    }
    
    return true;
}
