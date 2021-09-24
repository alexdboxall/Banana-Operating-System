//
//  NRegion.cpp
//  NGUI
//
//  Created by Alex Boxall on 16/9/21.
//  Copyright © 2021 Alex Boxall. All rights reserved.
//

#include "NRegion.hpp"
#include "NToplevel.hpp"

void Region_paint_handler(Window* desktop_window, void* v) {
    auto handler = ((NRegion*) v)->paintHandler;
    if (handler) {
        handler((NRegion*) v);
    }
}

NRegion::NRegion(int _x, int _y, int w, int h, Context* context) {
    ctxt = context;
    
    x = _x;
    y = _y;
    width = w;
    height = h;
    
    win = (Window*)malloc(sizeof(Window));
    Window_init((Window*)win, x, y, w, h, WIN_NODECORATION, ctxt);
    win->paint_function = Region_paint_handler;
    win->paint_function_args = (void*) this;
}

Context* NRegion::getContext() {
    return ctxt;
}

void NRegion::add(NRegion* rgn) {
    Window_insert_child(win, rgn->win);
}

void NRegion::fillRect(int x, int y, int w, int h, uint32_t col) {
    Context_fill_rect(ctxt, x, y, w, h, col);
}

void NRegion::drawRect(int x, int y, int w, int h, uint32_t col) {
    Context_draw_rect(ctxt, x, y, w, h, col);
}

void NRegion::horizontalLine(int x, int y, int w, uint32_t col) {
    Context_horizontal_line(ctxt, x, y, w, col);
}

void NRegion::verticalLine(int x, int y, int h, uint32_t col) {
    Context_vertical_line(ctxt, x, y, h, col);
}

void NRegion::drawBasicText(int x, int y, uint32_t col, const char* text) {
    Context_draw_text(ctxt, (char*) text, x, y, col);
}
