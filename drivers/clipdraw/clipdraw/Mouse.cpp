
#include "Mouse.hpp"
#include "Video.hpp"
#include "Region.hpp"
#include "NFrame.hpp"
#include "krnl/main.hpp"
#include "krnl/terminal.hpp"
#include "krnl/physmgr.hpp"
#include "thr/prcssthr.hpp"
#include "sys/syscalls.hpp"
#include "hal/intctrl.hpp"
#include "hw/acpi.hpp"
#include "fs/vfs.hpp"
#include "krnl/kheap.hpp"
#include <hal/video.hpp>

#pragma GCC optimize ("O0")

extern NButton* desktopWindow;

int mouseX;
int mouseY;
int mouseButtons;

uint8_t ___mouse_data[CURSOR_DATA_SIZE * MAX_CURSOR_TYPES] = {
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

// both should be identical save for relX/Y
Region tightMouseRegionOld;
Region tightMouseRegionNew;

void mouseInit(Screen scr)
{
	tightMouseRegionOld = createTightCursorRegion(0, 0, (uint32_t*) (___mouse_data + MOUSE_OFFSET_NORMAL));
	tightMouseRegionNew = createTightCursorRegion(0, 0, (uint32_t*) (___mouse_data + MOUSE_OFFSET_NORMAL));
}

void hideCursor(Screen scr, int oldX, int oldY, int newX, int newY)
{
	tightMouseRegionOld.relX = oldX;
	tightMouseRegionOld.relY = oldY;
	tightMouseRegionNew.relX = newX;
	tightMouseRegionNew.relY = newY;

	Region clearRgn = getRegionDifference(tightMouseRegionOld, tightMouseRegionNew);
	desktopWindow->repaintCursorRegion(scr, clearRgn);

	free(clearRgn.data);
}

void showCursor(Screen scr)
{
	videoDrawCursor(scr, mouseX, mouseY, (uint32_t*) (___mouse_data + MOUSE_OFFSET_NORMAL));

	/*int usableKilobytes = Phys::usablePages * 4;
	int usedKilobytes = Phys::usedPages * 4;
	
	extern void drawVGAChar(int x, int y, int c, int fg, int bg);

	drawVGAChar(0, 0, '0' + (usedKilobytes / 100000) % 10, 0xFFFFFF, 0x000000);
	drawVGAChar(1, 0, '0' + (usedKilobytes / 10000) % 10, 0xFFFFFF, 0x000000);
	drawVGAChar(2, 0, '0' + (usedKilobytes / 1000) % 10, 0xFFFFFF, 0x000000);
	drawVGAChar(3, 0, '0' + (usedKilobytes / 100) % 10, 0xFFFFFF, 0x000000);
	drawVGAChar(4, 0, '0' + (usedKilobytes / 10) % 10, 0xFFFFFF, 0x000000);
	drawVGAChar(5, 0, '0' + (usedKilobytes / 1) % 10, 0xFFFFFF, 0x000000);
	
	drawVGAChar(6, 0, '/', 0xFFFFFF, 0x000000);

	drawVGAChar(7, 0, '0' + (usableKilobytes / 100000) % 10, 0xFFFFFF, 0x000000);
	drawVGAChar(8, 0, '0' + (usableKilobytes / 10000) % 10, 0xFFFFFF, 0x000000);
	drawVGAChar(9, 0, '0' + (usableKilobytes / 1000) % 10, 0xFFFFFF, 0x000000);
	drawVGAChar(10, 0, '0' + (usableKilobytes / 100) % 10, 0xFFFFFF, 0x000000);
	drawVGAChar(11, 0, '0' + (usableKilobytes / 10) % 10, 0xFFFFFF, 0x000000);
	drawVGAChar(12, 0, '0' + (usableKilobytes / 1) % 10, 0xFFFFFF, 0x000000);
	
	drawVGAChar(13, 0, ' ', 0xFFFFFF, 0x000000);
	drawVGAChar(14, 0, 'K', 0xFFFFFF, 0x000000);
	drawVGAChar(15, 0, 'B', 0xFFFFFF, 0x000000);*/
}

#define DRAG_MODE_NONE		0
#define DRAG_MODE_MOVE		1
#define DRAG_RESIZE_BR		2

NFrame* draggingWindow;
bool startedDragging = false;
int dragMode;

#define EDGE_DRAG_REGION_SIZE	12

bool handleMouse(Screen scr, int xDelta, int yDelta, int zDeltaHz, int zDeltaVt, int buttons)
{
	bool needsRepaint = false;

	int oldMouseX = mouseX;
	int oldMouseY = mouseY;
	int oldButtons = mouseButtons;

	mouseX += xDelta;
	mouseY += yDelta;
	mouseButtons = buttons;

	if (mouseX < 0) mouseX = 0;
	if (mouseY < 0) mouseY = 0;
	if (mouseX >= scr->getWidth()) mouseX = scr->getWidth() - 1;
	if (mouseY >= scr->getHeight()) mouseY = scr->getHeight() - 1;

	hideCursor(scr, oldMouseX, oldMouseY, mouseX, mouseY);

	NFrame* pxOwner = desktopWindow->getPixelOwner(scr, mouseX, mouseY, true);

	if (!(buttons & MOUSE_BUTTON_LEFT) && (oldButtons & MOUSE_BUTTON_LEFT)) {
		if (draggingWindow && startedDragging) {
			draggingWindow->endDragState();
			needsRepaint = true;
		}

		startedDragging = false;
		dragMode = DRAG_MODE_MOVE;
		draggingWindow = nullptr;
	}

	if ((buttons & MOUSE_BUTTON_LEFT) && !(oldButtons & MOUSE_BUTTON_LEFT) && draggingWindow == nullptr) {
		if (pxOwner != desktopWindow)  {
			pxOwner->raise();

			int xOffset = mouseX - pxOwner->getAbsX();
			int yOffset = mouseY - pxOwner->getAbsY();

			if (yOffset >= 0 && yOffset < pxOwner->getTitlebarHeight()) {
				draggingWindow = pxOwner;
				startedDragging = false;
				dragMode = DRAG_MODE_MOVE;

			} else if (yOffset >= pxOwner->getHeight() - EDGE_DRAG_REGION_SIZE && xOffset >= pxOwner->getWidth() - EDGE_DRAG_REGION_SIZE) {
				draggingWindow = pxOwner;
				startedDragging = false;
				dragMode = DRAG_RESIZE_BR;

			} else {
				draggingWindow = nullptr;
				dragMode = DRAG_MODE_MOVE;
			}

			needsRepaint = true;
		}
	}

	if (draggingWindow && (xDelta || yDelta)) {
		int oldX = draggingWindow->getX();
		int oldY = draggingWindow->getY();
		int oldW = draggingWindow->getWidth();
		int oldH = draggingWindow->getHeight();

		int effectiveDeltaX = mouseX - oldMouseX;
		int effectiveDeltaY = mouseY - oldMouseY;

		if (!startedDragging) {
			startedDragging = true;
			draggingWindow->startDragState();
		}

		if (dragMode == DRAG_MODE_MOVE) {
			draggingWindow->setPosition(oldX + effectiveDeltaX, oldY + effectiveDeltaY);

		} else if (dragMode == DRAG_RESIZE_BR) {
			draggingWindow->setSize(mouseX - oldX, mouseY - oldY);
		}

		needsRepaint = true;
	}

	showCursor(scr);

	return needsRepaint;
}