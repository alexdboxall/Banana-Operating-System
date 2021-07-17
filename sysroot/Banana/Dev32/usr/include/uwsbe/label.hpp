#ifndef _WSBE_LABEL_HPP
#define _WSBE_LABEL_HPP

#include "frame.hpp"

class Label : public Frame
{
private:

protected:
	virtual void _impl() override;
	char* text;
	int x;
	int y;

	WsbeScript currScript;

	void redoPaintScript();

	uint32_t fgCol = 0x000000;
	uint32_t bgCol = WIN_BGCOLOR;

public:
	Label(int x, int y, const char* text = "");
	void setText(const char* text);	

	void setBgColour(uint32_t col);
	void setFgColour(uint32_t col);
};

#endif