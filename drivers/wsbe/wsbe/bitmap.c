#include "bitmap.h"

Bitmap* Bitmap_new(int x, int y, int w, int h, uint32_t* data)
{
	Bitmap* bitmap;
	if (!(bitmap = (Bitmap*) malloc(sizeof(Bitmap))))
		return bitmap;

	if (!Window_init((Window*) bitmap, x, y, w, h, WIN_NODECORATION, (Context*) 0)) {

		free(bitmap);
		return (Bitmap*) 0;
	}

	bitmap->window.paint_function = Bitmap_paint;
	bitmap->data = data;

	return bitmap;
}

void Bitmap_paint(Window* bitmap_window)
{
	//TODO: a 'Context_fill_bitmap' function which calls the graphics griver

	int i = 0;
	for (int y = 0; y < bitmap_window->height; ++y) {
		for (int x = 0; x < bitmap_window->width; ++x) {
			Context_fill_rect(bitmap_window->context, x, y, 1, 1, ((Bitmap*) bitmap_window)->data[i++]);
		}
	}
}