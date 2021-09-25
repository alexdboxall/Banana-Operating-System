#include "NTextFormatter.hpp"

#include <string.h>
#include <stdlib.h>

int lineSpacingTenths;
int wrapWidth;

bool needsRegeneration;
NFont* font;

void NTextFormatter::regenerate()
{
	needsRegeneration = false;

	// DO THINGS...

	generatedBoundingHeight = 0;
	generatedBoundingWidth = 0;
}


NTextFormatter::NTextFormatter() : NTextFormatter("") {}

NTextFormatter::NTextFormatter(const char* txt)
{
	text = (char*) malloc(strlen(txt));
	strcpy(text, txt);
}

char* NTextFormatter::getText()
{
	return text;
}

void NTextFormatter::setText(const char* text)
{
	setText((char*) text);

}
void NTextFormatter::setText(char* txt)
{
	if (text) {
		free(text);
		text = nullptr;
	}

	text = (char*) malloc(strlen(txt));
	strcpy(text, txt);
}

NTextFormatter::~NTextFormatter()
{
	if (text) {
		free(text);
		text = nullptr;
	}
}

void NTextFormatter::copyStyle(NTextFormatter fmt)
{
	lineSpacingTenths = fmt.lineSpacingTenths;
	wrapWidth = fmt.wrapWidth;
	wrapStyle = fmt.wrapStyle;
	font = fmt.font;

	needsRegeneration = true;
}

void NTextFormatter::setLineSpacing(int tenthPoints)
{
	lineSpacingTenths = tenthPoints;
	needsRegeneration = true;
}

int NTextFormatter::getLineSpacing()
{
	return lineSpacingTenths;
}

void NTextFormatter::setWrapWidth(int ww)
{
	wrapWidth = ww;
	needsRegeneration = true;
}

void NTextFormatter::setWrapStyle(NWrapStyle style)
{
	wrapStyle = style;
	needsRegeneration = true;
}

int NTextFormatter::getBoundingWidth()
{
	if (needsRegeneration) {
		regenerate();
	}
	return generatedBoundingWidth;
}

int NTextFormatter::getBoundingHeight()
{
	if (needsRegeneration) {
		regenerate();
	}
	return generatedBoundingHeight;
}

NFont* NTextFormatter::getFont()
{
	return font;
}

int NTextFormatter::getWrapWidth()
{
	return wrapWidth;
}

NWrapStyle NTextFormatter::getWrapStyle()
{
	return wrapStyle;
}

void NTextFormatter::setFont(NFont* f)
{
	font = f;
	needsRegeneration = true;
}