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

rem git add *.*
git add LICENSE
git add COPYRIGHT
git add README.md
git add kernel -f
git add firmware
git add bochs
git commit -a --allow-empty-message -m ""
git remote add origin https://github.com/A22347/Banana.git
rem git push -u origin main

cd kernel
cp crti.322 crti.32
cp crtn.322 crtn.32

make clean || pause
cp crti.322 crti.32
cp crtn.322 crtn.32
make -j4 kernel486 MARCH=i486 TUNING=i486 || (pause && exit)

make clean || pause
cp crti.322 crti.32
cp crtn.322 crtn.32
make -j4 kernelPentium2 MARCH=pentium4 TUNING=pentium2 || (pause && exit)


cd D:/Users/Alex/Desktop/Banana/kernel
python easteregg.py.bin
pause

cd D:/Users/Alex/Desktop/Banana
rm disasms/disasm.txt
rm disasms/disasm2.txt
rm disasms/disacpica.txt
rm disasms/dislegacy.txt
rm disasms/diswsbe.txt
rm disasms/dis87.txt
rm disasms/disboot.txt
objdump -drwC -Mintel kernel/KERNEL32.EXE >> disasms/disasm.lst
objdump -drwC -Mintel kernel/KRNLP2.EXE >> disasms/disasm2.lst
objdump -drwC -Mintel packages/banana/32/0002/acpica.sys >> disasms/disacpica.txt
objdump -drwC -Mintel packages/system/32/0002/legacy.sys >> disasms/dislegacy.txt
ndisasm -b16 kernel/STAGE1.BIN >> disboot.lst
call Run
pause