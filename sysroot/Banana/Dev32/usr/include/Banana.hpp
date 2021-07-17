//
//  Window.hpp
//  libgui
//
//  Created by Alex Boxall on 21/4/20.
//  Copyright © 2020 Alex Boxall. All rights reserved.
//

#ifndef Banana_hpp
#define Banana_hpp

#include "Control.hpp"
#include "Window.hpp"
#include "Entry.hpp"
#include "Label.hpp"
#include "Button.hpp"
#include "bitmap.hpp"

void setupApplication();
bool isColourDisplay();
bool getFullIconPath(const char* name, char* outbuffer, int n);

#endif /* Window_hpp */
