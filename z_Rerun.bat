D:
cd D:/Users/Alex/Desktop
qemu-system-i386 -vga std -cpu pentium -serial file:log3.txt -m 8 -rtc base=utc -soundhw pcspk,sb16 -d guest_errors,cpu_reset -monitor stdio -cdrom D:/Users/Alex/Desktop/Banana/Installer/BANANA.ISO -drive file="banana-os/newimage.img",id=abcdefg,if=none -device ich9-ahci,id=ahci -device ide-drive,drive=abcdefg,bus=ahci.0 
pause