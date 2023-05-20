#include "ergomax_tnk.h"
#include QMK_KEYBOARD_H

#include "raw_hid.h"
#include <string.h>

#ifdef OLED_ENABLE
#include OLED_FONT_H
extern uint8_t oled_rotation_width;
extern uint8_t oled_buffer[OLED_MATRIX_SIZE];
extern OLED_BLOCK_TYPE oled_dirty; 
#endif

// ビットマップ転送は負荷がかかるので、更新を必要最低限に
// quantum/keyboard.c の #if OLED_TIMEOUT > 0 の箇所を除去することで
// キーを押すたびに画面が表示されるのを抑止することができる
static bool require_oled_update = true;
static bool oled_clear_later = false;

// Winキーが押されているかどうか
static bool gui_key_down = false;

// キャッシュを用意することで特定の文字のみ更新できるように
static uint8_t lmsg[OLED_CHAR_LEN];

void oled_update(void)
{
	// I2Cが共有されているので片方のキーボードのみで処理する
    if(is_keyboard_master()) {
        require_oled_update = true;
    }
}

// キーボード初期化後に呼ばれる
void keyboard_post_init_user(void)
{
    memset(lmsg, 0, 32);
}

// レイヤー状態が変更されたときに呼び出される
layer_state_t layer_state_set_user(layer_state_t state)
{
    oled_update();
    return state;
}

// キーが押されたときに呼び出される関数
bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    if(keycode >= KC_FN1 && keycode <= KC_FN1 + 10){
		if(record->event.pressed) send_request(keycode - KC_FN1);
        return false;
    }

    switch (keycode) {
    case KC_LGUI:
    case KC_RGUI:
        gui_key_down = record->event.pressed;
    case KC_LSFT:
    case KC_RSFT:
    case KC_LALT:
    case KC_RALT:
    case KC_LCTL:
    case KC_RCTL:
        oled_update();
        break;

	/*
	default: // キーコードのテスト
		strcpy(msg + 16, get_u8_str(keycode, ' '));
		oled_update();
		break;
    */
	}
    return true;
}

bool led_update_user(led_t led_state)
{
    oled_update();
    return true;
}

#ifdef OLED_ENABLE
// OLEDを初期化するときに呼ばれる関数。戻り値は実際に適用する回転角度
oled_rotation_t oled_init_user(oled_rotation_t rotation)
{
    return rotation;
}

void set_oled_char(uint8_t col, uint8_t line, const uint8_t charcode)
{
    int pos = line * OLED_COLS + col;
    if(pos < 0 || pos >= OLED_CHAR_LEN || lmsg[pos] == charcode) return;

    lmsg[pos] = charcode;

    for(int l = 0; l < 2; l++){
        uint16_t index = (line * 2 + l) * oled_rotation_width + col * OLED_FONT_WIDTH;
        const uint8_t *glyph = &font[((charcode - OLED_FONT_START) * 2 + l) * OLED_FONT_WIDTH];
        memcpy_P(oled_buffer + index, glyph, OLED_FONT_WIDTH);

        oled_dirty |= ((OLED_BLOCK_TYPE)1 << (index / OLED_BLOCK_SIZE));
        oled_dirty |= ((OLED_BLOCK_TYPE)1 << ((index + OLED_FONT_WIDTH - 1) / OLED_BLOCK_SIZE));
    }
}

void set_oled_bitmap(uint8_t col, uint8_t line, const uint8_t *bmp)
{
    int pos = line * OLED_COLS + col;
    if(pos < 0 || pos >= OLED_CHAR_LEN) return;

    for(int l = 0; l < 2; l++){
        uint16_t index = (line * 2 + l) * oled_rotation_width + col * OLED_FONT_WIDTH;
        const uint8_t *bmpp = bmp + OLED_FONT_WIDTH * l;
        memcpy(oled_buffer + index, bmpp, OLED_FONT_WIDTH);
    }
}

// メッセージ領域の更新フラグを設置
void update_message_area(void)
{
    for(int l = 0; l < 2; l++){
        for(int c = 0; c < 16; c++){
            uint16_t index = (2 + l) * oled_rotation_width + c * OLED_FONT_WIDTH;
            oled_dirty |= ((OLED_BLOCK_TYPE)1 << (index / OLED_BLOCK_SIZE));
            oled_dirty |= ((OLED_BLOCK_TYPE)1 << ((index + OLED_FONT_WIDTH - 1) / OLED_BLOCK_SIZE));
        }
    }
}

void draw_status(void)
{
    led_t keys = host_keyboard_led_state();
    int mods = get_mods();

    int layer_index = 0;
    if(layer_state_cmp(layer_state, LAYER0)){
        layer_index = 1;
    }else if(layer_state_cmp(layer_state, LAYER1)){
        layer_index = 2;
    }else if(layer_state_cmp(layer_state, LAYER2)){
        layer_index = 3;
    }else if(layer_state_cmp(layer_state, LAYER3)){
        layer_index = 4;
    }

	//0123456789012345
	//[NCS] [SCAW] L0
    set_oled_char(0, 0, '[');
    set_oled_char(1, 0, keys.num_lock ? 'N' : ' ');
    set_oled_char(2, 0, keys.caps_lock ? 'C' : ' ');
    set_oled_char(3, 0, keys.scroll_lock ? 'S' : ' ');
    set_oled_char(4, 0, ']');
    set_oled_char(5, 0, ' ');
    set_oled_char(6, 0, '[');
    set_oled_char(7, 0, (mods & MOD_MASK_SHIFT) ? 'S' : ' ');
    set_oled_char(8, 0, (mods & MOD_MASK_CTRL) ? 'C' : ' ');
    set_oled_char(9, 0, (mods & MOD_MASK_ALT) ? 'A' : ' ');
    set_oled_char(10, 0, gui_key_down ? 'W' : ' ');
    set_oled_char(11, 0, ']');
    set_oled_char(12, 0, ' ');
    set_oled_char(13, 0, 'L');
    set_oled_char(14, 0, '0' + layer_index);
}

// OLEDが更新されるときに呼び出される関数
bool oled_task_user(void)
{
    if(require_oled_update == true) {
        if(oled_clear_later){
            update_message_area();
            oled_clear_later = false;
        }

	    draw_status();
		oled_on();
    	require_oled_update = false;
	}

	return true; // 現時点(Ver 0.18)で戻り値に意味は無い
}

__attribute__((weak))
void suspend_power_down_user(void)
{
    oled_off();
}
#endif

#ifdef RAW_ENABLE
void send_request(uint8_t command)
{
	uint8_t send_data[32];
	memset(send_data, 0, 32);
	send_data[0] = id_request_command;
    send_data[1] = command;
	raw_hid_send(send_data, 32);
}

void raw_hid_receive_kb(uint8_t *data, uint8_t length)
{
	if(data[0] == id_set_keyboard_value){
		uint8_t command = data[1];
		if(command == id_set_message){
			// メッセージの表示(最大16文字)
			char *cp = (char*)(data + 2);
			int slen = length - 2;
			for(int i = 0; i < 16; i++){
				if(cp[i] == '\0') slen = i;
                set_oled_char(i, 1, (i < slen) ? cp[i] : ' ');
			}

			oled_update();
        }else if(command == id_set_bitmap){
            // ビットマップの表示(8x16pixel, 16byte)
            set_oled_bitmap(data[2], 1, data + 3);
        }else if(command == id_update_message_area){
            update_message_area();
            oled_update();
		}else if(command == id_clear_message){
            OLED_BLOCK_TYPE _old_dirty = oled_dirty;
        
			// メッセージのリセット 
            for(int i = 0; i < 16; i++) set_oled_char(i, 1, ' ');
            
            // 3byte目に強制表示フラグがなければ、dirtyフラグは変更しない
			if(!(length > 2 && data[2])) {
                oled_clear_later = true;
                oled_dirty = _old_dirty;
            }
		}
	}
}
#endif // RAW_ENABLE