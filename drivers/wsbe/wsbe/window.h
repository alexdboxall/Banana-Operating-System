#ifndef WINDOW_H
#define WINDOW_H 

#include "context.h"
#include <inttypes.h>
#include <stdbool.h>

//================| Window Class Declaration |================//

//Feel free to play with this 'theme'
#define WIN_BGCOLOR             0xBBBBBB //A generic grey
#define WIN_TITLECOLOR          0x000080 //A nice subtle blue
#define WIN_TITLECOLOR_INACTIVE 0x808080 //A darker shade
#define WIN_TEXTCOLOR           0xFFFFFF
#define WIN_TEXTCOLOR_INACTIVE  0xFFFFFF
#define WIN_BORDERCOLOR         0x0
#define WIN_TITLEHEIGHT         31
#define WIN_BORDERWIDTH         3

//Some flags to define our window behavior
#define WIN_NODECORATION        0x1
#define WIN_TOPLEVELWIN         0x2

//Forward struct declaration for function type declarations
struct Window_struct;

//Callback function type declarations
typedef void (*WindowPaintHandler)(struct Window_struct*);
typedef void (*WindowMouseDownHandler)(struct Window_struct*, int, int);
typedef void (*WindowMouseUpHandler)(struct Window_struct*, int, int);
typedef void (*WindowMouseDragHandler)(struct Window_struct*, int, int);
typedef void (*WindowMouseMoveHandler)(struct Window_struct*, int, int);
typedef void (*WindowDoubleClickHandler)(struct Window_struct*, int, int);
typedef void (*WindowResizeHandler)(struct Window_struct*, int, int);
typedef void (*WindowMoveHandler)(struct Window_struct*, int, int);

#define DRAG_TYPE_NONE          0
#define DRAG_TYPE_MOVE          1
#define DRAG_TYPE_RESIZE_ALL    2

typedef struct Window_struct {  
    struct Window_struct* parent;
    int16_t x;
    int16_t y;
    int16_t width;
    int16_t height;
    uint16_t flags;
    Context* context;
    struct Window_struct* desktop;
    struct Window_struct* drag_child;
    struct Window_struct* active_child;
    List* children;
    int16_t drag_off_x;
    int16_t drag_off_y;
    int dragType;
    uint8_t last_button_state;
    WindowPaintHandler paint_function;
    WindowMouseDownHandler mousedown_function;
    WindowMouseDragHandler mousemove_function;
    WindowMouseMoveHandler mousedrag_function;
    WindowMouseUpHandler mouseup_function;
    WindowDoubleClickHandler doubleclick_function;
    WindowResizeHandler resize_function;
    WindowMoveHandler move_function;
    char* title;

    int16_t restoreWidth;
    int16_t restoreHeight;
    int16_t restoreX;
    int16_t restoreY;
    bool fullscreen;

    uint64_t nanoLastClicked;

    uint8_t* savedMouse;
    
} Window;

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
void Window_paint_handler(Window* window);
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
void Window_append_title(Window* window, char* additional_chars);
void Window_update_title(Window* window);

#endif //WINDOW_H
