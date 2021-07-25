set -e
for i in {1..50}]
do
  echo " "
done

dir=`pwd`
GCC="gcc"
LD="ld"

echo "Building"
sleep 1

[ ! -d "$dir/build/assembly" ] && mkdir -p $dir/build/assembly
[ ! -d "$dir/build/c-files" ] && mkdir -p $dir/build/c-files
[ ! -d "$dir/build/kernel" ] && mkdir -p $dir/build/kernel

cd $dir/src/assembly
#touch *.asm

list=("")

for FILE in *; do
    currentFile=$(echo "$FILE" | cut -f 1 -d '.')
    cd $dir/build/assembly
    nasm -f elf64 $dir/src/assembly/$FILE -o $currentFile.o;
done

cd $dir/src/c-files
#touch *.c

for FILE in *; do
    if [ "${FILE##*.}" = "c" ]; then
        currentFile=$(echo "$FILE" | cut -f 1 -d '.')
        cd $dir/build/c-files
        $GCC -c -I $dir/src/header-files -ffreestanding $dir/src/c-files/$FILE -o $currentFile.o;
    fi
done

cd $dir/src/kernel
#touch *.c

for FILE in *; do
    if [ "${FILE##*.}" = "c" ]; then
        currentFile=$(echo "$FILE" | cut -f 1 -d '.')
        cd $dir/build/kernel
        $GCC -c -I $dir/src/header-files -ffreestanding $dir/src/kernel/$FILE -o $currentFile.o;
    fi
done

cd $dir/build/assembly
#touch *.o

for FILE in *; do
    list+=("$dir/build/assembly/"$FILE)
done

cd $dir/build/c-files
#touch *.o

for FILE in *; do
    list+=("$dir/build/c-files/"$FILE)
done

cd $dir/build/kernel
#touch *.o

for FILE in *; do
    list+=("$dir/build/kernel/"$FILE)
done

cd $dir

echo ${list[*]}
$LD -n -o iso/boot/kernel.bin -T linker.ld ${list[*]}
grub-mkrescue /usr/lib/grub/i386-pc -o kernel.iso iso