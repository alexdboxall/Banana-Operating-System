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
cd D:/Users/Alex/Desktop/Banana/

echo dummy > qemuinhibit.txt

call Run

D:
cd D:\Users\Alex\Desktop\Banana\installer
call build.bat

D:
cd D:\Users\Alex\Desktop\Banana\installer

del Floppy\DATA1.BIN
del Floppy\DATA2.BIN
del Floppy\DATA3.BIN
del Floppy\DATA4.BIN
del Floppy\DATA5.BIN
del Floppy\DATA6.BIN
del Floppy\DATA7.BIN
del Floppy\DATA8.BIN
del Floppy\DATA9.BIN
call floppybuild.bat

D:
cd D:\Users\Alex\Desktop\Banana
cd Products
del /s /q *.*
cd ..

copy installer\DISK*.IMG Products\
copy ..\banana-os\newimage.img products\newimage.img
copy installer\BANANA.ISO Products\BANANA.ISO

del qemuinhibit.txt

echo DONE!
pause