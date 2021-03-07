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

git add *.*
git add kernel
git add firmware
git add bochs
git commit -a --allow-empty-message -m ""
git remote add origin https://github.com/A22347/Banana.git
git push -u origin main
 
cd kernel
cp crti.322 crti.32
cp crtn.322 crtn.32

rem make clean || pause
cp crti.322 crti.32
cp crtn.322 crtn.32
make -j4 kernel386 TUNING=i386 || (pause && exit)

rem make clean || pause
rem cp crti.322 crti.32
rem cp crtn.322 crtn.32
rem make -j1 TUNING=i386 kernel386NoACPI ACPI=-DJUMPER32 || pause

cd D:/Users/Alex/Desktop/Banana
rm disasm.txt
rm disacpica.txt
rm dislegacy.txt
rm diswsbe.txt
rm dis87.txt
objdump -drwC -Mintel kernel/KERNEL32.EXE >> disasm.txt
objdump -drwC -Mintel packages/banana/32/0002/acpica.sys >> disacpica.txt
objdump -drwC -Mintel packages/system/32/0002/legacy.sys >> dislegacy.txt
objdump -drwC -Mintel packages/banana/32/0001/wsbe.sys >> diswsbe.txt
objdump -drwC -Mintel packages/system/32/0002/em8087.sys >> dis87.txt

call Run
pause