#pragma once

#include <stdint.h>

#define GDO_CHILD_DIM_LEN			16		//a power of 2 speeds things up because the compiler can shift instead of divide

enum class GDOType : uint8_t
{
	Region,
	Rectangle,

};

struct GDOList;
struct GDOListNode;
struct Context;

struct GDO
{
	GDOType type;
	Context* context;

	union
	{
		struct
		{
			int x;
			int y;
			int w;
			int h;

			GDO*** childDim;
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

	void (*contextDrawFunc)(GDO*);
	void update();

	GDO(GDOType type, Context* ctxt);
	~GDO();

};
