//
//  NButton.cpp
//  NGUI
//
//  Created by Alex Boxall on 16/9/21.
//  Copyright © 2021 Alex Boxall. All rights reserved.
//

#include <stdint.h>

#include "NButton.hpp"

#include <string.h>
#include <stdlib.h>

int standardButtonPainter(NRegion* _self)
{
    NButton* self = (NButton*) _self;

    if (self->mouseDown && !self->disabled) {
        switch (self->style) {
        case ButtonStyle::PopOut:
            self->fillRect(0, 0, self->width, self->height, 0xD4D4D4);
            self->drawRect(0, 0, self->width, 1, 0xAAAAAA);
            self->drawRect(0, 0, 1, self->height, 0xAAAAAA);

            self->drawRect(0, self->height - 1, self->width, 1, 0xFFFFFF);
            self->drawRect(self->width - 1, 0, 1, self->height, 0xFFFFFF);
            break;

        case ButtonStyle::Standard:
            self->fillRect(0, 0, self->width, self->height, 0x808080);
            break;

        default:
            break;
        }

    } else if (self->mouseOver && !self->disabled) {
        switch (self->style) {
        case ButtonStyle::PopOut:
            self->fillRect(0, 0, self->width, self->height, 0xD4D4D4);
            self->drawRect(0, 0, self->width, 1, 0xFFFFFF);
            self->drawRect(0, 0, 1, self->height, 0xFFFFFF);

            self->drawRect(0, self->height - 1, self->width, 1, 0xAAAAAA);
            self->drawRect(self->width - 1, 0, 1, self->height, 0xAAAAAA);
            break;

        case ButtonStyle::Standard:
            self->fillRect(0, 0, self->width, self->height, 0xAAAAAA);
            self->drawRect(0, 0, self->width, self->height, 0x808080);
            self->drawRect(1, 1, self->width - 2, self->height - 2, 0x808080);
            break;

        default:
            break;
        }

    } else {
        switch (self->style) {
        case ButtonStyle::PopOut:
            self->fillRect(0, 0, self->width, self->height, 0xD4D4D4);
            break;

        case ButtonStyle::Standard:
            self->fillRect(0, 0, self->width, self->height, 0xAAAAAA);
            break;

        default:
            break;
        }
    }

    if (self->bmp && self->iconPos != ButtonIconPosition::Ignore) {
        switch (self->iconPos) {
        case ButtonIconPosition::Left:
        {
            int ww, hh;
            Context_bound_text(self->getContext(), self->text, &ww, &hh);
            ww += self->bmp->width + self->textPadding + self->iconPadding;
            int w1 = (self->width - ww) / 2;
            if (self->iconFixedWidth != -1) w1 = self->iconFixedWidth;
            Context_draw_bitmap(self->getContext(), self->bmp->data, w1, (self->height - self->bmp->height) / 2, self->bmp->width, self->bmp->height);
            w1 += self->iconPadding + self->bmp->width;
            if (self->fixedWidth != -1) w1 = self->fixedWidth;
            self->drawBasicText(w1, (self->height - hh) / 2, self->disabled ? 0x808080 : 0x000000, self->text);
            break;
        }
        case ButtonIconPosition::Right:
        {
            int ww, hh;
            Context_bound_text(self->getContext(), self->text, &ww, &hh);
            ww += self->textPadding;
            int ogww = ww;
            ww += self->bmp->width + self->iconPadding;
            int w1 = (self->width - ww) / 2;
            if (self->fixedWidth != -1) w1 = self->fixedWidth;
            self->drawBasicText(w1, (self->height - hh) / 2, self->disabled ? 0x808080 : 0x000000, self->text);
            w1 += self->iconPadding + ogww;
            if (self->iconFixedWidth != -1) w1 = self->iconFixedWidth;
            Context_draw_bitmap(self->getContext(), self->bmp->data, w1, (self->height - self->bmp->height) / 2, self->bmp->width, self->bmp->height);

            break;
        }
        case ButtonIconPosition::Replace:
        {
            int ww = self->bmp->width;
            int hh = self->bmp->height;
            int w1 = (self->width - ww) / 2;
            if (self->iconFixedWidth != -1) w1 = self->iconFixedWidth;
            Context_draw_bitmap(self->getContext(), self->bmp->data, w1, (self->height - hh) / 2, self->bmp->width, self->bmp->height);
            break;
        }
        default:
            break;
        }
        
    } else {
        int ww, hh;
        Context_bound_text(self->getContext(), self->text, &ww, &hh);
        int w1 = (self->width - ww) / 2;
        if (self->fixedWidth != -1) w1 = self->fixedWidth;
        self->drawBasicText(w1, (self->height - hh) / 2, self->disabled ? 0x808080 : 0x000000, self->text);
    }

    return 0;
}

void NButton::invalidate()
{
    Window_invalidate(win, 0, 0, win->height, win->width);
}

void buttonSetMouseOver(Window* w, void* self_, int x, int y)
{    
    if (!((NButton*) self_)->mouseOver) {
        ((NButton*) self_)->mouseOver = true;
        ((NButton*) self_)->invalidate();
    }
}

void buttonResetMouseOver(Window* w, void* self_)
{    
    if (((NButton*) self_)->mouseOver) {
        ((NButton*) self_)->mouseOver = false;
        ((NButton*) self_)->invalidate();
    }
}

void buttonSetMouseDown(Window* w, void* self_, int x, int y)
{
    if (!((NButton*) self_)->mouseDown) {
        ((NButton*) self_)->mouseDown = true;
        ((NButton*) self_)->invalidate();
    }
}

void buttonResetMouseDown(Window* w, void* self_, int x, int y)
{
    if (((NButton*) self_)->mouseDown) {
        ((NButton*) self_)->mouseDown = false;
        if (((NButton*) self_)->mouseOver && ((NButton*) self_)->buttonCommand) {
            ((NButton*) self_)->buttonCommand((NButton*) self_);
        }
        ((NButton*) self_)->invalidate();
    }
}

NButton::NButton(int x, int y, int w, int h, NTopLevel* tl, const char* text, ButtonStyle style) : NButton(x, y, w, h, tl->getContext(), text, style)
{

}

NButton::NButton(int x, int y, int w, int h, NRegion* rgn, const char* text, ButtonStyle style) : NButton(x, y, w, h, rgn->getContext(), text, style)
{

}

NButton::NButton(int x, int y, int w, int h, Context* context, const char* _text, ButtonStyle _style) :
	NRegion(x, y, w, h, context)
{
	text = (char*) malloc(strlen(_text));
	strcpy(text, _text);

	style = _style;

    bmp = nullptr;
    buttonCommand = nullptr;
    disabled = false;

    iconPadding = 2;
    textPadding = 2;
    iconFixedWidth = -1;
    fixedWidth = -1;

    mouseOver = false;
    mouseDown = false;
    weNeedToDeleteNLoadedBitmap = false;
	paintHandler = standardButtonPainter;

    win->mouseup_function    = buttonResetMouseDown;
    win->mousedown_function  = buttonSetMouseDown;
    win->mousemove_function  = buttonSetMouseOver;
    win->mouseleave_function = buttonResetMouseOver;
}

bool NButton::isEnabled()
{
    return !disabled;
}

void NButton::enable(bool enabled)
{
    disabled = !enabled;
    invalidate();
}

void NButton::disable()
{
    enable(false);
}

void NButton::setFixedWidth(int fw)
{
    fixedWidth = fw;
    invalidate();
}

void NButton::setTextPositionAutomatically()
{
    setFixedWidth(-1);
}

void NButton::setIconFixedWidth(int fw)
{
    iconFixedWidth = fw;
    invalidate();
}

void NButton::setIconPositionAutomatically()
{
    setIconFixedWidth(-1);
}

char* NButton::getText()
{
    return text;
}

void NButton::setText(const char* _text)
{
    if (text) free(text);
    text = (char*) malloc(strlen(_text));
    strcpy(text, _text);

    invalidate();
}

void NButton::setTextPadding(int padding)
{
    textPadding = padding;
    invalidate();
}

void NButton::setIconPadding(int padding)
{
    iconPadding = padding;
    invalidate();
}

void NButton::setStyle(ButtonStyle _style)
{
    style = _style;
    invalidate();
}

ButtonStyle NButton::getStyle()
{
    return style;
}

void NButton::setCommand(NButtonCallback cmd)
{
    buttonCommand = cmd;
}

NButtonCallback NButton::getCommand()
{
    return buttonCommand;
}

void NButton::invoke()
{
    if (buttonCommand) {
        buttonCommand(this);
    }
}

void NButton::setIconPosition(ButtonIconPosition pos)
{
    iconPos = pos;
    invalidate();
}

void NButton::setIcon(NLoadedBitmap* _bmp, ButtonIconPosition pos)
{
    if (bmp && weNeedToDeleteNLoadedBitmap) {
        delete bmp;
        bmp = nullptr;
    }

    bmp = _bmp;
    weNeedToDeleteNLoadedBitmap = false;
    setIconPosition(pos);
}

void NButton::setIcon(const char* file, ButtonIconPosition pos)
{
    setIcon(new NLoadedBitmap(file), pos);
    weNeedToDeleteNLoadedBitmap = true;
}

void NButton::removeIcon()
{
    if (bmp && weNeedToDeleteNLoadedBitmap) {
        delete bmp;
        bmp = nullptr;
    }
    invalidate();
}

NButton::~NButton()
{
    if (text) {
        free(text);
    }

    if (weNeedToDeleteNLoadedBitmap) {
        delete bmp;
    }
}