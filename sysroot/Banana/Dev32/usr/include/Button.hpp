//
//  Entry.hpp
//  gui
//
//  Created by Alex Boxall on 10/3/20.
//  Copyright © 2020 Alex Boxall. All rights reserved.
//

#ifndef Button_hpp
#define Button_hpp

#include "Control.hpp"
#include "Label.hpp"
#include "rectangle.hpp"
#include "character.hpp"

class Button: public Control {
private:
protected:
	void paint();

	Rectangle* innerRect;
	Label* theLabel;

	EventHandler command;
	Control* commandMaster;
	
	void defaultButtonHandler(Control* sender, Event e);

public:
	void setText(const char* text);
	char* getText();

	void setPosition(int xpos, int ypos);

	void setCommand(Control* master, EventHandler command);

    Button(Control* parent, int x, int y, const char* text = "", int w = 100, int h = 25);
};

#endif /* Control_hpp */
