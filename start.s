.extern kernel_main

.global start


.set MB_MAGIC, 0x1BADB002
.set MB_FLAGS, (1 << 0) | (1 << 1)
.set MB_CHECKSUM, (0 - (MB_MAGIC + MB_FLAGS))
 

.section .multiboot
	.align 4
	.long MB_MAGIC
	.long MB_FLAGS
	.long MB_CHECKSUM
 
.section .bss
	.align 16
	stack_bottom:
		.skip 4096 // Reserve a 4096-byte (4K) stack
	stack_top:

	idt_info:
		dw idt_end - idt_start - 1
		dd idt_start
 
.section .text
	start:
		mov $stack_top, %esp // Set the stack pointer to the top of the stack

		lidt ldt_info
		call kernel_main

		hang:
			cli
			hlt
			jmp hang