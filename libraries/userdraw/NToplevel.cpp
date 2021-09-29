//
//  NToplevel.cpp
//  NGUI
//
//  Created by Alex Boxall on 16/9/21.
//  Copyright © 2021 Alex Boxall. All rights reserved.
//

#include "NToplevel.hpp"
#include "NRegion.hpp"
#include <string.h>

void* operator new(size_t size)
{
    return malloc(size);
}

void* operator new[](size_t size)
{
    return malloc(size);
}

void operator delete(void* p)
{
    free(p);
}

void operator delete[](void* p)
{
    free(p);
}

void operator delete(void* p, unsigned long)
{

}

void operator delete[](void* p, unsigned long)
{

}


extern "C" uint64_t SystemCall(size_t, size_t, size_t, size_t);

NxWindow NxCreateWindow(int w, int h, const char* name) {
    NiLinkWindowStruct krnlWin;
    krnlWin.x = 200;
    krnlWin.y = 200;
    krnlWin.w = w;
    krnlWin.h = h;
    krnlWin.flags[0] = WIN_FLAGS_DEFAULT_0;
    krnlWin.flags[0] |= WIN_FLAGS_0_HIDE_ON_INVALIDATE /* | WIN_FLAGS_0_DRAW_OUTLINE_INSTEAD_OF_SHADOW | WIN_FLAGS_0_FORCE_RECTANGULAR*/;
    krnlWin.buffer = (uint32_t*) malloc(krnlWin.w * krnlWin.h * 4);
    strcpy(krnlWin.name, "This is a test!");
    memset(krnlWin.buffer, 0xFF, krnlWin.w * krnlWin.h * 4);
    SystemCall((size_t) SystemCallNumber::WSBE, LINKCMD_CREATE_WINDOW, 0, (size_t) &krnlWin);

    Context* context = Context_new(w, h, krnlWin.buffer);

    NxWindow ret;
    ret.framebuffer = krnlWin.buffer;
    ret.ctxt = context;
    ret.krnlWin = krnlWin;

    return ret;
}

int defaultToplevelPainter(NTopLevel* self) {
    Context* ctxt = self->getContext();

    Context_fill_rect(ctxt, 0, 25, ctxt->width, ctxt->height - 25, 0xD0D0D0);
    
    if (self->paintHandlerHook) {
        self->paintHandlerHook(self);
    }
    
    Context_fill_rect(ctxt, 0, 0, ctxt->width, 25, 0xFFFFFF);
    Context_draw_text(ctxt, self->name, 15, 6, 0x000000);
    
    return 0;
}

void Toplevel_paint_handler(Window* desktop_window, void* v) {
    auto handler = ((NTopLevel*) v)->paintHandler;
    if (handler) {
        handler((NTopLevel*) v);
    }
}

Context* NTopLevel::getContext() {
    return win->context;
}

NTopLevel::NTopLevel(const char* nam, int width, int height)
{
    w = width;
    h = height;

    name = (char*) malloc(strlen(nam));
    strcpy(name, nam);

    nxw = NxCreateWindow(w, h, name);

    win = (Window*) malloc(sizeof(Window));
    Window_init((Window*) win, 0, 0, nxw.ctxt->width, nxw.ctxt->height, WIN_NODECORATION, nxw.ctxt);
    win->paint_function = Toplevel_paint_handler;
    win->paint_function_args = (void*) this;

    paintHandler = defaultToplevelPainter;
    paintHandlerHook = nullptr;
}

int NTopLevel::getX() {
    return x;
}

int NTopLevel::getY() {
    return y;
}

int NTopLevel::getWidth() {
    return w;
}

int NTopLevel::getHeight() {
    return h;
}
    
void NTopLevel::setX(int _x) {
    x = _x;

    //you need to write an upsync() function
}

void NTopLevel::setY(int _y) {
    y = _y;

    //you need to write an upsync() function
}

void NTopLevel::setWidth(int width) {
    w = width;

    //you need to write an upsync() function
}

void NTopLevel::setHeight(int height) {
    h = height;

    //you need to write an upsync() function
}

void NTopLevel::sync() {
    SystemCall((size_t) SystemCallNumber::WSBE, LINKCMD_READ_FLAGS, 0, (size_t) &nxw.krnlWin);
    
    int oldSize = w * h;
    int newSize = nxw.krnlWin.w * nxw.krnlWin.h;

    w = nxw.krnlWin.w;
    h = nxw.krnlWin.h;
    x = nxw.krnlWin.x;
    y = nxw.krnlWin.y;
    
    if (newSize > oldSize) {
        nxw.krnlWin.buffer = (uint32_t*) realloc(nxw.krnlWin.buffer, w * h * 4);
        nxw.ctxt->buffer = nxw.krnlWin.buffer;
        nxw.framebuffer = nxw.krnlWin.buffer;
    }
   
    nxw.ctxt->width = nxw.krnlWin.w;
    nxw.ctxt->height = nxw.krnlWin.h;

    win->width = w;
    win->height = h;
}

void NTopLevel::defaultEventHandler(NiEvent evnt)
{
    switch (evnt.type) {
    case EVENT_TYPE_MOUSE_MOVE:
    case EVENT_TYPE_MOUSE_DRAG:
    case EVENT_TYPE_MOUSE_DOWN:
    case EVENT_TYPE_MOUSE_UP:
    case EVENT_TYPE_RMOUSE_DOWN:
    case EVENT_TYPE_RMOUSE_UP:
    {
        processMouse(evnt);
        repaintFlush();
        break;
    }

    case EVENT_TYPE_KEYDOWN:
    {
        processKeyboard(evnt);
        repaintFlush();
        break;
    }

    case EVENT_TYPE_NULL:
        break;

    default:
        if (evnt.needsRedraw) repaint();
        break;
    }
}

void NTopLevel::simpleMainloop()
{
    initialise();

    while (1) {
        NiEvent evnt = process();

        switch (evnt.type) {

        default:
            defaultEventHandler(evnt);
            break;
        }
    }
}

void NTopLevel::processKeyboard(KeyStates key)
{
    Window_process_key(win, key);
}

void NTopLevel::processKeyboard(NiEvent evnt)
{
    KeyStates ks;
    ks.key = evnt.key;
    ks.ctrl = evnt.ctrl;
    ks.alt = evnt.alt;
    ks.shift = evnt.shift;
    processKeyboard(ks);
}

void NTopLevel::processMouse(int mouseX, int mouseY, int mouseB)
{
    Window_process_mouse(win, mouseX, mouseY, mouseB);
}

void NTopLevel::processMouse(NiEvent evnt)
{
    processMouse(evnt.mouseX - x, evnt.mouseY - y, evnt.mouseButtons);
}

void NTopLevel::repaintFlush()
{
    uint8_t* invl = win->context->invalidatedScanlines;

    int start = -1;
    for (int i = 0; i < win->context->height; ++i) {
        if (invl[i >> 3] & (1 << (i & 7))) {
            if (start == -1) {
                start = i;
            }
        } else {
            if (start != -1) {
                int end = i;
                size_t scanValue = start | (end << 16);
                SystemCall((size_t) SystemCallNumber::WSBE, LINKCMD_RESUPPLY_SCANLINE, scanValue, (size_t) &nxw.krnlWin);
                start = -1;
            }
        }
    }
    if (start != -1) {
        int end = win->context->height;
        size_t scanValue = start | (end << 16);
        SystemCall((size_t) SystemCallNumber::WSBE, LINKCMD_RESUPPLY_SCANLINE, scanValue, (size_t) &nxw.krnlWin);
        start = -1;
    }

    memset(win->context->invalidatedScanlines, 0, sizeof(win->context->invalidatedScanlines));
}

void NTopLevel::repaint() {
    Window_paint(win, (List*)0, 1);
    repaintFlush();
}

NiEvent NTopLevel::process() {
    int events = SystemCall((size_t) SystemCallNumber::WSBE, LINKCMD_GET_EVENTS, 0, (size_t) &nxw.krnlWin);
    if (events < 0) {
        NiEvent dmy;
        dmy.type = EVENT_TYPE_NULL;
        dmy.needsRedraw = false;
        return dmy;
    }
    
    if (nxw.krnlWin.evnt.needsRedraw) {
        sync();
    }

    return nxw.krnlWin.evnt;
}

void NTopLevel::add(NRegion* rgn) {
    Window_insert_child(win, rgn->win);
}

void NTopLevel::initialise()
{
    nxw.krnlWin.flags[0] &= ~WIN_FLAGS_0_HIDDEN;
    SystemCall((size_t) SystemCallNumber::WSBE, LINKCMD_UPDATE_FLAGS, 0, (size_t) &nxw.krnlWin);
    SystemCall((size_t) SystemCallNumber::WSBE, LINKCMD_REDRAW, 0, (size_t) &nxw.krnlWin);
    sync();
    repaint();
}