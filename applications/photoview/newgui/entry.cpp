
#include <stdio.h>
#include <string.h>
#include <udraw/banana.hpp>

extern "C" int main(int argc, char** argv) {
    if (argc != 2) return 1;

    createSystemBrushes();

    NLoadedBitmap* bmp = new NLoadedBitmap(argv[1]);
    
    NTopLevel* mainwin = new NTopLevel("Photo Viewer", bmp->width + 40, bmp->height + 65, WIN_FLAGS_DEFAULT_0 | WIN_FLAGS_0_HIDDEN | WIN_FLAGS_0_PRETTY | WIN_FLAGS_0_NO_RESIZE);

    NImageViewer* imgview = new NImageViewer(20, 45, mainwin, bmp, bmp->width, bmp->height);

    mainwin->add(imgview);
    mainwin->initialise();

    while (1) {
        mainwin->defaultEventHandler(mainwin->process());
    }
    
    return 0;
}

