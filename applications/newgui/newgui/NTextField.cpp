//
//  NButton.cpp
//  NGUI
//
//  Created by Alex Boxall on 16/9/21.
//  Copyright © 2021 Alex Boxall. All rights reserved.
//

#include <stdint.h>

#include "NTextField.hpp"

#include <string.h>
#include <stdlib.h>

int standardTextFieldPainter(NRegion* _self)
{
    //this function is arcane black magic

    NTextField* self = (NTextField*) _self;
    self->invalidating = true;

    self->fillRect(0, 0, self->width, self->height, 0xFFFFFF);
   
    char x[2];
    x[1] = 0;

    unsigned int xpos = 0;
    unsigned int ypos = 0;
    unsigned int lastBiggest = 0;
    bool prevNewline = true;
    int xplus = 0;
    int yheight = 12;

    unsigned int startOfLine = -1;
    unsigned int startOfLineXPos = 0;
    bool drawMode = false;

    int justifyScalePer256 = 256;
    int justifyLeftovers = 0;
    
    bool selectionOn = false;
    int stDrawSpot = 0;

    int prevSpaceI = -1;
    int prevSpaceXPos = -1;
    int wordWrapTop = -1;

    bool canSkipSpace = false;

    for (int i = 0; self->text[i]; ++i) {
        if (self->text[i] == ' ' && canSkipSpace && self->wrapMode == TextWrap::Word) {
            continue;
        } else if (canSkipSpace) {
            canSkipSpace = false;
        }
        if (self->callback) {
            //self->callback(self, i);
        }
        if (self->text[i] == ' ' && !drawMode && self->wrapMode == TextWrap::Word) {
            prevSpaceI = i;
            prevSpaceXPos = xpos;
        }
        
        int effectiveWidth = self->width - self->marginLeft - self->marginRight;

        if (self->text[i] != '\n') {
            x[0] = self->text[i];
            Context_bound_text(self->ctxt, x, &xplus, &yheight);
            xplus = (xplus * self->charSpacingPercent + 50) / 100;
            if (self->alignment == TextAlignment::Justify && drawMode) {
                int temp = (xplus * justifyScalePer256 + justifyLeftovers) / 256;
                justifyLeftovers = (xplus * justifyScalePer256 + justifyLeftovers) % 256;
                xplus = temp;
            }
        }

        bool wrapPoint = (self->text[i] != '\n' && (xplus + (prevNewline ? 0 : xpos) - ((drawMode && !prevNewline) ? stDrawSpot : 0) > effectiveWidth && (self->wrapMode == TextWrap::Character || self->wrapMode == TextWrap::Word)));
        bool wordWrap = false;
        if (!drawMode && wrapPoint && self->text[i] != ' ' && self->wrapMode == TextWrap::Word && prevSpaceI != -1) {
            wordWrapTop = prevSpaceI;
            i = prevSpaceI - 1;
            xpos = prevSpaceXPos;
            wordWrap = true;
        }
        if (drawMode && i == wordWrapTop) {
            wrapPoint = true;
            wordWrap = true;
            wordWrapTop = -1;
        }

        if (self->text[i] == '\n' || wrapPoint || !self->text[i + 1]) {
            if (drawMode || prevNewline) {
                xpos = 0;
                ypos += lastBiggest;
                prevNewline = true;
                canSkipSpace = wrapPoint;
                drawMode = false;
                if (wrapPoint && !wordWrap) --i;
                continue;

            } else {
                canSkipSpace = wrapPoint;
                drawMode = true;
                if (self->alignment == TextAlignment::Left) {
                    xpos = 0;

                } else if (self->alignment == TextAlignment::Right) {
                    xpos = (self->width - self->marginLeft - self->marginRight) - xpos;

                } else if (self->alignment == TextAlignment::Centre) {
                    xpos = ((self->width - self->marginLeft - self->marginRight) - xpos) / 2;
                
                } else if (self->alignment == TextAlignment::Justify) {
                    if (xpos == 0 || !wrapPoint) {
                        justifyScalePer256 = 256;
                    } else {
                        justifyScalePer256 = (effectiveWidth * 256 + 128) / xpos;
                    }
                    
                    justifyLeftovers = 0;
                    xpos = 0;
                }
                stDrawSpot = xpos;

                prevNewline = false;
                i = startOfLine;
                --i;
                continue;
            }
        }
        if (prevNewline) {
            prevNewline = false;
            lastBiggest = 0;
            startOfLine = i;
            drawMode = false;
            stDrawSpot = 0;
            xpos = 0;
        }

        yheight = (yheight * self->lineSpacingTenths + 5) / 10;

        if (drawMode) {
            if (self->curStart == i && self->curEnd == i) {
                self->fillRect(xpos - self->scrollX - 1 + self->marginLeft, ypos - self->scrollY + self->marginTop, 1, yheight, self->cursorCol);
            }
            if (self->curStart == i) {
                selectionOn ^= 1;
            }
            if (self->curEnd == i) {
                selectionOn ^= 1;
            }
            if (selectionOn) {
                self->fillRect(xpos - self->scrollX + self->marginLeft, ypos - self->scrollY - 1 + self->marginTop, xplus, yheight, self->selBgCol);
            }
            self->drawBasicText(xpos - self->scrollX + self->marginLeft, ypos - self->scrollY + self->marginTop, selectionOn ? self->selFgCol : self->fgCol, x);
        }
        xpos += xplus;

        if (yheight > lastBiggest) {
            lastBiggest = yheight;
        }
    }
   
    self->fillRect(0, 0, self->width, self->marginTop, 0xFFFFFF);
    self->fillRect(0, 0, self->marginLeft, self->height, 0xFFFFFF);
    self->fillRect(0, self->height - self->marginBottom, self->width, self->marginBottom, 0xFFFFFF);
    self->fillRect(self->width - self->marginRight, 0, self->marginRight, self->height, 0xFFFFFF);

    self->invalidating = false;
    return 0;
}

void NTextField::setTextWrap(TextWrap wrap)
{
    wrapMode = wrap;
    invalidate();
}

TextWrap NTextField::getTextWrap()
{
    return wrapMode;
}

void NTextField::invalidate()
{
    if (invalidating) return;
    Window_invalidate(win, 0, 0, win->height, win->width);
}

NTextField::NTextField(int x, int y, int w, int h, NTopLevel* tl, const char* text) : NTextField(x, y, w, h, tl->getContext(), text)
{

}

NTextField::NTextField(int x, int y, int w, int h, NRegion* rgn, const char* text) : NTextField(x, y, w, h, rgn->getContext(), text)
{

}

NTextField::NTextField(int x, int y, int w, int h, Context* context, const char* _text) :
	NRegion(x, y, w, h, context)
{
	text = (char*) malloc(strlen(_text));
	strcpy(text, _text);

    scrollX = 0;
    scrollY = 0;

    invalidating = false;

    lineSpacingTenths = 15;
    charSpacingPercent = 100;

    alignment = TextAlignment::Left;
    wrapMode = TextWrap::Character;

    callback = nullptr;

    fgCol = 0x000000;
    cursorCol = 0x000000;
    selFgCol = 0xFFFFFF;
    selBgCol = 0x000080;

    marginTop = 4;
    marginBottom = 4;
    marginLeft = 4;
    marginRight = 4;

    curStart = 3;
    curEnd = 36;

	paintHandler = standardTextFieldPainter;
}

NTextFieldFormattingCallback NTextField::getFormattingCallback()
{
    return callback;
}

void NTextField::setFormattingCallback(NTextFieldFormattingCallback call)
{
    call = callback;
}

void NTextField::setForegroundColour(uint32_t col)
{
    fgCol = col;
    invalidate();
}

uint32_t NTextField::getForegroundColour()
{
    return fgCol;
}

void NTextField::setAlignment(TextAlignment align)
{
    alignment = align;
    invalidate();
}

TextAlignment NTextField::getAlignment()
{
    return alignment;
}

char* NTextField::getText()
{
    return text;
}

void NTextField::setText(const char* _text)
{
    if (text) free(text);
    text = (char*) malloc(strlen(_text));
    strcpy(text, _text);

    invalidate();
}

NTextField::~NTextField()
{
    if (text) {
        free(text);
    }
}