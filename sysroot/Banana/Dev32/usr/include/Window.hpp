//
//  Window.hpp
//  libgui
//
//  Created by Alex Boxall on 21/4/20.
//  Copyright © 2020 Alex Boxall. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

#include "Control.hpp"

class Window : public Control {
private:

protected:
	friend class Control;

    char windowTitle[256];
    
    int _x;
    int _y;
    int _w;
    int _h;
    
	void internalUpdateXYWH();
	Control* focus;

	bool canClose = false;

	bool isMain = false;
	bool destroyed = false;

public:
    Region* region;

	void _respondToEvents();
    
	void setFocus(bool focus = true);
	bool isFocused();

	void allowClosing(bool mode = true);

    void mainloop();
    
    void defaultWindowResizeHandler(Control* sender, Event e);
    void defaultWindowMoveHandler(Control* sender, Event e);
    
    Window(Window* parent, const char* title = "New Window");
    
    void setTitle(const char* title);
    void setPosition(int x, int y);
    void setSize(int w, int h);

	void setLimits(int minw, int minh, int maxw, int maxh);

	void destroy();
	void terminate(int returnCode);

	void setIcon(const char* filepath, uint32_t transparentColour = 0x99FFFF);
};

#endif /* Window_hpp */
