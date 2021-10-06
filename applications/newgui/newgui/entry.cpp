
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

#include <time.h>
NButton* cells[30][30];
bool mines[30][30];
uint8_t state[30][30];

#define CELL_STATE_UNKNOWN      0
#define CELL_STATE_QUESTION     1
#define CELL_STATE_FLAGGED      2
#define CELL_STATE_SAFE         3
#define CELL_STATE_EXPLOSION    4

bool firstClick = true;

int GAME_WIDTH = 10;
int GAME_HEIGHT = 10;

bool canRightClick = true;
bool gameLost = false;

bool isMine(int x, int y)
{
    if (x < 0 || y < 0 || x >= GAME_WIDTH || y >= GAME_HEIGHT) return false;
    return mines[y][x];
}

void createMine()
{
    while (true) {
        int x = rand() % GAME_WIDTH;
        int y = rand() % GAME_HEIGHT;
        if (!isMine(x, y)) {
            mines[y][x] = true;
            break;
        }
    }
}

int findPosition(NButton* btn)
{
    for (int y = 0; y < GAME_HEIGHT; ++y) {
        for (int x = 0; x < GAME_WIDTH; ++x) {
            if (cells[y][x] == btn) {
                return y * GAME_WIDTH + x;
            }
        }
    }
    return -1;
}

int getNearbyCount(int x, int y)
{
    int count = 0;
    count += (int) isMine(x - 1, y);
    count += (int) isMine(x + 1, y);
    count += (int) isMine(x, y + 1);
    count += (int) isMine(x, y - 1);
    count += (int) isMine(x - 1, y + 1);
    count += (int) isMine(x + 1, y + 1);
    count += (int) isMine(x - 1, y - 1);
    count += (int) isMine(x + 1, y - 1);
    return count;
}

void setSafe(int x, int y)
{
    if (x < 0 || y < 0 || x >= GAME_WIDTH || y >= GAME_HEIGHT) return;
    if (state[y][x] == CELL_STATE_SAFE) return;
    if (state[y][x] == CELL_STATE_EXPLOSION) return;

    if (isMine(x, y)) {
        if (firstClick) {
            createMine();
            mines[y][x] = false;

        } else {
            cells[y][x]->setText("");
            cells[y][x]->setIcon("C:/Banana/Icons/minemine.tga");
            state[y][x] = CELL_STATE_EXPLOSION;
            gameLost = true;

            for (int y = 0; y < GAME_HEIGHT; ++y) {
                for (int x = 0; x < GAME_WIDTH; ++x) {
                    if (mines[y][x]) {
                        if (state[y][x] == CELL_STATE_UNKNOWN || state[y][x] == CELL_STATE_QUESTION) {
                            cells[y][x]->setIcon("C:/Banana/Icons/minemine2.tga");
                        }
                    } else if (state[y][x] == CELL_STATE_FLAGGED) {
                        cells[y][x]->setIcon("C:/Banana/Icons/minewrong.tga");
                    }
                }
            }
            return;
        }
    }

    firstClick = false;

    state[y][x] = CELL_STATE_SAFE;

    int nearby = getNearbyCount(x, y);
    if (nearby == 0) {
        cells[y][x]->removeIcon();
        cells[y][x]->setText("-");

        setSafe(x - 1, y);
        setSafe(x + 1, y);
        setSafe(x, y + 1);
        setSafe(x, y - 1);
        setSafe(x - 1, y + 1);
        setSafe(x + 1, y + 1);
        setSafe(x - 1, y - 1);
        setSafe(x + 1, y - 1);

    } else {
        uint32_t fgcols[] = {
            0x0000FF,
            0x008000,
            0xFF0000,
            0x000080,
            0x800000,
            0x008080,
            0x000000,
            0x808080,
        };

        char txt[5];
        sprintf(txt, "%d", nearby);
        cells[y][x]->removeIcon();
        cells[y][x]->setForegroundColour(fgcols[nearby - 1]);
        cells[y][x]->setText(txt);
    }
}


void rightClickUpCallback(Window* window, void* self_, int mx, int my)
{
    canRightClick = true;
}

void rightClickCallback(Window* window, void* self_, int mx, int my)
{
    if (gameLost) return;

    if (!canRightClick) return;
    canRightClick = false;
    NButton* btn = (NButton*) self_;

    int pos = findPosition(btn);
    int x = pos % GAME_WIDTH;
    int y = pos / GAME_WIDTH;

    if (state[y][x] == CELL_STATE_UNKNOWN) {
        state[y][x] = CELL_STATE_FLAGGED;
        cells[y][x]->setIcon("C:/Banana/Icons/mineflag.tga");
        cells[y][x]->setText("");

    } else if (state[y][x] == CELL_STATE_FLAGGED) {
        state[y][x] = CELL_STATE_QUESTION;
        cells[y][x]->removeIcon();
        cells[y][x]->setText("?");

    } else if (state[y][x] == CELL_STATE_QUESTION) {
        state[y][x] = CELL_STATE_UNKNOWN;
        cells[y][x]->removeIcon();
        cells[y][x]->setText("");
    }
}

NTopLevel* mainwin;

int clickCallback(NButton* btn)
{
    if (gameLost) return 0;

    int pos = findPosition(btn);
    int x = pos % GAME_WIDTH;
    int y = pos / GAME_WIDTH;

    if (state[y][x] == CELL_STATE_FLAGGED) return 0;

    setSafe(x, y);

    bool done = true;
    for (y = 0; y < GAME_HEIGHT; ++y) {
        for (x = 0; x < GAME_WIDTH; ++x) {
            if (state[y][x] != CELL_STATE_SAFE && !mines[y][x]) {
                done = false;
                break;
            }
        }
    }

    if (done) {
        mainwin->setTitle("You won! :)");
    }

    return 0;
}

void newGame(int w, int h)
{
    for (int y = 0; y < 30; ++y) {
        for (int x = 0; x < 30; ++x) {
            if (cells[y][x] != nullptr) {
                mainwin->remove(cells[y][x]);
                delete cells[y][x];
                cells[y][x] = nullptr;
            }
        }
    }

    GAME_WIDTH = w;
    GAME_HEIGHT = h;

    gameLost = false;
    canRightClick = true;

    int numMines = (GAME_WIDTH * GAME_HEIGHT) * 10 / 64 + 1;

    srand(clock());
    firstClick = true;

    for (int y = 0; y < GAME_HEIGHT; ++y) {
        for (int x = 0; x < GAME_WIDTH; ++x) {
            mines[y][x] = false;
            state[y][x] = CELL_STATE_UNKNOWN;
            cells[y][x] = new NButton(30 + x * 25, 90 + y * 25, 25, 25, mainwin, " ", ButtonStyle::AlwaysPopOut);
            cells[y][x]->disableAutomaticInvalidation();
            cells[y][x]->setCommand(clickCallback);
            cells[y][x]->enableBold();
            cells[y][x]->setRightMouseDownHandler(rightClickCallback);
            cells[y][x]->setRightMouseUpHandler(rightClickUpCallback);
            mainwin->add(cells[y][x]);
            cells[y][x]->enableAutomaticInvalidation();
        }
    }

    for (int i = 0; i < numMines; ++i) {
        createMine();
    }

    mainwin->repaint();
}

int easyGame(NButton* btn)
{
    newGame(10, 10);
    return 0;
}

int nrmlGame(NButton* btn)
{
    newGame(15, 15);
    return 0;
}

int hardGame(NButton* btn)
{
    newGame(25, 15);
    return 0;
}

void gui2()
{
    mainwin = new NTopLevel("Minesweeper", 750, 450);

    for (int y = 0; y < 30; ++y) {
        for (int x = 0; x < 30; ++x) {
            cells[y][x] = nullptr;
        }
    }

    NButton* easy = new NButton(30, 30, 80, 28, mainwin, "Easy", ButtonStyle::AlwaysPopOut);
    NButton* nrml = new NButton(130, 30, 80, 28, mainwin, "Normal", ButtonStyle::AlwaysPopOut);
    NButton* hard = new NButton(230, 30, 80, 28, mainwin, "Hard", ButtonStyle::AlwaysPopOut);

    easy->setCommand(easyGame);
    nrml->setCommand(nrmlGame);
    hard->setCommand(hardGame);

    mainwin->add(easy);
    mainwin->add(nrml);
    mainwin->add(hard);

}

uint8_t* desktopBuffer;
uint32_t desktopColours[128];
int desktopWidth = 0;
int desktopHeight = 0;
int desktopTaskbarHeight = 32;

extern "C" uint64_t SystemCall(size_t, size_t, size_t, size_t);

uint8_t encodeDesktopColour(uint32_t rgb, bool t)
{
    int r = (rgb >> 16) & 0xFF;
    int g = (rgb >> 8) & 0xFF;
    int b = (rgb >> 0) & 0xFF;

    r += 40;
    r *= 3;
    r /= 255;

    g += 20;
    g *= 7;
    g /= 255;

    b += 40;
    b *= 3;
    b /= 255;

    uint32_t out = (r << 5) | (g << 2) | b;

    return out;
}

void desktop()
{
    for (int i = 0; i < 128; ++i) {
        desktopColours[i] = 0;
    }
    desktopColours[0] = 0x808080;
    desktopColours[1] = 0xC0C0C0;

    uint32_t wh = SystemCall((size_t) SystemCallNumber::WSBE, LINKCMD_RESUPPLY_DESKTOP, 1, (size_t) desktopColours);
    desktopWidth = wh >> 16;
    desktopHeight = wh & 0xFFFF;

    desktopBuffer = (uint8_t*) malloc(desktopWidth * desktopHeight);
    
    NLoadedBitmap* nbmp = new NLoadedBitmap("C:/Banana/System/crisp.tga");

    int i = 0;
    for (int y = 0; y < desktopHeight; ++y) {
        for (int x = 0; x < desktopWidth; ++x) {
            int ax = (x * nbmp->width) / desktopWidth;
            int px = (x * nbmp->width) % desktopWidth;
            int ay = (y * nbmp->height) / desktopHeight;
            int py = (y * nbmp->height) % desktopHeight;

            uint32_t norm = nbmp->data[ay * nbmp->width + ax];
            uint32_t side = nbmp->data[ay * nbmp->width + ax + 1];
            uint32_t down = nbmp->data[(ay + 1) * nbmp->width + ax];
            uint32_t diag = nbmp->data[(ay + 1) * nbmp->width + ax + 1];

            int rN = (norm >> 16) & 0xFF;
            int rS = (side >> 16) & 0xFF;
            int rD = (down >> 16) & 0xFF;
            int rG = (diag >> 16) & 0xFF;

            int gN = (norm >> 8) & 0xFF;
            int gS = (side >> 8) & 0xFF;
            int gD = (down >> 8) & 0xFF;
            int gG = (diag >> 8) & 0xFF;
            
            int bN = (norm >> 0) & 0xFF;
            int bS = (side >> 0) & 0xFF;
            int bD = (down >> 0) & 0xFF;
            int bG = (diag >> 0) & 0xFF;

            int npx = desktopWidth - px;
            int npy = desktopHeight - py;
            px = px * 256 / desktopWidth;
            npx = npx * 256 / desktopWidth;
            py = py * 256 / desktopHeight;
            npy = npy * 256 / desktopHeight;

            int mr = (rN * (npx + npy) + rS * (px + npy) + rD * (npx + py) + rG * (px + py)) / 1024;
            int mg = (gN * (npx + npy) + gS * (px + npy) + gD * (npx + py) + gG * (px + py)) / 1024;
            int mb = (bN * (npx + npy) + bS * (px + npy) + bD * (npx + py) + bG * (px + py)) / 1024;
            desktopBuffer[i++] = encodeDesktopColour((mr << 16) | (mg << 8) | mb, (x + y) & 1);

            //desktopBuffer[i++] = 0x37;
            //desktopBuffer[i++] = encodeDesktopColour(nbmp->data[ay * nbmp->width + ax]);
        }
    }

    delete nbmp;

    
    DIR* dir;
    struct dirent* ent;
    int diri = 0;
    NLoadedBitmap* dirico = new NLoadedBitmap("C:/Banana/Icons/colour/folder.tga");
    NLoadedBitmap* textico = new NLoadedBitmap("C:/Banana/Icons/colour/text.tga");
    NLoadedBitmap* otherico = new NLoadedBitmap("C:/Banana/Icons/colour/file.tga");
    NLoadedBitmap* exeico = new NLoadedBitmap("C:/Banana/Icons/colour/exe.tga");

    int iconsPerColumn = (desktopHeight - desktopTaskbarHeight - 16) / 64;

    if ((dir = opendir("C:/Banana/System")) != NULL) {
        while ((ent = readdir(dir)) != NULL) {       

            int lastFullStopPtr = -1;
            for (int i = 0; ent->d_name[i]; ++i) {
                if (ent->d_name[i] == '.') {
                    lastFullStopPtr = i;
                }
            }

            char ext[32];
            memset(ext, 0, 32);
            int j = 0;
            if (lastFullStopPtr != -1) {
                for (int i = lastFullStopPtr + 1; ent->d_name[i] && j < 31; ++i) {
                    ext[j++] = ent->d_name[i];
                }
            }

            int baseX = (diri / iconsPerColumn) * 64 + 25;
            int baseY = (diri % iconsPerColumn) * 64 + 10;

            NLoadedBitmap* ico;
            if (ent->d_type & DT_DIR) {
                ico = dirico;
            } else {
                if (!strcasecmp("TXT", ext)) {
                    ico = textico;
                } else if (!strcasecmp("EXE", ext)) {
                    ico = exeico;
                } else if (!strcasecmp("COM", ext)) {
                    ico = exeico;
                } else {
                    ico = otherico;
                }
            }

            for (int y = 0; y < ico->height; ++y) {
                for (int x = 0; x < ico->width; ++x) {
                    if (ico->data[y * ico->width + x] == 0) continue;
                    desktopBuffer[(baseY + y) * desktopWidth + baseX + x] = encodeDesktopColour(ico->data[y * ico->width + x] & 0xFFFFFF, false);
                }
            }

            ++diri;
        }
        closedir(dir);

    } else {
        
    }

    for (int y = desktopHeight - desktopTaskbarHeight; y < desktopHeight; ++y) {
        for (int x = 0; x < desktopWidth; ++x) {
            desktopBuffer[y * desktopWidth + x] = \
                (y == desktopHeight - desktopTaskbarHeight) ? 128 : \
                (y == desktopHeight - desktopTaskbarHeight + 1) ? 127 : 129;
        }
    }

    delete exeico;
    delete dirico;
    delete textico;
    delete otherico;

    SystemCall((size_t) SystemCallNumber::WSBE, LINKCMD_RESUPPLY_DESKTOP, 0, (size_t) desktopBuffer);
}

extern "C" int main() {
    createSystemBrushes();

    desktop();

    gui2();

    NTopLevel* win = new NTopLevel("Sentences - *Untitled Document", 600, 400, WIN_FLAGS_DEFAULT_0 | WIN_FLAGS_0_HIDDEN | WIN_FLAGS_0_PRETTY);
       
    txtf = new NTextField(15, 90, 570, 295, win, "When the master of the lamp says bow, you bow!\nYou forget who wears the pants around here now\nA man who knows just what to do\nAnd who to do it to\nWho's he? M-E!\n");
    txtf->setTextWrap(TextWrap::Word);
    txtf->enableHiddenData(0x7E, 0x7F, 6);
    txtf->setFormattingCallback(formattingCallback);
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

    mainwin->initialise();

    while (1) {
        mainwin->defaultEventHandler(mainwin->process());
        
        NiEvent evnt = win->process();
        switch (evnt.type) {

        default:
            win->defaultEventHandler(evnt);
            break;
        }
    }
    
    return 0;
}

