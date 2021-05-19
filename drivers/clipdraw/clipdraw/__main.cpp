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
#include "hw/ports.hpp"
#include "hw/acpi.hpp"
#include "fs/vfs.hpp"

extern "C" {
	#include "libk/string.h"
}

#include "context.hpp"
#include "gdo.hpp"
#include "region.hpp"
#include "rect.hpp"


void start(void* s)
{
	kprintf("CLIPDRAW STARTED.\n");
	extern Video* screen;

	Context* ctxt = new Context(screen);
	Region* window = new Region(0, 0, ctxt->width, ctxt->height, ctxt);

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

	/*Rectangle* rect = new Rectangle(0, 0, ctxt->width, ctxt->height, 0x008080, ctxt);
	window->addChild(rect);*/
	
	/*window->addChild(new Rectangle(50, 50, 100, 100, b1, ctxt));
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
	window->addChild(new Rectangle(500, 350, 100, 100, bC, ctxt));*/

	window->addChild(new Region(10, 10, 300, 200, ctxt));
	//window->addChild(new Region(100, 150, 40, 300, ctxt));
	window->addChild(new Region(200, 100, 200, 300, ctxt));

	window->update();

	while (1) {
		blockTask(TaskState::Paused);
	}
}
