#include <stdint.h>

#include "main.hpp"

#include "core/main.hpp"
#include "core/terminal.hpp"
#include "core/physmgr.hpp"
#include "sys/syscalls.hpp"
#include "hal/intctrl.hpp"
#include "hw/ports.hpp"
#include "hw/acpi.hpp"
#include "hal/video.hpp"
#include "thr/prcssthr.hpp"
#include "hal/timer.hpp"
#include "reg/registry.hpp"
#include "fs/vfs.hpp"

#include "thomas.h"

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

uint32_t* parsedTGA;
int desktopImageWidth = 640;
int desktopImageHeight = 480;
uint32_t desktopBgCol = 0x008080;
bool desktopUseBgCol = true;

extern "C" bool invertMouse;

extern "C" void bitblit(int sx, int sy, int x, int y, int w, int h, int pitch, uint32_t* data)
{
    extern Video* screen;
    screen->bitblit(sx, sy, x, y, w, h, pitch, data);
}

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

void loadCursors()
{
    File* f = new File("C:/Banana/Cursors/STANDARD.CUR", kernelProcess);
    FileStatus status = f->open(FileOpenMode::Read);
    if (status != FileStatus::Success) {
        kprintf("CURSOR LOAD: BAD 1\n");
        return;
    }

    uint64_t size;
    bool dir;
    f->stat(&size, &dir);
    int read;
    uint8_t* curdata = (uint8_t*) malloc(size);
    f->read(size, curdata, &read);
    if (read != (int) size) {
        kprintf("CURSOR LOAD: BAD 2\n");
        return;
    }

    int numCursors = size / 260;
    kprintf("CURSORS: %d\n", numCursors);
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
            kprintf("CURSOR LOAD: BAD 3\n");
            break;
        }

        memcpy(___mouse_data + offset, curdata + numCursors * 4 + i * CURSOR_DATA_SIZE, CURSOR_DATA_SIZE);
    }

    free(curdata);
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

extern "C" void debugwrite(char* t)
{
    kprintf(t);
}


extern "C" void debugwritestrhx(char* t, uint32_t hx)
{
    kprintf("%s%X", t, hx);
}


extern "C" void loadbuiltinfonts();

namespace Krnl
{
    extern void (*guiPanicHandler)();
    extern void (*guiProgramFaultHandler)();
}

void faulthandler()
{

}

void panichandler()
{
    extern Video* screen;

    uint32_t vgaLookup[16] = {
        0x000000,
        0x0000AA,
        0x00AA00,
        0x00AAAA,
        0xAA0000,
        0xAA00AA,
        0xD4AA2A,
        0xAAAAAA,
        0x555555,
        0x5555FF,
        0x55FF55,
        0x55FFFF,
        0xFF5555,
        0xFF55FF,
        0xFFFF55,
        0xFFFFFF,
    };

    int spot = 0;
    for (int y = 0; y < 480; ++y) {
        for (int x = 0; x < 320; ++x) {
            uint8_t d = thomas[spot++];
            uint32_t c1 = vgaLookup[d & 0xF];
            uint32_t c2 = vgaLookup[d >> 4];

            if (x > 325 / 2 && x < 395 / 2 && y > 190 && y < 270) {
                if (c1 == 0xD4AA2A) c1 = 0xFFFFAA;
                if (c2 == 0xD4AA2A) c2 = 0xFFFFAA;
            }
            screen->putpixel(x * 2, y, c1);
            screen->putpixel(x * 2 + 1, y, c2);
        }
    }
}

#include "interface.h"



void guiProc(Window* window, Message msg) {
    switch (msg.type) {
    case MESSAGE_PAINT:
    {
        break;
    }

    default:
        guiDefaultProc(window, msg);
    }
}

void internalMain(Window* __v)
{
    __v->hasProc = true;
    while (1) {
        nanoSleep(1000 * 1000 * 200);
        Message msg;
        int count = getMessage(__v, &msg);
        if (!count) continue;
        guiProc((Window*) msg.window, msg);
    }
}

void myapp(void* ctxt)
{
    //unlockScheduler();

    Window* test = createWindow(150, 100, 350, 200, WIN_TOPLEVELWIN);
    test->hasProc = true;
    setWindowTitle(test, "WSBE Window!");
    addWindow((Window*) getDesktop(), test);

    internalMain(test);
}

extern "C" uint64_t sysWSBE(regs* r);

int main(int argc, const char* argv[])
{
    extern uint64_t(*systemCallHandlers[128])(regs * r);
    systemCallHandlers[(int) SystemCallNumber::WSBE] = sysWSBE;

    Process* p = new Process("C:/guitest.exe");
    p->createUserThread();

    extern Video* screen;
    Krnl::guiPanicHandler = panichandler;
    Krnl::guiProgramFaultHandler = faulthandler;

    //FFFF55
    //AA5500
    //D4AA2A

    int br;
    char bgImgName[256];
    Reg::readStringWithDefault((char*) "wsbe", (char*) "@desktop:imageFile", bgImgName, 255, (char*) "C:/Banana/Wallpapers/crisp.tga");
    File* f = new File(bgImgName, kernelProcess);
    uint64_t tgalen;
    bool dir;
    f->stat(&tgalen, &dir);
    uint8_t* bgImgTGA = (uint8_t*) malloc(tgalen);
    f->open(FileOpenMode::Read);
    f->read(tgalen, bgImgTGA, &br);
    f->close();
    int wo;
    int ho;
    extern Video* screen;
    parsedTGA = screen->tgaParse(bgImgTGA, tgalen, &wo, &ho);
    kprintf("wo = %d, ho = %d\n", wo, ho);
    desktopImageWidth = wo;
    desktopImageHeight = ho;

    canDoMouse = false;
    loadCursors();
    loadbuiltinfonts();

    desktopUseBgCol = Reg::readIntWithDefault((char*) "wsbe", (char*) "@desktop:backgroundMode", 0) == 0;
    desktopBgCol = Reg::readIntWithDefault((char*) "wsbe", (char*) "@desktop:solidColour", 0x008080/*0x2A2AD4*/);
    invertMouse = Reg::readIntWithDefault((char*) "wsbe", (char*) "invertMouse", 0);

    guiMouseHandler = handleMouse;

    //Fill this in with the info particular to your project
    Context* context = Context_new(0, 0, 0);
    context->buffer = nullptr;
    context->width = screen->getWidth();
    context->height = screen->getHeight();

    mouse_x = context->width / 2;
    mouse_y = context->height / 2;

    //Create the desktop
    desktop = Desktop_new(context);

    while (1) {
        blockTask(TaskState::Paused);
    }

    return 0;
}

