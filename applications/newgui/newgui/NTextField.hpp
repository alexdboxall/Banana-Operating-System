//
//  NButton.hpp
//  NGUI
//
//  Created by Alex Boxall on 16/9/21.
//  Copyright © 2021 Alex Boxall. All rights reserved.
//

#ifndef NTextField_hpp
#define NTextField_hpp

#include "NRegion.hpp"
#include "NToplevel.hpp"

enum class TextAlignment
{
	Left,
	Right,
	Centre,
	Justify
};

enum class TextWrap
{
	None,
	Character,
	Word,
};

class NTextField;
typedef int (*NTextFieldFormattingCallback)(NTextField*, int);

class NTextField : public NRegion
{
protected:
	friend int standardTextFieldPainter(NRegion* self);

	char* text;
	int scrollX;
	int scrollY;

	int lineSpacingTenths;
	int charSpacingPercent;

	TextAlignment alignment;

	int marginTop;
	int marginBottom;
	int marginLeft;
	int marginRight;

	TextWrap wrapMode;

	int curStart;
	int curEnd;

	uint32_t fgCol;
	uint32_t selFgCol;
	uint32_t selBgCol;
	uint32_t cursorCol;

	NTextFieldFormattingCallback callback;

	bool invalidating;

public:
	NTextField(int x, int y, int w, int h, Context* context, const char* text = "");
	NTextField(int x, int y, int w, int h, NTopLevel* tl, const char* text = "");
	NTextField(int x, int y, int w, int h, NRegion* rgn, const char* text = "");
	~NTextField();

	void setTextWrap(TextWrap wrap);
	TextWrap getTextWrap();

	void setAlignment(TextAlignment align);
	TextAlignment getAlignment();

	void invalidate();

	NTextFieldFormattingCallback getFormattingCallback();
	void setFormattingCallback(NTextFieldFormattingCallback call);

	void setForegroundColour(uint32_t col);
	uint32_t getForegroundColour();

	char* getText();
	void setText(const char* text);
};

#endif