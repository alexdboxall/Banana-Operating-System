#include "ellipse.hpp"

void elpsDrawFunc(GDO* obj)
{
	obj->context->ellipse(true, obj->dataShape.x, obj->dataShape.y, obj->dataShape.w, obj->dataShape.h, obj->dataShape.colour);
}

void elpsPtnDrawFunc(GDO* obj)
{
	obj->context->ellipse(true, obj->dataShape.x, obj->dataShape.y, obj->dataShape.w, obj->dataShape.h, (Brush*) obj->dataShape.colour);
}

Ellipse::Ellipse(int x, int y, int w, int h, Brush* brush, Context* ctxt): GDO(GDOType::Ellipse, ctxt)
{
	dataShape.x = x;
	dataShape.y = y;
	dataShape.w = w;
	dataShape.h = h;
	dataShape.colour = (uint32_t) brush;

	contextDrawFunc = elpsPtnDrawFunc;
}

Ellipse::Ellipse(int x, int y, int w, int h, uint32_t col, Context* ctxt): GDO(GDOType::Rectangle, ctxt)
{
	dataShape.x = x;
	dataShape.y = y;
	dataShape.w = w;
	dataShape.h = h;
	dataShape.colour = col;

	contextDrawFunc = elpsDrawFunc;
}