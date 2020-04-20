#!/bin/bash

set -x

/usr/libexec/gcc/x86_64-redhat-linux/4.8.5/cc1 -quiet -g main.c -quiet -dumpbase main.c -mtune=generic -march=x86-64 -auxbase main -Os -version -o /tmp/ccVvtbNu.s

as  --64 -o /tmp/ccAYgYY2.o /tmp/ccVvtbNu.s

#/usr/libexec/gcc/x86_64-redhat-linux/4.8.5/collect2 -z max-page-size=4096 --build-id --no-add-needed --eh-frame-hdr --hash-style=gnu -m elf_x86_64 -dynamic-linker /lib64/ld-linux-x86-64.so.2 -o main /usr/lib/gcc/x86_64-redhat-linux/4.8.5/../../../../lib64/crt1.o /usr/lib/gcc/x86_64-redhat-linux/4.8.5/../../../../lib64/crti.o -L/usr/lib/gcc/x86_64-redhat-linux/4.8.5 -L/usr/lib/gcc/x86_64-redhat-linux/4.8.5/../../../../lib64 -L/lib/../lib64 -L/usr/lib/../lib64 -L/usr/lib/gcc/x86_64-redhat-linux/4.8.5/../../.. /tmp/ccAYgYY2.o  -lc /usr/lib/gcc/x86_64-redhat-linux/4.8.5/../../../../lib64/crtn.o

/usr/libexec/gcc/x86_64-redhat-linux/4.8.5/collect2 -z max-page-size=4096 -T main.lds --build-id --no-add-needed --eh-frame-hdr --hash-style=gnu -m elf_x86_64 -dynamic-linker /lib64/ld-linux-x86-64.so.2 -o main -L/usr/lib/gcc/x86_64-redhat-linux/4.8.5 -L/usr/lib/gcc/x86_64-redhat-linux/4.8.5/../../../../lib64 -L/lib/../lib64 -L/usr/lib/../lib64 -L/usr/lib/gcc/x86_64-redhat-linux/4.8.5/../../.. /tmp/ccAYgYY2.o  -lc 


strip -R .gnu.version -R .gnu.hash -R .eh_frame_hdr -R .eh_frame -R .comment -R .note.ABI-tag -R .note.gnu.build-id ./main
#./tool/ELFkickers-3.1a/bin/sstrip ./main

./main && md5sum ./main
