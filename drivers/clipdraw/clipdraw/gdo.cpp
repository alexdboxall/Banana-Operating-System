#include "gdo.hpp"
#include "context.hpp"
#include <krnl/panic.hpp>
extern "C" {
	#include <libk/string.h>
}

#include "region.hpp"

void GDO::update(List<CRect*>* dirtyRegions, bool paintChildren)
{
	if (type != GDOType::Region) {
		panic("UPDATE CALLED ON NON-REGION");

	} else {
		int i, screen_x, screen_y, child_screen_x, child_screen_y;
		Region* current_child;
		CRect* temp_rect;
		Region* window = (Region*) this;

		if (!context) return;

		window->applyBoundClipping(0, dirtyRegions);

		screen_x = window->screenX();
		screen_y = window->screenY();

		context->clippingOn = false;

		window->resetNext();
		while (window->hasNext()) {
			auto next = window->getNext();

			if (next->type == GDOType::Region) {
				current_child = (Region*) next;

				child_screen_x = current_child->screenX();
				child_screen_y = current_child->screenY();

				temp_rect = new CRect(child_screen_y, child_screen_x,
									 child_screen_y + current_child->dataRegion.h - 1,
									 child_screen_x + current_child->dataRegion.w - 1);
				context->subClipRect(temp_rect);
				delete temp_rect;
			}
		}

		context->transX = screen_x;
		context->transY = screen_y;

		//context->clippingOn = false;

		window->resetNext();
		while (window->hasNext()) {
			GDO* next = window->getNext();
			if (next->type != GDOType::Region) {
				if (next->contextDrawFunc) {
					next->contextDrawFunc(next);
				}
			}
		}

		context->clearClipRects();
		context->transX = 0;
		context->transY = 0;

		if (paintChildren) {
			window->resetNext();
			while (window->hasNext()) {
				GDO* next = window->getNext();
				if (next->type == GDOType::Region) {
					Region* currentChild = ((Region*) next);

					if (dirtyRegions) {
						int j = 0;
						for (; j < dirtyRegions->length(); ++j) {
							temp_rect = dirtyRegions->getDesiredElement(j)->getValue();
							int screen_x = currentChild->screenX();
							int screen_y = currentChild->screenY();

							if (temp_rect->left <= (screen_x + currentChild->dataRegion.w - 1) &&
								temp_rect->right >= screen_x &&
								temp_rect->top <= (screen_y + currentChild->dataRegion.h - 1) &&
								temp_rect->bottom >= screen_y) {
								break;
							}
						}

						if (j == dirtyRegions->length()) {
							continue;
						}
					}

					currentChild->update(dirtyRegions, 1);
				}
			}
		}
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
		kprintf("allocating the child dim.\n");
		dataRegion.iter = 0;
		childDim = (GDO***) malloc(sizeof(GDO**) * GDO_CHILD_DIM_LEN);
		kprintf("childDim = 0x%X\n", childDim);
		for (int i = 0; i < GDO_CHILD_DIM_LEN; ++i) {
			childDim[i] = nullptr;
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
	if (!childDim) {
		panic("NO CHILD DIM");
	}
	GDO** dim = childDim[(unsigned) index / GDO_CHILD_DIM_LEN];
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

int GDO::screenX()
{
	if (type != GDOType::Region) {
		kprintf("GDO::screenX on non-region");
	}
	if (parent) {
		if (parent->type != GDOType::Region) {
			panic("pre-emptive GDO::screenX on non-region");
		}
		return dataRegion.x + parent->screenX();
	}
	return dataRegion.x;
}

int GDO::screenY()
{
	if (type != GDOType::Region) {
		kprintf("GDO::screenY on non-region");
	}
	if (parent) {
		if (parent->type != GDOType::Region) {
			panic("pre-emptive GDO::screenY on non-region");
		}
		return dataRegion.y + parent->screenY();
	}
	return dataRegion.y;
}

int GDO::addChild(GDO* obj)
{
	if (type != GDOType::Region) {
		panic("GDO::addChild on non-region");
		return 0;
	}
	obj->parent = this;

	int notDim = -1;
	for (int i = 0; i < GDO_CHILD_DIM_LEN; ++i) {
		GDO** dim = childDim[i];
		if (dim) {
			for (int j = 0; j < GDO_CHILD_DIM_LEN; ++j) {
				if (!dim[j]) {
					dim[j] = obj;
					return i * GDO_CHILD_DIM_LEN + j;
				}
			}

		} else if (notDim == -1) {
			notDim = i;
		}
	}

	if (notDim != -1) {
		//create a new dim
		kprintf("CREATING A NEW DIM AT %d\n", notDim);
		childDim[notDim] = (GDO**) malloc(sizeof(GDO*) * GDO_CHILD_DIM_LEN);		//MUST BE calloc!
		memset(childDim[notDim], 0, sizeof(GDO*) * GDO_CHILD_DIM_LEN);
		childDim[notDim][0] = obj;
		return notDim * GDO_CHILD_DIM_LEN;
	}

	panic("GDO::addChild no more slots left!");
	return -1;
}

bool GDO::removeChild(int index)
{
	if (type != GDOType::Region) {
		panic("GDO::removeChild on non-region");
		return false;
	}
	if (index >= GDO_CHILD_DIM_LEN * GDO_CHILD_DIM_LEN) return false;
	GDO** dim = childDim[(unsigned) index / GDO_CHILD_DIM_LEN];
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