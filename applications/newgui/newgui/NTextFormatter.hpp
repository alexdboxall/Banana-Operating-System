//
//  NButton.hpp
//  NGUI
//
//  Created by Alex Boxall on 16/9/21.
//  Copyright © 2021 Alex Boxall. All rights reserved.
//

#ifndef NTextFormatter_hpp
#define NTextFormatter_hpp

#include <stdint.h>

class NFont;

enum class NWrapStyle
{
	None,
	Character,
	Word,
};

class NTextFormatter
{
protected:
	int lineSpacingTenths;
	int wrapWidth;
	NWrapStyle wrapStyle;

	void regenerate();
	bool needsRegeneration;

	int generatedBoundingWidth;
	int generatedBoundingHeight;

	NFont* font;

	char* text;

public:
	~NTextFormatter();
	NTextFormatter();
	NTextFormatter(const char* text);

	void copyStyle(NTextFormatter fmt);

	void setLineSpacing(int tenthPoints);
	int getLineSpacing();

	void setWrapWidth(int wrapWidth);
	void setWrapStyle(NWrapStyle style);
	int getWrapWidth();
	NWrapStyle getWrapStyle();

	int getBoundingWidth();
	int getBoundingHeight();

	NFont* getFont();
	void setFont(NFont* f);

	char* getText();
	void setText(const char* text);
	void setText(char* text);
};

#endif