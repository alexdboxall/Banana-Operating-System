//
//  Entry.hpp
//  gui
//
//  Created by Alex Boxall on 10/3/20.
//  Copyright © 2020 Alex Boxall. All rights reserved.
//

#ifndef Label_hpp
#define Label_hpp

#include "Control.hpp"
#include "rectangle.hpp"
#include "character.hpp"

class Label: public Control {
private:
protected:
	char* text;
	int textAllocLength;
	Font* font;

	static const int maxCharacters = 512;
	Character* currentCharacters[maxCharacters];

public:
	void setText(const char* text);
	char* getText();

	void paint();

    Label(Control* parent, int x, int y, const char* text = "", int w = 400, int h = 20);
};

#endif /* Control_hpp */
