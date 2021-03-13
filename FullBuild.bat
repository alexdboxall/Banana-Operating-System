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
rem call build
cd ..\INSTALLER
rem call build
cd ..\..

cd applications
rem call build

cd ..\drivers
rem call build

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
make -j4 TUNING=pentium4 kernelPentium4 || pause
make clean || pause
make -j4 TUNING=nehalem kernelNehalem || pause
make clean || pause
make -j4 TUNING=haswell kernelHaswell || pause
make clean || pause
make -j4 TUNING=broadwell kernelBroadwell || pause

D:
cd D:/Users/Alex/Desktop/Banana/kernel
copy KRNL*.EXE ..\installer\root\zfiles\cdextras\krnl

cd D:/Users/Alex/Desktop/Banana
call RunBig
pause