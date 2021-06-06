#include "context.hpp"

#include <core/kheap.hpp>
extern "C" {
	#include <libk/string.h>
}

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

CRect* CRect::intersect(CRect* rect_b)
{
	CRect* rect_a = this;
	CRect* result_rect;

	if (!(rect_a->left <= rect_b->right &&
		rect_a->right >= rect_b->left &&
		rect_a->top <= rect_b->bottom &&
		rect_a->bottom >= rect_b->top)) {
		return nullptr;
	}

	result_rect = new CRect(rect_a->top, rect_a->left, rect_a->bottom, rect_a->right);

	if (rect_b->left >= result_rect->left && rect_b->left <= result_rect->right) {
		result_rect->left = rect_b->left;
	}

	if (rect_b->top >= result_rect->top && rect_b->top <= result_rect->bottom) {
		result_rect->top = rect_b->top;
	}

	if (rect_b->right >= result_rect->left && rect_b->right <= result_rect->right) {
		result_rect->right = rect_b->right;
	}

	if (rect_b->bottom >= result_rect->top && rect_b->bottom <= result_rect->bottom) {
		result_rect->bottom = rect_b->bottom;
	}

	return result_rect;
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
	clippingOn = true;

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

void Context::intersectClipRect(CRect* rect)
{
	clippingOn = true;

	int i;
	List<CRect*>* output_rects = new List<CRect*>;
	CRect* current_rect;
	CRect* intersect_rect;

	for (i = 0; i < clip_rects->length(); i++) {
		current_rect = clip_rects->getDesiredElement(i)->getValue();
		intersect_rect = current_rect->intersect(rect);

		if (intersect_rect) {
			output_rects->insertAtTail(intersect_rect);
		}
	}

	while (clip_rects->length()) {
		clip_rects->deleteTail();
	}
	delete clip_rects;

	clip_rects = output_rects;
	delete rect;
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
	clippingOn = false;
}

void Context::clearClipRects()
{
	clippingOn = false;

	while (clip_rects->length()) {
		delete clip_rects->getHead()->getValue();
		clip_rects->deleteHead();
	}
}

void Context::drawRect(int x, int y, int w, int h, uint32_t color)
{
	drawHorizontalLine(x, y, w, color);                 //top
	drawVerticalLine(x, y + 1, h - 2, color);           //left 
	drawHorizontalLine(x, y + h - 1, w, color);         //bottom
	drawVerticalLine(x + w - 1, y + 1, h - 2, color);   //right
}

void Context::drawHorizontalLine(int x, int y, int length, uint32_t colour)
{
	fillRect(x, y, length, 1, colour);
}

void Context::drawVerticalLine(int x, int y, int length, uint32_t colour)
{
	fillRect(x, y, 1, length, colour);
}

void Context::clippedRect(int x, int y, int w, int h, CRect* clip_area, Brush* brush)
{
	int curX;
	int maxX = x + w;
	int maxY = y + h;

	x += transX;
	y += transY;

	int ox = x;
	int oy = y;

	maxX += transX;
	maxY += transY;

	if (x < clip_area->left) x = clip_area->left;
	if (y < clip_area->top) y = clip_area->top;
	if (maxX > clip_area->right + 1) maxX = clip_area->right + 1;
	if (maxY > clip_area->bottom + 1) maxY = clip_area->bottom + 1;

	w = maxX - x;
	h = maxY - y;

	for (int yy = y; yy < y + h; ++yy) {
		uint8_t pattern = brush->pattern[(yy - oy + brush->originY) % brush->height];

		for (int xx = x; xx < x + w; ++xx) {
			bool bit = pattern & (1 << ((xx - ox + brush->originX) % brush->width));

			if (bit) {
				screen->putpixel(xx, yy, brush->fg);

			} else if (brush->bg != 0xFFFFFFFF) {
				screen->putpixel(xx, yy, brush->bg);
			}
		}
	}
}

uint32_t palette256[256];

void Context::clippedBitmap8(uint8_t* data, int x, int y, int w, int h, CRect* bound_rect)
{
	x += transX;
	y += transY;

	int offX = 0;
	int offY = 0;
	int countX = w;
	int countY = h;

	if (x > bound_rect->right || (x + w) <= bound_rect->left ||
		y > bound_rect->bottom || (y + h) <= bound_rect->top) {
		return;
	}

	if (x < bound_rect->left) {
		offX = bound_rect->left - x;
	}

	if ((x + w) > bound_rect->right) {
		countX = bound_rect->right - x + 1;
	}

	if (y < bound_rect->top) {
		offY = bound_rect->top - y;
	}

	if ((y + h) > bound_rect->bottom) {
		countY = bound_rect->bottom - y + 1;
	}

	for (int fontY = offY; fontY < countY; fontY++) {
		for (int fontX = offX; fontX < countX; fontX++) {
			uint32_t col = palette256[data[fontY * w + fontX]];
			if (col != 0xFFFFFFFF) {
				screen->putpixel(fontX + x, fontY + y, col);
			}
		}
	}
}

void Context::clippedBitmap1(uint8_t* data, int x, int y, int w, int h, CRect* bound_rect, uint32_t colour)
{
	x += transX;
	y += transY;

	int offX = 0;
	int offY = 0;
	int countX = w;
	int countY = h;

	if (x > bound_rect->right || (x + w) <= bound_rect->left ||
		y > bound_rect->bottom || (y + h) <= bound_rect->top) {
		return;
	}

	if (x < bound_rect->left) {
		offX = bound_rect->left - x;
	}

	if ((x + w) > bound_rect->right) {
		countX = bound_rect->right - x + 1;
	}

	if (y < bound_rect->top) {
		offY = bound_rect->top - y;
	}

	if ((y + h) > bound_rect->bottom) {
		countY = bound_rect->bottom - y + 1;
	}

	uint8_t shift_line = 0;

	for (int fontY = offY; fontY < countY; fontY++) {
		shift_line = data[fontY];
		shift_line <<= offX;

		for (int fontX = offX; fontX < countX; fontX++) {
			if (shift_line & 0x80) {
				screen->putpixel(fontX + x, fontY + y, colour);
			}

			shift_line <<= 1;
		}
	}
}

void Context::drawBitmap8(uint8_t* data, int x, int y, int w, int h)
{
	int i;
	CRect* clip_area;
	CRect screen_area;

	if (clip_rects->length()) {
		for (i = 0; i < clip_rects->length(); i++) {
			clip_area = clip_rects->getDesiredElement(i)->getValue();
			clippedBitmap8(data, x, y, w, h, clip_area);
		}

	} else {
		if (!clippingOn) {
			screen_area.top = 0;
			screen_area.left = 0;
			screen_area.bottom = height - 1;
			screen_area.right = width - 1;
			clippedBitmap8(data, x, y, w, h, &screen_area);
		}
	}
}

void Context::drawBitmap1(uint8_t* data, int x, int y, int w, int h, uint32_t colour)
{
	int i;
	CRect* clip_area;
	CRect screen_area;

	if (clip_rects->length()) {
		for (i = 0; i < clip_rects->length(); i++) {
			clip_area = clip_rects->getDesiredElement(i)->getValue();
			clippedBitmap1(data, x, y, w, h, clip_area, colour);
		}

	} else {
		if (!clippingOn) {
			screen_area.top = 0;
			screen_area.left = 0;
			screen_area.bottom = height - 1;
			screen_area.right = width - 1;
			clippedBitmap1(data, x, y, w, h, &screen_area, colour);
		}
	}
}

void plot(Context* ctxt, int x, int y, CRect* clip_area)
{
	ctxt->clippedRect(x, y, 1, 1, clip_area, (uint32_t) 0x0);
}

void midptellipse(Context* ctxt, int rx, int ry,
				  int xc, int yc, CRect* clip_area)
{
	float dx, dy, d1, d2, x, y;
	x = 0;
	y = ry;

	// Initial decision parameter of region 1
	d1 = (ry * ry) - (rx * rx * ry) +
		(0.25 * rx * rx);
	dx = 2 * ry * ry * x;
	dy = 2 * rx * rx * y;

	// For region 1
	while (dx < dy) {

		// Print points based on 4-way symmetry
		plot(ctxt, x + xc, y + yc, clip_area);
		plot(ctxt, -x + xc, y + yc, clip_area);
		plot(ctxt, x + xc, -y + yc, clip_area);
		plot(ctxt, -x + xc, -y + yc, clip_area);

		// Checking and updating value of
		// decision parameter based on algorithm
		if (d1 < 0) {
			x++;
			dx = dx + (2 * ry * ry);
			d1 = d1 + dx + (ry * ry);
		} else {
			x++;
			y--;
			dx = dx + (2 * ry * ry);
			dy = dy - (2 * rx * rx);
			d1 = d1 + dx - dy + (ry * ry);
		}
	}

	// Decision parameter of region 2
	d2 = ((ry * ry) * ((x + 0.5) * (x + 0.5))) +
		((rx * rx) * ((y - 1) * (y - 1))) -
		(rx * rx * ry * ry);

	// Plotting points of region 2
	while (y >= 0) {

		// Print points based on 4-way symmetry
		plot(ctxt, x + xc, y + yc, clip_area);
		plot(ctxt, -x + xc, y + yc, clip_area);
		plot(ctxt, x + xc, -y + yc, clip_area);
		plot(ctxt, -x + xc, -y + yc, clip_area);

		// Checking and updating parameter
		// value based on algorithm
		if (d2 > 0) {
			y--;
			dy = dy - (2 * rx * rx);
			d2 = d2 + (rx * rx) - dy;
		} else {
			y--;
			x++;
			dx = dx + (2 * ry * ry);
			dy = dy - (2 * rx * rx);
			d2 = d2 + dx - dy + (rx * rx);
		}
	}
}

void Context::clippedEllipse(bool fill, int x, int y, int w, int h, CRect* clip_area, uint32_t colour)
{
	midptellipse(this, w / 2, y / 2, x + w / 2, y + h / 2, clip_area);
}

void Context::clippedEllipse(bool fill, int x, int y, int w, int h, CRect* clip_area, Brush* brush)
{
	clippedEllipse(fill, x, y, w, h, clip_area, 0xFF0000);
}

void Context::clippedRect(int x, int y, int w, int h, CRect* clip_area, uint32_t colour)
{
	int curX;
	int maxX = x + w;
	int maxY = y + h;

	x += transX;
	y += transY;
	maxX += transX;
	maxY += transY;

	if (x < clip_area->left) x = clip_area->left;
	if (y < clip_area->top) y = clip_area->top;
	if (maxX > clip_area->right + 1) maxX = clip_area->right + 1;
	if (maxY > clip_area->bottom + 1) maxY = clip_area->bottom + 1;

	w = maxX - x;
	h = maxY - y;

	screen->putrect(x, y, w, h, colour);
}

void Context::fillRect(int x, int y, int w, int h, Brush* brush)
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
			clip_area = clip_rects->getDesiredElement(i)->getValue();
			clippedRect(x, y, w, h, clip_area, brush);
		}

	} else {
		if (!clippingOn) {
			screen_area.top = 0;
			screen_area.left = 0;
			screen_area.bottom = height - 1;
			screen_area.right = width - 1;
			clippedRect(x, y, w, h, &screen_area, brush);
		}
	}
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
			clip_area = clip_rects->getDesiredElement(i)->getValue();
			clippedRect(x, y, w, h, clip_area, colour);
		}

	} else {
		if (!clippingOn) {
			screen_area.top = 0;
			screen_area.left = 0;
			screen_area.bottom = height - 1;
			screen_area.right = width - 1;
			clippedRect(x, y, w, h, &screen_area, colour);
		}
	}
}

void Context::ellipse(bool fill, int x, int y, int w, int h, uint32_t colour)
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
			clip_area = clip_rects->getDesiredElement(i)->getValue();
			clippedEllipse(fill, x, y, w, h, clip_area, colour);
		}

	} else {
		if (!clippingOn) {
			screen_area.top = 0;
			screen_area.left = 0;
			screen_area.bottom = height - 1;
			screen_area.right = width - 1;
			clippedEllipse(fill, x, y, w, h, clip_area, colour);
		}
	}
}

void Context::ellipse(bool fill, int x, int y, int w, int h, Brush* brush)
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
			clip_area = clip_rects->getDesiredElement(i)->getValue();
			clippedEllipse(fill, x, y, w, h, clip_area, brush);
		}

	} else {
		if (!clippingOn) {
			screen_area.top = 0;
			screen_area.left = 0;
			screen_area.bottom = height - 1;
			screen_area.right = width - 1;
			clippedEllipse(fill, x, y, w, h, clip_area, brush);
		}
	}
}