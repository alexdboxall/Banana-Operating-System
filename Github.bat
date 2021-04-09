
D:
cd D:/Users/Alex/Desktop/Banana

git add *.*
git add kernel
git add firmware
git add applications
git add bochs
git add drivers
git add packages
git add sysroot
git add installer/*.txt
git add installer/*.bat
git add installer/*.s
git add installer/*.py
git add libraries/STLport-5.1.5
git add libraries/newlib-3.3.0
git add libraries/build-newlib
git add libraries/*.*

git commit -a --allow-empty-message -m ""
git remote add origin https://github.com/A22347/Banana.git
git push -u origin main

pause