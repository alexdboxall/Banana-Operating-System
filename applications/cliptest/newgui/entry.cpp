
#include <stdio.h>
#include <string.h>
#include <uclip/userclip.hpp>
extern "C" {
    #include <unistd.h>
    #include <dirent.h>
}

extern "C" int main(int argc, char** argv) {

    Window* myWindow = new Window(100, 100, 200, 100, "Window from userspace!");
    myWindow->setParentAsDesktop();
    myWindow->raise();

    while (1) {

    }
    
    return 0;
}

