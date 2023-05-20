from PIL import Image
import numpy
import sys

argvs = sys.argv
argc = len(argvs)

src = "font/unscii-16-ascii.bmp" if argc <= 1 else argvs[1]
dest = "glcdfont.c" if argc <= 2 else argvs[2]

res_file = open(dest, 'w')
res_file.write("#include \"progmem.h\"\n\nstatic const unsigned char PROGMEM font[] = {\n")

print("{} => {}".format(src, dest))

img = Image.open(src).convert('RGB')
data = numpy.array(img)

w,h = img.size
sw = w
if sw % 8 != 0:
	sw = sw + (8 - (sw % 8))

print("(Width, Height, Stride) => ({},{},{})".format(w, h, sw))

ot = 0
for y in range(0, h, 16):
	for x in range(0, w, 8):
		
		for yb in range(0, 2):
			for xx in range(0, 8):
				dx = x + xx
				v = 0x00

				for yy in range(0, 8):
					dy = y + yb * 8 + yy
					c = 1 if data[dy, dx][0] > 128 else 0
					v = v | (c << yy)

				res_file.write("0x{:02X},".format(v))
				ot = ot + 1
				if ot == 20:
					res_file.write("\n")
					ot = 0

res_file.write("\n};")
res_file.close()