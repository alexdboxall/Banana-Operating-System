//
//  NButton.hpp
//  NGUI
//
//  Created by Alex Boxall on 16/9/21.
//  Copyright © 2021 Alex Boxall. All rights reserved.
//

#ifndef NButton_hpp
#define NButton_hpp

#include "NRegion.hpp"
#include "NToplevel.hpp"
#include "NLoadedBitmap.hpp"

enum class ButtonStyle
{
	Standard,
	PopOut,
	AlwaysPopOut,
};

enum class ButtonIconPosition
{
	Replace,
	Ignore,
	Left,
	Right,
};

class NButton;
typedef int (*NButtonCallback)(NButton*);

class NButton : public NRegion
{
protected:
	friend int standardButtonPainter(NRegion* self);
	friend void buttonSetMouseOver(Window* w, void* self_, int x, int y);
	friend void buttonResetMouseOver(Window* w, void* self_);
	friend void buttonSetMouseDown(Window* w, void* self_, int x, int y);
	friend void buttonResetMouseDown(Window* w, void* self_, int x, int y);

	bool mouseOver;
	bool disabled;
	bool mouseDown;
	char* text;
	ButtonStyle style;
	NButtonCallback buttonCommand;
	ButtonIconPosition iconPos;
	int iconFixedWidth;
	int fixedWidth;

	int textPadding;
	int iconPadding;
	NLoadedBitmap* bmp;
	bool weNeedToDeleteNLoadedBitmap;

	uint32_t fgCol;
	uint32_t bgCol;

	bool bold;

public:
	NButton(int x, int y, int w, int h, Context* context, const char* text = "Button", ButtonStyle style = ButtonStyle::Standard);
	NButton(int x, int y, int w, int h, NTopLevel* tl, const char* text = "Button", ButtonStyle style = ButtonStyle::Standard);
	NButton(int x, int y, int w, int h, NRegion* rgn, const char* text = "Button", ButtonStyle style = ButtonStyle::Standard);
	~NButton();
	
	void enableBold(bool on = true);
	void disableBold();

	bool isEnabled();
	void enable(bool enabled = true);
	void disable();

	void invalidate();
	void invoke();

	void setBackgroundColour(uint32_t col);
	uint32_t getBackgroundColour();
	void setForegroundColour(uint32_t col);
	uint32_t getForegroundColour();

	void setIcon(NLoadedBitmap* bmp, ButtonIconPosition pos = ButtonIconPosition::Replace);
	void setIcon(const char* file, ButtonIconPosition pos = ButtonIconPosition::Replace);
	void setIconPosition(ButtonIconPosition pos);
	void setIconPadding(int padding);
	void setTextPadding(int padding);
	void setFixedWidth(int fw);
	void setTextPositionAutomatically();
	void setIconFixedWidth(int fw);
	void setIconPositionAutomatically();
	void removeIcon();

	char* getText();
	void setText(const char* text);

	void setStyle(ButtonStyle style);
	ButtonStyle getStyle();

	void setCommand(NButtonCallback cmd);

	NButtonCallback getCommand();
};

#endif