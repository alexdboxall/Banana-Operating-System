#pragma once

#include "context.hpp"
#include "region.hpp"

struct RootRegion
{
	Region* region;
	int mouseX;
	int mouseY;
	int cursorBase;
};

extern RootRegion rootRgn;