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
git add LICENSE
git add COPYRIGHT
git add README.md
git add kernel -f
git add firmware
git add bochs
git commit -a --allow-empty-message -m ""
git remote add origin https://github.com/A22347/Banana.git
git push -u origin main
 
cd kernel
cp crti.322 crti.32
cp crtn.322 crtn.32

make clean || pause
cp crti.322 crti.32
cp crtn.322 crtn.32
make -j4 kernel486 TUNING=i486 || (pause && exit)

make clean || pause
cp crti.322 crti.32
cp crtn.322 crtn.32
make -j4 kernelPentium2 TUNING=pentium2 || (pause && exit)


cd D:/Users/Alex/Desktop/Banana
rm disasm.txt
rm disasm2.txt
rm disacpica.txt
rm dislegacy.txt
rm diswsbe.txt
rm dis87.txt
rm disboot.txt
objdump -drwC -Mintel kernel/KERNEL32.EXE >> disasm.txt
objdump -drwC -Mintel kernel/KRNLP2.EXE >> disasm2.txt
objdump -drwC -Mintel packages/banana/32/0002/acpica.sys >> disacpica.txt
objdump -drwC -Mintel packages/system/32/0002/legacy.sys >> dislegacy.txt
ndisasm -b16 kernel/STAGE1.BIN >> disboot.txt
call Run
pause