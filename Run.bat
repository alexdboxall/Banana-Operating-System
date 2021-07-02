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

D:
cd D:/Users/Alex/Desktop/Banana
rm disacpica.txt
rm dislegacy.txt
rm disclipdraw.txt
rm disvesa.txt
rm disvga.txt
rm discmd.txt
rm disbios.txt
rm dissys.txt
rm disac97.txt
rm disrtl.txt
objdump -drwC -Mintel packages/banana/32/0002/acpica.sys >> disacpica.txt
objdump -drwC -Mintel packages/system/32/0002/legacy.sys >> dislegacy.txt
objdump -drwC -Mintel packages/banana/32/0001/clipdraw.dll >> disclipdraw.txt
objdump -drwC -Mintel packages/banana/32/0002/vga.sys >> disvga.txt
objdump -drwC -Mintel packages/banana/32/0002/ac97.sys >> disac97.txt
objdump -drwC -Mintel packages/banana/32/0002/rtl8139.sys >> disrtl.txt
objdump -drwC -Mintel packages/banana/32/0002/vesa.sys >> disvesa.txt
objdump -drwC -Mintel packages/system/32/0001/command.exe >> discmd.txt
objdump -drwC -Mintel packages/system/32/0001/system.dll >> dissys.txt

cd D:/Users/Alex/Desktop/Banana/firmware/BOOT2
call build.bat

cd D:/Users/Alex/Desktop/Banana/firmware/pbe
call build.bat
rem cp "D:/Users/Alex/Desktop/Banana/firmware/pbe/firmware.lib" "D:/Users/Alex/Desktop/Banana/kernel/firmware.lib"

cp "D:/Users/Alex/Desktop/Banana/COPYRIGHT" "D:/Users/Alex/Desktop/Banana/packages/banana/32/0006/COPYRIGHT" || pause
cp "D:/Users/Alex/Desktop/Banana/LICENSE" "D:/Users/Alex/Desktop/Banana/packages/banana/32/0006/LICENSE" || pause

cd D:/Users/Alex/Desktop/Banana/packages
python create.py



cd D:/Users/Alex/Desktop/Banana/installer/FloppyRoot
xdelta3 -f -s D:/Users/Alex/Desktop/Banana/kernel/KRNL386.EXE D:/Users/Alex/Desktop/Banana/kernel/KRNL486.EXE 386TO4.DIF
xdelta3 -f -s D:/Users/Alex/Desktop/Banana/kernel/KRNL486.EXE D:/Users/Alex/Desktop/Banana/kernel/KRNL586.EXE 486TO5.DIF
cd D:/Users/Alex/Desktop/banana-os
del newimage.img
del basicimage.img






imdisk -a -f newimage.img -s 64M -m T: -p "/fs:fat32 /y /a:512" || pause

cd D:/Users/Alex/Desktop/Banana
robocopy D:/Users/Alex/Desktop/Banana/sysroot/ T:/ /E
rmdir T:\Banana\Dev32 /s /q
mkdir T:\Banana\Dev32
rmdir T:\Banana\Dev64 /s /q
mkdir T:\Banana\Dev64

cp D:/Users/Alex/Desktop/Banana/packages/banana.cab T:/Banana/Packages

rem cp D:/Users/Alex/Desktop/Banana/packages/*.cab T:/Banana/Packages
rem rm T:\Banana\Packages\devel.cab
rem rm T:\Banana\Packages\system.cab
rem rm T:\Banana\Packages\pci.cab
rem rm T:\Banana\Packages\wallpaper.cab

robocopy D:/Users/Alex/Desktop/Banana/packages/system/32/0001 T:/Banana/System /E
robocopy D:/Users/Alex/Desktop/Banana/packages/system/32/0002 T:/Banana/Drivers /E
cd kernel
copy "D:/Users/Alex/Desktop/Banana/kernel/BANANABT" "T:/Banana/BANANABT" || pause
copy "D:/Users/Alex/Desktop/Banana/kernel/FIRMWARE.LIB" "T:/Banana/FIRMWARE.LIB" || pause
copy "D:/Users/Alex/Desktop/Banana/kernel/KERNEL32.EXE" "T:/BANANA/System/KERNEL32.EXE" || pause
copy "D:/Users/Alex/Desktop/Banana/kernel/TRAMP.EXE" "T:/Banana/System/tramp.exe" || pause
rem python ../genCoreFileBackups.py || pause

cd ../tools
copy "D:/Users/Alex/Desktop/Banana/tools/lotsof0s.bin" "T:/dummy.txt"
copy "D:/Users/Alex/Desktop/Banana/tools/lotsof0s.bin" "T:/dummy2.txt"
rm T:\dummy.txt
rm T:\dummy2.txt
copy "D:/Users/Alex/Desktop/Banana/tools/lotsof0s.bin" "T:/dummy.txt"
copy "D:/Users/Alex/Desktop/Banana/tools/lotsof0s.bin" "T:/dummy2.txt"
copy "D:/Users/Alex/Desktop/Banana/tools/lotsof0s.bin" "T:/dummy3.txt"
copy "D:/Users/Alex/Desktop/Banana/tools/lotsof0s.bin" "T:/dummy4.txt"
copy "D:/Users/Alex/Desktop/Banana/tools/lotsof0s.bin" "T:/dummy5.txt"
copy "D:/Users/Alex/Desktop/Banana/tools/lotsof0s.bin" "T:/dummy6.txt"
copy "D:/Users/Alex/Desktop/Banana/tools/lotsof0s.bin" "T:/dummy7.txt"
copy "D:/Users/Alex/Desktop/Banana/tools/lotsof0s.bin" "T:/dummy8.txt"
copy "D:/Users/Alex/Desktop/Banana/tools/lotsof0s.bin" "T:/dummy9.txt"
copy "D:/Users/Alex/Desktop/Banana/tools/lotsof0s.bin" "T:/dummyA.txt"
copy "D:/Users/Alex/Desktop/Banana/tools/lotsof0s.bin" "T:/dummyB.txt"
copy "D:/Users/Alex/Desktop/Banana/tools/lotsof0s.bin" "T:/dummyC.txt"
copy "D:/Users/Alex/Desktop/Banana/tools/lotsof0s.bin" "T:/dummyD.txt"
copy "D:/Users/Alex/Desktop/Banana/tools/lotsof0s.bin" "T:/dummyE.txt"
copy "D:/Users/Alex/Desktop/Banana/tools/lotsof0s.bin" "T:/dummyF.txt"

copy "D:/Users/Alex/Desktop/Banana/tools/less0s.bin" "T:/dummyAA.txt"
copy "D:/Users/Alex/Desktop/Banana/tools/less0s.bin" "T:/dummyAB.txt"
copy "D:/Users/Alex/Desktop/Banana/tools/less0s.bin" "T:/dummyAC.txt"
copy "D:/Users/Alex/Desktop/Banana/tools/less0s.bin" "T:/dummyAD.txt"
copy "D:/Users/Alex/Desktop/Banana/tools/less0s.bin" "T:/dummyAE.txt"
copy "D:/Users/Alex/Desktop/Banana/tools/less0s.bin" "T:/dummyAF.txt"
copy "D:/Users/Alex/Desktop/Banana/tools/less0s.bin" "T:/dummyAG.txt"
copy "D:/Users/Alex/Desktop/Banana/tools/less0s.bin" "T:/dummyAH.txt"
copy "D:/Users/Alex/Desktop/Banana/tools/less0s.bin" "T:/dummyAI.txt"
copy "D:/Users/Alex/Desktop/Banana/tools/less0s.bin" "T:/dummyAJ.txt"
copy "D:/Users/Alex/Desktop/Banana/tools/less0s.bin" "T:/dummyAK.txt"
copy "D:/Users/Alex/Desktop/Banana/tools/less0s.bin" "T:/dummyAL.txt"
copy "D:/Users/Alex/Desktop/Banana/tools/less0s.bin" "T:/dummyAM.txt"
copy "D:/Users/Alex/Desktop/Banana/tools/less0s.bin" "T:/dummyAN.txt"
copy "D:/Users/Alex/Desktop/Banana/tools/less0s.bin" "T:/dummyAO.txt"
copy "D:/Users/Alex/Desktop/Banana/tools/less0s.bin" "T:/dummyAP.txt"

copy "D:/Users/Alex/Desktop/Banana/tools/tiny0s.bin" "T:/dummyA111.txt"
copy "D:/Users/Alex/Desktop/Banana/tools/tiny0s.bin" "T:/dummyA112.txt"
copy "D:/Users/Alex/Desktop/Banana/tools/tiny0s.bin" "T:/dummyA113.txt"
copy "D:/Users/Alex/Desktop/Banana/tools/tiny0s.bin" "T:/dummyA114.txt"
copy "D:/Users/Alex/Desktop/Banana/tools/tiny0s.bin" "T:/dummyA115.txt"
copy "D:/Users/Alex/Desktop/Banana/tools/tiny0s.bin" "T:/dummyA116.txt"
copy "D:/Users/Alex/Desktop/Banana/tools/tiny0s.bin" "T:/dummyA117.txt"
copy "D:/Users/Alex/Desktop/Banana/tools/tiny0s.bin" "T:/dummyA118.txt"
copy "D:/Users/Alex/Desktop/Banana/tools/tiny00.bin" "T:/dummyA101.txt"
copy "D:/Users/Alex/Desktop/Banana/tools/tiny00.bin" "T:/dummyA102.txt"
copy "D:/Users/Alex/Desktop/Banana/tools/tiny00.bin" "T:/dummyA103.txt"
copy "D:/Users/Alex/Desktop/Banana/tools/tiny00.bin" "T:/dummyA104.txt"
copy "D:/Users/Alex/Desktop/Banana/tools/tiny00.bin" "T:/dummyA105.txt"
copy "D:/Users/Alex/Desktop/Banana/tools/tiny00.bin" "T:/dummyA106.txt"
copy "D:/Users/Alex/Desktop/Banana/tools/tiny00.bin" "T:/dummyA107.txt"
copy "D:/Users/Alex/Desktop/Banana/tools/tiny00.bin" "T:/dummyA108.txt"
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

cd D:/Users/Alex/Desktop/
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

qemu-system-i386 -soundhw pcspk,ac97 -vga std -nic model=rtl8139 -cpu max -serial file:log3.txt -m 32 -cdrom D:/Users/Alex/Desktop/banana-os/Installer/BANANA.ISO -fda mikeos.flp -rtc base=utc -d guest_errors,cpu_reset -monitor stdio  -drive file="banana-os/newimage.img",id=abcdefg,if=none -device ich9-ahci,id=ahci -device ide-drive,drive=abcdefg,bus=ahci.0  
pause
	rem -cdrom D:/Users/Alex/Desktop/banana-os/Installer/BANANA.ISO
	rem  -cdrom D:/Users/Alex/Desktop/Banana/Installer/BANANA.ISO -drive file="banana-os/newimage.img",id=abcdefg,if=none -device ich9-ahci,id=ahci -device ide-drive,drive=abcdefg,bus=ahci.0 
	rem -hda "banana-os/newimage.img"
	rem -cdrom D:/Users/Alex/Desktop/banana-os/Installer/BANANA.ISO 
	rem -hda banana-os/newimage.img 
)


imdisk -a -f banana-os/newimage.img -m W:
rd /S /Q output 
robocopy W:/ output /E
imdisk -D -m W:
