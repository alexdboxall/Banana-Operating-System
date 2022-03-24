
#include <udraw/banana.hpp>

extern "C" {
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
}

#include <stdint.h>


uint64_t redAvg;
uint64_t grnAvg;
uint64_t bluAvg;

char desktopBasePath[256] = "C:/Banana/System";

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
    uint16_t boundW : 14;
    uint16_t directory : 1;
    uint16_t valid : 1;
    uint16_t boundH : 14;
    uint16_t app : 1;
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

uint32_t* desktopBuffer;
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

uint32_t encodeDesktopColour(uint32_t rgb, bool blue)
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

    uint32_t out = 0x40000000 | (r << 16) | (g << 8) | b;

    return out;
}

NLoadedBitmap* backgroundBitmap;
uint32_t* desktopBuffer2;

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

    desktopBuffer = (uint32_t*) malloc(desktopWidth * desktopHeight * 4);
    desktopBuffer2 = (uint32_t*) malloc(desktopWidth * desktopHeight * 4);

    desktopContext = Context_new(desktopWidth, desktopHeight, (uint32_t*) desktopBuffer);
    desktopContext->desktopCtxt = 1;
    desktopContext->desktopBuff32 = desktopBuffer;

    backgroundBitmap = new NLoadedBitmap("C:/Banana/System/crisp.tga");

    iconsPerColumn = (desktopHeight - desktopTaskbarHeight - 4) / desktopCellHeight;
}

void drawBackground()
{
    redAvg = 0;
    grnAvg = 0;
    bluAvg = 0;

    int i = 0;
    for (int y = 0; y < desktopHeight; ++y) {
        for (int x = 0; x < desktopWidth; ++x) {
            int ax = (x * backgroundBitmap->width) / desktopWidth;
            int px = (x * backgroundBitmap->width) % desktopWidth;
            int ay = (y * backgroundBitmap->height) / desktopHeight;
            int py = (y * backgroundBitmap->height) % desktopHeight;

            uint32_t norm = backgroundBitmap->data[ay * backgroundBitmap->width + ax];
            uint32_t side = backgroundBitmap->data[ay * backgroundBitmap->width + ax + 1];
            uint32_t down = backgroundBitmap->data[(ay + 1) * backgroundBitmap->width + ax];
            uint32_t diag = backgroundBitmap->data[(ay + 1) * backgroundBitmap->width + ax + 1];

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

            if (files[i].app && files[i].bmp) {
                delete files[i].bmp;
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
    strcpy(fileAssoc[nextFileAssoc].extension, "BMP");
    fileAssoc[nextFileAssoc++].iconBitmap = new NLoadedBitmap("C:/Banana/Icons/colour/picture.tga");

    fileAssoc[nextFileAssoc].valid = true;
    strcpy(fileAssoc[nextFileAssoc].extension, "TGA");
    fileAssoc[nextFileAssoc].openProgram = (char*) malloc(221);
    strcpy(fileAssoc[nextFileAssoc].openProgram, "C:/Banana/System/photoview.app/program.exe");
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
    files[nextDesktopFile].app = false;
    files[nextDesktopFile].directory = bmp == dirico;

    strcpy(files[nextDesktopFile].displayName, displayName);
    files[nextDesktopFile].filepath = (char*) malloc(strlen(filepath) + 1);
    strcpy(files[nextDesktopFile].filepath, filepath);

    char* drawname = files[nextDesktopFile].filepath;
    if (drawname[strlen(drawname) - 1] == 'p' && drawname[strlen(drawname) - 2] == 'p' && drawname[strlen(drawname) - 3] == 'a' && drawname[strlen(drawname) - 4] == '.') {
        drawname[strlen(drawname) - 4] = 0;

        char iconFilepath[256];
        sprintf(iconFilepath, "%s/%s/icon32.tga", desktopBasePath, filepath);
        files[nextDesktopFile].bmp = new NLoadedBitmap(iconFilepath);
        files[nextDesktopFile].app = true;
    }

    int id = nextDesktopFile;
    ++nextDesktopFile;
    return id;
}

void partialDesktopUpdate();

void drawTime()
{
    time_t rawtime;
    time(&rawtime);
    struct tm* timeinfo = localtime(&rawtime);

    static char previousTimeString[80];
    static bool firstTime = true;

    char timeString[80];

    int hour = timeinfo->tm_hour;
    bool pm = false;
    if (hour == 0) {
        hour = 12;
    } else if (hour == 12) {
        pm = true;
    } else if (hour > 12) {
        hour -= 12;
        pm = true;
    }

    sprintf(timeString, "%d:%02d:%02d %cM", hour, timeinfo->tm_min, timeinfo->tm_sec, pm ? 'P' : 'A');
    if (!strcmp(timeString, previousTimeString) && !firstTime) {
        return;
    }
    firstTime = false;
    strcpy(previousTimeString, timeString);

    int baseX = desktopWidth - 95;
    int baseY = desktopHeight - desktopTaskbarHeight + 7;

    Context_fill_rect(desktopContext, baseX, baseY, 100, desktopHeight - baseY, 0xC0C0C0);
    Context_draw_text(desktopContext, timeString, baseX, baseY, 0x000000);

    invalidateLeftAndRight(baseX);
    invalidateLeftAndRight(desktopWidth);
    for (int y = baseY; y < desktopTaskbarHeight; ++y) {
        invalidateDesktopScanline(y);
    }

    partialDesktopUpdate();
}

void drawTaskbar()
{
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

    drawTime();
}

void refresh()
{
    deregisterFiles();
    drawBackground();

    DIR* dir;
    struct dirent* ent;
    int diri = 0;

    if ((dir = opendir(desktopBasePath)) != NULL) {
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

    drawTaskbar();

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


void openProgram(int cs)
{
    if (files[cs].directory || files[cs].assocTypeID != -1 || files[cs].app) {
        char progPath[256];
        char path[256];
        if (files[cs].directory && !files[cs].app) {
            strcpy(path, "C:/Banana/System/cabinet.app/program.exe");
            sprintf(progPath, "%s/%s", desktopBasePath, files[cs].filepath);

        } else if (files[cs].app) {
            sprintf(path, "%s/%s.app/program.exe", desktopBasePath, files[cs].filepath);
            sprintf(progPath, "");

        } else {
            strcpy(path, fileAssoc[files[cs].assocTypeID].openProgram);
            sprintf(progPath, "%s/%s", desktopBasePath, files[cs].filepath);
        }

        char* argvv[3];
        argvv[0] = path;
        argvv[1] = files[cs].app ? nullptr : progPath;
        argvv[2] = 0;
        int pid = SystemCall((size_t) SystemCallNumber::Spawn, 0, (size_t) argvv, (size_t) argvv[0]);

        deselectAllIcons();
        partialDesktopUpdate();
    }
}

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

    uint64_t lastClickMicrosecond = 0;

    int cs = 0;
    while (1) {
        bool doubleClickIntervalDetected = false;

        int events = SystemCall((size_t) SystemCallNumber::WSBE, LINKCMD_GET_EVENTS, 0, (size_t) &dummyWin);
        if (events < 0) {
            continue;
        }

        drawTime();

        if (dummyWin.evnt.type == EVENT_TYPE_MOUSE_DOWN) {
            drawAnts = true;
            firstAntDraw = true;
            antBaseX = dummyWin.evnt.mouseX;
            antBaseY = dummyWin.evnt.mouseY;

            uint64_t mouseClickMicrosecond = SystemCall((size_t) SystemCallNumber::GetUnixTime, 2, 0, 0);
            
            if (mouseClickMicrosecond - lastClickMicrosecond < 500000 && files[cs].valid && files[cs].selected) {
                doubleClickIntervalDetected = true;
            }
            
            lastClickMicrosecond = mouseClickMicrosecond;
        }

        if (dummyWin.evnt.type == EVENT_TYPE_MOUSE_UP) {
            drawAnts = false;
        }

        if (drawAnts) { 
            bool needsUpdate = false;
            bool anyFilesAreSelected = false;
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
                    if (files[i].selected) {
                        anyFilesAreSelected = true;
                    }
                    if (!needsUpdate) cs = i;
                    redrawIcon(i);
                    needsUpdate = true;
                }
            }

            if (doubleClickIntervalDetected) {
                if (files[cs].valid && files[cs].selected) {
                    openProgram(cs);
                    lastClickMicrosecond = 0;
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
                openProgram(cs);
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