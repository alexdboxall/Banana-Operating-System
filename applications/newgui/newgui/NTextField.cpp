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
    NTextField* self = (NTextField*) _self;

    self->fillRect(0, 0, self->width, self->height, 0xFFFFFF);
   
    char x[2];
    x[1] = 0;

    unsigned int xpos = self->marginLeft;
    unsigned int ypos = self->marginTop;
    unsigned int ogxpos = xpos;
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

    for (int i = 0; self->text[i]; ++i) {
        if (self->text[i] == '\n') {
            if (drawMode || prevNewline) {
                xpos = ogxpos;
                ypos += (lastBiggest * self->lineSpacingTenths + 5) / 10;
                prevNewline = true;
                drawMode = false;
                continue;

            } else {
                drawMode = true;
                if (self->alignment == TextAlignment::Left) {
                    xpos = ogxpos;

                } else if (self->alignment == TextAlignment::Right) {
                    xpos = (self->width - self->marginLeft - self->marginRight) - xpos;

                } else if (self->alignment == TextAlignment::Centre) {
                    xpos = ((self->width - self->marginLeft - self->marginRight) - xpos) / 2;
                
                } else if (self->alignment == TextAlignment::Justify) {
                    if (xpos == 0) {
                        justifyScalePer256 = 256;
                    } else {
                        justifyScalePer256 = ((self->width - self->marginLeft - self->marginRight) * 256 + 128) / xpos;
                    }
                    
                    justifyLeftovers = 0;
                    xpos = 0;
                }

                prevNewline = false;
                i = startOfLine;
            }
        }
        if (prevNewline) {
            selectionOn = false;
            prevNewline = false;
            lastBiggest = 0;
            startOfLine = i;
            drawMode = false;
            xpos = 0;
        }
        x[0] = self->text[i];
        Context_bound_text(self->ctxt, x, &xplus, &yheight);
        xplus = (xplus * self->charSpacingPercent + 50) / 100;
        if (self->alignment == TextAlignment::Justify && drawMode) {
            int temp = (xplus * justifyScalePer256 + justifyLeftovers) / 256;
            justifyLeftovers = (xplus * justifyScalePer256 + justifyLeftovers) % 256;
            xplus = temp;
        }
        
        // text wrapping...

        if (drawMode) {
            if (self->curStart == i && self->curEnd == i) {
                self->fillRect(xpos - self->scrollX - 1, ypos - self->scrollY, 1, yheight, 0x000000);
            }
            if (self->curStart == i) {
                selectionOn ^= 1;
            }
            if (self->curEnd == i) {
                selectionOn ^= 1;
            }
            if (selectionOn) {
                self->fillRect(xpos - self->scrollX, ypos - self->scrollY, xplus, yheight, 0x0000AA);
            }
            self->drawBasicText(xpos - self->scrollX, ypos - self->scrollY, 0x000000, x);
        }
        xpos += xplus;

        if (yheight > lastBiggest) {
            lastBiggest = yheight;
        }
    }
   
    return 0;
}

void NTextField::invalidate()
{
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

    lineSpacingTenths = 15;
    charSpacingPercent = 100;

    alignment = TextAlignment::Left;

    marginTop = 4;
    marginBottom = 4;
    marginLeft = 4;
    marginRight = 4;

    curStart = 3;
    curEnd = 6;

	paintHandler = standardTextFieldPainter;
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