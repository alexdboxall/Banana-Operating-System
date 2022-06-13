#pragma once

#include <stdint.h>
#include "Region.hpp"
#include "Video.hpp"

void fillRegion(Screen scr, Region rgn, uint32_t colour);
uint32_t drawCharacter(Screen scr, Region rgn, int inX, int inY, uint32_t colour, char c);
