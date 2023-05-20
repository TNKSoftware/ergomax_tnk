#include QMK_KEYBOARD_H
#include "ergomax_tnk.h"
#include "keymap_japanese.h"

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
                                                                      KC_TRNS,    KC_TRNS                                                                            \
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