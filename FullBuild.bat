@echo off
NET SESSION >nul 2>&1
IF %ERRORLEVEL% EQU 0 (
timeout 0
) ELSE (
echo Please run this script with Administator privileges
pause
exit
)

D:
cd D:/Users/Alex/Desktop/Banana

rem git add .
rem git commit -a --allow-empty-message -m ''
rem git remote add origin https://github.com/A22347/Banana-OS.git
rem git push -u origin master
 
cd firmware\BOOT2
call build
cd ..\INSTALLER
call build
cd ..\..

cd applications
call build

cd ..\drivers
call build

cd ..

cd kernel

make clean || pause
make -j4 TUNING=i386 kernel386 || pause
make clean || pause
make -j4 TUNING=i486 kernel486 || pause
make clean || pause
make -j4 TUNING=pentium kernelPentium || pause
make clean || pause
make -j4 TUNING=pentium2 kernelPentium2 || pause
make clean || pause
make -j4 TUNING=pentium3 kernelPentium3 || pause
make clean || pause
make -j4 TUNING=pentium4 kernelPentium4 || pause
make clean || pause
make -j4 TUNING=core2 kernelCore2 || pause
make clean || pause
make -j4 TUNING=nehalem kernelNehalem || pause
make clean || pause
make -j4 TUNING=westmere kernelWestmere || pause
make clean || pause
make -j4 TUNING=sandybridge kernelSandy || pause
make clean || pause
make -j4 TUNING=ivybridge kernelIvy || pause
make clean || pause
make -j4 TUNING=haswell kernelHaswell || pause
make clean || pause
make -j4 TUNING=broadwell kernelBroadwell || pause
make clean || pause
make -j4 TUNING=skylake kernelSkylake || pause
make clean || pause
make -j4 TUNING=cannonlake kernelCannonlake || pause

D:
cd D:/Users/Alex/Desktop/Banana/kernel
copy KRNL*.EXE ..\installer\root\zfiles\cdextras\krnl

cd D:/Users/Alex/Desktop/Banana
call RunBig
pause