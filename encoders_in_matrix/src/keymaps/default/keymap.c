// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

EIM_ENCODER_NAMES(ENC_IN_MATRIX)

EIM_ENCODERS_BEGIN
  EIM_ENC(ENC_IN_MATRIX, EIM_PADA(1, 1), EIM_PADB(2, 1))
EIM_ENCODERS_END


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_3x3(
        KC_A,    KC_B,    KC_C,
        KC_D,    KC_NO,   KC_F,
        KC_G,    KC_NO,   KC_I
    )
};

void encoders_in_matrix_update_user(enc_names_t encoder, bool clockwise) {
  switch(encoder) {
    case ENC_IN_MATRIX:
      if(clockwise)
        tap_code(KC_UP);
      else
        tap_code(KC_DOWN);
      break;
      default:
      break;
  }
}

void keyboard_post_init_user(void) {
  debug_enable=true;
  debug_matrix=true;
}