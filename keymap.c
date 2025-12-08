#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_NO, KC_LGUI, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, RSFT_T(KC_QUOT), LSA(KC_1), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, LSA(KC_2), LCTL(KC_NO), MO(1), HYPR(KC_NO), LALT_T(KC_SPC)),
    [1] = LAYOUT(KC_TRNS, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_DEL, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_CIRC, KC_LPRN, KC_RPRN, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, KC_UP, KC_TAB, KC_COLN, KC_TRNS, KC_TRNS, KC_BSLS, KC_PIPE, KC_SLSH, KC_EQL, KC_MINS, KC_BSPC, KC_LEFT, KC_DOWN, KC_RGHT, KC_ENT, KC_TRNS, KC_TRNS, KC_GRV, KC_DQUO, KC_QUOT, KC_UNDS, KC_PLUS, KC_LT, KC_GT, KC_AMPR, KC_ASTR, KC_TILD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};

// Emacs-style key overrides (Colemak-DH matrix positions, GNOME as target DE)
// Enter, tab, backspace, delete
const key_override_t ctrl_m_enter = ko_make_basic(MOD_MASK_CTRL, KC_H, KC_ENT);  // M is at H
const key_override_t ctrl_i_tab = ko_make_basic(MOD_MASK_CTRL, KC_L, KC_TAB);    // I is at L
const key_override_t ctrl_h_backspace = ko_make_basic(MOD_MASK_CTRL, KC_M, KC_BSPC); // H is at M
const key_override_t ctrl_d_del = ko_make_basic(MOD_MASK_CTRL, KC_V, KC_DEL);    // D is at V
// Delete word forward and backward
const key_override_t alt_h_del_word_backward = ko_make_basic(MOD_MASK_ALT, KC_M, LCTL(KC_BSPC));
const key_override_t alt_d_del_word_forward = ko_make_basic(MOD_MASK_ALT, KC_V, LCTL(KC_DEL));
// Movement
const key_override_t ctrl_n_down = ko_make_basic(MOD_MASK_CTRL, KC_J, KC_DOWN);  // N is at J
const key_override_t ctrl_p_up = ko_make_basic(MOD_MASK_CTRL, KC_R, KC_UP);      // P is at R
const key_override_t ctrl_f_right = ko_make_basic(MOD_MASK_CTRL, KC_E, KC_RIGHT); // F is at E
const key_override_t ctrl_b_left = ko_make_basic(MOD_MASK_CTRL, KC_T, KC_LEFT);  // B is at T
const key_override_t alt_n_down = ko_make_basic(MOD_MASK_ALT, KC_J, LCTL(KC_DOWN));  // N is at J
const key_override_t alt_p_up = ko_make_basic(MOD_MASK_ALT, KC_R, LCTL(KC_UP));      // P is at R
const key_override_t alt_f_right = ko_make_basic(MOD_MASK_ALT, KC_E, LCTL(KC_RIGHT)); // F is at E
const key_override_t alt_b_left = ko_make_basic(MOD_MASK_ALT, KC_T, LCTL(KC_LEFT));  // B is at T
// Cut, copy, paste
const key_override_t ctrl_w_cut = ko_make_basic(MOD_MASK_CTRL, KC_W, LSFT(KC_DEL));
const key_override_t ctrl_y_paste = ko_make_basic(MOD_MASK_CTRL, KC_O, LSFT(KC_INS));
const key_override_t alt_w_copy = ko_make_basic(MOD_MASK_ALT, KC_W, LCTL(KC_INS));
// Workspace switch
const key_override_t alt_u_workspace = ko_make_basic(MOD_MASK_ALT, KC_I, LCTL(KC_F10)); // U is at I
// Undo
const key_override_t ctrl_slash_undo = ko_make_basic(MOD_MASK_CTRL, KC_SLSH, LCTL(KC_Z));
// Redo
const key_override_t ctrl_shift_slash_redo = ko_make_basic(MOD_MASK_SA, KC_SLSH, LCS(KC_Z));
// Expand
const key_override_t alt_slash_expand = ko_make_basic(MOD_MASK_ALT, KC_SLSH, LCTL(KC_F12));

const key_override_t *key_overrides[] = {
    &ctrl_m_enter,
    &ctrl_i_tab,
    &ctrl_h_backspace,
    &ctrl_d_del,
    &alt_h_del_word_backward,
    &alt_d_del_word_forward,
    &ctrl_n_down,
    &ctrl_p_up,
    &ctrl_f_right,
    &ctrl_b_left,
    &alt_n_down,
    &alt_p_up,
    &alt_f_right,
    &alt_b_left,
    &ctrl_w_cut,
    &ctrl_y_paste,
    &alt_w_copy,
    &alt_u_workspace,
    &ctrl_slash_undo,
    &ctrl_shift_slash_redo,
    &alt_slash_expand
};

// NOTE: use ydotool and dotool to hack the hard parts!
