#pragma once

#include <stdint.h>
#include "Region.hpp"

struct FONTDATA1
{
    char chr;
    uint8_t font[14];
    uint8_t size;
};

struct FONTDATA2
{
    char signature[16];
    struct FONTDATA1 FONTD[256];
};

extern struct FONTDATA2 FONT;

void loadLegacyFonts();
Region getLegacyFontRegion(int fontID, int c, int* realW, int* realH);