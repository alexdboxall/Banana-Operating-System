#include <stdint.h>

#include "main.hpp"

#include "core/main.hpp"
#include "core/terminal.hpp"
#include "core/physmgr.hpp"
#include "hal/intctrl.hpp"
#include "hw/ports.hpp"
#include "hw/acpi.hpp"
#include "hw/video/vga.hpp"
#include "core/prcssthr.hpp"
#include "registry/registry.hpp"
#include "fs/vfs.hpp"

extern "C" {
	#include "libk/string.h"
}

extern int main(int argc, const char* argv[]);

void start()
{
    main(0, nullptr);
}

extern "C" {
    #include "desktop.h"
    #include "button.h"
}

int mouse_x = 10;
int mouse_y = 10;
int buttons = 0;
Desktop* desktop = nullptr;

extern "C" void screenputrect(int x, int y, int max_x, int max_y, uint32_t color)
{
    extern Video* screen;
    screen->putrect(x, y, max_x - x, max_y - y, color);
}

extern "C" void screenputpixel(int x, int y, uint32_t color)
{
    extern Video* screen;
    screen->putpixel(x, y, color);
}


char szstring[64];
WindowPaintHandler oldHandler;

void resizehandler(struct Window_struct* win, int w, int h)
{
    //sprintf(szstring, "W: %d, H: %d", w, h);
}

void newPaint(struct Window_struct* win)
{
    oldHandler(win);
    Context_draw_text(win->context, szstring, 50, 50, 0);
}

void mdown(struct Window_struct* win, int x, int y)
{
    strcpy(szstring, "Mouse down.");
    Window_paint(win, 0, 1);
}

void mup(struct Window_struct* win, int x, int y)
{
    strcpy(szstring, "Mouse up.");
    Window_paint(win, 0, 1);
}

void mmove(struct Window_struct* win, int x, int y)
{
    strcpy(szstring, "Mouse move.");
    Window_paint(win, 0, 1);
}

void mdrag(struct Window_struct* win, int x, int y)
{
    strcpy(szstring, "Mouse drag.");
    Window_paint(win, 0, 1);
}

char tw[] = "Test Window";
//And, finally, the handler that causes that button to make a new calculator
void spawn_calculator(Button* button, int x, int y)
{
    strcpy(szstring, "Please resize this window!");

    Window* w = (Window*) malloc(sizeof(Window));
    Window_init(w, 50, 50, 300, 200, WIN_TOPLEVELWIN, 0);
    Window_set_title(w, (char*) tw);
    Window_insert_child((Window*) desktop, w);
    //w->resize_function = resizehandler;
    //w->mousedown_function = mdown;
    //w->mouseup_function = mup;
    //w->mousedrag_function = mdrag;
    //w->mousemove_function = mmove;

    oldHandler = w->paint_function;
    w->paint_function = newPaint;
    Window_paint((Window*) desktop, (List*) 0, 1);

    /*//Create and install a calculator
    Calculator* temp_calc = Calculator_new();
    Window_insert_child((Window*)desktop, (Window*)temp_calc);
    Window_move((Window*)temp_calc, 0, 0);*/
}

bool canDoMouse = false;

extern "C" void (*guiMouseHandler) (int xdelta, int ydelta, int btns, int z);
extern "C" void handleMouse(int xdelta, int ydelta, int btns, int z)
{
    mouse_x += xdelta;
    mouse_y += ydelta;

    if (mouse_x < 1) mouse_x = 1;
    if (mouse_y < 1) mouse_y = 1;
    if (mouse_x > 639) mouse_x = 639;
    if (mouse_y > 479) mouse_y = 479;

    buttons = 0;
    if (btns & 1) {
        buttons = 1;
    }

    canDoMouse = true;
}


char nw[] = "New Window";
char wsbeinit[] = "INITING... WSBE INIT.\n";

int main(int argc, const char* argv[])
{
    guiMouseHandler = handleMouse;

    //Fill this in with the info particular to your project
    Context* context = Context_new(0, 0, 0);
    context->buffer = nullptr;
    context->width = 800;
    context->height = 600;

    //Create the desktop
    desktop = Desktop_new(context);

    //Create a simple launcher window
    Button* launch_button = Button_new(10, 10, 150, 30);
    Window_set_title((Window*) launch_button, (char*) nw);
    launch_button->onmousedown = spawn_calculator;
    Window_insert_child((Window*) desktop, (Window*) launch_button);

    //Initial draw
    Window_paint((Window*) desktop, (List*) 0, 1);

    //Install our handler of mouse events
    //fake_os_installMouseCallback(main_mouse_callback);

    Desktop_process_mouse(desktop, mouse_x, mouse_y, buttons);

    spawn_calculator(nullptr, 0, 0);

    while (1) {  
        if (canDoMouse) {
            Desktop_process_mouse(desktop, mouse_x, mouse_y, buttons);
            canDoMouse = false;
        }
    }

    return 0;
}

