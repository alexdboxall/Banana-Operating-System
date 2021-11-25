
#include <stdio.h>
#include <string.h>
#include <udraw/banana.hpp>
extern "C" {
    #include <unistd.h>
    #include <dirent.h>
}

int consolePaintHandler(NTopLevel* self) {
    Context_fill_rect(self->getContext(), 20, 40, 80 * 8, 25 * 16, 0x000000);
    return 0;
}

extern "C" int main() {
    createSystemBrushes();

    NTopLevel* win = new NTopLevel("Console", 680, 460, WIN_FLAGS_DEFAULT_0 | WIN_FLAGS_0_HIDDEN | WIN_FLAGS_0_PRETTY);
    win->paintHandlerHook = consolePaintHandler;
    win->initialise();

    while (1) {        
        NiEvent evnt = win->process();
        switch (evnt.type) {

        default:
            win->defaultEventHandler(evnt);
            break;
        }
    }
    
    return 0;
}

