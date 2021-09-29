#ifndef CONTEXT_H
#define CONTEXT_H

#include <inttypes.h>
#include <stdint.h>
#include "list.h"
#include "rect.h"

//================| Context Class Declaration |================//

//A structure for holding information about a framebuffer
typedef struct Context_struct {  
    uint32_t* buffer; //A pointer to our framebuffer
    uint16_t width; //The dimensions of the framebuffer
    uint16_t height; 
    int translate_x; //Our new translation values
    int translate_y;
    List* clip_rects;
    uint8_t clipping_on;
    uint8_t invalidatedScanlines[560];      //supports 8K monitors

} Context;

//Methods
Context* Context_new(uint16_t width, uint16_t height, uint32_t* buffer);
void Context_fill_rect(Context* context, int x, int y,  
                       unsigned int width, unsigned int height, uint32_t color);
void Context_horizontal_line(Context* context, int x, int y,
                             unsigned int length, uint32_t color);
void Context_vertical_line(Context* context, int x, int y,
                           unsigned int length, uint32_t color);                                                   
void Context_draw_rect(Context* context, int x, int y,
                       unsigned int width, unsigned int height, uint32_t color);
void Context_intersect_clip_rect(Context* context, Rect* rect);                       
void Context_subtract_clip_rect(Context* context, Rect* subtracted_rect);                       
void Context_add_clip_rect(Context* context, Rect* rect);
void Context_clear_clip_rects(Context* context);
void Context_draw_text(Context* context, char* string, int x, int y, uint32_t color);
void Context_bound_text(Context* context, char* string, int* x, int* y);
void Context_draw_bitmap(Context* context, uint32_t* data, int x, int y, int w, int h);

#define BRUSH_STOCK_BLACK               0xE0000000
#define BRUSH_STOCK_DARK_GREY           0xE0000001
#define BRUSH_STOCK_GREY                0xE0000002
#define BRUSH_STOCK_LIGHT_GREY          0xE0000003
#define BRUSH_STOCK_WHITE               0xE0000004
#define BRUSH_STOCK_NULL                0xE0000005
#define BRUSH_HATCH_FORWARD_DIAGONAL    0xE0000006
#define BRUSH_HATCH_BACKWARD_DIAGONAL   0xE0000007
#define BRUSH_HATCH_CROSS               0xE0000008
#define BRUSH_HATCH_DIAGONAL_CROSS      0xE0000009
#define BRUSH_HATCH_HORIZONTAL          0xE000000A
#define BRUSH_HATCH_VERTICAL            0xE000000B
#define BRUSH_DITHER_HALF               0xE000000C
#define BRUSH_DITHER_QUARTER            0xE000000D
#define BRUSH_DITHER_THREE_QUARTERS     0xE000000E
#define BRUSH_DITHER_DOUBLE             0xE000000F

#define BRUSH_FIRST_USER_BRUSH          0xE0000010

typedef struct Brush {
    uint32_t fg;
    uint32_t bg;
    
    uint8_t pattern[7];
    uint8_t patternWidth : 4;
    uint8_t patternHeight : 4;
} Brush;

uint32_t createBrush(Brush b);
void freeBrush(uint32_t b);
void createSystemBrushes();
uint32_t copyBrush(uint32_t b);

#endif //CONTEXT_H
