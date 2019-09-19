#!/bin/bash

gcc -g test_memcpy.c memcpy.c -Wl,--wrap=memcpy -o test_memcpy
#gcc -g test_memcpy.c -o test_memcpy

