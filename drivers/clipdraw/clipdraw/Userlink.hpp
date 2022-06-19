#pragma once

#include <stdint.h>
#include <stddef.h>

class NFrame;

enum class UserCommand : uint32_t
{
	CreateWindow,
	AddChild,
	GetDesktop,
	SetCoordinates,
	GetCoordinates,
	Fullscreen,
	Raise,
	Hide,
	Invalidate,
};

namespace UserCommandArg
{
	struct CreateWindow
	{
		int x;
		int y;
		int w;
		int h;
		int flags;
		char name[64];
	};

	struct AddChild
	{
		void* parent;
	};

	struct Fullscreen
	{
		bool state;
		bool set;
		bool toggle;
	};

	struct Hide
	{
		bool state;
		bool set;
		bool stateOverall;
	};

	struct Coordinates
	{
		int x;
		int y;
		int w;
		int h;
		int absX;
		int absY;

		bool setX;
		bool setY;
		bool setW;
		bool setH;
		bool setAll;
	};
};

uint64_t usermodeLinkHandler(UserCommand command, NFrame* frame, void* arg);