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
	friend int textFieldEngine(NRegion* _self, int posi, int* x, int* y, int* lastHeight);
	friend void textfieldKeyHandler(Window* w, void* self_, KeyStates key);
	friend void textfieldEnterHandler(Window* w, void* self_);
	friend void textfieldLeaveHandler(Window* w, void* self_);

	void getPositionFromIndex(int index, int* x, int* y, int* lastHeight = nullptr);

	char* text;
	int textLength;

	int scrollX;
	int scrollY;

	int oldCursor;

	int lastKnownCursorXPos;

	int tabStopPixels;

	bool keepBlinkOneExtraTick;
	bool blinkState;

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
	uint32_t bgCol;
	uint32_t underlineCol;
	uint32_t selFgCol;
	uint32_t selBgCol;
	uint32_t cursorCol;

	bool bold;
	bool underline;
	uint8_t underlinePattern[4];
	int underlineWidth;

	NTextFieldFormattingCallback callback;

	int poisonCharacter;
	int poisonCharacterReverse;
	int poisonHiddenDataLength;

	void incCurEnd();
	void incCurStart();
	void decCurEnd();
	void decCurStart();

	void normaliseCursorPosition();

public:
	NTextField(int x, int y, int w, int h, Context* context, const char* text = "");
	NTextField(int x, int y, int w, int h, NTopLevel* tl, const char* text = "");
	NTextField(int x, int y, int w, int h, NRegion* rgn, const char* text = "");
	~NTextField();

	void enableHiddenData(int poisonValue, int reversePoison, int tokenLength);
	void disableHiddenData();

	void insert(int pos, char* text);

	int getCursorStart();
	int getCursorEnd();
	void setCursorPosition(int pos);
	void selectText(int start, int end);

	void setUnderline(int width, uint8_t* pattern);
	int getUnderline(uint8_t* pattern);

	void enableBold(bool on = true);
	void disableBold();

	void enableUnderline(bool on = true);
	void disableUnderline();

	void setTextWrap(TextWrap wrap);
	TextWrap getTextWrap();

	void setAlignment(TextAlignment align);
	TextAlignment getAlignment();

	NTextFieldFormattingCallback getFormattingCallback();
	void setFormattingCallback(NTextFieldFormattingCallback call);

	void setForegroundColour(uint32_t col);
	void setBackgroundColour(uint32_t col);
	void setUnderlineColour(uint32_t col);
	void setHighlightForegroundColour(uint32_t col);
	void setHighlightBackgroundColour(uint32_t col);
	void setCursorColour(uint32_t col);

	uint32_t getForegroundColour();
	uint32_t getBackgroundColour();
	uint32_t getUnderlineColour();
	uint32_t getHighlightForegroundColour();
	uint32_t getHighlightBackgroundColour(); 
	uint32_t getCursorColour();

	char* getText();
	void setText(const char* text);
};

#endif