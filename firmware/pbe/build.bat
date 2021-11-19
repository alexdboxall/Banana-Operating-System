D:
cd C:/Users/Alex/Desktop/Banana/firmware/pbe/objects || (pause & exit)
del *.* /Q

cd ../common
i386-banana-gcc -c -ffreestanding -Os ff.c -o ../objects/ff.o || pause
i386-banana-gcc -c -ffreestanding -O0 diskio.c -o ../objects/diskio.o || pause
i386-banana-gcc -c -ffreestanding -Os main.c -o ../objects/main.o || pause

i386-banana-gcc -c -ffreestanding -Os ../arch/x86.c -o ../objects/x86c.o || pause

cd ..
nasm arch/x86.asm -o objects/boot.oo -felf32 || pause
i386-banana-gcc -T linker.ld objects/boot.oo objects/*.o -o FIRMWARE.LIB -ffreestanding -nostdlib || pause