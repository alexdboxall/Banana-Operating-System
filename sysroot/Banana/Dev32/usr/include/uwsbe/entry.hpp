#ifndef _WSBE_ENTRY_HPP
#define _WSBE_ENTRY_HPP

#include "frame.hpp"

class Entry : public Frame
{
private:

protected:
	friend void _entryKeyDownHandler(Frame* f, Message msg);
	friend void _entryEnterLeaveHandler(Frame* f, Message msg);
	friend void _entryLbuttonHandler(Frame* f, Message msg);
	friend void _entryBlinkHandler(Frame* f, Message msg);
	virtual void _impl() override;
	
	bool blinkState;
	bool keepBlinkOneExtraTick;

	char* text;
	char* placeholder;
	int curStart;
	int curEnd;
	int x;
	int y;
	int width;

	void entryKeyDownHandler(Frame* f, Message msg);
	void entryEnterLeaveHandler(Frame* f, Message msg);
	void entryLbuttonHandler(Frame* f, Message msg);
	void entryBlinkHandler(Frame* f, Message msg);

	int textLength;

	WsbeScript currScript;
	char maskChar = 0;

public:
	void redoPaintScript();

	Entry(int x, int y, int width, const char* text = "");

	void setText(const char* text);	
	char* getText();

	void setMaskCharacter(char c);
	void removeMaskCharacter();

	void setPlaceholder(const char* text);
};

#endif