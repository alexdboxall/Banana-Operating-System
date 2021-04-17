#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <stdint.h>
#include <stdbool.h>

#define WINDOW_MAX_MESSAGE      16

#define MESSAGE_NULL            0
#define MESSAGE_PAINT           1
#define MESSAGE_RESIZING        2
#define MESSAGE_RESIZED         3
#define MESSAGE_MOVING          4
#define MESSAGE_MOVED           5
#define MESSAGE_LBUTTON_DOWN    6
#define MESSAGE_LBUTTON_UP      7
#define MESSAGE_MBUTTON_DOWN    8
#define MESSAGE_MBUTTON_UP      9
#define MESSAGE_RBUTTON_DOWN    10
#define MESSAGE_RBUTTON_UP      11
#define MESSAGE_MOUSE_MOVE      12
#define MESSAGE_MOUSE_DRAG      13
#define MESSAGE_CREATE          14
#define MESSAGE_DESTROY         15
#define MESSAGE_SCROLLWHEEL     16
#define MESSAGE_KEYDOWN         17
#define MESSAGE_KEYUP           18
#define MESSAGE_LBUTTON_DOUBLE  19
#define MESSAGE_MBUTTON_DOUBLE  20
#define MESSAGE_RBUTTON_DOUBLE  21
#define MESSAGE_MOUSE_ENTER     22
#define MESSAGE_MOUSE_LEAVE     23
#define MESSAGE_TIMER           24
#define MESSAGE_GETTEXT         25
#define MESSAGE_FOCUS_ENTER     26
#define MESSAGE_FOCUS_LEAVE     27
#define MESSAGE_CURSOR_BLINK    28


typedef struct Message
{
    uint8_t type : 8;

    uint8_t lbutton : 1;
    uint8_t mbutton : 1;
    uint8_t rbutton : 1;
    uint8_t ctrl : 1;
    uint8_t alt : 1;
    uint8_t shift : 1;
    uint8_t keyrelease : 1;
    uint8_t paintChildren: 1;

    void* window;

    union
    {
        struct
        {
            int dispx;
            int dispy;
            void* dr;
        };
        struct
        {
            uint16_t mousex;
            uint16_t mousey;

            uint16_t scrollx : 4;
            uint16_t scrolly : 4;
            uint16_t : 8;
        };
        struct
        {
            uint16_t key;
        };
        /*struct
        {
            Timer* timerPtr;
        };*/
        struct
        {
            char* textPtr;
        };
    };

} Message;

#endif