#pragma once

#include "context.hpp"
#include "gdo.hpp"
#include "brush.hpp"

struct Rectangle: public GDO
{
	Rectangle(int x, int y, int w, int h, uint32_t col, Context* context);
	Rectangle(int x, int y, int w, int h, Brush* brush, Context* context);
};