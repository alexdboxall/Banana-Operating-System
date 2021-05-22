#include "region.hpp"

void regnDrawFunc(GDO* gdo)
{

}

Region::Region(int x, int y, int w, int h, Context* ctxt) : GDO(GDOType::Region, ctxt)
{
	dataRegion.x = x;
	dataRegion.y = y;
	dataRegion.w = w;
	dataRegion.h = h;

	contextDrawFunc = regnDrawFunc;
}

void Region::applyBoundClipping(int in_recursion, List<CRect*>* dirty_regions)
{
    CRect* temp_rect;
    int screen_x, screen_y;
    List<Region*>* clip_windows;
    Region* clipping_window;

    if (!context) return;

    screen_x = screenX();
    screen_y = screenY();

    temp_rect = new CRect(screen_y, screen_x, screen_y + dataRegion.h - 1,
                         screen_x + dataRegion.w - 1);

    if (!parent) {
        if (dirty_regions) {
            for (int i = 0; i < dirty_regions->length(); ++i) {
                CRect* current_dirty_rect = dirty_regions->getDesiredElement(i)->getValue();
                CRect* clone_dirty_rect = new CRect(current_dirty_rect->top,
                                            current_dirty_rect->left,
                                            current_dirty_rect->bottom,
                                            current_dirty_rect->right);

                context->addClipRect(clone_dirty_rect);
            }
            context->intersectClipRect(temp_rect);

        } else {
            context->addClipRect(temp_rect);
        }

        return;
    }

    ((Region*) parent)->applyBoundClipping(1, dirty_regions);

    context->intersectClipRect(temp_rect);
    clip_windows = ((Region*) parent)->getRegionsAbove(this);

    while (clip_windows->length()) {
        clipping_window = clip_windows->getHead()->getValue();
        clip_windows->deleteHead();

        screen_x = clipping_window->screenX();
        screen_y = clipping_window->screenY();

        temp_rect = new CRect(screen_y, screen_x,
                             screen_y + clipping_window->dataRegion.h - 1,
                             screen_x + clipping_window->dataRegion.w - 1);
        context->subClipRect(temp_rect);

        delete temp_rect;
    }

    delete clip_windows;
}

List<Region*>* Region::getRegionsAbove(Region* window)
{
    int i;
    Region* desktop = this;
    Region* current_window;
    List<Region*>* return_list = new List<Region*>;
    desktop->resetNext();

    while (desktop->hasNext()) {
        if ((Region*) desktop->getNext() == window) {
            break;
        }
    }

    while (desktop->hasNext()) {
        current_window = (Region*) desktop->getNext();

        if (current_window && \
            current_window->dataRegion.x <= (window->dataRegion.x + window->dataRegion.w - 1) &&
            current_window->dataRegion.y <= (window->dataRegion.y + window->dataRegion.h - 1) &&
            (current_window->dataRegion.x + current_window->dataRegion.w - 1) >= window->dataRegion.x &&
            (current_window->dataRegion.y + current_window->dataRegion.h - 1) >= window->dataRegion.y) {

            return_list->insertAtTail(current_window);
        }
    }

    return return_list;
}