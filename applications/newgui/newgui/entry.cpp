
#include <stdio.h>
#include "banana.hpp"

int disableBtn(NButton* btn)
{
    btn->disable();
    return 0;
}

extern "C" int appMain() {
    createSystemBrushes();

    NTopLevel* win = new NTopLevel("My Test Window", 600, 400);
        
    NButton* btn = new NButton(50, 100, 150, 35, win, "My Test Button");
    btn->setCommand(disableBtn);
    win->add(btn);

    {
        NButton* btn2 = new NButton(300, 100, 100, 24, win, "New");
        btn2->setIcon("C:/Banana/Icons/Office/new.tga", ButtonIconPosition::Right);
        btn2->setIconPadding(12);
        win->add(btn2);
    }
    {
        NButton* btn2 = new NButton(300, 140, 100, 24, win, "Open");
        btn2->setIcon("C:/Banana/Icons/Office/open.tga", ButtonIconPosition::Right);
        btn2->setIconPadding(12);
        win->add(btn2);
    }
    {
        NButton* btn2 = new NButton(300, 180, 100, 24, win, "Save");
        btn2->setIcon("C:/Banana/Icons/Office/save.tga", ButtonIconPosition::Right);
        btn2->setIconPadding(12);
        win->add(btn2);
    }
    {
        NButton* btn2 = new NButton(300, 220, 100, 24, win, "Print");
        btn2->setIcon("C:/Banana/Icons/Office/print.tga", ButtonIconPosition::Right);
        btn2->setIconPadding(12);
        win->add(btn2);
    }
    {
        NButton* btn2 = new NButton(300, 260, 100, 24, win, "Copy");
        btn2->setIcon("C:/Banana/Icons/Office/copy.tga", ButtonIconPosition::Right);
        btn2->setIconPadding(12);
        btn2->setTextPadding(12);
        win->add(btn2);
    }
    {
        NButton* btn2 = new NButton(300, 300, 100, 24, win, "Paste");
        btn2->setIcon("C:/Banana/Icons/Office/paste.tga", ButtonIconPosition::Right);
        btn2->setIconPadding(12);
        win->add(btn2);
    }

    win->initialise();

    while (1) {
        NiEvent evnt = win->process();

        switch (evnt.type) {
        case EVENT_TYPE_MOUSE_MOVE:
        case EVENT_TYPE_MOUSE_DRAG:
        case EVENT_TYPE_MOUSE_DOWN:
        case EVENT_TYPE_MOUSE_UP:
        {
            win->processMouse(evnt);
            win->repaintFlush();
            break;
        }

        case EVENT_TYPE_NULL:
            break;

        default:
            if (evnt.needsRedraw) win->repaint();
            break;
        }
    }
    
    return 0;
}

