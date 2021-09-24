//
//  NToplevel.hpp
//  NGUI
//
//  Created by Alex Boxall on 16/9/21.
//  Copyright © 2021 Alex Boxall. All rights reserved.
//

#ifndef NToplevel_hpp
#define NToplevel_hpp

#include <stdio.h>

extern "C" {
    #include "D:\Users\Alex\Desktop\Banana\kernel\sys\syscalls.hpp"
    #include "D:\Users\Alex\Desktop\Banana\drivers\clipdraw\clipdraw\userlink.h"
}

extern "C" {
    #include "context.h"
    #include "window.h"
}

class NRegion;

struct NxWindow {
    NiLinkWindowStruct krnlWin;
    uint32_t* framebuffer;
    Context* ctxt;
};

class NTopLevel {
protected:
    NxWindow nxw;
    Window* win;
    
    int x, y, w, h;
    
public:
    char* name;
    int (*paintHandler)(NTopLevel* self);
    int (*paintHandlerHook)(NTopLevel* self);

    NTopLevel(const char* name = "Window", int width = 320, int height = 200);
    
    Context* getContext();
    
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    
    void setX(int x);
    void setY(int y);
    void setWidth(int width);
    void setHeight(int height);

    void sync();
    void repaint();
    void repaintFlush();
    NiEvent process();
    void initialise();
    void processMouse(int mouseX, int mouseY, int mouseB);
    void processMouse(NiEvent evnt);
    
    void add(NRegion* rgn);
};

#endif /* NToplevel_hpp */
