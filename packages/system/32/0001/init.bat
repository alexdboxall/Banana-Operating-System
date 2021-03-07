cls
echo
echo Please wait while Banana installs system components...
echo
cd C:/Banana/Packages
unpack banana.cab _temp
cd ..
install _temp
echo DO NOT DELETE THIS FILE > C:/Banana/System/setupisd.one
cls
echo
echo System components have been installed. 
echo Please press ENTER to restart Banana.
echo
pause
restart