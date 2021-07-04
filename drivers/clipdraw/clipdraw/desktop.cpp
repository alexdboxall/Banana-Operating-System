#include "desktop.hpp"
#include "window.hpp"
#include <krnl/panic.hpp>
#include <core/kheap.hpp>

extern "C" {
#include <libk/string.h>
}

#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")

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


extern void (*guiMouseHandler) (int xdelta, int ydelta, int buttons, int z);
NIDesktop* mouseDesktop;

void clipdrawHandleMouse(int xdelta, int ydelta, int buttons, int z)
{
	mouseDesktop->handleMouse(xdelta, ydelta, buttons, z);
}

NIDesktop::NIDesktop(NIContext* context)
{
	ctxt = context;

	mouseX = 30;
	mouseY = 30;
	cursorOffset = MOUSE_OFFSET_NORMAL;

	head = new DesktopWindowNode;
	head->next = nullptr;
	head->win = nullptr;

	mouseDesktop = this;
	guiMouseHandler = clipdrawHandleMouse;
}

DesktopWindowNode* NIDesktop::getLastNode()
{
	DesktopWindowNode* curr = head;
	
	while (curr->next) {
		curr = curr->next;
	}

	return curr;
}

void NIDesktop::addWindow(NIWindow* window)
{
	DesktopWindowNode* last = getLastNode();
	last->win = window;
	last->next = new DesktopWindowNode;
	last = last->next;
	last->win = nullptr;
	last->next = nullptr;
}

void NIDesktop::raiseWindow(NIWindow* window)
{
	deleteWindow(window);
	
	DesktopWindowNode* a = new DesktopWindowNode;
	a->next = head;
	a->win = window;

	head = a;
}

void NIDesktop::deleteWindow(NIWindow* window)
{
	DesktopWindowNode* curr = head;
	while (curr->next) {
		if (curr->win == window) {
			curr->win = nullptr;
			if (curr->next) curr->next = curr->next->next;
			return;
		}
		curr = curr->next;
	}
}

void NIDesktop::rangeRefresh(int top, int bottom, int left, int right)
{
	for (int y = top; y < bottom; ++y) {
		renderScanline(y, left, right);
	}
}

void NIDesktop::completeRefresh()
{
	for (int y = 0; y < ctxt->height; ++y) {
		renderScanline(y, 0, ctxt->width);
	}

	ctxt->screen->drawCursor(mouseX, mouseY, (uint32_t*) (___mouse_data + cursorOffset), 0);
}

void NIDesktop::handleMouse(int xdelta, int ydelta, int buttons, int z)
{
	//clear old mouse
	rangeRefresh(mouseY, mouseY + MOUSE_HEIGHT, mouseX, mouseX + MOUSE_WIDTH);

	//move mouse
	mouseX += xdelta;
	mouseY += ydelta;

	//check boundaries
	if (mouseX < 0) mouseX = 0;
	if (mouseY < 0) mouseY = 0;
	if (mouseX > ctxt->width - 1) mouseX = ctxt->width - 1;
	if (mouseY > ctxt->height - 1) mouseY = ctxt->height - 1;

	//paint new mouse
	//ctxt->screen->putrect(mouseX, mouseY, 15, 25, 0);
	ctxt->screen->drawCursor(mouseX, mouseY, (uint32_t*) (___mouse_data + cursorOffset), 0);
}

uint8_t render[2048];
uint32_t renderData[2048];

#pragma GCC optimize ("Ofast")
void NIDesktop::renderScanline(int line, int left, int right)
{
	memset(render, 0, sizeof(render));

	int expectedBytes = right - left;

	DesktopWindowNode* curr = head;
	while (curr->next) {
		if (!curr) break;
		NIWindow* window = curr->win;
		if (!window) break;

		if (window->ypos <= line && line < window->ypos + window->height) {
			int ls = window->renderTable[line - window->ypos].leftSkip;
			int rs = window->renderTable[line - window->ypos].rightSkip;
			for (int i = window->xpos + ls; i < window->xpos + window->width - rs; ++i) {
				if (!render[i] && i >= left && i < right) {
					render[i] = 1;
					renderData[i] = window->renderTable[line - window->ypos].data32[i - window->xpos];
					--expectedBytes;
					if (expectedBytes == 0) {
						goto done;
					}
				}
			}
		}
		
		curr = curr->next;
	}

	for (int i = left; i < right; ++i) {
		if (!render[i]) {
			render[i] = 1;
			renderData[i] = 0x5580FF;
			--expectedBytes;
			if (expectedBytes == 0) {
				goto done;
			}
		}
	}

done:
	ctxt->screen->blit(renderData + left, left, line, right - left, 1);
}
#pragma GCC optimize ("Os")
