#include "region.hpp"

void regnDrawFunc(GDO* gdo)
{

}

Region::Region(int x, int y, int w, int h, Context* ctxt) : GDO(GDOType::Region, ctxt)
{
	dataRegion.x = x;
	dataRegion.y = y;
	dataRegion.w = w;
	dataRegion.h = h;

	contextDrawFunc = regnDrawFunc;
}