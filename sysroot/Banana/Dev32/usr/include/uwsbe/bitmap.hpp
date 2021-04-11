#ifndef _WSBE_BITMAP_HPP
#define _WSBE_BITMAP_HPP

#include "frame.hpp"

class Bitmap : public Frame
{
private:

protected:
	virtual void _impl() override;

	WsbeScript currScript;

public:
	Bitmap(int x, int y, const char* filename = "");
};

#endif