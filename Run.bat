@echo off
NET SESSION >nul 2>&1
IF %ERRORLEVEL% EQU 0 (
timeout 0
) ELSE (
echo Please run this script with Administator privileges
pause
exit
)

@echo on

C:
cd C:/Users/Alex/Desktop/Banana
cd disasms
rm *.txt
cd ..
objdump -drwC -Mintel packages/banana/32/0002/acpica.sys >> disasms/disacpica.txt
objdump -drwC -Mintel packages/banana/32/0001/newgui.exe >> disasms/disnewgui.txt
objdump -drwC -Mintel packages/system/32/0002/legacy.sys >> disasms/dislegacy.txt
objdump -drwC -Mintel packages/banana/32/0001/clipdraw.dll >> disasms/disclipdraw.txt
objdump -drwC -Mintel packages/banana/32/0002/vga.sys >> disasms/disvga.txt
objdump -drwC -Mintel packages/banana/32/0002/ac97.sys >> disasms/disac97.txt
objdump -drwC -Mintel packages/banana/32/0002/vesa.sys >> disasms/disvesa.txt
objdump -drwC -Mintel packages/system/32/0001/command.exe >> disasms/discmd.txt
objdump -drwC -Mintel packages/system/32/0001/system.dll >> disasms/dissys.txt
objdump -drwC -Mintel packages/banana/32/0001/desktop.exe >> disasms/disdesktop.txt

cd C:/Users/Alex/Desktop/Banana/firmware/BOOT2
call build.bat

cd C:/Users/Alex/Desktop/Banana/firmware/pbe
call build.bat
rem cp "C:/Users/Alex/Desktop/Banana/firmware/pbe/firmware.lib" "C:/Users/Alex/Desktop/Banana/kernel/firmware.lib"

cp "C:/Users/Alex/Desktop/Banana/COPYRIGHT" "C:/Users/Alex/Desktop/Banana/packages/banana/32/0006/COPYRIGHT" || pause
cp "C:/Users/Alex/Desktop/Banana/LICENSE" "C:/Users/Alex/Desktop/Banana/packages/banana/32/0006/LICENSE" || pause

cd C:/Users/Alex/Desktop/Banana/packages
python create.py



cd C:/Users/Alex/Desktop/banana-os
del newimage.img
del basicimage.img






imdisk -a -f newimage.img -s 64M -m T: -p "/fs:fat32 /y /a:512" || pause

cd C:/Users/Alex/Desktop/Banana
robocopy C:/Users/Alex/Desktop/Banana/sysroot/ T:/ /E
rmdir T:\Banana\Dev32 /s /q
mkdir T:\Banana\Dev32
rmdir T:\Banana\Dev64 /s /q
mkdir T:\Banana\Dev64

cp C:/Users/Alex/Desktop/Banana/packages/banana.cab T:/Banana/Packages

rem cp C:/Users/Alex/Desktop/Banana/packages/*.cab T:/Banana/Packages
rem rm T:\Banana\Packages\devel.cab
rem rm T:\Banana\Packages\system.cab
rem rm T:\Banana\Packages\pci.cab
rem rm T:\Banana\Packages\wallpaper.cab

robocopy C:/Users/Alex/Desktop/Banana/packages/system/32/0001 T:/Banana/System /E
robocopy C:/Users/Alex/Desktop/Banana/packages/system/32/0002 T:/Banana/Drivers /E
cd kernel
copy "C:/Users/Alex/Desktop/Banana/kernel/BANANABT" "T:/Banana/BANANABT" || pause
copy "C:/Users/Alex/Desktop/Banana/kernel/FIRMWARE.LIB" "T:/Banana/FIRMWARE.LIB" || pause
copy "C:/Users/Alex/Desktop/Banana/kernel/KERNEL32.EXE" "T:/BANANA/System/KERNEL32.EXE" || pause
copy "C:/Users/Alex/Desktop/Banana/kernel/KRNLP2.EXE" "T:/BANANA/System/KRNLP2.EXE" || pause
copy "C:/Users/Alex/Desktop/Banana/kernel/TRAMP.EXE" "T:/Banana/System/tramp.exe" || pause

cd ../tools
copy "C:/Users/Alex/Desktop/Banana/tools/lotsof0s.bin" "T:/dummy.txt"
copy "c:/Users/Alex/Desktop/Banana/tools/lotsof0s.bin" "T:/dummy2.txt"
rm T:\dummy.txt
rm T:\dummy2.txt
copy "C:/Users/Alex/Desktop/Banana/tools/lotsof0s.bin" "T:/dummy.txt"
copy "C:/Users/Alex/Desktop/Banana/tools/lotsof0s.bin" "T:/dummy2.txt"
copy "C:/Users/Alex/Desktop/Banana/tools/lotsof0s.bin" "T:/dummy3.txt"
copy "C:/Users/Alex/Desktop/Banana/tools/lotsof0s.bin" "T:/dummy4.txt"
copy "C:/Users/Alex/Desktop/Banana/tools/lotsof0s.bin" "T:/dummy5.txt"
copy "C:/Users/Alex/Desktop/Banana/tools/lotsof0s.bin" "T:/dummy6.txt"
copy "C:/Users/Alex/Desktop/Banana/tools/lotsof0s.bin" "T:/dummy7.txt"
copy "C:/Users/Alex/Desktop/Banana/tools/lotsof0s.bin" "T:/dummy8.txt"
copy "C:/Users/Alex/Desktop/Banana/tools/lotsof0s.bin" "T:/dummy9.txt"
copy "C:/Users/Alex/Desktop/Banana/tools/lotsof0s.bin" "T:/dummyA.txt"
copy "C:/Users/Alex/Desktop/Banana/tools/lotsof0s.bin" "T:/dummyC.txt"
copy "C:/Users/Alex/Desktop/Banana/tools/lotsof0s.bin" "T:/dummyD.txt"
copy "C:/Users/Alex/Desktop/Banana/tools/lotsof0s.bin" "T:/dummyE.txt"
copy "C:/Users/Alex/Desktop/Banana/tools/lotsof0s.bin" "T:/dummyF.txt"

copy "C:/Users/Alex/Desktop/Banana/tools/less0s.bin" "T:/dummyAA.txt"
copy "C:/Users/Alex/Desktop/Banana/tools/less0s.bin" "T:/dummyAB.txt"
copy "C:/Users/Alex/Desktop/Banana/tools/less0s.bin" "T:/dummyAC.txt"
copy "C:/Users/Alex/Desktop/Banana/tools/less0s.bin" "T:/dummyAD.txt"
copy "C:/Users/Alex/Desktop/Banana/tools/less0s.bin" "T:/dummyAE.txt"
copy "C:/Users/Alex/Desktop/Banana/tools/less0s.bin" "T:/dummyAF.txt"
copy "C:/Users/Alex/Desktop/Banana/tools/less0s.bin" "T:/dummyAG.txt"
copy "C:/Users/Alex/Desktop/Banana/tools/less0s.bin" "T:/dummyAH.txt"
copy "C:/Users/Alex/Desktop/Banana/tools/less0s.bin" "T:/dummyAI.txt"
copy "C:/Users/Alex/Desktop/Banana/tools/less0s.bin" "T:/dummyAJ.txt"
copy "C:/Users/Alex/Desktop/Banana/tools/less0s.bin" "T:/dummyAK.txt"
copy "C:/Users/Alex/Desktop/Banana/tools/less0s.bin" "T:/dummyAL.txt"
copy "C:/Users/Alex/Desktop/Banana/tools/less0s.bin" "T:/dummyAM.txt"
copy "C:/Users/Alex/Desktop/Banana/tools/less0s.bin" "T:/dummyAN.txt"
copy "C:/Users/Alex/Desktop/Banana/tools/less0s.bin" "T:/dummyAO.txt"
copy "C:/Users/Alex/Desktop/Banana/tools/less0s.bin" "T:/dummyAP.txt"

copy "C:/Users/Alex/Desktop/Banana/tools/tiny0s.bin" "T:/dummyA111.txt"
copy "C:/Users/Alex/Desktop/Banana/tools/tiny0s.bin" "T:/dummyA112.txt"
copy "C:/Users/Alex/Desktop/Banana/tools/tiny0s.bin" "T:/dummyA113.txt"
copy "C:/Users/Alex/Desktop/Banana/tools/tiny0s.bin" "T:/dummyA114.txt"
copy "C:/Users/Alex/Desktop/Banana/tools/tiny0s.bin" "T:/dummyA115.txt"
copy "C:/Users/Alex/Desktop/Banana/tools/tiny0s.bin" "T:/dummyA116.txt"
copy "C:/Users/Alex/Desktop/Banana/tools/tiny0s.bin" "T:/dummyA117.txt"
copy "C:/Users/Alex/Desktop/Banana/tools/tiny0s.bin" "T:/dummyA118.txt"
copy "C:/Users/Alex/Desktop/Banana/tools/tiny00.bin" "T:/dummyA101.txt"
copy "C:/Users/Alex/Desktop/Banana/tools/tiny00.bin" "T:/dummyA102.txt"
copy "C:/Users/Alex/Desktop/Banana/tools/tiny00.bin" "T:/dummyA103.txt"
copy "C:/Users/Alex/Desktop/Banana/tools/tiny00.bin" "T:/dummyA104.txt"
copy "C:/Users/Alex/Desktop/Banana/tools/tiny00.bin" "T:/dummyA105.txt"
copy "C:/Users/Alex/Desktop/Banana/tools/tiny00.bin" "T:/dummyA106.txt"
copy "C:/Users/Alex/Desktop/Banana/tools/tiny00.bin" "T:/dummyA107.txt"
copy "C:/Users/Alex/Desktop/Banana/tools/tiny00.bin" "T:/dummyA108.txt"
rm T:\dummy.txt
rm T:\dummy2.txt
rm T:\dummy3.txt
rm T:\dummy4.txt
rm T:\dummy5.txt
rm T:\dummy6.txt
rm T:\dummy7.txt
rm T:\dummy8.txt
rm T:\dummy9.txt
rm T:\dummyA.txt
rm T:\dummyB.txt
rm T:\dummyC.txt
rm T:\dummyD.txt
rm T:\dummyE.txt
rm T:\dummyF.txt
rm T:\dummyAA.txt
rm T:\dummyAB.txt
rm T:\dummyAC.txt
rm T:\dummyAD.txt
rm T:\dummyAE.txt
rm T:\dummyAF.txt
rm T:\dummyAG.txt
rm T:\dummyAH.txt
rm T:\dummyAI.txt
rm T:\dummyAJ.txt
rm T:\dummyAK.txt
rm T:\dummyAL.txt
rm T:\dummyAM.txt
rm T:\dummyAN.txt
rm T:\dummyAO.txt
rm T:\dummyAP.txt
rm T:\dummyA111.txt
rm T:\dummyA112.txt
rm T:\dummyA113.txt
rm T:\dummyA114.txt
rm T:\dummyA115.txt
rm T:\dummyA116.txt
rm T:\dummyA117.txt
rm T:\dummyA118.txt
rm T:\dummyA101.txt
rm T:\dummyA102.txt
rm T:\dummyA103.txt
rm T:\dummyA104.txt
rm T:\dummyA105.txt
rm T:\dummyA106.txt
rm T:\dummyA107.txt
rm T:\dummyA108.txt

cd C:/Users/Alex/Desktop/
attrib +r "T:/Banana/BANANABT" 
attrib +r "T:/Banana/FIRMWARE.LIB" 
rem attrib +h +r "T:/JUMPER32.SYS" 
attrib +r "T:/BANANA/SYSTEM/KERNEL64.EXE" 
attrib +r "T:/BANANA/SYSTEM/KERNEL32.EXE" 
attrib "T:/BANANA/SYSTEM/TRAMP.EXE" 

imdisk -D -m T:

python Banana/join.py || pause


cd banana-os
copy newimage.img basicimage.img
cd ../


rem -serial file:log.txt

if exist Banana/qemuinhibit.txt (
    echo a
) else (
	rem "C:/Program Files/QEMU/qemu-system-i386" -L "C:\Program Files\qemu" 
	rem qemu-system-i386
	
cd banana-os

rem -nic model=rtl8139
qemu-system-i386 -soundhw pcspk,sb16 -vga std -cpu pentium3 -serial file:log3.txt -m 32 -rtc base=localtime -d guest_errors,cpu_reset -monitor stdio -drive file=newimage.img,id=abcdefg,if=none -device ich9-ahci,id=ahci -device ide-hd,drive=abcdefg,bus=ahci.0 
pause
	rem -cdrom D:/Users/Alex/Desktop/banana-os/Installer/BANANA.ISO
	rem  -cdrom D:/Users/Alex/Desktop/Banana/Installer/BANANA.ISO -drive file="banana-os/newimage.img",id=abcdefg,if=none -device ich9-ahci,id=ahci -device ide-drive,drive=abcdefg,bus=ahci.0 
	rem -hda "banana-os/newimage.img"
	rem -cdrom D:/Users/Alex/Desktop/banana-os/Installer/BANANA.ISO 
	rem -hda banana-os/newimage.img 
)


imdisk -a -f newimage.img -m W:
rd /S /Q output 
robocopy W:/ output /E
imdisk -D -m W:
