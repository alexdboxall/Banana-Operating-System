#pragma once

#include "context.hpp"
#include "gdo.hpp"

struct Region: public GDO
{
	Region(int x, int y, int w, int h, Context* context);

	void applyBoundClipping(int in_recursion, List<CRect*>* dirty_regions);
	List<Region*>* getRegionsAbove(Region* window);

};

