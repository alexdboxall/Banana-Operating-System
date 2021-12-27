
#include <stdio.h>
#include <string.h>
#include <udraw/banana.hpp>
extern "C" {
    #include <unistd.h>
    #include <dirent.h>
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



extern "C" int main() {
    createSystemBrushes();

    mainwin = new NTopLevel("Minesweeper", 750, 450, WIN_FLAGS_DEFAULT_0 | WIN_FLAGS_0_HIDDEN | WIN_FLAGS_0_PRETTY);

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

    NLoadedBitmap* bmp = new NLoadedBitmap("C:/Banana/Icons/minemine.tga");
    mainwin->add(easy);
    mainwin->add(nrml);
    mainwin->add(hard);
    mainwin->setIcon(bmp);
    mainwin->initialise();

    while (1) {
        mainwin->defaultEventHandler(mainwin->process());
    }
    
    return 0;
}

