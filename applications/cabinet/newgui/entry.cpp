
#include <stdio.h>
#include <string.h>
#include <udraw/banana.hpp>
extern "C" {
    #include <unistd.h>
    #include <dirent.h>
}

char currentDirectory[256];
NTopLevel* rootWindow;
int gridSizeW = 100;
int gridSizeH = 85;

void drawIcon(int pos, struct dirent* entry)
{
    int gridX = pos % gridSizeW;
    int gridY = pos / gridSizeW;

    int pixelX = gridX * gridSizeW + 30;
    int pixelY = gridY * gridSizeH + 50;

    char displayName[300];
    strcpy(displayName, entry->d_name);

    Context* ctxt = rootWindow->getContext();
    int ellipsisWidth, boundX, boundY;
    Context_bound_text(ctxt, "...", &ellipsisWidth, &boundY);
    Context_bound_text(ctxt, displayName, &boundX, &boundY);

    bool clipped = false;
    while (boundX > gridSizeW - 5 - (clipped ? ellipsisWidth : 0)) {
        clipped = true;

        while (displayName[strlen(displayName) - 1] == ' ') displayName[strlen(displayName) - 1] = 0;
        displayName[strlen(displayName) - 1] = 0;
        while (displayName[strlen(displayName) - 1] == ' ') displayName[strlen(displayName) - 1] = 0;

        Context_bound_text(ctxt, displayName, &boundX, &boundY);
        boundX += ellipsisWidth;
    }

    if (clipped) {
        strcat(displayName, "...");
    }
    Context_draw_rect(ctxt, pixelX, pixelY, gridSizeW - 5, gridSizeH - 5, 0x000000);
    Context_draw_text(ctxt, displayName, pixelX + (gridSizeW - boundX) / 2 - 3, pixelY + gridSizeH - 9 - boundY, 0x000000);
}

int handlePaint(NTopLevel* self)
{
    int windowWidth = rootWindow->getWidth();
    int windowHeight = rootWindow->getHeight();

    int iconsWide = windowWidth / gridSizeW;
    int iconsHigh = windowHeight / gridSizeH;

    struct dirent* dp;
    DIR* dirp = opendir(currentDirectory);
    int i = 0;
    if (dirp) {
        while ((dp = readdir(dirp)) != NULL) {
            drawIcon(i, dp);
            ++i;
        }   
        closedir(dirp);

        if (i == 0) {
            Context_draw_text(rootWindow->getContext(), "This folder is empty...", 30, 50, 0x000000);
        }

    } else {
        Context_draw_text(rootWindow->getContext(), "This folder doesn't exist...", 30, 50, 0x000000);
    }

    return 0;
}

void updateTitlebar()
{
    char title[300];
    sprintf(title, "Cabinet - %s", currentDirectory);
    rootWindow->setTitle(title);
}

void changeDirectory(char* dir)
{
    strcpy(currentDirectory, dir);
    updateTitlebar();
}


extern "C" int main(int argc, char** argv) {
    createSystemBrushes();

    rootWindow = new NTopLevel("Cabinet", 600, 400, WIN_FLAGS_DEFAULT_0 | WIN_FLAGS_0_HIDDEN | WIN_FLAGS_0_PRETTY);
    rootWindow->paintHandlerHook = handlePaint;
    rootWindow->initialise();

    NLoadedBitmap* bmp = new NLoadedBitmap("C:/Banana/Icons/cabinet.tga");
    rootWindow->setIcon(bmp);

    if (argc >= 2) {
        changeDirectory(argv[1]);
    } else {
        changeDirectory("C:/");
    }

    while (1) {        
        NiEvent evnt = rootWindow->process();

        switch (evnt.type) {
        case EVENT_TYPE_RESIZED:
        case EVENT_TYPE_RESIZE_DOWN:
            rootWindow->defaultEventHandler(evnt);
            break;

        default:
            rootWindow->defaultEventHandler(evnt);
            break;
        }
    }
    
    return 0;
}

