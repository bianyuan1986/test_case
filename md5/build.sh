#!/bin/bash

set -x

#/usr/libexec/gcc/x86_64-redhat-linux/4.8.5/cc1 -quiet -v main.c -quiet -dumpbase main.c -mtune=generic -march=x86-64 -auxbase main -Os -version -fPIC -o /tmp/ccVvtbNu.s
/usr/libexec/gcc/x86_64-redhat-linux/4.8.5/cc1 -quiet -v main.c -quiet -dumpbase main.c -mtune=generic -march=x86-64 -auxbase main -Os -version -o /tmp/ccVvtbNu.s
as -v --64 -o /tmp/ccAYgYY2.o /tmp/ccVvtbNu.s
/usr/libexec/gcc/x86_64-redhat-linux/4.8.5/collect2 --build-id --no-add-needed --eh-frame-hdr --hash-style=gnu -m elf_x86_64 -dynamic-linker /lib64/ld-linux-x86-64.so.2 -o main /usr/lib/gcc/x86_64-redhat-linux/4.8.5/../../../../lib64/crt1.o /usr/lib/gcc/x86_64-redhat-linux/4.8.5/../../../../lib64/crti.o -L/usr/lib/gcc/x86_64-redhat-linux/4.8.5 -L/usr/lib/gcc/x86_64-redhat-linux/4.8.5/../../../../lib64 -L/lib/../lib64 -L/usr/lib/../lib64 -L/usr/lib/gcc/x86_64-redhat-linux/4.8.5/../../.. /tmp/ccAYgYY2.o -lgcc --as-needed -lgcc_s --no-as-needed -lc -lgcc --as-needed -lgcc_s --no-as-needed /usr/lib/gcc/x86_64-redhat-linux/4.8.5/../../../../lib64/crtn.o

#strip -R .gnu.hash -R .eh_frame_hdr -R .eh_frame -R .comment -R .note.ABI-tag -R .note.gnu.build-id ./main
#./tool/ELFkickers-3.1a/bin/sstrip ./main

./main && md5sum ./main
