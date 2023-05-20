#pragma once


// QMK 0.18ではinfo.jsonに記述しても反映されない
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 1

#ifdef EMTNK_SAFETY
/// 一部のPro Micro互換機で必要
// もう片側が動作しない場合
#define SPLIT_USB_DETECT
// パソコン起動時に認識せず、USBを再接続しなければならない場合
#define SPLIT_USB_TIMEOUT 20000
#define SPLIT_USB_TIMEOUT_POLL 50
// スリープ復帰時に特定のキーが押しっぱなしになってしまう場合
#define USB_SUSPEND_WAKEUP_DELAY 5000
#endif

// マジックコマンドの使用を可能にするキーの組み合わせ
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)) \
)

#ifdef OLED_ENABLE
// OLEDの画面をスリープにする間隔(ms)
#define OLED_TIMEOUT 5000
#define OLED_FONT_H "keyboards/ergomax_tnk/glcdfont.c"

#define OLED_FONT_WIDTH 8
#define OLED_FONT_HEIGHT 16
#define OLED_FONT_START 0x20
#define OLED_ROWS 2
#define OLED_COLS 16
#define OLED_CHAR_LEN (OLED_COLS * OLED_ROWS)
#endif