//
//  NButton.cpp
//  NGUI
//
//  Created by Alex Boxall on 16/9/21.
//  Copyright © 2021 Alex Boxall. All rights reserved.
//

#include <stdint.h>

#include "NTextField.hpp"
#include "NFont.hpp"

#include <string.h>
#include <stdlib.h>

int textFieldEngine(NRegion* _self, int posi, int* xout, int* yout)
{
    //this function is arcane black magic

    NTextField* self = (NTextField*) _self;
    self->invalidating = true;

    if (posi == -1) {
        int ml = self->marginLeft ? self->marginLeft - 1 : 0;
        int mt = self->marginTop ? self->marginTop - 1 : 0;
        self->fillRect(ml, mt, self->width - ml - self->marginRight, self->height - mt - self->marginTop, self->bgCol);
    }

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
        if ((uint8_t) self->text[i] == self->poisonCharacter) {
            i += self->poisonHiddenDataLength + 1;
            continue;
        }
        if (self->text[i] == ' ' && canSkipSpace && self->wrapMode == TextWrap::Word) {
            continue;
        } else if (canSkipSpace) {
            canSkipSpace = false;
        }
        if (self->callback) {
            self->callback(self, i);
        }
        if (self->text[i] == ' ' && !drawMode && self->wrapMode == TextWrap::Word) {
            prevSpaceI = i;
            prevSpaceXPos = xpos;
        }

        int effectiveWidth = self->width - self->marginLeft - self->marginRight;

        if (self->text[i] != '\n') {
            x[0] = self->text[i];
            Context_bound_text(self->ctxt, x, &xplus, &yheight);
            if (self->bold && xplus) {
                ++xplus;
            }
            if (self->text[i] == '\t') {
                xplus = ((xpos + self->tabStopPixels + 1) / self->tabStopPixels) * self->tabStopPixels - xpos;
            }
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
                int xx = xpos - self->scrollX + self->marginLeft;
                if (self->alignment == TextAlignment::Centre && prevNewline) xx = effectiveWidth / 2 + self->marginLeft;
                if (self->alignment == TextAlignment::Right) xx = effectiveWidth + self->marginLeft;
                if (posi == -1) {
                    if (self->curStart == i && self->curEnd == i) self->fillRect(xx - 1, ypos - self->scrollY + self->marginTop, 1, lastBiggest, self->cursorCol);
                    if (self->curStart == i) selectionOn ^= 1;
                    if (self->curEnd == i) selectionOn ^= 1;
                    if (selectionOn) self->fillRect(xx, ypos - self->scrollY - 1 + self->marginTop, 1, lastBiggest, self->selBgCol);
                } else if (i == posi) {
                    *xout = xx;
                    *yout = ypos - self->scrollY + self->marginTop;
                    self->invalidating = false;
                    return 0;
                }

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
            if (posi == -1) {
                if (self->curStart == i && self->curEnd == i) self->fillRect(xpos - self->scrollX - 1 + self->marginLeft, ypos - self->scrollY + self->marginTop, 1, yheight, self->cursorCol);
                if (self->curStart == i) selectionOn ^= 1;
                if (self->curEnd == i) selectionOn ^= 1;
                if (selectionOn) self->fillRect(xpos - self->scrollX + self->marginLeft, ypos - self->scrollY - 1 + self->marginTop, xplus, yheight, self->selBgCol);
                self->drawBasicText(xpos - self->scrollX + self->marginLeft, ypos - self->scrollY + self->marginTop, selectionOn ? self->selFgCol : self->fgCol, x);
                if (self->bold) {
                    self->drawBasicText(xpos - self->scrollX + self->marginLeft + 1, ypos - self->scrollY + self->marginTop, selectionOn ? self->selFgCol : self->fgCol, x);
                }
                if (self->underline) {
                    for (int jy = 0; jy < 4; ++jy) {
                        for (int jx = 0; jx < xplus; ++jx) {
                            if ((self->underlinePattern[jy] >> ((xpos - self->scrollX + self->marginLeft + jx) % self->underlineWidth)) & 1) {
                                self->drawRect(xpos - self->scrollX + self->marginLeft + jx, ypos - self->scrollY + self->marginTop + jy + yheight, 1, 1, self->underlineCol);
                            }
                        }
                    }
                }
            
            } else if (i == posi) {
                *xout = xpos - self->scrollX + self->marginLeft;
                *yout = ypos - self->scrollY + self->marginTop;
                self->invalidating = false;
                return 0;
            }
        }
        xpos += xplus;

        if (yheight > lastBiggest) {
            lastBiggest = yheight;
        }
    }

    if (posi == -1) {
        self->fillRect(0, 0, self->width, self->marginTop, self->bgCol);
        self->fillRect(0, 0, self->marginLeft == 0 ? 0 : self->marginLeft - 1, self->height, self->bgCol);
        self->fillRect(0, self->height - self->marginBottom, self->width, self->marginBottom, self->bgCol);
        self->fillRect(self->width - self->marginRight, 0, self->marginRight, self->height, self->bgCol);

        /*NFont* nf = new NFont();
        int ret = nf->loadFont("C:/Banana/Fonts/SFN/SERIF.SFN");
        if (ret != 0) {
            self->bgCol = 0xFF0000;
        } else {
            ret = nf->setFont(16, SSFN_STYLE_REGULAR);
            if (ret != 0) {
                self->bgCol = 0x00FF00;
            } else {
                ret = nf->render("K", 50, 50, self);
                if (ret != 0) {
                    if (ret == -1) self->bgCol = 0x0000FF;
                    if (ret == -2) self->bgCol = 0x000080;
                    if (ret == -3) self->bgCol = 0x00FFFF;
                    if (ret == -4) self->bgCol = 0x00FF80;
                    if (ret == -5) self->bgCol = 0x0080FF;
                    if (ret == -6) self->bgCol = 0x80FF80;
                    if (ret == -7) self->bgCol = 0x8080FF;
                }
            }
        }*/
    }
    self->invalidating = false;
    return posi == -1 ? 0 : -1;
}

void NTextField::getPositionFromIndex(int index, int* x, int* y)
{
    textFieldEngine(this, index, x, y);
}

int standardTextFieldPainter(NRegion* _self)
{
    return textFieldEngine(_self, -1, 0, 0);
}

void NTextField::setTextWrap(TextWrap wrap)
{
    wrapMode = wrap;
    internalInvalidate();
}

void NTextField::setUnderline(int width, uint8_t* pattern)
{
    memcpy(underlinePattern, pattern, sizeof(underlinePattern));
    underlineWidth = width;
    internalInvalidate();
}

int NTextField::getUnderline(uint8_t* pattern)
{
    memcpy(pattern, underlinePattern, sizeof(underlinePattern));
    return underlineWidth;
}

TextWrap NTextField::getTextWrap()
{
    return wrapMode;
}

NTextField::NTextField(int x, int y, int w, int h, NTopLevel* tl, const char* text) : NTextField(x, y, w, h, tl->getContext(), text)
{

}

NTextField::NTextField(int x, int y, int w, int h, NRegion* rgn, const char* text) : NTextField(x, y, w, h, rgn->getContext(), text)
{

}

void NTextField::normaliseCursorPosition()
{
retry:
    for (int i = 0; i < poisonHiddenDataLength + 2; ++i) {
        if (text[curStart + i] == poisonCharacter) break;
        if (text[curStart + i] == poisonCharacterReverse) {
            curStart += i + 1;
            goto retry;
        }
    }

    for (int i = 0; i < poisonHiddenDataLength + 2; ++i) {
        if (text[curEnd + i] == poisonCharacter) break;
        if (text[curEnd + i] == poisonCharacterReverse) {
            curEnd += i + 1;
            goto retry;
        }
    }

    if (curStart != 0) {
        for (int i = 0; i < poisonHiddenDataLength + 2; ++i) {
            if (text[curStart - i] == poisonCharacterReverse) break;
            if (text[curStart - i] == poisonCharacter) {
                curStart -= i + 1;
                goto retry;
            }
        }
    } 

    if (curEnd != 0) {
        for (int i = 0; i < poisonHiddenDataLength + 2; ++i) {
            if (text[curEnd - i] == poisonCharacterReverse) break;
            if (text[curEnd - i] == poisonCharacter) {
                curEnd -= i + 1;
                goto retry;
            }
        }
    }
}

void NTextField::insert(int pos, char* inserted)
{
    if (pos < 0) return;

    char* txt = (char*) malloc(strlen(text) + strlen(inserted) + 4);
    for (int i = 0; i < pos; ++i) {
        txt[i] = text[i];
        txt[i + 1] = 0;
    }
    strcat(txt, inserted);
    strcat(txt, text + pos);
    setText(txt);
    free(txt);

    normaliseCursorPosition();
}

void NTextField::incCurEnd()
{
    while (text[++curEnd] == poisonCharacter) {
        curEnd += poisonHiddenDataLength + 1;
    }
}

void NTextField::incCurStart()
{
    while (text[++curStart] == poisonCharacter) {
        curStart += poisonHiddenDataLength + 1;
    }
}

void NTextField::decCurEnd()
{
    while (text[--curEnd] == poisonCharacterReverse) {
        curEnd -= poisonHiddenDataLength + 1;
    }

    if (curEnd < 0) curEnd = 0;
}

void NTextField::decCurStart()
{
    while (text[--curStart] == poisonCharacterReverse) {
        curStart -= poisonHiddenDataLength + 1;
    }

    if (curStart < 0) curStart = 0;
}

void textfieldKeyHandler(Window* w, void* self_, KeyStates key)
{
    NTextField* self = (NTextField*) self_;
    int msgkey = key.key;
    bool msgctrl = key.ctrl;
    bool msgshift = key.shift;

    if (msgkey == (int) Left) {
        self->keepBlinkOneExtraTick = true;
        self->blinkState = true;

        if (msgctrl) {
            if (msgshift) {
                if (self->curEnd) self->curEnd = 0;

            } else {
                self->curStart = 0;
                self->curEnd = 0;
            }

        } else {
            if (msgshift) {
                if (self->curEnd) self->decCurEnd();

            } else {
                if (self->curEnd) self->decCurEnd();
                self->curStart = self->curEnd;
            }
        }

    } else if (msgkey == (int) Up) {
        self->keepBlinkOneExtraTick = true;
        self->blinkState = true;

        if (msgctrl) {
            
        } else {
            int x1, y1;
            int x2, y2;
            int y3 = -1;
            self->getPositionFromIndex(self->curEnd, &x1, &y1);
            for (int i = self->curEnd; i != -1;) {
                self->decCurEnd();
                i = self->curEnd;
                self->getPositionFromIndex(i, &x2, &y2);
                if (y2 < y1) {
                    if (y3 == -1) y3 = y2;
                    if (y2 != y3) {
                        self->incCurEnd();
                        break;
                    }
                    if (x2 <= x1) break;
                }
            }

            if (!msgshift) self->curStart = self->curEnd;
        }

    } else if (msgkey == (int) Down) {
        self->keepBlinkOneExtraTick = true;
        self->blinkState = true;

        if (msgctrl) {

        } else {
            int x1, y1;
            int x2, y2;
            int y3 = -1;
            self->getPositionFromIndex(self->curEnd, &x1, &y1);
            for (int i = self->curEnd; self->text[i];) {
                self->incCurEnd();
                i = self->curEnd;
                self->getPositionFromIndex(i, &x2, &y2);
                if (y2 > y1) {
                    if (y3 == -1) y3 = y2;
                    if (y2 != y3) {
                        self->decCurEnd();
                        break;
                    }
                    if (x2 >= x1) break;
                }
            }

            if (!msgshift) self->curStart = self->curEnd;
        }

    } else if (msgkey == (int) Right) {
        self->keepBlinkOneExtraTick = true;
        self->blinkState = true;

        if (msgctrl) {
            if (msgshift) {
                while (self->curEnd < strlen(self->text)) self->incCurEnd();

            } else {
                self->curEnd = strlen(self->text);
                self->curStart = strlen(self->text);
            }

        } else {
            if (msgshift) {
                if (self->curEnd < strlen(self->text)) self->incCurEnd();

            } else {
                if (self->curEnd < strlen(self->text)) self->incCurEnd();
                self->curStart = self->curEnd;
            }
        }

    } else if (((msgkey >= ' ' && msgkey < 127) || msgkey == '\b' || msgkey == '\n' || msgkey == '\t') && !msgctrl) {
        self->keepBlinkOneExtraTick = true;
        self->blinkState = true;

        while (strlen(self->text) + 4 > self->textLength) {
            self->textLength *= 2;
            self->text = (char*) realloc(self->text, self->textLength);
        }

        if (self->curEnd < self->curStart) {
            int temp = self->curEnd;
            self->curEnd = self->curStart;
            self->curStart = temp;
        }

        char* txt = (char*) calloc(16 + strlen(self->text), 1);

        strcpy(txt, self->text);

        while (self->curEnd > self->curStart) {
            self->decCurEnd();
            int rem = self->curEnd;
            int len = strlen(txt);
            int i;
            for (i = rem; i < len - 1; i++) txt[i] = txt[i + 1];
            if (i < len) txt[i] = '\0';
        }

        if (msgkey == '\b' && self->curEnd) {
            self->decCurEnd();
            int rem = self->curEnd;
            int len = strlen(txt);
            int i;
            for (i = rem; i < len - 1; i++) txt[i] = txt[i + 1];
            if (i < len) txt[i] = '\0';

        } else {
            memmove(txt + self->curEnd + 1, txt + self->curEnd, strlen(txt + self->curEnd));
            txt[self->curStart] = msgkey;
            self->incCurEnd();
        }

        self->curStart = self->curEnd;

        strcpy(self->text, txt);
        free(txt);

    } else if (msgctrl && (msgkey == 'a' || msgkey == 'A') && !msgshift) {
        //Ctrl+A

        self->curStart = 0;
        while (self->curEnd < strlen(self->text)) self->incCurEnd();
        self->keepBlinkOneExtraTick = true;
        self->blinkState = true;

    } else {
        //don't repaint
        return;
    }

    self->invalidate();
}

NTextField::NTextField(int x, int y, int w, int h, Context* context, const char* _text) :
	NRegion(x, y, w, h, context)
{
    textLength = 64;
    text = (char*) calloc(textLength, 1);

    setText(_text);

    scrollX = 0;
    scrollY = 0;

    lineSpacingTenths = 15;
    charSpacingPercent = 100;

    alignment = TextAlignment::Left;
    wrapMode = TextWrap::Character;

    callback = nullptr;

    fgCol = 0x000000;
    bgCol = 0xFFFFFF;
    cursorCol = 0x000000;
    selFgCol = 0xFFFFFF;
    selBgCol = 0x000080;
    underlineCol = 0x000000;

    poisonCharacter = -1;
    poisonCharacterReverse = -2;
    poisonHiddenDataLength = 0;

    underline = false;
    underlinePattern[0] = 0;
    underlinePattern[1] = 1;
    underlinePattern[2] = 0;
    underlinePattern[3] = 0;
    underlineWidth = 1;

    tabStopPixels = 64;     //cannot be zero!!

    marginTop = 4;
    marginBottom = 4;
    marginLeft = 4;
    marginRight = 4;

    curStart = 3;
    curEnd = 36;

    win->keydown_function = textfieldKeyHandler;

	paintHandler = standardTextFieldPainter;
}

void NTextField::enableHiddenData(int poisonValue, int reversePoison, int tokenLength)
{
    poisonCharacter = poisonValue;
    poisonCharacterReverse = reversePoison;
    poisonHiddenDataLength = tokenLength;
}

void NTextField::disableHiddenData()
{
    enableHiddenData(-1, -2, 0);
}

NTextFieldFormattingCallback NTextField::getFormattingCallback()
{
    return callback;
}

void NTextField::setFormattingCallback(NTextFieldFormattingCallback call)
{
    callback = call;
}

int NTextField::getCursorStart()
{
    return curStart;
}

int NTextField::getCursorEnd()
{
    return curEnd;
}

void NTextField::setCursorPosition(int pos)
{
    selectText(pos, pos);
}

void NTextField::selectText(int start, int end)
{
    curStart = start;
    curEnd = end;
    internalInvalidate();
}

void NTextField::setForegroundColour(uint32_t col)
{
    fgCol = col;
    internalInvalidate();
}

uint32_t NTextField::getForegroundColour()
{
    return fgCol;
}

void NTextField::enableBold(bool on)
{
    bold = on;
}

void NTextField::disableBold()
{
    enableBold(false);
}

void NTextField::enableUnderline(bool on)
{
    underline = on;
}

void NTextField::disableUnderline()
{
    enableUnderline(false);
}

void NTextField::setBackgroundColour(uint32_t col)
{
    bgCol = col;
    internalInvalidate();
}

uint32_t NTextField::getBackgroundColour()
{
    return bgCol;
}

void NTextField::setHighlightBackgroundColour(uint32_t col)
{
    selBgCol = col;
}

uint32_t NTextField::getHighlightBackgroundColour()
{
    return selBgCol;
}

void NTextField::setHighlightForegroundColour(uint32_t col)
{
    selFgCol = col;
}

uint32_t NTextField::getHighlightForegroundColour()
{
    return selFgCol;
}

void NTextField::setCursorColour(uint32_t col)
{
    cursorCol = col;
    internalInvalidate();
}

uint32_t NTextField::getCursorColour()
{
    return cursorCol;
}

void NTextField::setUnderlineColour(uint32_t col)
{
    underlineCol = col;
    internalInvalidate();
}

uint32_t NTextField::getUnderlineColour()
{
    return underlineCol;
}

void NTextField::setAlignment(TextAlignment align)
{
    alignment = align;
    internalInvalidate();
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
    while (strlen(_text) + 16 > textLength) {
        textLength *= 2;
        text = (char*) realloc(text, textLength);
    }

    strcpy(text, _text);
    curStart = strlen(text);
    curEnd = strlen(text);

    internalInvalidate();
}

NTextField::~NTextField()
{
    if (text) {
        free(text);
    }
}