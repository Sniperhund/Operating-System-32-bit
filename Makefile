kernel_source_files := $(shell find src/impl/kernel -name *.c)
kernel_object_files := $(patsubst src/impl/kernel/%.c, build/kernel/%.o, $(kernel_source_files))

x86_c_source_files := $(shell find src/impl/x86 -name *.c)
x86_c_object_files := $(patsubst src/impl/x86/%.c, build/x86/%.o, $(x86_c_source_files))

x86_asm_source_files := $(shell find src/impl/x86 -name *.asm)
x86_asm_object_files := $(patsubst src/impl/x86/%.asm, build/x86/%.o, $(x86_asm_source_files))

x86_object_files := $(x86_c_object_files) $(x86_asm_object_files)

$(kernel_object_files): build/kernel/%.o : src/impl/kernel/%.c
	mkdir -p $(dir $@) && \
	x86_64-elf-gcc -c -I src/intf -ffreestanding $(patsubst build/kernel/%.o, src/impl/kernel/%.c, $@) -o $@

$(x86_c_object_files): build/x86/%.o : src/impl/x86/%.c
	mkdir -p $(dir $@) && \
	x86_64-elf-gcc -c -I src/intf -ffreestanding $(patsubst build/x86/%.o, src/impl/x86/%.c, $@) -o $@

$(x86_asm_object_files): build/x86/%.o : src/impl/x86/%.asm
	mkdir -p $(dir $@) && \
	nasm -f elf64 $(patsubst build/x86/%.o, src/impl/x86/%.asm, $@) -o $@

.PHONY: build
build: $(kernel_object_files) $(x86_object_files)
	mkdir -p dist/x86 && \
	x86_64-elf-ld -n -o dist/x86/kernel.bin -T targets/x86/linker.ld $(kernel_object_files) $(x86_object_files) && \
	cp dist/x86/kernel.bin targets/x86/iso/boot/kernel.bin && \
	grub-mkrescue /usr/lib/grub/i386-pc -o dist/x86/kernel.iso targets/x86/iso
