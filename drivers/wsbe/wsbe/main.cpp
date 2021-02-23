#include <stdint.h>

#include "main.hpp"

#include "core/main.hpp"
#include "core/terminal.hpp"
#include "core/physmgr.hpp"
#include "hal/intctrl.hpp"
#include "hw/ports.hpp"
#include "hw/acpi.hpp"
#include "hal/video.hpp"
#include "core/prcssthr.hpp"
#include "hal/timer.hpp"
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

int mouse_x;
int mouse_y;
int buttons = 0;
Desktop* desktop = nullptr;

extern "C" bool invertMouse;

extern "C" void screendrawcursor(int x, int y, uint8_t* data)
{
    extern Video* screen;
    screen->drawCursor(x, y, data, invertMouse);
}

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

extern "C" uint64_t getNanoSinceBoot()
{
    return nanoSinceBoot;
}

char cursorBad1[] = "CURSOR LOAD: BAD 1\n";
char cursorBad2[] = "CURSOR LOAD: BAD 2\n";
char cursorBad3[] = "CURSOR LOAD: BAD 3\n";
char cursorNumStr[] = "CURSORS: %d\n";

void loadCursors()
{
    File* f = new File("C:/Banana/Cursors/STANDARD.CUR", kernelProcess);
    FileStatus status = f->open(FileOpenMode::Read);
    if (status != FileStatus::Success) {
        kprintf(cursorBad1);
        return;
    }

    uint64_t size;
    bool dir;
    f->stat(&size, &dir);
    int read;
    uint8_t* curdata = (uint8_t*) malloc(size);
    f->read(size, curdata, &read);
    if (read != (int) size) {
        kprintf(cursorBad2);
        return;
    }

    int numCursors = size / 260;
    kprintf(cursorNumStr, numCursors);
    kprintf((char*) curdata);
    for (int i = 0; i < numCursors; ++i) {
        int offset;
        if (!memcmp(curdata + i * 4, "NRML", 4)) {
            offset = MOUSE_OFFSET_NORMAL;
        } else if (!memcmp((char*) curdata + i * 4, "WAIT", 4)) {
            offset = MOUSE_OFFSET_WAIT;
        } else if (!memcmp((char*) curdata + i * 4, "TLDR", 4)) {
            offset = MOUSE_OFFSET_TLDR;
        } else if (!memcmp((char*) curdata + i * 4, "TEXT", 4)) {
            offset = MOUSE_OFFSET_TEXT;
        } else if (!memcmp((char*) curdata + i * 4, "VERT", 4)) {
            offset = MOUSE_OFFSET_VERT;
        } else if (!memcmp((char*) curdata + i * 4, "HORZ", 4)) {
            offset = MOUSE_OFFSET_HORZ;
        } else if (!memcmp((char*) curdata + i * 4, "HAND", 4)) {
            offset = MOUSE_OFFSET_HAND;
        }  else {
            kprintf(cursorBad3);
            break;
        }

        memcpy(___mouse_data + offset, curdata + numCursors * 4 + i * CURSOR_DATA_SIZE, CURSOR_DATA_SIZE);
    }

    free(curdata);
}

char tw[] = "The quick brown fox jumps";
//And, finally, the handler that causes that button to make a new calculator
void spawn_calculator(Button* button, int x, int y)
{
    Window* w = (Window*) malloc(sizeof(Window));
    Window_init(w, 50, 50, 300, 200, WIN_TOPLEVELWIN, 0);
    Window_set_title(w, (char*) tw);
    Window_insert_child((Window*) desktop, w);

    Window_paint((Window*) desktop, (List*) 0, 1);
}

bool canDoMouse = false;

extern "C" void (*guiMouseHandler) (int xdelta, int ydelta, int btns, int z);
extern "C" void handleMouse(int xdelta, int ydelta, int btns, int z)
{
    mouse_x += xdelta;
    mouse_y += ydelta;

    if (mouse_x < 1) mouse_x = 1;
    if (mouse_y < 1) mouse_y = 1;
    if (mouse_x > desktop->window.width - 2) mouse_x = desktop->window.width - 2;
    if (mouse_y > desktop->window.height - 2) mouse_y = desktop->window.height - 2;

    buttons = 0;
    if (btns & 1) {
        buttons = 1;
    }

    //canDoMouse = true;
    Desktop_process_mouse(desktop, mouse_x, mouse_y, buttons);
}

char nw[] = "New Window";
char wsbeinit[] = "INITING... WSBE INIT.\n";
char registryFilename[] = "wsbe";
char registryMouseInvertKey[] = "invertmouse";
char registryMouseDesktopCol[] = "desktopcolour";

extern "C" void debugwrite(char* t)
{
    kprintf(t);
}

extern "C" void loadbuiltinfonts();

int main(int argc, const char* argv[])
{
    canDoMouse = false;
    loadCursors();
    loadbuiltinfonts();

    desktopColour = Reg::readIntWithDefault((char*) registryFilename, (char*) registryMouseDesktopCol, 0x2A2AD4);
    invertMouse = Reg::readIntWithDefault((char*) registryFilename, (char*) registryMouseInvertKey, 0);

    guiMouseHandler = handleMouse;

    //Fill this in with the info particular to your project
    Context* context = Context_new(0, 0, 0);
    context->buffer = nullptr;
    context->width = 640;
    context->height = 480;

    mouse_x = context->width / 2;
    mouse_y = context->height / 2;

    //Create the desktop
    desktop = Desktop_new(context);

    //Create a simple launcher window
    Button* launch_button = Button_new(10, 10, 150, 30);
    Window_set_title((Window*) launch_button, (char*) nw);
    launch_button->onmousedown = spawn_calculator;
    Window_insert_child((Window*) desktop, (Window*) launch_button);
    Window_paint((Window*) desktop, (List*) 0, 1);

    spawn_calculator(nullptr, 0, 0);

    Desktop_process_mouse(desktop, mouse_x, mouse_y, buttons);
    Desktop_process_mouse(desktop, mouse_x, mouse_y, buttons);

    while (1) {  
        sleep(2);
    }

    return 0;
}

