#pragma once

#include <stdint.h>

class Video;
typedef Video* Screen;

void videoDrawRect(Screen scr, int x, int y, int w, int h, uint32_t colour);
void videoDrawRectDotted(Screen scr, int x, int y, int w, int h, uint32_t colour);
void videoPutpixel(Screen scr, int x, int y, uint32_t colour);
void videoDrawCursor(Screen scr, int x, int y, uint32_t* data);
void videoReloadSavedBehindCursor(Screen scr, int mouse_x, int mouse_y);
void videoSaveBehindCursor(Screen scr, int mouse_x, int mouse_y);
void videoInvalidateSavedCursor();