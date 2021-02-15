#ifndef DESKTOP_H
#define DESKTOP_H

#include "list.h"
#include "context.h"
#include "window.h"


//================| Desktop Class Declaration |================//

//Information for drawing a pretty mouse
#define MOUSE_WIDTH 32
#define MOUSE_HEIGHT 32
#define MOUSE_BUFSZ (MOUSE_WIDTH * MOUSE_HEIGHT)

#define MAX_CURSOR_TYPES 8
#define CURSOR_DATA_SIZE (MOUSE_WIDTH * MOUSE_HEIGHT / 8 * 2)

#define MOUSE_OFFSET_NORMAL		CURSOR_DATA_SIZE * 0;
#define MOUSE_OFFSET_TEXT		CURSOR_DATA_SIZE * 1;
#define MOUSE_OFFSET_WAIT		CURSOR_DATA_SIZE * 2;
#define MOUSE_OFFSET_TLDR		CURSOR_DATA_SIZE * 3;

typedef struct Desktop_struct {
    Window window; //Inherits window class
    uint16_t mouse_x;
    uint16_t mouse_y;
} Desktop;

extern uint8_t mouse_data[CURSOR_DATA_SIZE * MAX_CURSOR_TYPES];

//Methods
Desktop* Desktop_new(Context* context);
void Desktop_paint_handler(Window* desktop_window);
void Desktop_process_mouse(Desktop* desktop, uint16_t mouse_x,
                           uint16_t mouse_y, uint8_t mouse_buttons);

#endif //DESKTOP_H
