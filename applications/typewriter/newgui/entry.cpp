
#include <stdio.h>
#include <string.h>
#include <udraw/banana.hpp>
extern "C" {
    #include <unistd.h>
    #include <dirent.h>
}

NTextField* txtf;

int saveCmd(NButton* btn)
{
    FILE* f = fopen("C:/test.txt", "wb");
    fwrite(txtf->getText(), strlen(txtf->getText()), 1, f);
    fclose(f);
    return 0;
}

extern "C" int main(int argc, char** argv) {
    createSystemBrushes();

    NTopLevel* win = new NTopLevel("Typewriter", 600, 400, WIN_FLAGS_DEFAULT_0 | WIN_FLAGS_0_HIDDEN | WIN_FLAGS_0_PRETTY);
       
    txtf = new NTextField(15, 60, 570, 295, win, "");
    txtf->setTextWrap(TextWrap::Word);

    txtf->resize(win->getWidth() - 30, win->getHeight() - 75);

    if (argc == 2) {
        FILE* f = fopen(argv[1], "r");
        if (f) {
            fseek(f, 0, SEEK_END);
            long size = ftell(f);
            rewind(f);
            char* data = (char*) malloc(size + 2);
            fread(data, size, 1, f);
            fclose(f);
            txtf->setText(data);
        }
    } else {
        txtf->setText("");
    }

    win->add(txtf);

    {
        NButton* btn = new NButton(15, 30, 24, 24, win, "");
        btn->setIcon("C:/Banana/Icons/Office/new.tga");
        btn->setStyle(ButtonStyle::PopOut);
        win->add(btn);
    }
    {
        NButton* btn = new NButton(15 + 25 * 1, 30, 24, 24, win, "");
        btn->setIcon("C:/Banana/Icons/Office/open.tga");
        btn->setStyle(ButtonStyle::PopOut);
        win->add(btn);
    }
    {
        NButton* btn = new NButton(15 + 25 * 2, 30, 24, 24, win, "");
        btn->setIcon("C:/Banana/Icons/Office/save.tga");
        btn->setStyle(ButtonStyle::PopOut);  
        btn->setCommand(saveCmd);
        win->add(btn);
    }
    // --------------------------------
    {
        NButton* btn = new NButton(15 + 25 * 3 + 10, 30, 24, 24, win, "");
        btn->setIcon("C:/Banana/Icons/Office/print.tga");
        btn->setStyle(ButtonStyle::PopOut);
        win->add(btn);
    }
    // --------------------------------
    {
        NButton* btn = new NButton(15 + 25 * 5 + 20, 30, 24, 24, win, "");
        btn->setIcon("C:/Banana/Icons/Office/copy.tga");
        btn->setStyle(ButtonStyle::PopOut);
        win->add(btn);
    }
    {
        NButton* btn = new NButton(15 + 25 * 6 + 20, 30, 24, 24, win, "");
        btn->setIcon("C:/Banana/Icons/Office/paste.tga");
        btn->setStyle(ButtonStyle::PopOut);
        win->add(btn);
    }
    // --------------------------------
    {
        NButton* btn = new NButton(15 + 25 * 7 + 30, 30, 24, 24, win, "");
        btn->setIcon("C:/Banana/Icons/Office/undo.tga");
        btn->setStyle(ButtonStyle::PopOut);
        win->add(btn);
    }
    {
        NButton* btn = new NButton(15 + 25 * 8 + 30, 30, 24, 24, win, "");
        btn->setIcon("C:/Banana/Icons/Office/redo.tga");
        btn->setStyle(ButtonStyle::PopOut);
        win->add(btn);
    }
    
    win->initialise();

    while (1) {        
        NiEvent evnt = win->process();

        switch (evnt.type) {
        case EVENT_TYPE_RESIZED:
        case EVENT_TYPE_RESIZE_DOWN:
            txtf->resize(win->getWidth() - 30, win->getHeight() - 105);
            win->defaultEventHandler(evnt);
            break;

        default:
            win->defaultEventHandler(evnt);
            break;
        }
    }
    
    return 0;
}

