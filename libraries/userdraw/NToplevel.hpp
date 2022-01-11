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
    #include "C:\Users\Alex\Desktop\Banana\kernel\sys\syscalls.hpp"
    #include "C:\Users\Alex\Desktop\Banana\drivers\clipdraw\clipdraw\userlink.h"
}

extern "C" {
    #include "context.h"
    #include "window.h"
}

#include "NLoadedBitmap.hpp"

class NRegion;

struct NxWindow {
    NiLinkWindowStruct krnlWin;
    uint32_t* framebuffer;
    Context* ctxt;
};

enum class NWindowCloseType
{
    TerminateAlways,
    TerminateIfLast,
    Destroy,
    Ignore,
};

class NTopLevel {
protected:
    friend int defaultToplevelPainter(NTopLevel* self);
    
    NxWindow nxw;
    Window* win;
    
    int x, y, w, h;

    NLoadedBitmap* winIcon = nullptr;
    
    bool destroyed = false;

public:
    char* name;
    int (*paintHandler)(NTopLevel* self);
    int (*paintHandlerHook)(NTopLevel* self);

    NTopLevel(const char* name = "Window", int width = 320, int height = 200, int flags = -1);
    virtual ~NTopLevel();

    Context* getContext();

    void setIcon(NLoadedBitmap* icn);
    void removeIcon();

    void destroy();
    
    int getX();
    int getY();
    int getWidth();
    int getHeight();

    void setTitle(const char* name);
    char* getTitle();
    
    void setX(int x);
    void setY(int y);
    void setWidth(int width);
    void setHeight(int height);
    void setPosition(int x, int y);
    void setSize(int width, int height);

    void simpleMainloop();

    void sync();
    void upsync();
    void repaint();
    void repaintFlush();
    NiEvent process();
    void initialise();
    void processMouse(int mouseX, int mouseY, int mouseB);
    void processMouse(NiEvent evnt);
    void processKeyboard(KeyStates ks);
    void processKeyboard(NiEvent evnt);

    void defaultEventHandler(NiEvent evnt);

    void remove(NRegion* rgn);
    void add(NRegion* rgn);
};

#endif /* NToplevel_hpp */
