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
    return 0;
}    

void addWindow(Window* parent, Window* child)
{
    
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


struct regs
{
    //PUSHED LATER				PUSHED EARLIER
    //POPPED EARLIER			POPPED LATER
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;

    //VM8086 ONLY
    unsigned int v86es, v86ds, v86fs, v86gs;
};

void debugwritestrhx(char* t, uint32_t hx);

uint64_t sysWSBE(struct regs* r)
{
    if (r->ebx == WSBE_CREATE_WINDOW) {
        struct MoreArgs* ma = (struct MoreArgs*) r->ecx;

        Window* win = (Window*) malloc(sizeof(Window));
        Window_init(win, ma->x, ma->y, ma->w, ma->h, ma->flags, 0);
        Window_set_title(win, "");
        win->hasProc = true;
        return (size_t) win;

    } else if (r->ebx == WSBE_SET_WINDOW_TITLE) {
        Window_set_title((Window*) r->ecx, (char*) r->edx);
        return 0;

    } else if (r->ebx == WSBE_UPDATE_WINDOW) {
        Window_paint((Window*) r->ecx, 0, 1);
        return 0;

    } else if (r->ebx == WSBE_ADD_WINDOW) {
        Window_insert_child((Window*) r->ecx, (Window*) r->edx);
        return 0;

    } else if (r->ebx == WSBE_GET_DESKTOP) {
        return (size_t) desktop;

    } else if (r->ebx == WSBE_SET_SCRIPT) {
        struct MoreArgs* ma = (struct MoreArgs*) r->ecx;

        Window* win = (Window*) ma->obj;
        memcpy(win->repaintScript, (const void*) r->edx, ma->flags);
        win->repaintScript[ma->flags] = OP_END;
        return 0;
    }

    return 0;
}