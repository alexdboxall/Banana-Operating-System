
D:
cd D:/Users/Alex/Desktop/Banana
cd kernel
cp crti.322 crti.32
cp crtn.322 crtn.32
cd ..
git add *.*
git add COPYRIGHT
git add LICENSE
git add kernel -f
git add firmware
git add applications
git add bochs
git add drivers
git add doc
git add packages -f
git add sysroot
git add ip
git add installer/*.txt -f
git add installer/*.bat -f
git add installer/*.s -f
git add installer/*.py -f
git add installer/*.vbs -f
git add libraries/newlib-3.3.0 -f
git add libraries/userdraw -f

git commit -a --allow-empty-message -m ""
git remote add origin https://github.com/A22347/Banana-Operating-System.git
git push -u origin main

pause