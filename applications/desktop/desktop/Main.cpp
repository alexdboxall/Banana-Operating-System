
#include <udraw/banana.hpp>

extern "C" {
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
}

#include <stdint.h>


uint64_t redAvg;
uint64_t grnAvg;
uint64_t bluAvg;

#define MAX_DESKTOP_FILES 512
#define MAX_DESKTOP_DISPLAY_NAME_LENGTH 18

int leftMostInvalid = -1;
int rightMostInvalid = -1;

struct DesktopFile
{
    uint16_t iconX;
    uint16_t iconY;
    uint16_t textX;
    uint16_t textY;
    uint16_t boundW : 15;
    uint16_t valid : 1;
    uint16_t boundH : 15;
    uint16_t selected : 1;
    NLoadedBitmap* bmp;
    char displayName[MAX_DESKTOP_DISPLAY_NAME_LENGTH];
    char* filepath;
    int assocTypeID;
};

int iconsPerColumn;

struct FileAssociaton
{
    char extension[32];
    NLoadedBitmap* iconBitmap;
    char* openProgram;
    bool valid;
};

#define MAX_DESKTOP_FILE_TYPES 256

NLoadedBitmap* dirico;
NLoadedBitmap* otherico;

DesktopFile files[MAX_DESKTOP_FILES];
FileAssociaton fileAssoc[MAX_DESKTOP_FILE_TYPES];
int nextFileAssoc = 0;
int nextDesktopFile = 0;

uint16_t* desktopBuffer;
uint32_t desktopColours[128];
int desktopWidth = 0;
int desktopHeight = 0;
int desktopTaskbarHeight = 28;
int desktopCellWidth = 86;
int desktopCellHeight = 64;
int desktopIconSize = 32;
Context* desktopContext;


void invalidateDesktopScanline(int line)
{
    desktopContext->invalidatedScanlines[line >> 3] |= 1 << (line & 7);
}

void invalidateLeftAndRight(int x)
{
    if (leftMostInvalid == -1) {
        leftMostInvalid = x;
        rightMostInvalid = x;
        return;
    }

    if (x < leftMostInvalid) {
        leftMostInvalid = x;
    }
    if (x > rightMostInvalid) {
        rightMostInvalid = x;
    }
}

extern "C" uint64_t SystemCall(size_t, size_t, size_t, size_t);

uint16_t encodeDesktopColour(uint32_t rgb, bool blue)
{
    int r = (rgb >> 16) & 0xFF;
    int g = (rgb >> 8) & 0xFF;
    int b = (rgb >> 0) & 0xFF;

    if (blue) {
        r *= 3;
        r /= 4;
        g *= 3;
        g /= 4;
    }

    r += 5;
    r *= 31;
    r /= 255;
    g += 5;
    g *= 31;
    g /= 255;
    b += 5;
    b *= 31;
    b /= 255;

    uint32_t out = 0x8000 | (r << 10) | (g << 5) | b;
    /*r += 40;
    r *= 3;
    r /= 255;

    g += 20;
    g *= 7;
    g /= 255;

    b += 40;
    b *= 3;
    b /= 255;
    
    uint32_t out = (r << 5) | (g << 2) | b;*/

    return out;
}

void init()
{
    for (int i = 0; i < MAX_DESKTOP_FILES; ++i) {
        files[i].valid = false;
    }

    for (int i = 0; i < 128; ++i) {
        desktopColours[i] = 0;
    }
    desktopColours[0] = 0x808080;
    desktopColours[1] = 0xC0C0C0;

    uint32_t wh = SystemCall((size_t) SystemCallNumber::WSBE, LINKCMD_RESUPPLY_DESKTOP, 1, (size_t) desktopColours);
    desktopWidth = wh >> 16;
    desktopHeight = wh & 0xFFFF;

    desktopBuffer = (uint16_t*) malloc(desktopWidth * desktopHeight * 2);

    desktopContext = Context_new(desktopWidth, desktopHeight, (uint32_t*) desktopBuffer);
    desktopContext->desktopCtxt = 1;

    iconsPerColumn = (desktopHeight - desktopTaskbarHeight - 4) / desktopCellHeight;
}

void drawBackground()
{
    NLoadedBitmap* nbmp = new NLoadedBitmap("C:/Banana/System/crisp.tga");

    redAvg = 0;
    grnAvg = 0;
    bluAvg = 0;

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
            px = px * 2048 / desktopWidth;
            npx = npx * 2048 / desktopWidth;
            py = py * 2048 / desktopHeight;
            npy = npy * 2048 / desktopHeight;

            int mr = (rN * (npx + npy) + rS * (px + npy) + rD * (npx + py) + rG * (px + py)) / 8192;
            int mg = (gN * (npx + npy) + gS * (px + npy) + gD * (npx + py) + gG * (px + py)) / 8192;
            int mb = (bN * (npx + npy) + bS * (px + npy) + bD * (npx + py) + bG * (px + py)) / 8192;

            redAvg += mr;
            grnAvg += mg;
            bluAvg += mb;
            desktopBuffer[i++] = encodeDesktopColour((mr << 16) | (mg << 8) | mb, false);
        }
    }

    redAvg /= desktopWidth * desktopHeight;
    grnAvg /= desktopWidth * desktopHeight;
    bluAvg /= desktopWidth * desktopHeight;

    //delete nbmp;
}


void deregisterFiles()
{
    nextDesktopFile = 0;
    for (int i = 0; i < MAX_DESKTOP_FILES; ++i) {
        if (files[i].valid) {
            files[i].valid = false;
            if (files[i].filepath) {
                free(files[i].filepath);
                files[i].filepath = nullptr;
            }
        }
    }
}

void loadIconBitmaps()
{
    dirico = new NLoadedBitmap("C:/Banana/Icons/colour/folder.tga");
    otherico = new NLoadedBitmap("C:/Banana/Icons/colour/file.tga");

    for (int i = 0; i < MAX_DESKTOP_FILE_TYPES; ++i) {
        fileAssoc[i].valid = false;
    }

    char str[800];
    char str2[800];
    int failure1 = SystemCall((size_t) SystemCallNumber::RegistryEasyReadString, (size_t) "BANANA/FILEASSOC/ICON/TXT", (size_t) str, (size_t) "C:/Banana/Registry/System/SYSTEM.REG");
    int failure2 = SystemCall((size_t) SystemCallNumber::RegistryEasyReadString, (size_t) "BANANA/FILEASSOC/OPEN/TXT", (size_t) str2, (size_t) "C:/Banana/Registry/System/SYSTEM.REG");

    if (!failure1 && !failure2) {
        fileAssoc[nextFileAssoc].valid = true;
        strcpy(fileAssoc[nextFileAssoc].extension, "TXT");
        fileAssoc[nextFileAssoc].openProgram = (char*) malloc(strlen(str2) + 1);
        strcpy(fileAssoc[nextFileAssoc].openProgram, str2);
        fileAssoc[nextFileAssoc++].iconBitmap = new NLoadedBitmap(str);
    }

    fileAssoc[nextFileAssoc].valid = true;
    strcpy(fileAssoc[nextFileAssoc].extension, "EXE");
    fileAssoc[nextFileAssoc].openProgram = (char*)malloc(221);
    strcpy(fileAssoc[nextFileAssoc].openProgram, "C:/Banana/System/conhost.exe");
    fileAssoc[nextFileAssoc++].iconBitmap = new NLoadedBitmap("C:/Banana/Icons/colour/exe.tga");

    fileAssoc[nextFileAssoc].valid = true;
    strcpy(fileAssoc[nextFileAssoc].extension, "COM");
    fileAssoc[nextFileAssoc++].iconBitmap = new NLoadedBitmap("C:/Banana/Icons/colour/exe.tga");

    fileAssoc[nextFileAssoc].valid = true;
    strcpy(fileAssoc[nextFileAssoc].extension, "ISO");
    fileAssoc[nextFileAssoc++].iconBitmap = new NLoadedBitmap("C:/Banana/Icons/colour/iso.tga");

    fileAssoc[nextFileAssoc].valid = true;
    strcpy(fileAssoc[nextFileAssoc].extension, "CFG");
    fileAssoc[nextFileAssoc++].iconBitmap = new NLoadedBitmap("C:/Banana/Icons/colour/cfg.tga");

    fileAssoc[nextFileAssoc].valid = true;
    strcpy(fileAssoc[nextFileAssoc].extension, "BAT");
    fileAssoc[nextFileAssoc++].iconBitmap = new NLoadedBitmap("C:/Banana/Icons/colour/bat.tga");

    fileAssoc[nextFileAssoc].valid = true;
    strcpy(fileAssoc[nextFileAssoc].extension, "TGA");
    fileAssoc[nextFileAssoc++].iconBitmap = new NLoadedBitmap("C:/Banana/Icons/colour/picture.tga");
    fileAssoc[nextFileAssoc].valid = true;
    strcpy(fileAssoc[nextFileAssoc].extension, "BMP");
    fileAssoc[nextFileAssoc++].iconBitmap = new NLoadedBitmap("C:/Banana/Icons/colour/picture.tga");
    fileAssoc[nextFileAssoc].valid = true;
    strcpy(fileAssoc[nextFileAssoc].extension, "PNG");
    fileAssoc[nextFileAssoc++].iconBitmap = new NLoadedBitmap("C:/Banana/Icons/colour/picture.tga");
    fileAssoc[nextFileAssoc].valid = true;
    strcpy(fileAssoc[nextFileAssoc].extension, "GIF");
    fileAssoc[nextFileAssoc++].iconBitmap = new NLoadedBitmap("C:/Banana/Icons/colour/picture.tga");
    fileAssoc[nextFileAssoc].valid = true;
    strcpy(fileAssoc[nextFileAssoc].extension, "JPG");
    fileAssoc[nextFileAssoc++].iconBitmap = new NLoadedBitmap("C:/Banana/Icons/colour/picture.tga");
    fileAssoc[nextFileAssoc].valid = true;
    strcpy(fileAssoc[nextFileAssoc].extension, "JPEG");
    fileAssoc[nextFileAssoc++].iconBitmap = new NLoadedBitmap("C:/Banana/Icons/colour/picture.tga");
}

void redrawIcon(int id)
{
    char* drawname = files[id].displayName;

    bool selected = files[id].selected;

    invalidateLeftAndRight(files[id].textX - 1);
    invalidateLeftAndRight(files[id].textX + files[id].boundW + 1);

    if (redAvg >= 0xA0 && redAvg <= 0xD0 && grnAvg >= 0xA0 && grnAvg <= 0xD0 && bluAvg >= 0xA0 && bluAvg <= 0xD0) {
        bluAvg = 0xC0;
        grnAvg = 0xC0;
        redAvg = 0xC0;
    } else {
        redAvg = redAvg < 0x30 ? 0x00 : redAvg < 0xC0 ? 0x80 : 0xFF;
        grnAvg = grnAvg < 0x30 ? 0x00 : grnAvg < 0xC0 ? 0x80 : 0xFF;
        bluAvg = bluAvg < 0x30 ? 0x00 : bluAvg < 0xC0 ? 0x80 : 0xFF;
    }

    if (desktopWidth <= 640) {
        for (int i = 0; i < 2; ++i) {
            if (redAvg == 0xFF && grnAvg == 0x80 && bluAvg == 0x00) grnAvg = 0x00;
            if (redAvg == 0xFF && grnAvg == 0x80 && bluAvg == 0x80) bluAvg = 0x00;
            if (redAvg == 0xFF && grnAvg == 0x00 && bluAvg == 0x80) bluAvg = 0xFF;
            if (redAvg == 0xFF && grnAvg == 0xFF && bluAvg == 0x80) bluAvg = 0x00;
            if (redAvg == 0xFF && grnAvg == 0x80 && bluAvg == 0xFF) grnAvg = 0x00;
            if (grnAvg == 0xFF && redAvg == 0x80 && bluAvg == 0x00) redAvg = 0x00;
            if (grnAvg == 0xFF && redAvg == 0x80 && bluAvg == 0x80) bluAvg = 0x00;
            if (grnAvg == 0xFF && redAvg == 0x00 && bluAvg == 0x80) bluAvg = 0x00;
            if (grnAvg == 0xFF && redAvg == 0x80 && bluAvg == 0xFF) redAvg = 0x00;
            if (bluAvg == 0xFF && grnAvg == 0x80 && redAvg == 0x00) grnAvg = 0x00;
            if (bluAvg == 0xFF && grnAvg == 0x80 && redAvg == 0x80) redAvg = 0x00;
            if (bluAvg == 0xFF && grnAvg == 0x00 && redAvg == 0x80) bluAvg = 0x80;
        }
    }

    uint32_t textBg = (redAvg << 16) | (grnAvg << 8) | bluAvg;
    uint32_t textFg = (redAvg + grnAvg + bluAvg < 128 * 3) ? 0xFFFFFF : 0x000000;

    Context_fill_rect(desktopContext, files[id].textX - 1, files[id].textY - 1, files[id].boundW + 2, files[id].boundH + 2, selected ? 0x000080 : textBg);
    Context_draw_text(desktopContext, drawname, files[id].textX, files[id].textY, selected ? 0xFFFFFF : textFg);
    
    NLoadedBitmap* ico = files[id].bmp;
    int baseX = files[id].iconX;
    int baseY = files[id].iconY;
    invalidateLeftAndRight(baseX);
    invalidateLeftAndRight(baseX + desktopIconSize);
    for (int y = 0; y < desktopIconSize; ++y) {
        invalidateDesktopScanline(baseY + y);
        for (int x = 0; x < desktopIconSize; ++x) {
            if (ico->data[y * ico->width + x] == 0) continue;
            desktopBuffer[(baseY + y) * desktopWidth + baseX + x] = encodeDesktopColour(ico->data[y * ico->width + x] & 0xFFFFFF, selected);
        }
    }
}

int registerFile(char* filepath, char* displayName, NLoadedBitmap* bmp, int tx, int ty, int ix, int iy, int bw, int bh, int assocType)
{
    files[nextDesktopFile].bmp = bmp;
    files[nextDesktopFile].iconX = ix;
    files[nextDesktopFile].iconY = iy;
    files[nextDesktopFile].textX = tx;
    files[nextDesktopFile].textY = ty;
    files[nextDesktopFile].boundW = bw;
    files[nextDesktopFile].boundH = bh;
    files[nextDesktopFile].valid = true;
    files[nextDesktopFile].selected = false;
    files[nextDesktopFile].assocTypeID = assocType;

    strcpy(files[nextDesktopFile].displayName, displayName);
    files[nextDesktopFile].filepath = (char*) malloc(strlen(filepath) + 1);
    strcpy(files[nextDesktopFile].filepath, filepath);

    int id = nextDesktopFile;
    ++nextDesktopFile;
    return id;
}



void refresh()
{
    deregisterFiles();
    drawBackground();

    DIR* dir;
    struct dirent* ent;
    int diri = 0;

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

            int baseX = (diri / iconsPerColumn) * desktopCellWidth + 10;
            int baseY = (diri % iconsPerColumn) * desktopCellHeight + 10;

            NLoadedBitmap* ico;
            int fileAssocType = -1;

            if (ent->d_type & DT_DIR) {
                ico = dirico;
            } else {
                ico = otherico;

                for (int j = 0; j < MAX_DESKTOP_FILE_TYPES; ++j) {
                    if (fileAssoc[j].valid) {
                        if (!strcasecmp(fileAssoc[j].extension, ext)) {
                            ico = fileAssoc[j].iconBitmap;
                            fileAssocType = j;
                            break;
                        }
                    }
                }
            }

            char drawname[MAX_DESKTOP_DISPLAY_NAME_LENGTH];
            for (int i = 0; i < MAX_DESKTOP_DISPLAY_NAME_LENGTH - 1 && ent->d_name[i]; ++i) {
                drawname[i] = ent->d_name[i];
                drawname[i + 1] = 0;
            }
            int bndx, bndy;
            Context_bound_text(desktopContext, drawname, &bndx, &bndy);
            if (bndx > desktopCellWidth - 2) {
                //a lot of times there will be a dot for file extension, so without this 4 dots get displayed
                while (strlen(drawname) >= 6 && drawname[strlen(drawname) - 4] == '.') drawname[strlen(drawname) - 1] = 0;
                drawname[strlen(drawname) - 1] = '.';
                drawname[strlen(drawname) - 2] = '.';
                drawname[strlen(drawname) - 3] = '.';        

                while (1) {
                    Context_bound_text(desktopContext, drawname, &bndx, &bndy);
                    if (bndx < desktopCellWidth) break;

                    drawname[strlen(drawname) - 1] = 0;
                    drawname[strlen(drawname) - 3] = '.';
                }
            }

            int id = registerFile(ent->d_name, drawname, ico, baseX + desktopCellWidth / 2 - bndx / 2, baseY + desktopIconSize + 8, baseX + (desktopCellWidth - desktopIconSize) / 2, baseY, bndx, bndy, fileAssocType);
            redrawIcon(id);

            ++diri;
        }
        closedir(dir);
    }

    invalidateLeftAndRight(0);
    invalidateLeftAndRight(desktopWidth);
    for (int y = desktopHeight - desktopTaskbarHeight; y < desktopHeight; ++y) {
        invalidateDesktopScanline(y);
        for (int x = 0; x < desktopWidth; ++x) {
            desktopBuffer[y * desktopWidth + x] = \
                (y == desktopHeight - desktopTaskbarHeight) ? 128 : \
                (y == desktopHeight - desktopTaskbarHeight + 1) ? 127 : 129;
        }
    }

    //delete exeico;
    //delete dirico;
    //delete textico;
    //delete otherico;

    int args[4];
    args[0] = 0;
    args[1] = desktopWidth * desktopHeight;
    args[2] = 0;
    args[3] = desktopWidth;
    int retv = SystemCall((size_t) SystemCallNumber::WSBE, LINKCMD_RESUPPLY_DESKTOP, (size_t) args, (size_t) desktopBuffer);
    if (retv != 4) {
        while (1);
    }

    SystemCall((size_t) SystemCallNumber::WSBE, LINKCMD_RESUPPLY_DESKTOP, 2, 0);
    memset(desktopContext->invalidatedScanlines, 0, sizeof(desktopContext->invalidatedScanlines));
}

extern "C" void __gxx_personality_v0()
{

}

void deselectAllIcons()
{
    for (int i = 0; i < MAX_DESKTOP_FILES; ++i) {
        if (files[i].selected && files[i].valid) {
            files[i].selected = false;
            redrawIcon(i);
        }
    }
}

void selectAllIcons()
{
    for (int i = 0; i < MAX_DESKTOP_FILES; ++i) {
        if (!files[i].selected && files[i].valid) {
            files[i].selected = true;
            redrawIcon(i);
        }
    }
}

void partialDesktopUpdate()
{
    uint8_t* invl = desktopContext->invalidatedScanlines;

    int start = -1;
    for (int i = 0; i < desktopHeight; ++i) {
        if (invl[i >> 3] & (1 << (i & 7))) {
            if (start == -1) {
                start = i;
            }
        } else {
            if (start != -1) {
                int end = i;
                int args[4];
                args[0] = start * desktopWidth;
                args[1] = (end - start) * desktopWidth;
                args[2] = leftMostInvalid;
                args[3] = rightMostInvalid;
                SystemCall((size_t) SystemCallNumber::WSBE, LINKCMD_RESUPPLY_DESKTOP, (size_t) args, (size_t) (desktopBuffer + start * desktopWidth));
                start = -1;
            }
        }
    }
    if (start != -1) {
        int end = desktopHeight;
        int args[4];
        args[0] = start * desktopWidth;
        args[1] = (end - start) * desktopWidth;
        args[2] = leftMostInvalid;
        args[3] = rightMostInvalid;
        SystemCall((size_t) SystemCallNumber::WSBE, LINKCMD_RESUPPLY_DESKTOP, (size_t) args, (size_t) (desktopBuffer + start * desktopWidth));
        start = -1;
    }

    leftMostInvalid = -1;
    rightMostInvalid = -1;
    memset(desktopContext->invalidatedScanlines, 0, sizeof(desktopContext->invalidatedScanlines));
}

int antBaseX;
int antBaseY;
int antPrevX;
int antPrevY;
bool drawAnts;
bool firstAntDraw;

int main (int argc, char *argv[])
{
    SystemCall((size_t) SystemCallNumber::WSBE, WSBE_FORCE_INIT_EBX, WSBE_FORCE_INIT_ECX, WSBE_FORCE_INIT_EDX);
    
    NiLinkWindowStruct dummyWin;
    dummyWin.x = 1;
    dummyWin.y = 1;
    dummyWin.w = 5;
    dummyWin.h = 5;
    dummyWin.flags[0] = WIN_FLAGS_0_HIDDEN | WIN_FLAGS_0_HIDE_ON_INVALIDATE;
    dummyWin.bufferSize = 5 * 5;
    dummyWin.buffer = (uint32_t*) malloc(5 * 5 * 4);

    strcpy(dummyWin.name, "DUMMY");
    SystemCall((size_t) SystemCallNumber::WSBE, LINKCMD_CREATE_WINDOW, 0, (size_t) &dummyWin);
    SystemCall((size_t) SystemCallNumber::WSBE, LINKCMD_BE_THE_DESKTOP, 0, (size_t) dummyWin.krnlWindow);
    SystemCall((size_t) SystemCallNumber::WSBE, LINKCMD_SET_CURSOR, LINKCMD_CURSOR_NORMAL, (size_t) &dummyWin);

    init();
    loadIconBitmaps();
    refresh();

    int cs = 0;
    while (1) {
        int events = SystemCall((size_t) SystemCallNumber::WSBE, LINKCMD_GET_EVENTS, 0, (size_t) &dummyWin);
        if (events < 0) {
            continue;
        }

        if (dummyWin.evnt.type == EVENT_TYPE_MOUSE_DOWN) {
            drawAnts = true;
            firstAntDraw = true;
            antBaseX = dummyWin.evnt.mouseX;
            antBaseY = dummyWin.evnt.mouseY;
        }

        if (dummyWin.evnt.type == EVENT_TYPE_MOUSE_UP) {
            drawAnts = false;
        }

        if (drawAnts) { 
            bool needsUpdate = false;
            for (int i = 0; i < MAX_DESKTOP_FILES; ++i) {
                if (!files[i].valid) continue;

                int ax1 = files[i].iconX;
                int ay1 = files[i].iconY;
                int ax2 = files[i].iconX + desktopIconSize;
                int ay2 = files[i].iconY + desktopIconSize;

                int bx1 = antBaseX < dummyWin.evnt.mouseX ? antBaseX : dummyWin.evnt.mouseX;
                int by1 = antBaseY < dummyWin.evnt.mouseY ? antBaseY : dummyWin.evnt.mouseY;
                int bx2 = antBaseX < dummyWin.evnt.mouseX ? dummyWin.evnt.mouseX : antBaseX;
                int by2 = antBaseY < dummyWin.evnt.mouseY ? dummyWin.evnt.mouseY : antBaseY;

                bool overlap = (ax1 < bx2 && ax2 > bx1 && ay1 < by2 && ay2 > by1);

                if (files[i].selected != overlap) {
                    files[i].selected = overlap;
                    if (!needsUpdate) cs = i;
                    redrawIcon(i);
                    needsUpdate = true;
                }
            }

            if (needsUpdate) {
                partialDesktopUpdate();
            }

            firstAntDraw = false;
            antPrevX = dummyWin.evnt.mouseX;
            antPrevY = dummyWin.evnt.mouseY;
        }
        
        if (dummyWin.evnt.type == EVENT_TYPE_KEYDOWN) {
            if (dummyWin.evnt.ctrl && (dummyWin.evnt.key == 'A' || dummyWin.evnt.key == 'a')) {
                selectAllIcons();
                partialDesktopUpdate();
            }

            if (dummyWin.evnt.key == (int) KeyboardSpecialKeys::Escape) {
                deselectAllIcons();
                partialDesktopUpdate();
            }

            if (dummyWin.evnt.key == (int) KeyboardSpecialKeys::Tab) {
                if (dummyWin.evnt.shift) {
                    if (cs - 1 >= 0 && files[cs - 1].valid) cs -= 1;
                    else cs = nextDesktopFile - 1;
                } else {
                    if (cs + 1 < MAX_DESKTOP_FILES && files[cs + 1].valid) cs += 1;
                    else cs = 0;
                }
                
                deselectAllIcons();
                files[cs].selected = true;
                redrawIcon(cs);
                partialDesktopUpdate();
            }

            if (dummyWin.evnt.key == (int)KeyboardSpecialKeys::Enter) {
                if (files[cs].assocTypeID != -1) {
                    char* path = fileAssoc[files[cs].assocTypeID].openProgram;
                    char* argvv[3];
                    argvv[0] = path;
                    argvv[1] = 0;
                    int pid = SystemCall((size_t)SystemCallNumber::Spawn, 0, (size_t)argvv, (size_t)argvv[0]);

                    deselectAllIcons();
                    partialDesktopUpdate();
                }
            }

            if (dummyWin.evnt.key == (int) KeyboardSpecialKeys::Right && cs + iconsPerColumn < MAX_DESKTOP_FILES && files[cs + iconsPerColumn].valid) {
                deselectAllIcons();
                cs += iconsPerColumn;
                files[cs].selected = true;
                redrawIcon(cs);
                partialDesktopUpdate();
            }

            if (dummyWin.evnt.key == (int) KeyboardSpecialKeys::Left && cs - iconsPerColumn >= 0 && files[cs - iconsPerColumn].valid) {
                deselectAllIcons();
                cs -= iconsPerColumn;
                files[cs].selected = true;
                redrawIcon(cs);
                partialDesktopUpdate();
            }

            if (dummyWin.evnt.key == (int) KeyboardSpecialKeys::Down && cs + 1 < MAX_DESKTOP_FILES && files[cs + 1].valid) {
                deselectAllIcons();
                cs += 1;
                files[cs].selected = true;
                redrawIcon(cs);
                partialDesktopUpdate();
            }

            if (dummyWin.evnt.key == (int) KeyboardSpecialKeys::Up && cs - 1 >= 0 && files[cs - 1].valid) {
                deselectAllIcons();
                cs -= 1;
                files[cs].selected = true;
                redrawIcon(cs);
                partialDesktopUpdate();
            }
        }
    }
	return 0;
}