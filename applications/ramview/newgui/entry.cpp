
#include <stdio.h>
#include <string.h>
#include <udraw/banana.hpp>
extern "C" {
    #include <unistd.h>
    #include <dirent.h>
}

extern "C" int main(int argc, char** argv) {
    createSystemBrushes();

    NTopLevel* rootWindow = new NTopLevel("RAM Viewer", 280, 130, WIN_FLAGS_DEFAULT_0 | WIN_FLAGS_0_HIDDEN | WIN_FLAGS_0_PRETTY | WIN_FLAGS_0_NO_RESIZE);
    rootWindow->initialise();

    NTextField* nt = new NTextField(30, 30, 200, 70, rootWindow);
    rootWindow->add(nt);

    while (1) {        
        NiEvent evnt = rootWindow->process();

        extern uint64_t SystemCall(size_t, size_t, size_t, size_t);
        uint32_t r = SystemCall((size_t) SystemCallNumber::GetRAMData, 0, 0, 0);

        uint64_t totalPages = r & 0xFFFFFF;
        int percent = (r >> 24);

        uint64_t usedPages = totalPages;
        usedPages *= percent;
        usedPages /= 200;

        char text[256];
        if (totalPages >= 64 * 1024) {
            sprintf(text, "%d of %d MB used.\n%d%% used\n", (uint32_t) (usedPages / 1024 * 4), (uint32_t) (totalPages / 1024 * 4), percent / 2);
        } else {
            sprintf(text, "%d of %d KB used.\n%d%% used\n", (uint32_t) (usedPages * 4), (uint32_t) (totalPages * 4), percent / 2);
        }

        nt->setText(text);

        switch (evnt.type) {
        default:
            rootWindow->defaultEventHandler(evnt);
            break;
        }
    }
    
    return 0;
}

