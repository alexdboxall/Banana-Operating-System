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
#define WIN_NORESIZING          0x4

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

#define OP_FILL_RECT		0
#define OP_DRAW_RECT		1
#define OP_HORZ_LINE		2
#define OP_VERT_LINE		3
#define OP_DRAW_TEXT		4
#define OP_DRAW_BITMAP		5
#define OP_VARIABLE			6
#define OP_DEFAULT_VARS		7
#define OP_END				8
#define OP_VARIABLE2		9

#define OP_VARIABLE_SET		0
#define OP_VARIABLE_ADD		1
#define OP_VARIABLE_SUB		2
#define OP_VARIABLE_MUL		3
#define OP_VARIABLE_DIV		4
#define OP_VARIABLE_AND		5
#define OP_VARIABLE_OR		6
#define OP_VARIABLE_XOR		7
#define OP_VARIABLE_SHL		8
#define OP_VARIABLE_SHR		9
#define OP_VARIABLE_MOD		10
#define OP_VARIABLE_REG		11
#define OP_VARIABLE_NOT		12
#define OP_VARIABLE_NEG		13
#define OP_VARIABLE_SLIDE	14

#define WSBE_CREATE_WINDOW          0
#define WSBE_SET_WINDOW_TITLE       1
#define WSBE_UPDATE_WINDOW          2
#define WSBE_ADD_WINDOW             3
#define WSBE_GET_DESKTOP            4
#define WSBE_SET_SCRIPT             5
#define WSBE_COPY_WINDOW            6
#define WSBE_TEXT_WIDTH_HEIGHT      7

    struct MoreArgs
    {
        uint16_t x;
        uint16_t y;
        uint16_t w;
        uint16_t h;

        uint32_t col;
        uint32_t flags;

        void* obj;
        void* obj2;
        void* obj3;
    };


#ifdef __cplusplus
}
#endif

#endif