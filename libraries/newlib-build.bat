echo RECONFIGURE PASSING --enable-newlib-long-time_t AS A CONFIGURE ARGUMENT TO MAKE time_t 64 bit
pause

D:
cd D:/Users/Alex/Desktop/Banana/libraries/build-newlib

rem ../newlib-3.0.0/configure --prefix=/usr --target=i386-banana --enable-newlib-long-time_t
rem ../newlib-3.3.0/configure --prefix=/usr --target=i386-banana --enable-newlib-long-time_t --enable-lto

make all
make DESTDIR=D:/Users/Alex/Desktop/Banana/sysroot/Banana/Dev32 install
cp -ar D:/Users/Alex/Desktop/Banana/sysroot/Banana/Dev32/usr/i386-banana/*              D:/Users/Alex/Desktop/Banana/sysroot/Banana/Dev32/usr/
cp     D:/Users/Alex/Desktop/Banana/sysroot/Banana/Dev32/usr/i386-banana/lib/crt0.o     D:/Users/Alex/Desktop/Banana/sysroot/Banana/Dev32/startfiles/
pause