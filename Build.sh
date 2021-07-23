echo "Building"

[ ! -d "/root/env/build/assembly" ] && mkdir -p /root/env/build/assembly
[ ! -d "/root/env/build/c-files" ] && mkdir -p /root/env/build/c-files
[ ! -d "/root/env/build/kernel" ] && mkdir -p /root/env/build/kernel

cd /root/env/src/assembly
touch *.s

list=("")

for FILE in *; do
    currentFile=$(echo "$FILE" | cut -f 1 -d '.')
    cd /root/env/build/assembly
    i686-elf-gcc -std=gnu99 -ffreestanding -g -c /root/env/src/assembly/$FILE -o $currentFile.o;
done

cd /root/env/src/c-files
touch *.c

for FILE in *; do
    if [ "${FILE##*.}" = "c" ]; then
        currentFile=$(echo "$FILE" | cut -f 1 -d '.')
        cd /root/env/build/c-files
        i686-elf-gcc -std=gnu99 -ffreestanding -g -c /root/env/src/c-files/$FILE -o $currentFile.o;
    fi
done

cd /root/env/src/kernel
touch *.c

for FILE in *; do
    if [ "${FILE##*.}" = "c" ]; then
        currentFile=$(echo "$FILE" | cut -f 1 -d '.')
        cd /root/env/build/kernel
        i686-elf-gcc -std=gnu99 -ffreestanding -g -c /root/env/src/kernel/$FILE -o $currentFile.o;
    fi
done

cd /root/env/build/assembly
touch *.o

for FILE in *; do
    list+=("/root/env/build/assembly/"$FILE)
done

cd /root/env/build/c-files
touch *.o

for FILE in *; do
    list+=("/root/env/build/c-files/"$FILE)
done

cd /root/env/build/kernel
touch *.o

for FILE in *; do
    list+=("/root/env/build/kernel/"$FILE)
done

cd /root/env

echo ${list[*]}
i686-elf-gcc -ffreestanding -nostdlib -g -T linker.ld ${list[*]} -o iso/boot/kernel.bin -lgcc
grub-mkrescue /usr/lib/grub/i386-pc -o kernel.iso iso