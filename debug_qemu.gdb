set architecture i386:x86-64
set debug remote 1
set pagination off
target remote localhost:1234
symbol-file iso/boot/kernel.bin
layout split
layout regs
