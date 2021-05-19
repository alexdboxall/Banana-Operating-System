#include "gdo.hpp"
#include "context.hpp"
#include <krnl/panic.hpp>
extern "C" {
	#include <libk/string.h>
}

void GDO::update()
{
	if (type != GDOType::Region) {
		panic("GDO::update on non-region");
		return;
	}

	context->fillRect(0, 0, context->width, context->height, 0x2267FE);
	context->clearClipRects();

	resetNext();
	while (hasNext()) {
		GDO* obj = getNext();

		if (obj && obj->type == GDOType::Region) {
			kprintf("RRRR: %d, %d, %d, %d\n", obj->dataRegion.y, \
					obj->dataRegion.x, \
					obj->dataRegion.y + obj->dataRegion.h - 1, \
					obj->dataRegion.x + obj->dataRegion.w - 1);

			context->addClipRect(new CRect(\
								 obj->dataRegion.y, \
								 obj->dataRegion.x, \
								 obj->dataRegion.y + obj->dataRegion.h - 1, \
								 obj->dataRegion.x + obj->dataRegion.w - 1));
		}

		/*if (obj && obj->contextDrawFunc) {
			obj->contextDrawFunc(obj);
		}*/
	}

	for (int i = 0; i < context->clip_rects->length(); ++i) {
		CRect* temp_rect = context->clip_rects->getDesiredElement(i)->getValue();

		kprintf("RECT: %d, %d, %d, %d\n", temp_rect->left, temp_rect->top,
				temp_rect->right - temp_rect->left + 1,
				temp_rect->bottom - temp_rect->top + 1);

		context->fillRect(temp_rect->left, temp_rect->top,
						  temp_rect->right - temp_rect->left + 1,
						  temp_rect->bottom - temp_rect->top + 1, 0x0000FF * i);
	}
}

void GDO::resetNext()
{
	dataRegion.iter = 0;
}


GDO::GDO(GDOType t, Context* ctxt)
{
	context = ctxt;
	type = t;
	contextDrawFunc = nullptr;

	if (type == GDOType::Region) {
		dataRegion.iter = 0;
		dataRegion.childDim = (GDO***) malloc(sizeof(GDO**) * GDO_CHILD_DIM_LEN);
		for (int i = 0; i < GDO_CHILD_DIM_LEN; ++i) {
			dataRegion.childDim[i] = nullptr;
		}

	}
}

GDO::~GDO()
{

}

bool GDO::hasNext()
{
	int temp = dataRegion.iter;
	while (temp < GDO_CHILD_DIM_LEN * GDO_CHILD_DIM_LEN) {
		GDO* ch = getChild(temp++);
		if (ch) return true;
	}
	return false;
}

GDO* GDO::getNext()
{
	while (dataRegion.iter < GDO_CHILD_DIM_LEN * GDO_CHILD_DIM_LEN) {
		GDO* ch = getChild(dataRegion.iter++);
		if (ch) return ch;
	}
	return nullptr;
}

GDO* GDO::getChild(int index)
{
	if (index >= GDO_CHILD_DIM_LEN * GDO_CHILD_DIM_LEN) return nullptr;
	GDO** dim = dataRegion.childDim[(unsigned) index / GDO_CHILD_DIM_LEN];
	if (!dim) {
		return nullptr;
	}
	return dim[(unsigned) index % GDO_CHILD_DIM_LEN];
}

int GDO::indexOf(GDO* obj)
{
	for (int i = 0; i < GDO_CHILD_DIM_LEN * GDO_CHILD_DIM_LEN; ++i) {
		GDO* ch = getChild(dataRegion.iter++);
		if (ch == obj) return i;
	}
	return -1;
}

int GDO::addChild(GDO* obj)
{
	int notDim = -1;
	for (int i = 0; i < GDO_CHILD_DIM_LEN; ++i) {
		GDO** dim = dataRegion.childDim[i];
		if (dim) {
			for (int j = 0; j < GDO_CHILD_DIM_LEN; ++j) {
				if (!dim[j]) {
					dim[j] = obj;
					return i * GDO_CHILD_DIM_LEN + j;
				}
			}

		} else {
			notDim = i;
		}
	}

	if (notDim) {
		//create a new dim
		dataRegion.childDim[notDim] = (GDO**) malloc(sizeof(GDO*) * GDO_CHILD_DIM_LEN);		//MUST BE calloc!
		memset(dataRegion.childDim[notDim], 0, sizeof(GDO*) * GDO_CHILD_DIM_LEN);
		dataRegion.childDim[notDim][0] = obj;
		return notDim * GDO_CHILD_DIM_LEN;
	}

	panic("GDO::addChild no more slots left!");
	return -1;
}

bool GDO::removeChild(int index)
{
	if (index >= GDO_CHILD_DIM_LEN * GDO_CHILD_DIM_LEN) return false;
	GDO** dim = dataRegion.childDim[(unsigned) index / GDO_CHILD_DIM_LEN];
	if (!dim) {
		return false;
	}
	bool ret = dim[(unsigned) index % GDO_CHILD_DIM_LEN] != nullptr;
	dim[(unsigned) index % GDO_CHILD_DIM_LEN] = nullptr;
	return ret;
}

bool GDO::removeChild(GDO* obj)
{
	int index = indexOf(obj);
	if (index == -1) {
		return false;
	}
	return removeChild(index);
}