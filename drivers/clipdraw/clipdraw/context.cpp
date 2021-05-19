#include "context.hpp"

CRect::CRect()
{

}

CRect::CRect(int t, int l, int b, int r)
{
    top = t;
    left = l;
    bottom = b;
    right = r;
}

List<CRect*>* CRect::split(CRect* cutting_rect)
{
    CRect* subject_rect = this;

    List<CRect*>* output_rects = new List<CRect*>;

    CRect subject_copy;
    subject_copy.top = subject_rect->top;
    subject_copy.left = subject_rect->left;
    subject_copy.bottom = subject_rect->bottom;
    subject_copy.right = subject_rect->right;

    CRect* temp_rect;

    if (cutting_rect->left >= subject_copy.left && cutting_rect->left <= subject_copy.right) {
        temp_rect = new CRect(subject_copy.top, subject_copy.left,
                              subject_copy.bottom, cutting_rect->left - 1);

        output_rects->insertAtTail(temp_rect);
        subject_copy.left = cutting_rect->left;
    }

    if (cutting_rect->top >= subject_copy.top && cutting_rect->top <= subject_copy.bottom) {
        temp_rect = new CRect(subject_copy.top, subject_copy.left,
                              cutting_rect->top - 1, subject_copy.right);

        output_rects->insertAtTail(temp_rect);
        subject_copy.top = cutting_rect->top;
    }

    if (cutting_rect->right >= subject_copy.left && cutting_rect->right <= subject_copy.right) {
        temp_rect = new CRect(subject_copy.top, cutting_rect->right + 1,
                              subject_copy.bottom, subject_copy.right);

        output_rects->insertAtTail(temp_rect);
        subject_copy.right = cutting_rect->right;
    }

    if (cutting_rect->bottom >= subject_copy.top && cutting_rect->bottom <= subject_copy.bottom) {
        temp_rect = new CRect(cutting_rect->bottom + 1, subject_copy.left,
                              subject_copy.bottom, subject_copy.right);

        output_rects->insertAtTail(temp_rect);
        subject_copy.bottom = cutting_rect->bottom;
    }

    return output_rects;
}

void Context::subClipRect(CRect* added_rect)
{
    Context* context = this;
    int i, j;
    CRect* cur_rect;
    List<CRect*>* split_rects;

    for (i = 0; i < context->clip_rects->length(); ) {
        cur_rect = context->clip_rects->getDesiredElement(i)->getValue();

        if (!(cur_rect->left <= added_rect->right &&
            cur_rect->right >= added_rect->left &&
            cur_rect->top <= added_rect->bottom &&
            cur_rect->bottom >= added_rect->top)) {
            i++;
            continue;
        }

        context->clip_rects->deleteNode(context->clip_rects->getDesiredElement(i));
        split_rects = cur_rect->split(added_rect);
        delete cur_rect;

        while (split_rects->length()) {
            cur_rect = split_rects->getHead()->getValue();
            split_rects->deleteHead();
            context->clip_rects->insertAtTail(cur_rect);
        }

        delete split_rects;

        i = 0;
    }
}

void Context::addClipRect(CRect* added_rect)
{
    subClipRect(added_rect);
    clip_rects->insertAtTail(added_rect);
}

Context::Context(Video* scr)
{
    screen = scr;
    width = screen->getWidth();
    height = screen->getHeight();
    clip_rects = new List<CRect*>;
}

void Context::clearClipRects()
{
    kprintf("clearing clip rects.\n");
    while (clip_rects->length()) {
        delete clip_rects->getHead()->getValue();
        clip_rects->deleteHead();
    }
    kprintf("Cleared. length = %d\n", clip_rects->length());
}

void Context::drawRect(int x, int y, int width, int height, uint32_t color)
{
    drawHorizontalLine(x, y, width, color); //top
    drawVerticalLine(x, y + 1, height - 2, color); //left 
    drawHorizontalLine(x, y + height - 1, width, color); //bottom
    drawVerticalLine(x + width - 1, y + 1, height - 2, color); //right
}

void Context::drawHorizontalLine(int x, int y, int length, uint32_t colour)
{
    fillRect(x, y, length, 1, colour);
}

void Context::drawVerticalLine(int x, int y, int length, uint32_t colour)
{
    fillRect(x, y, 1, length, colour);
}

void Context::clippedRect(int x, int y, int width, int height, CRect* clip_area, Brush* brush)
{
    /*int curX;
    int maxX = x + width;
    int maxY = y + height;

    if (x < clip_area->left) x = clip_area->left;
    if (y < clip_area->top) y = clip_area->top;
    if (maxX > clip_area->right + 1) maxX = clip_area->right + 1;
    if (maxY > clip_area->bottom + 1) maxY = clip_area->bottom + 1;

    for (int yy = y; yy < y + height; ++yy) {
        uint8_t pattern = brush->pattern[(yy - y + brush->originY) % brush->height];

        for (int xx = x; xx < x + width; ++xx) {
            bool bit = pattern & (1 << ((xx - x + brush->originX) % brush->width));

            if (bit) {
                screen->putpixel(xx, yy, brush->fg);

            } else if (brush->bg != 0xFFFFFFFF) {
                screen->putpixel(xx, yy, brush->bg);
            }
        }
    }*/
}

void Context::clippedRect(int x, int y, int width, int height, CRect* clip_area, uint32_t colour)
{
    int curX;
    int maxX = x + width;
    int maxY = y + height;

    if (x < clip_area->left) x = clip_area->left;
    if (y < clip_area->top) y = clip_area->top;
    if (maxX > clip_area->right + 1) maxX = clip_area->right + 1;
    if (maxY > clip_area->bottom + 1) maxY = clip_area->bottom + 1;

    screen->putrect(x, y, maxX, maxY, colour);
}


void Context::fillRect(int x, int y, int width, int height, Brush* brush)
{
    return;

    /*int start_x, cur_x, cur_y, end_x, end_y;
    int max_x = x + width;
    int max_y = y + height;
    int i;
    CRect* clip_area;
    CRect screen_area;

    if (clip_rects->length()) {
        for (i = 0; i < clip_rects->length(); i++) {
            clip_area = clip_rects->getDesiredElement(i)->getValue();
            clippedRect(x, y, width, height, clip_area, brush);
        }

    } else {
        screen_area.top = 0;
        screen_area.left = 0;
        screen_area.bottom = height - 1;
        screen_area.right = width - 1;
        clippedRect(x, y, width, height, &screen_area, brush);
    }*/
}

void Context::fillRect(int x, int y, int w, int h, uint32_t colour)
{
    int max_x = x + w;
    int max_y = y + h;
    int i;
    CRect* clip_area;
    CRect screen_area;

    if (max_x > width) max_x = width;
    if (max_y > height) max_y = height;
    if (x < 0) x = 0;
    if (y < 0) y = 0;

    w = max_x - x;
    h = max_y - y;

    if (clip_rects->length()) {
        for (i = 0; i < clip_rects->length(); i++) {
            kprintf("fillrect found cliprect. %d\n", i);
            clip_area = clip_rects->getDesiredElement(i)->getValue();
            kprintf("--> %d, %d, %d, %d\n", clip_area->top, clip_area->bottom, clip_area->left, clip_area->right);
            clippedRect(x, y, w, h, clip_area, colour);
        }

    } else {
        screen_area.top = 0;
        screen_area.left = 0;
        screen_area.bottom = height - 1;
        screen_area.right = width - 1;
        clippedRect(x, y, w, h, &screen_area, colour);
    }

    kprintf("...\n\n");
}
