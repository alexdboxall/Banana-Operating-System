C:

cd C:/Users/alex/Desktop/Banana/kernel
nasm -O0 -f bin boot/FIRMWARE.ASM -o FIRMWARE.LIB -w+orphan-labels -i boot/ || pause

cd C:/Users/Alex/Desktop/Banana/firmware/Installer
call build.bat

cd C:/Users/Alex/Desktop/Banana/Installer

nasm -fbin iso.s -o Root/SETUP.EXE || (pause)

nasm -felf32 include/goodiso.s -o goodiso_s.o || (pause)
i386-banana-gcc -c include/goodiso.c -o goodiso_c.o -O0 -ffreestanding || (pause)
i386-banana-gcc -T include/goodiso.ld -o goodiso.drv goodiso_s.o goodiso_c.o -nostdlib || (pause)

copy /b C:\Users\Alex\Desktop\Banana\kernel\firmware.lib "Root\FIRMWARE.LIB" || (pause)
copy /b Root\SETUP.EXE+goodiso.drv "Root\SETUP.EXE" || (pause)
copy /b C:\Users\Alex\Desktop\banana-os\newimage.img "Root\OSIMAGE.SYS" || (pause)

rm goodiso_c.o
rm goodiso_s.o
rm goodiso.drv

cd Root
C:\Users\Alex\Downloads\cdrtools-1.11a01-win32-bin\mkisofs.exe -boot-load-size 31 -T -boot-load-seg 0x7C0 -nobak -o ../BANANA.ISO -V "BANANA OS 1.0" -no-emul-boot -iso-level 1 -b SETUP.EXE .

rem For the strangest of reasons, the above command WILL GENERATE AN IMAGE WHICH IS ~10KB
rem if the stack dump didn't exist before the script ran, and ~65KB (correct size) if 
rem if it DID exist prior to running this. Weird.

cd ../

if exist ..\qemuinhibit.txt (
    echo a
) else (
    "C:\Program Files\qemu\qemu-system-i386.exe" -d guest_errors,cpu_reset -m 64 -cdrom BANANA.ISO  -boot d -serial file:log.txt -soundhw all -monitor stdio -hda test.bin || pause
    rem "D:\Users\Alex\VirtualBox VMs\Banana OS\NewVirtualDisk17.vdi",format=vdi
    rem 
)