//
//  Control.hpp
//  gui
//
//  Created by Alex Boxall on 10/3/20.
//  Copyright © 2020 Alex Boxall. All rights reserved.
//

#ifndef Control_hpp
#define Control_hpp

#include "rectangle.hpp"
#include "region.hpp"

#define __GUI__IMPORT_
#include "D:/Users/Alex/Desktop/Banana/kernel/hal/keybrd.hpp"
#undef __GUI__IMPORT_

enum class EventType : int {
    //For 'EVENT_FINAL' to work, these must all be in order starting at zero!
    Load,
    Paint,
    Closing,
    Closed,
    Resized,
	Moved,
	Resizing,
	Moving,
	KeyDown,
	KeyHeld,
	KeyUp,
	MouseDown,
	MouseUp,
	MouseHeld,
	MouseMove,
	MouseDrag,
	Timer,
	InternalControlEvent,
    EVENT_FINAL,
};

class Control;

enum class MouseType: int
{
	None,
	Left,
	Right,
	Middle,
	Button4,
	Button5,
};

struct Event {
    EventType type;

	int x;
	int y;
	int w;
	int h;

	int globalMouseX;
	int globalMouseY;

	int mouseX;
	int mouseY;

	int key;
	int mouseZ;
	MouseType mouseType;

	bool capsLock;
	bool scrollLock;
	bool numlock;
	bool shift;
	bool ctrl;
	bool alt;
};

typedef void (Control::*EventHandler)(Control* sender, Event e);

class EventHandlerSet {
private:
protected:
    
    static constexpr int maxFunctions = 10;
    
    EventHandler functions[maxFunctions];
    EventHandler childHandler;
    
    int nextFunction = 0;
    
    Control* master;
    
public:
    EventHandlerSet(Control* master, EventHandler childInvoker);
    void add(EventHandler handler);
    void handle(Event e);
};

enum class DockMode {
    None,
    Fill,
    Left,
    Right,
    Top,
    Bottom
};

class Window;
class Control {
private:
    void defaultChildInvoker(Control* sender, Event e);
    void defaultResizeHandler(Control* sender, Event e);

protected:
    friend class EventHandlerSet;

    Control* parent;
    
    struct ChildNode {
        ChildNode* next;
        Control* child;
    };
    
    ChildNode* firstChild;
    ChildNode* lastChild;

	Window* masterWindow;		//used to get the currently focused control
        
    int x;
    int y;
    int w;
    int h;
    
    struct {
        int x;
        int y;
        int w;
        int h;
    } renderBounds;
    
    void addChild(Control* child);
    
public:
	GDO* mainRectangle;

	virtual void setFocus(bool focus = true);
	virtual bool isFocused();
	virtual void receivedFocus();
	virtual void lostFocus();

    void recalculatePosition();     //TODO: AFTER DEBUGGING, MAKE THIS PROTECTED

    EventHandlerSet events[(int) EventType::EVENT_FINAL];

    DockMode dock;

    struct {
        int width;
        int height;
    } minimum;
    
    struct {
        int width;
        int height;
    } maximum;
    
    Control(Control* parent);
    Control();
};

extern Event eventQueue;

void addSystemEvent(Event e);
Event removeSystemEvent();
bool isSystemEventEmpty();

#endif /* Control_hpp */
