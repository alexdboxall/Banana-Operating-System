#include "cursor.hpp"
#include "region.hpp"
#include "rootrgn.hpp"
#include <core/kheap.hpp>
#include <fs/vfs.hpp>
#include <core/common.hpp>

extern "C" {
#include <libk/string.h>
}

uint8_t mouse_data[CURSOR_DATA_SIZE * MAX_CURSOR_TYPES] = {
    0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00,
    0x1F, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00,
    0xFF, 0x01, 0x00, 0x00, 0xFF, 0x03, 0x00, 0x00, 0xFF, 0x07, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00,
    0xF7, 0x00, 0x00, 0x00, 0xF3, 0x00, 0x00, 0x00, 0xE1, 0x01, 0x00, 0x00, 0xE0, 0x01, 0x00, 0x00,
    0xC0, 0x03, 0x00, 0x00, 0xC0, 0x03, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00,
    0x11, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 0x41, 0x00, 0x00, 0x00, 0x81, 0x00, 0x00, 0x00,
    0x01, 0x01, 0x00, 0x00, 0x01, 0x02, 0x00, 0x00, 0xC1, 0x07, 0x00, 0x00, 0x49, 0x00, 0x00, 0x00,
    0x95, 0x00, 0x00, 0x00, 0x93, 0x00, 0x00, 0x00, 0x21, 0x01, 0x00, 0x00, 0x20, 0x01, 0x00, 0x00,
    0x40, 0x02, 0x00, 0x00, 0x40, 0x02, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

int krnlMouseX = 0;
int krnlMouseY = 0;
int krnlButtons = 0;

extern "C" void handleMouse(int xdelta, int ydelta, int btns, int z)
{
    krnlMouseX += xdelta;
    krnlMouseY += ydelta;

    if (krnlMouseX < 1) krnlMouseX = 1;
    if (krnlMouseY < 1) krnlMouseY = 1;
    if (krnlMouseX > rootRgn.region->context->width - 2) krnlMouseX = rootRgn.region->context->width - 2;
    if (krnlMouseY > rootRgn.region->context->height - 2) krnlMouseY = rootRgn.region->context->height - 2;

    krnlButtons = 0;
    if (btns & 1) {
        krnlButtons = MOUSE_BUTTON_LEFT;
    }

    processMouse(krnlMouseX, krnlMouseY, krnlButtons);
}

extern "C" void (*guiMouseHandler) (int xdelta, int ydelta, int btns, int z);

void startMouse()
{
    guiMouseHandler = handleMouse;
}

void setupCursor()
{

    krnlMouseX = 300;
    krnlMouseY = 200;
    rootRgn.mouseX = 300;
    rootRgn.mouseY = 200;

    rootRgn.cursorBase = 0;

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
        } else {
            kprintf("CURSOR LOAD: BAD 3\n");
            break;
        }

        memcpy(mouse_data + offset, curdata + numCursors * 4 + i * CURSOR_DATA_SIZE, CURSOR_DATA_SIZE);
    }

    free(curdata);
}

namespace Krnl
{
    void userIOReceived();
}

void processMouse(int mx, int my, int buttons)
{
    Krnl::userIOReceived();

    int i, x, y;
    Region* child;
    List<CRect*>* dirty_list = new List<CRect*>;

    CRect* mouse_rect = new CRect(rootRgn.mouseY, rootRgn.mouseX,
                                  rootRgn.mouseY + MOUSE_HEIGHT - 1,
                                  rootRgn.mouseX + MOUSE_WIDTH - 1);

    dirty_list->insertAtTail(mouse_rect);

    rootRgn.region->update(dirty_list, 1);

    dirty_list->deleteHead();
    delete dirty_list;
    delete mouse_rect;

    rootRgn.mouseX = mx;
    rootRgn.mouseY = my;

    rootRgn.region->context->screen->drawCursor(mx, my, mouse_data + rootRgn.cursorBase, 0);
}