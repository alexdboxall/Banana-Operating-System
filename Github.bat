
D:
cd D:/Users/Alex/Desktop/Banana

rem forfiles /s /c "cmd /q /c if @fsize GTR 52428800 echo @relpath" >> .gitignore

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

git commit -m "Initial commit"
rem -a --allow-empty-message -m ""
git remote add origin https://github.com/A22347/Banana.git
git branch -M main
git push -u origin main

pause