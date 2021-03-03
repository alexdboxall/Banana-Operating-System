#ifndef BITMAP_H
#define BITMAP_H

#include "window.h"

struct Bitmap_struct;

typedef struct Bitmap_struct
{
    Window window;
    uint32_t* data;

} Bitmap;

Bitmap* Bitmap_new(int x, int y, int w, int h, uint32_t* data);
void Bitmap_paint(Window* bitmap_window);

#endif //BUTTON_H
