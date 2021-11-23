#!/usr/bin/env python3

from math import ceil
from collections import OrderedDict
from PIL import Image

STATUSES = ['off', 'on']
DIGITS = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'colon']


def main():
    print('#include "images.h"\n')
    print_array('BELL_ICONS', [f'icons/bell_{i}.png' for i in STATUSES])
    print()
    print_array('WIFI_ICONS', [f'icons/wifi_{i}.png' for i in STATUSES])
    print()
    print_array('DIGITS_16', [f'digits16/{i}.png' for i in DIGITS])
    print()
    print_array('DIGITS_72', [f'digits72/{i}.png' for i in DIGITS])


def print_array(array_name, image_names):
    images = OrderedDict()
    for image_name in image_names:
        image = Image.open(image_name).convert('1')
        images[image_name] = image

    print(f'const image_t {array_name}[{len(images)}] = {{')

    for image_name, image in images.items():
        print(f'    {{ // "{image_name}"')
        print(f'        .width = {image.width},')
        print(f'        .height = {image.height},')
        print(f'        .buffer = (uint8_t[]){{\n            ', end='')

        data = image.tobytes()
        bytes_per_line = ceil(image.width / 8)
        for j, byte in enumerate(data):
            byte = '0x' + hex(byte)[2:].rjust(2, '0')
            print(byte, end=',')
            if j == len(data) - 1:
                print('\n', end='')
            elif j % bytes_per_line == bytes_per_line - 1:
                print('\n            ', end='')
            else:
                print(' ', end='')

        print('        },')
        print('    },')

    print('};')


if __name__ == '__main__':
    main()
