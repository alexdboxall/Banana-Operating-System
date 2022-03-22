D:
cd D:/Users/Alex/Desktop

"C:/Program Files/QEMU/qemu-system-i386" -M q35 -vga std -cpu 486 -serial file:log3.txt -m 16 -rtc base=utc -soundhw pcspk,sb16 -d guest_errors,cpu_reset -monitor stdio -cdrom D:/Users/Alex/Desktop/Banana/Installer/BANANA.ISO -hda banana-os/newimage.img
pause