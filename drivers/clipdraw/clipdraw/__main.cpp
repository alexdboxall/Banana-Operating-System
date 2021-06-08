#include <stdint.h>

void start(void* s);
void begin(void* s)
{
	start(s);
}

#include "main.hpp"

#include "core/main.hpp"
#include "core/terminal.hpp"
#include "core/physmgr.hpp"
#include "thr/prcssthr.hpp"
#include "reg/registry.hpp"
#include "hal/intctrl.hpp"
#include "hw/acpi.hpp"
#include "fs/vfs.hpp"

extern "C" {
	#include "libk/string.h"
}

#include "context.hpp"
#include "gdo.hpp"
#include "region.hpp"
#include "rect.hpp"
#include "cursor.hpp"
#include "lgcyfont.hpp"
#include "ellipse.hpp"
#include "rootrgn.hpp"

namespace Krnl
{
	void (*guiPanicHandler)(char*);
}

void start(void* s)
{
	extern Video* screen;

	kprintf("CLIPDRAW STARTED.\n");
	legacyFontInit();
	setupCursor();

	Context* ctxt = new Context(screen);
	Region* window = new Region(0, 0, ctxt->width, ctxt->height, ctxt);
	window->parent = nullptr;
	rootRgn.region = window;

	Rectangle* rect = new Rectangle(0, 0, ctxt->width, ctxt->height, 0x00AAAA, ctxt);
	window->addChild(rect);

	Brush* b1 = new Brush(BrushType::HatchForwardDiagonal);
	Brush* b2 = new Brush(BrushType::HatchBackwardDiagonal);
	Brush* b3 = new Brush(BrushType::HatchCross);
	Brush* b4 = new Brush(BrushType::HatchHorizontal);
	Brush* b5 = new Brush(BrushType::HatchDiagonalCross);
	Brush* b6 = new Brush(BrushType::HatchVertical);
	Brush* b7 = new Brush(BrushType::DitherHalf);
	Brush* b8 = new Brush(BrushType::DitherQuarter);
	Brush* b9 = new Brush(BrushType::DitherThreeQuarters);
	Brush* bA = new Brush(BrushType::StockBlack);
	Brush* bB = new Brush(BrushType::StockWhite);
	Brush* bC = new Brush(BrushType::DitherDouble);

	
	window->addChild(new Rectangle(50, 50, 100, 100, b1, ctxt));
	window->addChild(new Rectangle(200, 50, 100, 100, b2, ctxt));
	window->addChild(new Rectangle(350, 50, 100, 100, b3, ctxt));
	window->addChild(new Rectangle(500, 50, 100, 100, bA, ctxt));

	window->addChild(new Rectangle(50, 200, 100, 100, b4, ctxt));
	window->addChild(new Rectangle(200, 200, 100, 100, b5, ctxt));
	window->addChild(new Rectangle(350, 200, 100, 100, b6, ctxt));
	window->addChild(new Rectangle(500, 200, 100, 100, bB, ctxt));

	window->addChild(new Rectangle(50, 350, 100, 100, b7, ctxt));
	window->addChild(new Rectangle(200, 350, 100, 100, b8, ctxt));
	window->addChild(new Rectangle(350, 350, 100, 100, b9, ctxt));
	window->addChild(new Rectangle(500, 350, 100, 100, bC, ctxt));

	Region* rgn1 = new Region(10, 10, 300, 200, ctxt);
	window->addChild(rgn1);
	rgn1->addChild(new Rectangle(0, 0, 300, 200, 0x0000FF, rgn1->context));

	Brush* bz = new Brush(BrushType::HatchDiagonalCross);
	bz->bg = 0x00FF00;
	Brush* by = new Brush(BrushType::HatchBackwardDiagonal);
	by->bg = 0xFF8800;

	Region* rgn2 = new Region(50, 50, 200, 120, rgn1->context);
	rgn1->addChild(rgn2);
	rgn2->addChild(new Rectangle(0, 0, 70, 70, bz, rgn2->context));
	rgn2->addChild(new Ellipse(100, 20, 85, 70, by, rgn2->context));

	window->addChild(new LegacyTextObject(getLegacyFont(LegacyFontType::System), \
					 "The System font!", 50, 450, 0, ctxt));

	window->addChild(new LegacyTextObject(getLegacyFont(LegacyFontType::Serif), \
					 "Times New Roman!", 150, 450, 0, ctxt));
	
	window->addChild(new LegacyTextObject(getLegacyFont(LegacyFontType::Comic), \
					 "Comic Sans! :)", 260, 450, 0, ctxt));

	window->addChild(new LegacyTextObject(getLegacyFont(LegacyFontType::SansSerif), \
					 "Arial is so boring...", 350, 450, 0, ctxt));
	

	window->addChild(new LegacyTextObject(getLegacyFont(LegacyFontType::Mono), \
					 "Courier for programming...", 450, 450, 0, ctxt));

	window->addChild(new LegacyTextObject(getLegacyFont(LegacyFontType::Mono2), \
					 "PUT MOUSE IN TOP RIGHT CORNER TO TEST BSOD", 350, 465, 0, ctxt));
	

	//window->addChild(new Region(100, 150, 400, 300, ctxt));
	//window->addChild(new Region(200, 100, 200, 300, ctxt));

	Region* testWindow = new Region(170, 130, 300, 200, ctxt);
	testWindow->parent = window;
	
	Rectangle* r1 = new Rectangle(0, 0, 300, 200, 0xAAAAAA, ctxt);
	testWindow->addChild(r1);
	Rectangle* r2 = new Rectangle(0, 0, 300, 20, 0x0000FF, ctxt);
	testWindow->addChild(r2);
	window->addChild(testWindow);

	window->update(nullptr, 1);
	testWindow->update(nullptr, 1);
	startMouse();
	processMouse(300, 200, 0);

	while (1) {
		blockTask(TaskState::Paused);
	}
}
