//
//  Entry.hpp
//  gui
//
//  Created by Alex Boxall on 10/3/20.
//  Copyright © 2020 Alex Boxall. All rights reserved.
//

#ifndef Entry_hpp
#define Entry_hpp

#include "Control.hpp"
#include "rectangle.hpp"
#include "character.hpp"

class Entry : public Control {
private:
protected:
	Rectangle* innerRect;
	void paint();
	char* text;
	int textAllocLength;
	Font* font;

	static const int maxCharacters = 512;
	Character* currentCharacters[maxCharacters];
	Rectangle* currentHighlights[maxCharacters];

	Rectangle* cursorRect;

	int curStart;
	int curEnd;

	void keyhandler(Control* sender, Event e);
	void clickAndDragHandler(Control* sender, Event e);

	char maskChar = 0;

public:
	void setMaskCharacter(char c = '*');
	void clearMaskCharacter();

	void setText(const char* text);
	char* getText();

    Entry(Control* parent, int x, int y, int w, const char* text = "");
};

#endif /* Control_hpp */
