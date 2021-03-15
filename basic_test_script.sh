#!/bin/bash

bin/c_compiler -S test.c -o output.s
mips-linux-gnu-gcc -mfp32 -o output.o -c output.s
mips-linux-gnu-gcc -mgp32 -static -o output output.o test.c
qemu-mips output
echo $?
rm output.o
rm output.s
rm output

echo "All done"
