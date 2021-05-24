#pragma once

#include "context.hpp"
#include "gdo.hpp"

enum class LegacyFontType
{
	System,
	Mono,
	Mono2,
	Serif,
	SansSerif,
	Comic,
};

LegacyFont getLegacyFont(LegacyFontType type);

struct LegacyTextObject : public GDO
{
	LegacyTextObject(LegacyFont fnt, const char* string, int x, int y, uint32_t colour, Context* ctxt);
	LegacyTextObject(const char* string, int x, int y, uint32_t colour, Context* ctxt);
};

void legacyFontInit();