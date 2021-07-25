MBALIGN  equ  1 << 0            ; align loaded modules on page boundaries
MEMINFO  equ  1 << 1            ; provide memory map
FLAGS    equ  MBALIGN | MEMINFO ; this is the Multiboot 'flag' field
MAGIC    equ  0x1BADB002        ; 'magic number' lets bootloader find the header
CHECKSUM equ -(MAGIC + FLAGS)   ; checksum of above, to prove we are multiboot

section .multiboot
align 4
    ; do something with multiboot
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

section .bss
align 16
stack_bottom:
    resb 16384 ; 16 KiB
stack_top:

section .rodata
gdt:
    dq 0
.code: equ $ - gdt
    dq (1<<44) | (1<<47) | (1<<41) | (1<<43) | (1<<53)
.data: equ $ - gdt
    dq (1<<44) | (1<<47) | (1<<41)
.pointer:
    dw .pointer - gdt - 1
    dq gdt


section .text
global start
start:
    mov esp, stack_top

    lgdt [gdt.pointer]
    extern kernel_main
    call kernel_main

    cli
.hang:
    hlt
    jmp .hang
.end: