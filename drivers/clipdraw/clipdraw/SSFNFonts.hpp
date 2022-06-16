#pragma once

#include <stdint.h>
#include "Region.hpp"
#include "Font.hpp"

bool loadSSFNFont(Font* font, int handle);
Region getSSFNFontRegion(Font* font, int c, int* realW, int* realH);