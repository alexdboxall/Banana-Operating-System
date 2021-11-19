D:
cd D:/Users/Alex/Desktop/Banana/libraries/build-mlibc

meson build ../mlibc-master -Dstatic=true -Ddisable_posix_option=false -Ddisable_linux_option=false --cross-file ../mlibc-master/crossfile.txt
cd build
ninja
pause
exit

rem THEN IN BASH

export DESTDIR=D:/Users/Alex/Desktop/Banana/sysroot/Banana/Dev32/usr
cd D:/Users/Alex/Desktop/Banana/libraries/build-mlibc/build
meson install