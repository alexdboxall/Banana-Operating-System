#pragma once

#include "context.hpp"
#include "gdo.hpp"
#include "brush.hpp"

struct Ellipse: public GDO
{
	Ellipse(int x, int y, int w, int h, uint32_t col, Context* context);
	Ellipse(int x, int y, int w, int h, Brush* brush, Context* context);
};