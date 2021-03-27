#include "interface.h"
#include "libk/string.h"

void updateWindow(Window* window, int sx, int sy, List* dr, int pc);

Desktop* getDesktop()
{
    return desktop;
}

Message blankMessage(Window* window)
{
    Message m;
    m.window = window;
    m.type = MESSAGE_NULL;

    //TODO: set all of the keyboard / mouse bits

    return m;
}

void debugwrite(char* t);
void dispatchMessage(Window* window, Message msg)
{
    debugwrite("Dispatching message");
    if (window->messageCount == WINDOW_MAX_MESSAGE) {
        return;
    }
    window->messages[window->messageCount++] = msg;
    debugwrite("Dispatched message");
}

int getMessage(Window* window, Message* msg)
{
    debugwrite("Get message called");

    if (!window->messageCount) {
        debugwrite("No message");
        return 0;
    }

    *msg = window->messages[--window->messageCount];
    for (int i = 0; i < window->messageCount; ++i) {
        window->messages[i] = window->messages[i + 1];
    }

    debugwrite("There was a message");

    return window->messageCount + 1;
}

int guiDefaultProc(Window* window, Message msg)
{

}

Window* createWindow(int x, int y, int w, int h, int flags)
{
    Window* win = (Window*) malloc(sizeof(Window));
    //win->paint_function = updateWindow;
    Window_init(win, x, y, w, h, flags, 0);
    Window_set_title(win, "");
    return win;
}    

void addWindow(Window* parent, Window* child)
{
    Window_insert_child(parent, child);
    Window_paint((Window*) desktop, (List*) 0, 1);
}

void updateWindow(Window* window, int sx, int sy, List* dr, int pc)
{
    Message m = blankMessage(window);
    m.type = MESSAGE_PAINT;
    m.dispx = sx;
    m.dispy = sy;
    m.dr = dr;
    m.paintChildren = pc;
    dispatchMessage(m.window, m);
}

void raiseWindow(Window* window)
{
	Window_raise(window, 1);
}

void setWindowTitle(Window* window, char* title)
{
    Window_set_title(window, title);
}

Context* getWindowContext(Window* window)
{
	return window->context;
}