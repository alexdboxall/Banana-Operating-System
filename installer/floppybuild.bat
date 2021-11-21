C:

cd C:/Users/alex/Desktop/Banana/kernel
nasm -O0 -f bin boot/FIRMWARE.ASM -o FIRMWARE.LIB -w+orphan-labels -i boot/ || pause

cd C:/Users/Alex/Desktop/Banana/firmware/Installer
call build.bat

cd C:/Users/Alex/Desktop/Banana/firmware/FLOPPY
call build.bat

cd C:/Users/Alex/Desktop/Banana/Installer

del Floppy\DATA*.BIN

python zeros.py || (pause)

nasm -fbin iso.s -o Root/SETUP.EXE || (pause)
nasm -fbin fdboot.s -o Floppy/FBOOTSEC.BIN || pause

del DISK*.IMG

cd C:/Users/Alex/Desktop/Banana/Installer
imdisk -a -o fd -f DISK1.IMG -p "/fs:fat /y /a:512" -s 1440K -m P: || pause
copy Floppy\DATA1.BIN "P:/DISKETTE.001" || pause
copy Floppy\ZEROS.SYS "P:/ZEROS.SYS" || pause
copy Root\FIRMWARE.LIB "P:/FIRMWARE.LIB" || pause
copy Root\BOOTLOAD.EXE "P:/FLOPPY.EXE" || pause
imdisk -D -m P:


if exist Floppy\DATA2.BIN (
    imdisk -a -o fd -f DISK2.IMG -p "/fs:fat /y /a:512" -s 1440K -m P: || pause
    copy Floppy\DATA2.BIN "P:/DISKETTE.002" || pause
    imdisk -D -m P:
)

if exist Floppy\DATA3.BIN (
    imdisk -a -o fd -f DISK3.IMG -p "/fs:fat /y /a:512" -s 1440K -m P: || pause
    copy Floppy\DATA3.BIN "P:/DISKETTE.003" || pause
    imdisk -D -m P:
)

if exist Floppy\DATA4.BIN (
    imdisk -a -o fd -f DISK4.IMG -p "/fs:fat /y /a:512" -s 1440K -m P: || pause
    copy Floppy\DATA4.BIN "P:/DISKETTE.004" || pause
    imdisk -D -m P:
)

if exist Floppy\DATA5.BIN (
    imdisk -a -o fd -f DISK5.IMG -p "/fs:fat /y /a:512" -s 1440K -m P: || pause
    copy Floppy\DATA5.BIN "P:/DISKETTE.005" || pause
    imdisk -D -m P:
)

if exist Floppy\DATA6.BIN (
    imdisk -a -o fd -f DISK6.IMG -p "/fs:fat /y /a:512" -s 1440K -m P: || pause
    copy Floppy\DATA6.BIN "P:/DISKETTE.006" || pause
    imdisk -D -m P:
)

if exist Floppy\DATA7.BIN (
    imdisk -a -o fd -f DISK7.IMG -p "/fs:fat /y /a:512" -s 1440K -m P: || pause
    copy Floppy\DATA7.BIN "P:/DISKETTE.007" || pause
    imdisk -D -m P:
)

if exist Floppy\DATA8.BIN (
    imdisk -a -o fd -f DISK8.IMG -p "/fs:fat /y /a:512" -s 1440K -m P: || pause
    copy Floppy\DATA8.BIN "P:/DISKETTE.008" || pause
    imdisk -D -m P:
)

if exist Floppy\DATA9.BIN (
    imdisk -a -o fd -f DISK9.IMG -p "/fs:fat /y /a:512" -s 1440K -m P: || pause
    copy Floppy\DATA9.BIN "P:/DISKETTE.009" || pause
    imdisk -D -m P:
)

python floppyjoin.py

if exist ..\qemuinhibit.txt (
    echo a
) else (
    "C:\Program Files\qemu\qemu-system-i386.exe" -d guest_errors,cpu_reset -m 512 -boot d -serial file:log.txt -fda DISK1.IMG -soundhw all -monitor stdio -hda test.bin || pause
)
pause
rem "D:\Users\Alex\VirtualBox VMs\Banana OS\NewVirtualDisk17.vdi",format=vdi
rem 

