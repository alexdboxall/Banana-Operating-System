#ifndef WINDOW_H
#define WINDOW_H 

#include "context.h"
#include <inttypes.h>
#include <stdbool.h>
#include "user.h"

//Methods
Window* Window_new(int16_t x, int16_t y, uint16_t width,
                   uint16_t height, uint16_t flags, Context* context);
int Window_init(Window* window, int16_t x, int16_t y, uint16_t width,
                uint16_t height, uint16_t flags, Context* context);
int Window_screen_x(Window* window);
int Window_screen_y(Window* window);                   
void Window_paint(Window* window, List* dirty_regions, uint8_t paint_children);
void Window_process_mouse(Window* window, uint16_t mouse_x,
                          uint16_t mouse_y, uint8_t mouse_buttons);
void Window_paint_handler(Window* window, int sx, int sy, List* dr, int pc);
void Window_mousedown_handler(Window* window, int x, int y);
void Window_move_handler(Window* window, int x, int y);
void Window_resize_handler(Window* window, int x, int y);
List* Window_get_windows_above(Window* parent, Window* child);
List* Window_get_windows_below(Window* parent, Window* child);
void Window_raise(Window* window, uint8_t do_draw);
void Window_resize(Window* window, int new_w, int new_h);
void Window_move(Window* window, int new_x, int new_y);
Window* Window_create_window(Window* window, int16_t x, int16_t y,  
                             uint16_t width, int16_t height, uint16_t flags);
void Window_insert_child(Window* window, Window* child);   
void Window_invalidate(Window* window, int top, int left, int bottom, int right); 
void Window_set_title(Window* window, char* new_title);                       
void Window_update_title(Window* window);
void Window_paint_children(Window* window, List* dirty_regions);
List* Window_paint_wrapper(Window* window, List* dirty_regions, uint8_t paint_children);

#endif //WINDOW_H
