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

public:
	NTextField(int x, int y, int w, int h, Context* context, const char* text = "");
	NTextField(int x, int y, int w, int h, NTopLevel* tl, const char* text = "");
	NTextField(int x, int y, int w, int h, NRegion* rgn, const char* text = "");
	~NTextField();

	void setAlignment(TextAlignment align);
	TextAlignment getAlignment();

	void invalidate();

	char* getText();
	void setText(const char* text);
};

#endif