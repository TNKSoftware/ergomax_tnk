#include QMK_KEYBOARD_H
#include "ergomax_tnk.h"
#include "keymap_japanese.h"

// 英字配列のように振る舞うキーマップ。刻印済みキーキャップの表記に合わせたい人向け

#ifndef QK_KEY_OVERRIDE_TOGGLE
#define QK_KEY_OVERRIDE_TOGGLE KEY_OVERRIDE_TOGGLE
#endif
#define QK_OVTG QK_KEY_OVERRIDE_TOGGLE

const key_override_t ov_key_2 = ko_make_basic(MOD_MASK_SHIFT, KC_2, JP_AT);
const key_override_t ov_key_6 = ko_make_basic(MOD_MASK_SHIFT, KC_6, JP_CIRC);
const key_override_t ov_key_7 = ko_make_basic(MOD_MASK_SHIFT, KC_7, JP_AMPR);
const key_override_t ov_key_8 = ko_make_basic(MOD_MASK_SHIFT, KC_8, JP_ASTR);
const key_override_t ov_key_9 = ko_make_basic(MOD_MASK_SHIFT, KC_9, JP_LPRN);
const key_override_t ov_key_0 = ko_make_basic(MOD_MASK_SHIFT, KC_0, JP_RPRN);
const key_override_t ov_key_scln = ko_make_basic(MOD_MASK_SHIFT, JP_SCLN, JP_COLN);
const key_override_t ov_key_ovtg = ko_make_basic(0, KC_FN0, QK_OVTG);

const key_override_t **key_overrides = (const key_override_t *[]){
	&ov_key_2, &ov_key_6, &ov_key_7, &ov_key_8, &ov_key_9, &ov_key_0,
	&ov_key_scln, NULL 
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] =
{
    [LAYER0] = LAYOUT(
                 KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5, KC_F6,                         KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,                  \
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,  KC_PSCR,                       KC_PAUSE,KC_6,    KC_7,    KC_8,     KC_9,     KC_0,     KC_MINUS,     \
        JP_ZKHK, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,  KC_BSPC,                       KC_BSPC, KC_Y,    KC_U,    KC_I,     KC_O,     KC_P,     KC_BSPC,     \
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                          KC_H,    KC_J,    KC_K,     KC_L,     KC_SCLN,  KC_ENTER,     \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,  KC_DEL,                        KC_DEL,  KC_N,    KC_M,    KC_COMMA, KC_DOT,   KC_SLASH, KC_RSFT,    \
        KC_LCTL, KC_LALT, KC_LGUI, KC_NO,   MO(1),                                                           KC_LEFT, KC_UP,    KC_DOWN,  KC_RIGHT, KC_RCTL,       \
                                                            MO(1),    MO(2),      MO(2),   MO(1),                                                                   \
                                                  KC_SPACE, KC_ENTER, KC_TRNS,    KC_TRNS, KC_ENTER,  KC_SPACE,                                                     \
                                                                      QK_OVTG,    KC_TRNS                                                                            \
  ),
  [LAYER1] = LAYOUT(
                   KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                   KC_TRNS ,     KC_TRNS , KC_TRNS , KC_TRNS ,  KC_TRNS ,  KC_TRNS ,              \
        KC_TRNS ,   KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                   KC_TRNS ,     KC_TRNS , KC_TRNS , KC_TRNS ,  KC_TRNS ,  KC_TRNS ,  KC_TRNS ,    \
        KC_TRNS ,   KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                   KC_TRNS ,     KC_TRNS , KC_TRNS , KC_TRNS ,  KC_TRNS ,  KC_TRNS ,  KC_TRNS ,    \
        KC_TRNS ,   KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                                         KC_TRNS , KC_TRNS , KC_TRNS ,  KC_TRNS ,  KC_TRNS ,  KC_TRNS ,    \
        KC_TRNS ,   KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                    KC_TRNS ,     KC_TRNS , KC_TRNS , KC_TRNS ,  KC_TRNS ,  KC_TRNS ,  KC_TRNS ,    \
        KC_TRNS ,   KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                                                           KC_TRNS , KC_TRNS ,  KC_TRNS ,  KC_TRNS ,  KC_TRNS ,    \
                                                           KC_TRNS ,   KC_TRNS ,    KC_TRNS , KC_TRNS ,                                         \
                                                  KC_TRNS , KC_TRNS ,   KC_TRNS ,    KC_TRNS , KC_TRNS , KC_TRNS ,                                           \
                                                                      KC_TRNS ,    KC_TRNS                                                                  \
  ),
  [LAYER2] = LAYOUT(
                   KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                   KC_TRNS ,     KC_TRNS , KC_TRNS , KC_TRNS ,  KC_TRNS ,  KC_TRNS ,              \
        KC_TRNS ,   KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                   KC_TRNS ,     KC_TRNS , KC_TRNS , KC_TRNS ,  KC_TRNS ,  KC_TRNS ,  KC_TRNS ,    \
        KC_TRNS ,   KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                   KC_TRNS ,     KC_TRNS , KC_TRNS , KC_TRNS ,  KC_TRNS ,  KC_TRNS ,  KC_TRNS ,    \
        KC_TRNS ,   KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                                         KC_TRNS , KC_TRNS , KC_TRNS ,  KC_TRNS ,  KC_TRNS ,  KC_TRNS ,    \
        KC_TRNS ,   KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                    KC_TRNS ,     KC_TRNS , KC_TRNS , KC_TRNS ,  KC_TRNS ,  KC_TRNS ,  KC_TRNS ,    \
        KC_TRNS ,   KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                                                           KC_TRNS , KC_TRNS ,  KC_TRNS ,  KC_TRNS ,  KC_TRNS ,    \
                                                           KC_TRNS ,   KC_TRNS ,    KC_TRNS , KC_TRNS ,                                         \
                                                  KC_TRNS , KC_TRNS ,   KC_TRNS ,    KC_TRNS , KC_TRNS , KC_TRNS ,                                           \
                                                                      KC_TRNS ,    KC_TRNS                                                                  \
  ),
  [LAYER3] = LAYOUT(
                   KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                   KC_TRNS ,     KC_TRNS , KC_TRNS , KC_TRNS ,  KC_TRNS ,  KC_TRNS ,              \
        KC_TRNS ,   KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                   KC_TRNS ,     KC_TRNS , KC_TRNS , KC_TRNS ,  KC_TRNS ,  KC_TRNS ,  KC_TRNS ,    \
        KC_TRNS ,   KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                   KC_TRNS ,     KC_TRNS , KC_TRNS , KC_TRNS ,  KC_TRNS ,  KC_TRNS ,  KC_TRNS ,    \
        KC_TRNS ,   KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                                         KC_TRNS , KC_TRNS , KC_TRNS ,  KC_TRNS ,  KC_TRNS ,  KC_TRNS ,    \
        KC_TRNS ,   KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                    KC_TRNS ,     KC_TRNS , KC_TRNS , KC_TRNS ,  KC_TRNS ,  KC_TRNS ,  KC_TRNS ,    \
        KC_TRNS ,   KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                                                           KC_TRNS , KC_TRNS ,  KC_TRNS ,  KC_TRNS ,  KC_TRNS ,    \
                                                           KC_TRNS ,   KC_TRNS ,    KC_TRNS , KC_TRNS ,                                         \
                                                  KC_TRNS , KC_TRNS ,   KC_TRNS ,    KC_TRNS , KC_TRNS , KC_TRNS ,                                           \
                                                                      KC_TRNS ,    KC_TRNS                                                                  \
  ),
};
