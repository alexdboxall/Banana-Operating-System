#include "rect.hpp"

void rectDrawFunc(GDO* obj)
{
	obj->context->fillRect(obj->dataShape.x, obj->dataShape.y, obj->dataShape.w, obj->dataShape.h, obj->dataShape.colour);
}

void rectPtnDrawFunc(GDO* obj)
{
	obj->context->fillRect(obj->dataShape.x, obj->dataShape.y, obj->dataShape.w, obj->dataShape.h, (Brush*) obj->dataShape.colour);
}

Rectangle::Rectangle(int x, int y, int w, int h, Brush* brush, Context* ctxt): GDO(GDOType::Rectangle, ctxt)
{
	dataShape.x = x;
	dataShape.y = y;
	dataShape.w = w;
	dataShape.h = h;
	dataShape.colour = (uint32_t) brush;

	contextDrawFunc = rectPtnDrawFunc;
}

Rectangle::Rectangle(int x, int y, int w, int h, uint32_t col, Context* ctxt) : GDO(GDOType::Rectangle, ctxt)
{
	dataShape.x = x;
	dataShape.y = y;
	dataShape.w = w;
	dataShape.h = h;
	dataShape.colour = col;

	contextDrawFunc = rectDrawFunc;
}