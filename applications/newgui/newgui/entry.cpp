
#include <stdio.h>
#include "banana.hpp"

int disableBtn(NButton* btn)
{
    btn->disable();
    return 0;
}

NTextField* txtf;

int alignLeftCmd(NButton* btn)
{
    txtf->setAlignment(TextAlignment::Left); 
    return 0;
}

int alignCentreCmd(NButton* btn)
{
    txtf->setAlignment(TextAlignment::Centre);
    return 0;
}

int alignRightCmd(NButton* btn)
{
    txtf->setAlignment(TextAlignment::Right);
    return 0;
}

int alignJustifyCmd(NButton* btn)
{
    txtf->setAlignment(TextAlignment::Justify);
    return 0;
}

int underlineCmd(NButton* btn)
{
    int start = txtf->getCursorStart();

    if (start != txtf->getCursorEnd()) {
        txtf->insert(start, (char*) "\x7EU100\x7F");
        txtf->insert(txtf->getCursorEnd(), (char*) "\x7EU000\x7F");
    }

    return 0;
}

int formattingCallback(NTextField* t, int pos)
{
    bool underline = false;
    char* text = t->getText();
    for (int i = 0; text[i]; ++i) {
        if (text[i] == '\x7E') {
            if (text[i + 1] == 'U') {
                underline = text[i + 2] == '1';
            }
            i += 5;
            continue;
        }

        if (i == pos) {
            t->enableUnderline(underline);
        }
    }

    return 0;
}

extern "C" int appMain() {
    createSystemBrushes();

    NTopLevel* win = new NTopLevel("My Test Window", 600, 400);
       
    txtf = new NTextField(15, 90, 570, 295, win, "abc def\nThis is \x7EU100\x7Fsome random\x7EU000\x7F text.\nIt has some newlines in it too...\n\nThat was two newlines!\n\n\nThis is now going to be a test of the text wrap. Hopefully, this line should wrap onto the next line, and it should be justified. But, the last line should just be left aligned as usual, so it doesn't look too weird.\nThis should also be left aligned.\nTesting just one more thing..., which is the\n space after a newline thing.\n");
    txtf->setTextWrap(TextWrap::Word);
    txtf->enableHiddenData(0x7E, 0x7F, 4);
    txtf->setFormattingCallback(formattingCallback);
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
        win->add(btn);
    }
    // --------------------------------
    {
        NButton* btn = new NButton(15 + 25 * 3 + 10, 30, 24, 24, win, "");
        btn->setIcon("C:/Banana/Icons/Office/print.tga");
        btn->setStyle(ButtonStyle::PopOut);
        win->add(btn);
    }
    {
        NButton* btn = new NButton(15 + 25 * 4 + 10, 30, 24, 24, win, "");
        btn->setIcon("C:/Banana/Icons/Office/preview.tga");
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
    // --------------------------------
    {
        NButton* btn = new NButton(15 + 25 * 9 + 40, 30, 24, 24, win, "");
        btn->setIcon("C:/Banana/Icons/Office/table.tga");
        btn->setStyle(ButtonStyle::PopOut);
        win->add(btn);
    }
    {
        NButton* btn = new NButton(15 + 25 * 10 + 40, 30, 24, 24, win, "");
        btn->setIcon("C:/Banana/Icons/Office/columns.tga");
        btn->setStyle(ButtonStyle::PopOut);
        win->add(btn);
    }
    // --------------------------------
    {
        NButton* btn = new NButton(15 + 25 * 11 + 50, 30, 24, 24, win, "");
        btn->setIcon("C:/Banana/Icons/Office/paragraph.tga");
        btn->setStyle(ButtonStyle::PopOut);
        win->add(btn);
    }




    {
        NButton* btn = new NButton(15, 60, 24, 24, win, "");
        btn->setIcon("C:/Banana/Icons/Office/bold.tga");
        btn->setStyle(ButtonStyle::PopOut);
        win->add(btn);
    }
    {
        NButton* btn = new NButton(15 + 25 * 1, 60, 24, 24, win, "");
        btn->setIcon("C:/Banana/Icons/Office/italic.tga");
        btn->setStyle(ButtonStyle::PopOut);
        win->add(btn);
    }
    {
        NButton* btn = new NButton(15 + 25 * 2, 60, 24, 24, win, "");
        btn->setIcon("C:/Banana/Icons/Office/underline.tga");
        btn->setStyle(ButtonStyle::PopOut);
        btn->setCommand(underlineCmd);
        win->add(btn);
    }
    // --------------------------------
    {
        NButton* btn = new NButton(15 + 25 * 3 + 10, 60, 24, 24, win, "");
        btn->setIcon("C:/Banana/Icons/Office/left.tga");
        btn->setStyle(ButtonStyle::PopOut);
        win->add(btn);
        btn->setCommand(alignLeftCmd);
    }
    {
        NButton* btn = new NButton(15 + 25 * 4 + 10, 60, 24, 24, win, "");
        btn->setIcon("C:/Banana/Icons/Office/centre.tga");
        btn->setStyle(ButtonStyle::PopOut);
        win->add(btn);
        btn->setCommand(alignCentreCmd);
    }
    {
        NButton* btn = new NButton(15 + 25 * 5 + 10, 60, 24, 24, win, "");
        btn->setIcon("C:/Banana/Icons/Office/right.tga");
        btn->setStyle(ButtonStyle::PopOut);
        btn->setCommand(alignRightCmd);
        win->add(btn);
    }
    {
        NButton* btn = new NButton(15 + 25 * 6 + 10, 60, 24, 24, win, "");
        btn->setIcon("C:/Banana/Icons/Office/justify.tga");
        btn->setStyle(ButtonStyle::PopOut);
        win->add(btn);
        btn->setCommand(alignJustifyCmd);
    }
    // --------------------------------
    {
        NButton* btn = new NButton(15 + 25 * 7 + 20, 60, 24, 24, win, "");
        btn->setIcon("C:/Banana/Icons/Office/numpnt.tga");
        btn->setStyle(ButtonStyle::PopOut);
        win->add(btn);
    }
    {
        NButton* btn = new NButton(15 + 25 * 8 + 20, 60, 24, 24, win, "");
        btn->setIcon("C:/Banana/Icons/Office/dotpnt.tga");
        btn->setStyle(ButtonStyle::PopOut);
        win->add(btn);
    }

    win->initialise();

    while (1) {
        NiEvent evnt = win->process();

        switch (evnt.type) {

        default:
            win->defaultEventHandler(evnt);
            break;
        }
    }
    
    return 0;
}

