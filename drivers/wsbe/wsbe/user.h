#ifndef _USER_H_
#define _USER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "message.h"

    //================| Window Class Declaration |================//

    //Feel free to play with this 'theme'
#define WIN_BGCOLOR             0xBBBBBB //A generic grey
#define WIN_TITLECOLOR          0x000080 //A nice subtle blue
#define WIN_TITLECOLOR_INACTIVE 0x555555 //A darker shade
#define WIN_TEXTCOLOR           0xFFFFFF
#define WIN_TEXTCOLOR_INACTIVE  0xBBBBBB
#define WIN_BORDERCOLOR         0x0
#define WIN_TITLEHEIGHT         26
#define WIN_BORDERWIDTH         3

//Some flags to define our window behavior
#define WIN_NODECORATION        0x1
#define WIN_TOPLEVELWIN         0x2

//Forward struct declaration for function type declarations
    struct Window_struct;

    //Callback function type declarations
    typedef void (*WindowPaintHandler)(struct Window_struct*, int, int, List*, int);
    typedef void (*WindowMouseDownHandler)(struct Window_struct*, int, int);
    typedef void (*WindowMouseUpHandler)(struct Window_struct*, int, int);
    typedef void (*WindowMouseDragHandler)(struct Window_struct*, int, int);
    typedef void (*WindowMouseMoveHandler)(struct Window_struct*, int, int);
    typedef void (*WindowDoubleClickHandler)(struct Window_struct*, int, int);
    typedef void (*WindowResizeHandler)(struct Window_struct*, int, int);
    typedef void (*WindowMoveHandler)(struct Window_struct*, int, int);

#define DRAG_TYPE_NONE                      0
#define DRAG_TYPE_MOVE                      1
#define DRAG_TYPE_RESIZE_ALL                2
#define DRAG_TYPE_RESIZE_HZ                 3
#define DRAG_TYPE_RESIZE_VT                 4
#define DRAG_TYPE_RESIZE_HZ_LEFT            5
#define DRAG_TYPE_RESIZE_VT_TOP             6
#define DRAG_TYPE_RESIZE_ALL_BOTTOM_LEFT    7

    typedef struct Window_struct
    {
        struct Window_struct* parent;
        int16_t x;
        int16_t y;
        int16_t width;
        int16_t height;
        uint16_t flags;
        Context* context;
        Context* eventContext;
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

        int currentMouse;

        int previousMouseOverride;

        Message messages[WINDOW_MAX_MESSAGE];
        int messageCount;

        bool hasProc;
        uint8_t* repaintScript;

    } Window;

	typedef struct Rectangle
	{
		int left;
		int top;
		int right;
		int bottom;

	} Rectangle;

	typedef struct Point
	{
		int x;
		int y;
	} Point;




    //sort of internal stuff...

#define WSBE_CREATE_WINDOW          0
#define WSBE_SET_WINDOW_TITLE       1
#define WSBE_UPDATE_WINDOW          2
#define WSBE_ADD_WINDOW             3
#define WSBE_GET_DESKTOP            4
#define WSBE_SET_SCRIPT             5

    struct MoreArgs
    {
        uint16_t x;
        uint16_t y;
        uint16_t w;
        uint16_t h;

        uint32_t col;
        uint32_t flags;

        void* obj;
    };


#ifdef __cplusplus
}
#endif

#endif