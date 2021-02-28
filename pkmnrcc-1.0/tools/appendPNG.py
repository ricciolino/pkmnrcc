#!/usr/bin/python3.6
import sys
import os
from PIL import Image

if len(sys.argv) != 4 and len(sys.argv) != 5:
    print('Specify three or four parameters')
    exit(1)

if not sys.argv[3] == 'R' and not sys.argv[3] == 'D':
    print('Specify R or D as third parameter')
    exit(1)

if not os.path.exists(sys.argv[1]):
    print(f'File {sys.argv[1]} not exist')
    exit(1)
img1 = Image.open(sys.argv[1])

if not os.path.exists(sys.argv[2]):
    print(f'File {sys.argv[2]} not exist')
    exit(1)
img2 = Image.open(sys.argv[2])

if sys.argv[3] == 'R' and img1.size[1] != img2.size[1]:
    print('Heights cannot be different')
    exit(1)

if sys.argv[3] == 'D' and img1.size[0] != img2.size[0]:
    print('Widths cannot be different')
    exit(1)

if sys.argv[3] == 'R':
    img = Image.new('RGBA', (int(img1.size[0] + img2.size[0]), int(img1.size[1])))
    img.paste(img1, (0, 0))
    img.paste(img2, (int(img1.size[0]), 0))
else:
    img = Image.new('RGBA', (int(img1.size[0]), int(img1.size[1] + img2.size[1])))
    img.paste(img1, (0, 0))
    img.paste(img2, (0, int(img1.size[1])))

file_to_save = 'final.png'
if len(sys.argv) == 5:
    file_to_save = sys.argv[4] + '.png'

img.save(file_to_save)
