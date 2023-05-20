# 必要なライブラリをインポート
import codecs
import sys
from PIL import Image

argvs = sys.argv
argc = len(argvs)

src = "font/unscii-16-full.hex" if argc <= 1 else argvs[1]
dest = "font/unscii-16-ascii.bmp" if argc <= 2 else argvs[2]

charset = [0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 
           0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 
           0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 
           0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 
           0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 
           0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x2103]
cpos = 0
clen = len(charset)

# ビットマップ画像を格納するリスト
images = []

# 入力ファイルを開く
with codecs.open(src, encoding="utf-8") as f:
    
    n = 0

    # 1行ずつ読み込み、Unicode番号と画像の文字列に分割
    for line in f:
        if cpos >= clen:
            break

        line = line.strip()
        unicode_value, encoded_image = line.split(":")

        unicode_value = int(unicode_value, 16)

        if unicode_value != charset[cpos]:
            continue
        else:
            cpos = cpos + 1

        # 画像のバイト列を取得
        encoded_image = bytes.fromhex(encoded_image)

        # ビットマップ画像を復元
        height = 16
        width = 8 * len(encoded_image) // height
        image = Image.new("1", (width, height))
        for i in range(len(encoded_image)):
            byte = encoded_image[i]
            for j in range(8):
                pixel = byte & (1 << (7 - j))
                x = (i * 8 + j) % width
                y = (i * 8 + j) // width
                image.putpixel((x, y), pixel)

        # 復元した画像をリストに追加
        images.append(image)

# 画像を結合して保存
imgl = len(images)
total_width = 8 * 16
max_height = 16 * imgl // 16
if imgl % 16 > 0:
    max_height += 16 - (imgl % 16)
new_image = Image.new("1", (total_width, max_height))
x_offset = 0
for i, image in enumerate(images):
    x_offset = i % 16
    y_offset = i // 16
    new_image.paste(image, (x_offset * 8, y_offset* 16))
new_image.save(dest)