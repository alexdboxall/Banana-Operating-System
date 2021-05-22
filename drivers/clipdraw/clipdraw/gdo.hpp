#pragma once

#include <stdint.h>
#include <thr/prcssthr.hpp>

#include "list.hpp"

extern Process* kernelProcess;

#define GDO_CHILD_DIM_LEN			16		//a power of 2 speeds things up because the compiler can shift instead of divide

enum class GDOType : uint8_t
{
	Region,
	Rectangle,
	LegacyText,
	Ellipse,
};

typedef int LegacyFont;

struct GDOList;
struct GDOListNode;
struct Context;
struct CRect;

struct GDO
{
	GDOType type;
	Context* context;
	GDO* parent;
	GDO*** childDim;

	struct
	{
		//X,Y,W,H need to be lined up
		struct
		{
			int x;
			int y;
			int w;
			int h;

			char* text;
			uint32_t colour;
			LegacyFont font;

		} dataLegacyText;

		struct
		{
			int x;
			int y;
			int w;
			int h;

			int iter;
		} dataRegion;

		struct
		{
			int x;
			int y;
			int w;
			int h;
			uint32_t colour;

		} dataShape;
	};

	GDO* getChild(int index);
	int indexOf(GDO* obj);
	int addChild(GDO* obj);
	bool removeChild(int index);
	bool removeChild(GDO* obj);

	void resetNext();
	bool hasNext();
	GDO* getNext();

	int screenX();
	int screenY();

	void (*contextDrawFunc)(GDO*);
	void update(List<CRect*>* dirtyRegions, bool paintChildren);

	GDO(GDOType type, Context* ctxt);
	~GDO();

};