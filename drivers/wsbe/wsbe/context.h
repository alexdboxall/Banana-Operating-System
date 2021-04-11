#ifndef CONTEXT_H
#define CONTEXT_H

#include <inttypes.h>
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
} Context;

#define TEXT_FLAG_BOLD      1

//Methods
Context* Context_new(uint16_t width, uint16_t height, uint32_t* buffer);
Context* Context_copy(Context* original);

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

void Context_text_width_height(char* string, int flags, int* widthOut, int* heightOut);
void Context_draw_text(Context* context, char* string, int x, int y, uint32_t color, int flags);
void Context_draw_bitmap(Context* context, uint32_t* data, int x, int y, int w, int h);

#endif //CONTEXT_H
