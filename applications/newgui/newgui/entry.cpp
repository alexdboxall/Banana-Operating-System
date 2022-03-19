
#include <stdio.h>
#include <string.h>
#include <udraw/banana.hpp>
extern "C" {
    #include <unistd.h>
    #include <dirent.h>
}

int disableBtn(NButton* btn)
{
    btn->disable();
    return 0;
}

NTextField* txtf;

#define FMT_CMD_UNDERLINE       0
#define FMT_CMD_FOREGROUND_COL  1
#define FMT_CMD_BOLD            2
#define FMT_CMD_SET_ALIGN       3

#define FMT_ARG_ALIGN_LEFT      0
#define FMT_ARG_ALIGN_CENTRE    1
#define FMT_ARG_ALIGN_RIGHT     2
#define FMT_ARG_ALIGN_JUSTIFY   3

void insertCommand(uint16_t cmd, uint32_t arg, NTextField* t, int pos)
{
    uint64_t data = arg;
    data <<= 12;
    data |= cmd;

    uint8_t x[12];
    x[0] = 0x7E;
    x[1] = ((data >> 35) & 0x7F) | 0x80;
    x[2] = ((data >> 28) & 0x7F) | 0x80;
    x[3] = ((data >> 21) & 0x7F) | 0x80;
    x[4] = ((data >> 14) & 0x7F) | 0x80;
    x[5] = ((data >> 7) & 0x7F) | 0x80;
    x[6] = ((data >> 0) & 0x7F) | 0x80;
    x[7] = 0x7F;
    x[8] = 0;

    t->insert(pos, (char*) x);
}


int alignLeftCmd(NButton* btn)
{
    insertCommand(FMT_CMD_SET_ALIGN, FMT_ARG_ALIGN_LEFT, txtf, txtf->getCursorEnd());
    
    //txtf->setAlignment(TextAlignment::Left);
    return 0;
}

int alignCentreCmd(NButton* btn)
{
    insertCommand(FMT_CMD_SET_ALIGN, FMT_ARG_ALIGN_CENTRE, txtf, txtf->getCursorEnd());

    //txtf->setAlignment(TextAlignment::Centre);
    return 0;
}

int alignRightCmd(NButton* btn)
{
    insertCommand(FMT_CMD_SET_ALIGN, FMT_ARG_ALIGN_RIGHT, txtf, txtf->getCursorEnd());

    //txtf->setAlignment(TextAlignment::Right);
    return 0;
}

int alignJustifyCmd(NButton* btn)
{
    insertCommand(FMT_CMD_SET_ALIGN, FMT_ARG_ALIGN_JUSTIFY, txtf, txtf->getCursorEnd());

    //txtf->setAlignment(TextAlignment::Justify);
    return 0;
}

int saveCmd(NButton* btn)
{
    FILE* f = fopen("C:/test.doc", "wb");
    fwrite(txtf->getText(), strlen(txtf->getText()), 1, f);
    fclose(f);
    return 0;
}

int underlineCmd(NButton* btn)
{
    int lowly = txtf->getCursorStart();
    int high = txtf->getCursorEnd();
    if (lowly == high) return 0;

    if (lowly > high) {
        int temp = lowly;
        lowly = high;
        high = lowly;
    }

    insertCommand(FMT_CMD_UNDERLINE, 0, txtf, high);
    insertCommand(FMT_CMD_UNDERLINE, 1, txtf, lowly);

    return 0;
}

int boldCmd(NButton* btn)
{
    int lowly = txtf->getCursorStart();
    int high = txtf->getCursorEnd();
    if (lowly == high) return 0;

    if (lowly > high) {
        int temp = lowly;
        lowly = high;
        high = lowly;
    }

    insertCommand(FMT_CMD_BOLD, 0, txtf, high);
    insertCommand(FMT_CMD_BOLD, 1, txtf, lowly);

    return 0;
}

int formattingCallback(NTextField* t, int pos)
{
    char* text = t->getText();

    static int i = -1;

    static bool underline;
    static bool bold;
    static uint32_t colour;
    static TextAlignment alignment;

    if (pos != i + 1 || i == -1) {
        i = 0;
        alignment = TextAlignment::Left;
        underline = false;
        bold = false;
        colour = 0x000000;
    }

    t->enableUnderline(underline);
    t->setForegroundColour(colour);
    t->enableBold(bold);

    for (; text[i]; ++i) {
        if (text[i] == '\x7E') {
            uint64_t data = 0;
            for (int j = 0; j < 6; ++j) {
                data <<= 7;
                data |= ((uint8_t) text[i + 1 + j]) & 0x7F;
            }
           
            uint16_t cmd = data & 0x3FF;
            uint32_t arg = (data >> 12) & 0xFFFFFFFF;

            if (cmd == FMT_CMD_UNDERLINE) {
                underline = arg & 1;
            }
            if (cmd == FMT_CMD_BOLD) {
                bold = arg & 1;
            }
            if (cmd == FMT_CMD_FOREGROUND_COL) {
                colour = arg & 0xFFFFFF;
            }
            if (cmd == FMT_CMD_SET_ALIGN) {
                if (arg == FMT_ARG_ALIGN_CENTRE)    alignment = TextAlignment::Centre;
                if (arg == FMT_ARG_ALIGN_JUSTIFY)   alignment = TextAlignment::Justify;
                if (arg == FMT_ARG_ALIGN_LEFT)      alignment = TextAlignment::Left;
                if (arg == FMT_ARG_ALIGN_RIGHT)     alignment = TextAlignment::Right;
            }
            i += 7;
            continue;
        }

        if (i == pos) {
            t->disableAutomaticInvalidation();
            t->enableUnderline(underline);
            t->setForegroundColour(colour);
            t->enableBold(bold);
            t->setAlignment(alignment);
            t->enableAutomaticInvalidation();
            t->invalidate();

            break;
        }
    }

    return 0;
}

extern "C" int main(int argc, char** argv) {
    createSystemBrushes();

    NTopLevel* win = new NTopLevel("Sentences - *Untitled Document", 600, 400, WIN_FLAGS_DEFAULT_0 | WIN_FLAGS_0_HIDDEN | WIN_FLAGS_0_PRETTY);
       
    txtf = new NTextField(15, 90, 570, 295, win, "");
    txtf->setTextWrap(TextWrap::Word);
    txtf->enableHiddenData(0x7E, 0x7F, 6);
    txtf->setFormattingCallback(formattingCallback);

    if (argc == 2) {
        FILE* f = fopen(argv[1], "r");
        fseek(f, 0, SEEK_END);
        long size = ftell(f);
        rewind(f);
        char* data = (char*) malloc(size + 2);
        fread(data, size, 1, f);
        fclose(f);
        txtf->setText(data);
    }

    win->add(txtf);

    // "You forget who wears the pants around here now!"

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
        btn->setCommand(boldCmd);
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

    //mainwin->initialise();

    while (1) {
        //mainwin->defaultEventHandler(mainwin->process());
        
        NiEvent evnt = win->process();
        switch (evnt.type) {

        default:
            win->defaultEventHandler(evnt);
            break;
        }
    }
    
    return 0;
}

