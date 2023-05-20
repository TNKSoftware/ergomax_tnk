# git clone -b 0.18.17 https://github.com/qmk/qmk_firmware.git
# qmk compile -kb ergomax_tnk -km default
# qmk flash -kb ergomax_tnk -km default

# セーフティーオプションを有効にするには次のコメントを外します
# CFLAGS += -DEMTNK_SAFETY

RAW_ENABLE = yes
VIA_ENABLE = yes
BOOTMAGIC_ENABLE = yes

ifeq ($(KEYMAP), eng)
    KEY_OVERRIDE_ENABLE = yes
else
    KEY_OVERRIDE_ENABLE = no
endif