#pragma once

#include <stdint.h>

class Video;
typedef Video* Screen;

void videoDrawRect(Screen scr, int x, int y, int w, int h, uint32_t colour);
void videoDrawRectDotted(Screen scr, int x, int y, int w, int h, uint32_t colour);
void videoPutpixel(Screen scr, int x, int y, uint32_t colour);
void videoDrawCursor(Screen scr, int x, int y, uint32_t* data);
uint32_t videoGetpixel(Screen scr, int x, int y);
uint32_t* videoSaveAreaUnderCursor(Screen scr, int x, int y);
