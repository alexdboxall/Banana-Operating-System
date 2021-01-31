i386-banana-gcc -c -x c BOOT2.C -o BOOT2.O -std=gnu99 -O0 -ffreestanding -Wall -Wextra || pause
i386-banana-gcc -c -x c ../FIRMWARE.C -o FW.O -std=gnu99 -O0 -ffreestanding  || pause
i386-banana-gcc -T LINKER.LD -o ../../kernel/BANANABT -ffreestanding -nostdlib BOOT2.O FW.O -lgcc || pause