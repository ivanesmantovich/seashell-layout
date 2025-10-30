#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif
#include "os_detection.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_NO, LALT(KC_SPC), KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, RSFT_T(KC_QUOT), HYPR(KC_1), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, HYPR(KC_2), LCTL(KC_NO), MO(1), LGUI_T(KC_SPC), LALT_T(KC_SPC)),
    [1] = LAYOUT(KC_TRNS, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_CIRC, KC_LPRN, KC_RPRN, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, KC_UP, KC_TAB, KC_COLN, KC_TRNS, KC_TRNS, KC_BSLS, KC_PIPE, KC_SLSH, KC_EQL, KC_MINS, KC_BSPC, KC_LEFT, KC_DOWN, KC_RGHT, KC_ENT, KC_TRNS, KC_TRNS, KC_GRV, KC_DQUO, KC_QUOT, KC_UNDS, KC_PLUS, KC_LT, KC_GT, KC_AMPR, KC_ASTR, KC_TILD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};

// Emacs-style key overrides (Colemak-DH matrix positions)
// Enter, tab, backspace, delete
const key_override_t ctrl_m_enter = ko_make_basic(MOD_MASK_CTRL, KC_H, KC_ENT);  // M is at H
const key_override_t ctrl_i_tab = ko_make_basic(MOD_MASK_CTRL, KC_L, KC_TAB);    // I is at L
const key_override_t ctrl_h_backspace = ko_make_basic(MOD_MASK_CTRL, KC_M, KC_BSPC); // H is at M
const key_override_t ctrl_d_del = ko_make_basic(MOD_MASK_CTRL, KC_V, KC_DEL);    // D is at V
// Movement
const key_override_t ctrl_n_down = ko_make_basic(MOD_MASK_CTRL, KC_J, KC_DOWN);  // N is at J
const key_override_t ctrl_p_up = ko_make_basic(MOD_MASK_CTRL, KC_R, KC_UP);      // P is at R
const key_override_t ctrl_f_right = ko_make_basic(MOD_MASK_CTRL, KC_E, KC_RIGHT); // F is at E
const key_override_t ctrl_b_left = ko_make_basic(MOD_MASK_CTRL, KC_T, KC_LEFT);  // B is at T
// Cut, copy, paste
const key_override_t ctrl_w_cut = ko_make_basic(MOD_MASK_CTRL, KC_W, LGUI(KC_X));
const key_override_t ctrl_y_paste = ko_make_basic(MOD_MASK_CTRL, KC_O, LGUI(KC_B)); // Y is at O, V is at B
const key_override_t alt_w_copy = ko_make_basic(MOD_MASK_ALT, KC_W, LGUI(KC_C));
// Scroll
const key_override_t ctrl_v_pgdn = ko_make_basic(MOD_MASK_CTRL, KC_B, KC_PGDN);  // V is at B
const key_override_t alt_v_pgup = ko_make_basic(MOD_MASK_ALT, KC_B, KC_PGUP);    // V is at Bio.github.colemakmods.keyboardlayout.colemakdh.colemakdhmatrixio.github.colemakmods.keyboardlayout.colemakdh.colemakdhmatrixio.github.colemakmods.keyboardlayout.colemakdh.colemakdhmatrix

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

// Emacs-style OS-aware shortcuts (Colemak-DH matrix positions)
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint8_t mod_state = get_mods();

    // Ctrl+A/E for home/end
    if (mod_state & MOD_MASK_CTRL) {
      if (record->event.pressed) {
        switch (keycode) {
        case KC_A:  // A is at A
          unregister_mods(MOD_MASK_CTRL);
          if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS) {
            register_code16(LGUI(KC_LEFT));
          } else {
            register_code(KC_HOME);
          }
          set_mods(mod_state);
          return false;
        case KC_K:  // E is at K
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
        case KC_K:  // E is at K
          if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS) {
            unregister_code16(LGUI(KC_RIGHT));
          } else {
            unregister_code(KC_END);
          }
          return false;
        }
      }
    }
    
    // Alt+F/B for word movement
    if (mod_state & MOD_MASK_ALT) {
      if (record->event.pressed) {
        switch (keycode) {
        case KC_E:  // F is at E
          unregister_mods(MOD_MASK_ALT);
          if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS) {
            register_code16(LALT(KC_RIGHT));
          } else {
            register_code16(LCTL(KC_RIGHT));
          }
          set_mods(mod_state);
          return false;
        case KC_T:  // B is at T
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
        case KC_E:  // F is at E
          if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS) {
            unregister_code16(LALT(KC_RIGHT));
          } else {
            unregister_code16(LCTL(KC_RIGHT));
          }
          return false;
        case KC_T:  // B is at T
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
