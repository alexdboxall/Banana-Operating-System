#ifndef LIST_H
#define LIST_H

#include "listnode.h"
#include <stdint.h>

void screenputpixel(int x, int y, uint32_t color);
void screenputrect(int x, int y, int max_x, int max_y, uint32_t color);
void screendrawcursor(int x, int y, uint8_t * data);

//================| List Class Declaration |================//

//A type to encapsulate a basic dynamic list
typedef struct List_struct {
    unsigned int count; 
    ListNode* root_node;
} List;

//Methods
List* List_new();
int List_add(List* list, void* payload);
void* List_get_at(List* list, unsigned int index);
void* List_remove_at(List* list, unsigned int index);

#endif //LIST_H
