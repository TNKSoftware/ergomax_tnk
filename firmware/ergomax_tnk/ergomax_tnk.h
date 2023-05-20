#pragma once

#ifndef ERGOMAX_TNK_H
#define ERGOMAX_TNK_H

#include "quantum.h"

#ifdef RAW_ENABLE
void send_request(uint8_t command);
#define KC_FN0 192
#define KC_FN1 193
#endif

#ifdef OLED_ENABLE
void oled_update(void);
#endif

enum custom_command_id
{
#ifndef VIA_ENABLE
    id_set_keyboard_value = 0x03,
#endif

	// via_keyboard_value_id(~0x03)と重複しない番号
	id_set_message = 0x05,
	id_set_bitmap = 0x06,
	id_update_message_area = 0x07,
	id_clear_message = 0x08,

	id_request_command = 0x09
};

enum layer_number
{
    LAYER0 = 0, LAYER1, LAYER2, LAYER3
};

#define LAYOUT( \
         L00, L01, L02, L03, L04, L05,            R00, R01, R02, R03, R04, R05,         \
    L10, L11, L12, L13, L14, L15, L16,            R10, R11, R12, R13, R14, R15, R16,    \
    L20, L21, L22, L23, L24, L25, L26,            R20, R21, R22, R23, R24, R25, R26,    \
    L30, L31, L32, L33, L34, L35,                      R32, R33, R34, R35, R36, R37,    \
    L40, L41, L42, L43, L44, L45, L46,            R41, R42, R43, R44, R45, R46, R47,    \
    L50, L51, L52, L53, L54,                                R53, R54, R55, R56, R57,    \
                                  L36, L37,  R30, R31,                                  \
                             L55, L56, L47,  R40, R51, R52,                             \
                                       L57,  R50                                        \
) \
{ \
    { KC_NO, L00, L01, L02, L03, L04, L05, KC_NO }, \
    { L10,   L11, L12, L13, L14, L15, L16, KC_NO }, \
    { L20,   L21, L22, L23, L24, L25, L26, KC_NO }, \
    { L30,   L31, L32, L33, L34, L35, L36, L37   }, \
    { L40,   L41, L42, L43, L44, L45, L46, L47   }, \
    { L50,   L51, L52, L53, L54, L55, L56, L57   }, \
    { KC_NO, R05, R04, R03, R02, R01, R00, KC_NO }, \
    { R16,   R15, R14, R13, R12, R11, R10, KC_NO }, \
    { R26,   R25, R24, R23, R22, R21, R20, KC_NO }, \
    { R37,   R36, R35, R34, R33, R32, R31, R30   }, \
    { R47,   R46, R45, R44, R43, R42, R41, R40   }, \
    { R57,   R56, R55, R54, R53, R52, R51, R50   }, \
}

#endif