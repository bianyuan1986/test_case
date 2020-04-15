#!/bin/bash

set -x

#gcc main.c -g -o main && ./main && md5sum ./main
gcc main.c -Os -o main && strip -R .gnu.hash -R .eh_frame_hdr -R .eh_frame -R .comment -R .note.ABI-tag -R .note.gnu.build-id ./main && ./main && md5sum ./main

