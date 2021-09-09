#include "desktop.hpp"
#include "window.hpp"
#include <krnl/panic.hpp>
#include <core/kheap.hpp>
#include <krnl/hal.hpp>
#include <fs/vfs.hpp>

extern "C" {
#include "userlink.h"
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

NiEvent NiCreateEvent(NIWindow* win, int type, bool redraw)
{
	NiEvent evnt;
	evnt.type = type;
	evnt.needsRedraw = redraw;
	evnt.krnlWindow = (void*) win;
	evnt.mouseX = mouseDesktop->mouseX;
	evnt.mouseY = mouseDesktop->mouseY;
	return evnt;
}

void NiHandleMouse(int xdelta, int ydelta, int buttons, int z)
{
	mouseDesktop->handleMouse(xdelta, ydelta, buttons, z);
}

void NiLoadCursors()
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
		} else {
			kprintf("CURSOR LOAD: BAD 3\n");
			break;
		}

		memcpy(___mouse_data + offset, curdata + numCursors * 4 + i * CURSOR_DATA_SIZE, CURSOR_DATA_SIZE);
	}

	free(curdata);
}

NIDesktop::NIDesktop(NIContext* context)
{
	ctxt = context;

	mouseX = 30;
	mouseY = 30;
	cursorOffset = MOUSE_OFFSET_NORMAL;

	head = new List<NIWindow*>();

	mouseDesktop = this;
	guiMouseHandler = NiHandleMouse;
}


void NIDesktop::addWindow(NIWindow* window)
{
	head->insertAtHead(window);
	refreshWindowBounds(window);
}

void NIDesktop::raiseWindow(NIWindow* window)
{
	head->deleteElement(window);
	head->insertAtHead(window);
	refreshWindowBounds(window);
}

void NIDesktop::deleteWindow(NIWindow* window)
{
	head->deleteElement(window);
	refreshWindowBounds(window);
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


void NIDesktop::refreshWindowBounds(NIWindow* window)
{
	int a = window->ypos < 5 ? 0 : window->ypos - 5;
	int b = window->ypos + window->height > ctxt->height - 6 ? ctxt->height - 1 : window->ypos + window->height + 5;
	int c = window->xpos < 5 ? 0 : window->xpos - 5;
	int d = window->xpos + window->width > ctxt->width - 6 ? ctxt->width - 1 : window->xpos + window->width + 5;
	
	rangeRefresh(a, b, c, d);

	ctxt->screen->drawCursor(mouseX, mouseY, (uint32_t*) (___mouse_data + cursorOffset), 0);
}

void NIDesktop::invalidateAllDueToFullscreen(NIWindow* ignoredWindow)
{
	auto curr = head->getHead();
	while (curr->next) {
		if (!curr) break;
		NIWindow* window = curr->getValue();

		if (window && window != ignoredWindow) {
			window->invalidate();
		}

		curr = curr->next;
	}
}

NIWindow* NIDesktop::getTopmostWindowAtPixel(int x, int line)
{
	auto curr = head->getHead();
	while (curr->next) {
		if (!curr) break;
		NIWindow* window = curr->getValue();
		if (!window) break;

		if (window->ypos <= line && line < window->ypos + window->height) {
			int ls = window->renderTable[line - window->ypos].leftSkip;
			int rs = window->renderTable[line - window->ypos].rightSkip;
			if (window->xpos + ls <= x && x < window->xpos + window->width - rs) {
				return window;
			}
		}

		curr = curr->next;
	}

	return nullptr;
}

#pragma GCC optimize ("Os")

uint8_t render[2048];
uint8_t shadow[2048];
uint32_t renderData[2048];
NIWindow* movingWin = nullptr;

#define MOVE_TYPE_MOVE			1
#define MOVE_TYPE_RESIZE_BR		2
#define MOVE_TYPE_RESIZE_B		3
#define MOVE_TYPE_RESIZE_R		4

int movingType = 0;

extern uint64_t milliTenthsSinceBoot;

void NIDesktop::handleMouse(int xdelta, int ydelta, int buttons, int z)
{
	static int previousButtons = 0;
	static int moveBaseX = 0;
	static int moveBaseY = 0;
	static uint64_t lastClick = 0;

	//clear old mouse
	rangeRefresh(mouseY, mouseY + MOUSE_HEIGHT, mouseX, mouseX + MOUSE_WIDTH);

	int oldX = mouseX;
	int oldY = mouseY;

	//move mouse
	mouseX += xdelta;
	mouseY += ydelta;
	
	//check boundaries
	if (mouseX < 0) mouseX = 0;
	if (mouseY < 0) mouseY = 0;
	if (mouseX > ctxt->width - 1) mouseX = ctxt->width - 1;
	if (mouseY > ctxt->height - 1) mouseY = ctxt->height - 1;

	NIWindow* clickon = getTopmostWindowAtPixel(mouseX, mouseY);

	if (movingWin && movingType == MOVE_TYPE_MOVE) {
		bool release = !(buttons & 1) && (previousButtons & 1);

		for (int y = 1; y < movingWin->height - 1; ++y) {
			for (int x = 1; x < movingWin->width - 1; ++x) {
				if (!((x + y) & 31) && !(y & 3)) {
					if (oldX - moveBaseX + x >= 0 && oldX - moveBaseX + x < ctxt->width) rangeRefresh(oldY - moveBaseY + y, oldY - moveBaseY + y + 1, oldX - moveBaseX + x, oldX - moveBaseX + x + 1);
					if (!release && mouseX - moveBaseX + x >= 0 && mouseX - moveBaseX + x < ctxt->width) ctxt->screen->putpixel(mouseX - moveBaseX + x, mouseY - moveBaseY + y, 0);
				}
			}
		}

		if (!release) {
			int x1 = mouseX - moveBaseX;
			if (x1 < 0) x1 = 0;
			int x2 = mouseX - moveBaseX + movingWin->width - x1;
			if (x1 + x2 >= ctxt->width) {
				x2 = ctxt->width - x1;
				if (x2 < 0) x2 = 0;
			}
			if (x2) {
				int ox1 = oldX - moveBaseX;
				if (ox1 < 0) ox1 = 0;
				int ox2 = oldX - moveBaseX + movingWin->width - ox1;
				if (ox1 + ox2 >= ctxt->width) {
					ox2 = ctxt->width - ox1;
					if (ox2 < 0) ox2 = 0;
				}
				rangeRefresh(oldY - moveBaseY, oldY - moveBaseY + 1, ox1, ox1 + ox2);
				rangeRefresh(oldY - moveBaseY + movingWin->height - 1, oldY - moveBaseY + movingWin->height, ox1, ox1 + ox2);

				ctxt->screen->putrect(x1, mouseY - moveBaseY, x2, 1, 0);
				ctxt->screen->putrect(x1, mouseY - moveBaseY + movingWin->height - 1, x2, 1, 0);
			}
		}

		if (release) {
			auto win = movingWin;
			movingWin->xpos = mouseX - moveBaseX;
			movingWin->ypos = mouseY - moveBaseY;
			movingWin = nullptr;
			addWindow(win);
		}
	}

	if (movingWin && (movingType == MOVE_TYPE_RESIZE_BR || movingType == MOVE_TYPE_RESIZE_B || movingType == MOVE_TYPE_RESIZE_R)) {
		bool release = !(buttons & 1) && (previousButtons & 1);

		int oldW = movingWin->width + oldX - moveBaseX;
		int oldH = movingWin->height + oldY - moveBaseY;
		int newW = movingWin->width + mouseX - moveBaseX;
		int newH = movingWin->height + mouseY - moveBaseY;

		if (movingType == MOVE_TYPE_RESIZE_B) newW = oldW = movingWin->width;
		if (movingType == MOVE_TYPE_RESIZE_R) newH = oldH = movingWin->height;

		int mxW = oldW > newW ? oldW : newW;
		int mxH = oldH > newH ? oldH : newH;
		for (int y = 1; y < mxH; ++y) {
			for (int x = 1; x < mxW; ++x) {
				if (!((x + y) & 31) && !(y & 3)) {
					rangeRefresh(movingWin->ypos + y, movingWin->ypos + 1 + y, movingWin->xpos + x, movingWin->xpos + 1 + x);
					if (!release && x < newW && y < newH) ctxt->screen->putpixel(movingWin->xpos + x, movingWin->ypos + y, 0);
				}
			}
		}

		if (!release) {
			rangeRefresh(movingWin->ypos, movingWin->ypos + 1, movingWin->xpos, movingWin->xpos + oldW);
			ctxt->screen->putrect(movingWin->xpos, movingWin->ypos, newW, 1, 0);

			rangeRefresh(movingWin->ypos + oldH, movingWin->ypos + 1 + oldH, movingWin->xpos, movingWin->xpos + oldW);
			ctxt->screen->putrect(movingWin->xpos, movingWin->ypos + newH, newW, 1, 0);
		}

		if (release) {
			auto win = movingWin;
			movingWin = nullptr;

			NiEvent evnt = NiCreateEvent(win, EVENT_TYPE_RESIZED, true);
			win->width = newW;
			win->height = newH;
			win->rerender();
			addWindow(win);
			refreshWindowBounds(win);
			win->postEvent(evnt);
			cursorOffset = MOUSE_OFFSET_NORMAL;
		}
	}

	if ((buttons & 1) && clickon) {
		if (!(previousButtons & 1)) {
			uint64_t sincePrev = milliTenthsSinceBoot - lastClick;

			if (sincePrev < 3000 && mouseY - clickon->ypos < WINDOW_TITLEBAR_HEIGHT && !(clickon->flags & WINFLAG_DISABLE_RESIZE)) {
				if (clickon->fullscreen) {
					clickon->xpos = clickon->rstrx;
					clickon->ypos = clickon->rstry;
					clickon->width = clickon->rstrw;
					clickon->height = clickon->rstrh;

					invalidateAllDueToFullscreen(clickon);

				} else {
					clickon->rstrx = clickon->xpos;
					clickon->rstry = clickon->ypos;
					clickon->rstrw = clickon->width;
					clickon->rstrh = clickon->height;

					clickon->xpos = 0;
					clickon->ypos = 0;
					clickon->width = ctxt->width;
					clickon->height = ctxt->height;
				}
				sincePrev = 0;
				clickon->fullscreen ^= 1;
				NiEvent evnt = NiCreateEvent(clickon, EVENT_TYPE_RESIZED, true);
				clickon->postEvent(evnt);
				clickon->rerender();
				completeRefresh();

			} else {
				if (clickon != head->getHead()->getValue()) {
					raiseWindow(clickon);
				}
			}

			lastClick = milliTenthsSinceBoot;

		} else if (!movingWin) {
			if (mouseY - clickon->ypos > clickon->height - 15 && !clickon->fullscreen && !(clickon->flags & WINFLAG_DISABLE_RESIZE)) {
				movingWin = clickon;
				movingType = MOVE_TYPE_RESIZE_B;
				cursorOffset = MOUSE_OFFSET_VERT;
				moveBaseX = mouseX;
				moveBaseY = mouseY;
				deleteWindow(clickon);
			} 
			if (mouseX - clickon->xpos > clickon->width - 15 && !clickon->fullscreen && !(clickon->flags & WINFLAG_DISABLE_RESIZE)) {
				if (!movingWin) {
					movingWin = clickon;
					movingType = MOVE_TYPE_RESIZE_R;
					cursorOffset = MOUSE_OFFSET_HORZ;
					moveBaseX = mouseX;
					moveBaseY = mouseY;
					deleteWindow(clickon);
				} else {
					movingType = MOVE_TYPE_RESIZE_BR;
					cursorOffset = MOUSE_OFFSET_TLDR;
				}
			}

			if (!movingWin && mouseY - clickon->ypos < WINDOW_TITLEBAR_HEIGHT && !clickon->fullscreen) {
				movingWin = clickon;
				movingType = MOVE_TYPE_MOVE;
				moveBaseX = mouseX - clickon->xpos;
				moveBaseY = mouseY - clickon->ypos;
				deleteWindow(clickon);
			}
		}
	}

	//paint new mouse
	ctxt->screen->drawCursor(mouseX, mouseY, (uint32_t*) (___mouse_data + cursorOffset), 0);

	previousButtons = buttons;
}

void NIDesktop::renderScanline(int line, int left, int right)
{
	int expectedBytes = right - left;

	memset(render + left, 0, expectedBytes);
	memset(shadow + left, 128, expectedBytes);

	auto curr = head->getHead();
	while (curr->next) {
		if (!curr) break;
		NIWindow* window = curr->getValue();
		if (!window) break;

		if (movingWin == window) {
			curr = curr->next;
			continue;
		}

		window->request();

		if (line < window->ypos + window->height && !window->fullscreen) {
			for (int i = window->xpos; i < window->xpos + window->width; ++i) {
				if (i < left) continue;
				if (i > right) break;
				int j = line;
				while (j < window->ypos || \
					   (j - window->ypos >= 0 && window->renderTable[j - window->ypos].leftSkip > i - window->xpos) || \
					   (j - window->ypos >= 0 && i > window->xpos + window->width - window->renderTable[j - window->ypos].rightSkip) \
					   ) {
					++j;
					if (j - line > 5) break;
				}
				int diff = j - line;
				if (diff < 5 && diff > 0) {
					if (!render[i]) {
						diff--;
						shadow[i] = ((101 + diff * 8) * shadow[i] / 256) + (101 + diff * 8) / 2;
					}
				}
			}

		} else if (line > window->ypos && !window->fullscreen) {
			for (int i = window->xpos; i < window->xpos + window->width; ++i) {
				if (i < left) continue;
				if (i > right) break;
				int j = line;
				
				do {
					--j;
					if (line - j > 5) break;
				} while (j >= window->ypos + window->height || \
						 (j - window->ypos < window->height && window->renderTable[j - window->ypos].leftSkip > i - window->xpos) || \
						 (j - window->ypos < window->height && i > window->xpos + window->width - window->renderTable[j - window->ypos].rightSkip) \
						 );

				int diff = line - j;
				if (diff < 5 && diff >= 0) {
					if (!render[i]) {
						shadow[i] = ((93 + diff * 8) * shadow[i] / 256) + (93 + diff * 8) / 2;
					}
				}
			}
		}
		

		if (window->ypos <= line && line < window->ypos + window->height) {

			int ls = window->renderTable[line - window->ypos].leftSkip;
			int rs = window->renderTable[line - window->ypos].rightSkip;

			if (!window->fullscreen) {
				for (int i = 0; i < 4; ++i) {
					int j = window->xpos + ls - 4 + i;
					int k = window->xpos + window->width - rs + i;
					if (!render[j]) {
						shadow[j] = ((125 - i * 8) * shadow[j] / 256) + (125 - i * 8) / 2;
					}
					if (!render[k]) {
						shadow[k] = ((101 + i * 8) * shadow[k] / 256) + (101 + i * 8) / 2;
					}
				}
			}

			for (int i = window->xpos + ls; i < window->xpos + window->width - rs; ++i) {
				if (i < left) continue;
				if (i > right) break;
				if (!render[i]) {
					render[i] = 1;
					renderData[i] = window->data32[(line - window->ypos) * window->width + (i - window->xpos)];
					--expectedBytes;
					if (expectedBytes == 0) {
						goto done;
					}
				}
			}
		}

		if (window->fullscreen) break;
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
	curr = head->getHead();
	if (curr && curr->getValue() && !curr->getValue()->fullscreen) {
		for (int i = left; i < right; ++i) {
			int amount = shadow[i];
			if (amount != 128) {
				uint32_t og = renderData[i];

				uint32_t r = (og >> 16) & 0xFF;
				uint32_t g = (og >> 8) & 0xFF;
				uint32_t b = (og >> 0) & 0xFF;

				r = (r * amount) >> 7;
				g = (g * amount) >> 7;
				b = (b * amount) >> 7;

				renderData[i] = (r << 16) | (g << 8) | b;
			}
		}
	}

	ctxt->screen->bitblit(left, line, left, 0, right - left, 1, 0, renderData);
}
#pragma GCC optimize ("Os")
