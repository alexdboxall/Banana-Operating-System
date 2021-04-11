#include <inttypes.h>
#include <stdlib.h>
#include "window.h"
#include "desktop.h"

Window* active_window;

//Window constructor
Window* Window_new(int16_t x, int16_t y, uint16_t width,
				   uint16_t height, uint16_t flags, Context* context)
{

	//Try to allocate space for a new WindowObj and fail through if malloc fails
	Window* window;
	if (!(window = (Window*) malloc(sizeof(Window))))
		return window;

	//Attempt to initialize the new window
	if (!Window_init(window, x, y, width, height, flags, context)) {

		free(window);
		return (Window*) 0;
	}

	return window;
}

const uint8_t defaultRepaintScript[] = { 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x01, 0xFF, (WIN_BGCOLOR >> 0) & 0xFF, (WIN_BGCOLOR >> 8) & 0xFF, (WIN_BGCOLOR >> 16) & 0xFF, 0x00, 0x08 };

//Seperate object allocation from initialization so we can implement
//our inheritance scheme
int Window_init(Window* window, int16_t x, int16_t y, uint16_t width,
				uint16_t height, uint16_t flags, Context* context)
{

	//Moved over here from the desktop 
	//Create child list or clean up and fail
	if (!(window->children = List_new()))
		return 0;

	//Assign the property values
	window->x = x;
	window->y = y;
	window->width = width;
	window->height = height;
	window->context = context;
	window->flags = flags;
	window->parent = (Window*) 0;
	window->drag_child = (Window*) 0;
	window->drag_off_x = 0;
	window->drag_off_y = 0;
	window->last_button_state = 0;
	window->paint_function = Window_paint_handler;
	window->mousemove_function = Window_mousedown_handler;
	window->mousedrag_function = Window_mousedown_handler;
	window->mousedown_function = Window_mousedown_handler;
	window->mouseup_function = Window_mousedown_handler;
	window->doubleclick_function = Window_mousedown_handler;
	window->resize_function = Window_resize_handler;
	window->move_function = Window_move_handler;
	window->nanoLastClicked = 0;
	window->fullscreen = 0;
	window->previousMouseOverride = -1;
	window->currentMouse = MOUSE_OFFSET_NORMAL;
	window->active_child = (Window*) 0;
	window->title = (char*) 0;
	window->dragType = DRAG_TYPE_NONE;
	window->messageCount = 0;
	window->hasProc = false;
	window->repaintScript = defaultRepaintScript;

	if (flags & WIN_TOPLEVELWIN) {
		active_window = window;
	}

	return 1;
}

//Recursively get the absolute on-screen x-coordinate of this window
int Window_screen_x(Window* window)
{
	if (window->parent) {
		return window->x + Window_screen_x(window->parent);
	}

	return window->x;
}

//Recursively get the absolute on-screen y-coordinate of this window
int Window_screen_y(Window* window)
{
	if (window->parent) {
		return window->y + Window_screen_y(window->parent);
	}

	return window->y;
}

void Window_draw_border(Window* window)
{

	int screen_x = Window_screen_x(window);
	int screen_y = Window_screen_y(window);

	//draw line under titlebar
	Context_horizontal_line(window->context, screen_x, screen_y + WIN_TITLEHEIGHT - 3, window->width, WIN_BGCOLOR);
	Context_horizontal_line(window->context, screen_x, screen_y + WIN_TITLEHEIGHT - 2, window->width, WIN_BGCOLOR);
	Context_horizontal_line(window->context, screen_x, screen_y + WIN_TITLEHEIGHT - 1, window->width, WIN_BGCOLOR);

	//draw top
	Context_horizontal_line(window->context, screen_x, screen_y, window->width, WIN_BGCOLOR);
	Context_horizontal_line(window->context, screen_x + 1, screen_y + 1, window->width - 2, 0xFFFFFF);
	Context_horizontal_line(window->context, screen_x + 2, screen_y + 2, window->width - 4, WIN_BGCOLOR);

	//draw bottom
	Context_horizontal_line(window->context, screen_x + 2, screen_y + window->height - 3, window->width - 4, WIN_BGCOLOR);
	Context_horizontal_line(window->context, screen_x + 1, screen_y + window->height - 2, window->width - 2, 0x555555);
	Context_horizontal_line(window->context, screen_x, screen_y + window->height - 1, window->width, 0x000000);

	//draw left side
	Context_vertical_line(window->context, screen_x, screen_y, window->height - 1, WIN_BGCOLOR);
	Context_vertical_line(window->context, screen_x + 1, screen_y + 1, window->height - 3, 0xFFFFFF);
	Context_vertical_line(window->context, screen_x + 2, screen_y + 2, window->height - 5, WIN_BGCOLOR);

	//draw right side
	Context_vertical_line(window->context, screen_x + window->width - 1, screen_y, window->height, 0);
	Context_vertical_line(window->context, screen_x + window->width - 2, screen_y + 1, window->height - 2, 0x555555);
	Context_vertical_line(window->context, screen_x + window->width - 3, screen_y + 2, window->height - 4, WIN_BGCOLOR);


	//Fill in the titlebar background
	Context_fill_rect(window->context, screen_x + WIN_BORDERWIDTH, screen_y + WIN_BORDERWIDTH,
					  window->width - 2 * WIN_BORDERWIDTH, WIN_TITLEHEIGHT - 2 * WIN_BORDERWIDTH,
					  (active_window == window && window->parent->active_child == window) ? WIN_TITLECOLOR : WIN_TITLECOLOR_INACTIVE);

	//Draw the window title
	Context_draw_text(window->context, window->title, screen_x + 10, screen_y + 6,
					  (active_window == window && window->parent->active_child == window) ?
					  WIN_TEXTCOLOR : WIN_TEXTCOLOR_INACTIVE, TEXT_FLAG_BOLD);

	Context_fill_rect(window->context, screen_x + window->width - 21, screen_y + 5, 16, 16, WIN_BGCOLOR);
	Context_draw_rect(window->context, screen_x + window->width - 21, screen_y + 5, 16, 16, 0);

	Context_horizontal_line(window->context, screen_x + window->width - 21, screen_y + 5, 15, 0xFFFFFF);
	Context_vertical_line(window->context, screen_x + window->width - 21, screen_y + 5, 15, 0xFFFFFF);

	Context_horizontal_line(window->context, screen_x + window->width - 20, screen_y + 19, 14, 0x555555);
	Context_vertical_line(window->context, screen_x + window->width - 7, screen_y + 6, 14, 0x555555);

}

//Apply clipping for window bounds without subtracting child window rects
void Window_apply_bound_clipping(Window* window, int in_recursion, List* dirty_regions)
{

	Rect* temp_rect, * current_dirty_rect, * clone_dirty_rect;
	int screen_x, screen_y, i;
	List* clip_windows;
	Window* clipping_window;

	//Can't do this without a context
	if (!window->context)
		return;

	//Build the visibility rectangle for this window
	//If the window is decorated and we're recursing, we want to limit
	//the window's drawable area to the area inside the window decoration.
	//If we're not recursing, however, it means we're about to paint 
	//ourself and therefore we want to wait until we've finished painting
	//the window border to shrink the clipping area 
	screen_x = Window_screen_x(window);
	screen_y = Window_screen_y(window);

	if ((!(window->flags & WIN_NODECORATION)) && in_recursion) {

		//Limit client drawable area 
		screen_x += WIN_BORDERWIDTH;
		screen_y += WIN_TITLEHEIGHT;
		temp_rect = Rect_new(screen_y, screen_x,
							 screen_y + window->height - WIN_TITLEHEIGHT - WIN_BORDERWIDTH - 1,
							 screen_x + window->width - (2 * WIN_BORDERWIDTH) - 1);
	} else {

		temp_rect = Rect_new(screen_y, screen_x, screen_y + window->height - 1,
							 screen_x + window->width - 1);
	}

	//If there's no parent (meaning we're at the top of the window tree)
	//then we just add our rectangle and exit
	//Here's our change: If we were passed a dirty region list, we first
	//clone those dirty rects into the clipping region and then intersect
	//the top-level window bounds against it so that we're limited to the
	//dirty region from the outset
	if (!window->parent) {

		if (dirty_regions) {

			//Clone the dirty regions and put them into the clipping list
			for (i = 0; i < dirty_regions->count; i++) {

				//Clone
				current_dirty_rect = (Rect*) List_get_at(dirty_regions, i);
				clone_dirty_rect = Rect_new(current_dirty_rect->top,
											current_dirty_rect->left,
											current_dirty_rect->bottom,
											current_dirty_rect->right);

				//Add
				Context_add_clip_rect(window->context, clone_dirty_rect);
			}

			//Finally, intersect this top level window against them
			Context_intersect_clip_rect(window->context, temp_rect);

		} else {

			Context_add_clip_rect(window->context, temp_rect);
		}

		return;
	}

	//Otherwise, we first reduce our clipping area to the visibility area of our parent
	Window_apply_bound_clipping(window->parent, 1, dirty_regions);

	//Now that we've reduced our clipping area to our parent's clipping area, we can
	//intersect our own bounds rectangle to get our main visible area  
	Context_intersect_clip_rect(window->context, temp_rect);

	//And finally, we subtract the rectangles of any siblings that are occluding us 
	clip_windows = Window_get_windows_above(window->parent, window);

	while (clip_windows->count) {

		clipping_window = (Window*) List_remove_at(clip_windows, 0);

		//Get a rectangle from the window, subtract it from the clipping 
		//region, and dispose of it
		screen_x = Window_screen_x(clipping_window);
		screen_y = Window_screen_y(clipping_window);

		temp_rect = Rect_new(screen_y, screen_x,
							 screen_y + clipping_window->height - 1,
							 screen_x + clipping_window->width - 1);
		Context_subtract_clip_rect(window->context, temp_rect);
		free(temp_rect);
	}

	//Dispose of the used-up list 
	free(clip_windows);
}

void Window_update_title(Window* window)
{

	if (!window->context) {
		return;
	}

	if (window->flags & WIN_NODECORATION) {
		return;
	}

	Window_apply_bound_clipping(window, 0, (List*) 0);
	Window_draw_border(window);
	Context_clear_clip_rects(window->context);
}

//Request a repaint of a certain region of a window
void Window_invalidate(Window* window, int top, int left, int bottom, int right)
{

	List* dirty_regions;
	Rect* dirty_rect;

	//This function takes coordinates in terms of window coordinates
	//So we need to convert them to screen space 
	int origin_x = Window_screen_x(window);
	int origin_y = Window_screen_y(window);
	top += origin_y;
	bottom += origin_y;
	left += origin_x;
	right += origin_x;

	//Attempt to create a new dirty rect list 
	if (!(dirty_regions = List_new()))
		return;

	if (!(dirty_rect = Rect_new(top, left, bottom, right))) {

		free(dirty_regions);
		return;
	}

	if (!List_add(dirty_regions, dirty_rect)) {

		free(dirty_regions);
		free(dirty_rect);
		return;
	}

	Window_paint(window, dirty_regions, 0);

	//Clean up the dirty rect list
	List_remove_at(dirty_regions, 0);
	free(dirty_regions);
	free(dirty_rect);
}

//Another override-redirect function
void Window_paint(Window* window, List* dirty_regions, uint8_t paint_children)
{
	int i, j, screen_x, screen_y, child_screen_x, child_screen_y;
	Window* current_child;
	Rect* temp_rect;

	//Can't paint without a context
	if (!window->context)
		return;

	//Start by limiting painting to the window's visible area
	Window_apply_bound_clipping(window, 0, dirty_regions);

	//Set the context translation
	screen_x = Window_screen_x(window);
	screen_y = Window_screen_y(window);

	//If we have window decorations turned on, draw them and then further
	//limit the clipping area to the inner drawable area of the window 
	if (!(window->flags & WIN_NODECORATION)) {

		//Draw border
		Window_draw_border(window);

		//Limit client drawable area 
		screen_x += WIN_BORDERWIDTH;
		screen_y += WIN_TITLEHEIGHT;
		temp_rect = Rect_new(screen_y, screen_x,
							 screen_y + window->height - WIN_TITLEHEIGHT - WIN_BORDERWIDTH - 1,
							 screen_x + window->width - (2 * WIN_BORDERWIDTH) - 1);
		Context_intersect_clip_rect(window->context, temp_rect);
	}

	//Then subtract the screen rectangles of any children 
	//NOTE: We don't do this in Window_apply_bound_clipping because, due to 
	//its recursive nature, it would cause the screen rectangles of all of 
	//our parent's children to be subtracted from the clipping area -- which
	//would eliminate this window. 
	for (i = 0; i < window->children->count; i++) {

		current_child = (Window*) List_get_at(window->children, i);

		child_screen_x = Window_screen_x(current_child);
		child_screen_y = Window_screen_y(current_child);

		temp_rect = Rect_new(child_screen_y, child_screen_x,
							 child_screen_y + current_child->height - 1,
							 child_screen_x + current_child->width - 1);
		Context_subtract_clip_rect(window->context, temp_rect);
		free(temp_rect);
	}

	//Finally, with all the clipping set up, we can set the context's 0,0 to the top-left corner
	//of the window's drawable area, and call the window's final paint function 
	window->context->translate_x = screen_x;
	window->context->translate_y = screen_y;

	extern void scriptParse(uint8_t * code, Window * win);
	if (window->hasProc) {
		scriptParse(window->repaintScript, window);
	} else {
		window->paint_function(window, 0, 0, 0, 0);
	}

	Context_clear_clip_rects(window->context);
	window->context->translate_x = 0;
	window->context->translate_y = 0;

	//Even though we're no longer having all mouse events cause a redraw from the desktop
	//down, we still need to call paint on our children in the case that we were called with
	//a dirty region list since each window needs to be responsible for recursively checking
	//if its children were dirtied 

	for (i = 0; i < window->children->count; i++) {

		current_child = (Window*) List_get_at(window->children, i);

		if (dirty_regions) {

			//Check to see if the child is affected by any of the
			//dirty region rectangles
			for (j = 0; j < dirty_regions->count; j++) {

				temp_rect = (Rect*) List_get_at(dirty_regions, j);

				screen_x = Window_screen_x(current_child);
				screen_y = Window_screen_y(current_child);

				if (temp_rect->left <= (screen_x + current_child->width - 1) &&
					temp_rect->right >= screen_x &&
					temp_rect->top <= (screen_y + current_child->height - 1) &&
					temp_rect->bottom >= screen_y)
					break;
			}

			//Skip drawing this child if no intersection was found
			if (j == dirty_regions->count)
				continue;
		}

		//Otherwise, recursively request the child to redraw its dirty areas
		Window_paint(current_child, dirty_regions, 1);
	}
}

//This is the default paint method for a new window
void Window_paint_handler(Window* window, int sx, int sy, List* dr, int pc)
{

	//Fill in the window background
	Context_fill_rect(window->context, 0, 0,
					  window->width, window->height, WIN_BGCOLOR);

}

//Used to get a list of windows overlapping the passed window
List* Window_get_windows_above(Window* parent, Window* child)
{

	int i;
	Window* current_window;
	List* return_list;

	//Attempt to allocate the output list
	if (!(return_list = List_new()))
		return return_list;

	//We just need to get a list of all items in the
	//child list at higher indexes than the passed window
	//We start by finding the passed child in the list
	for (i = 0; i < parent->children->count; i++)
		if (child == (Window*) List_get_at(parent->children, i))
			break;

	//Now we just need to add the remaining items in the list
	//to the output (IF they overlap, of course)
	//NOTE: As a bonus, this will also automatically fall through
	//if the window wasn't found
	for (i++; i < parent->children->count; i++) {

		current_window = List_get_at(parent->children, i);

		//Our good old rectangle intersection logic
		if (current_window->x <= (child->x + child->width - 1) &&
			(current_window->x + current_window->width - 1) >= child->x &&
			current_window->y <= (child->y + child->height - 1) &&
			(current_window->y + current_window->height - 1) >= child->y)
			List_add(return_list, current_window); //Insert the overlapping window
	}

	return return_list;
}

//Used to get a list of windows which the passed window overlaps
//Same exact thing as get_windows_above, but goes backwards through
//the list. Could probably be made a little less redundant if you really wanted
List* Window_get_windows_below(Window* parent, Window* child)
{

	int i;
	Window* current_window;
	List* return_list;

	//Attempt to allocate the output list
	if (!(return_list = List_new()))
		return return_list;

	//We just need to get a list of all items in the
	//child list at higher indexes than the passed window
	//We start by finding the passed child in the list
	for (i = parent->children->count - 1; i > -1; i--)
		if (child == (Window*) List_get_at(parent->children, i))
			break;

	//Now we just need to add the remaining items in the list
	//to the output (IF they overlap, of course)
	//NOTE: As a bonus, this will also automatically fall through
	//if the window wasn't found
	for (i--; i > -1; i--) {

		current_window = List_get_at(parent->children, i);

		//Our good old rectangle intersection logic
		if (current_window->x <= (child->x + child->width - 1) &&
			(current_window->x + current_window->width - 1) >= child->x &&
			current_window->y <= (child->y + child->height - 1) &&
			(current_window->y + current_window->height - 1) >= child->y)
			List_add(return_list, current_window); //Insert the overlapping window
	}

	return return_list;
}


//Breaking 
void Window_raise(Window* window, uint8_t do_draw)
{
	if (window->flags & WIN_TOPLEVELWIN) {
		active_window = window;
	}

	int i;
	Window* parent, * last_active;

	if (!window->parent)
		return;

	parent = window->parent;

	if (parent->active_child == window)
		return;

	last_active = parent->active_child;

	//Find the child in the list
	for (i = 0; i < parent->children->count; i++)
		if ((Window*) List_get_at(parent->children, i) == window)
			break;

	List_remove_at(parent->children, i); //Pull window out of list
	List_add(parent->children, (void*) window); //Insert at the top

	//Make it active 
	parent->active_child = window;

	//Do a redraw if it was requested
	if (!do_draw)
		return;

	Window_paint(window, (List*) 0, 1);

	//Make sure the old active window gets an updated title color 
	Window_update_title(last_active);
}


//We're wrapping this guy so that we can handle any needed redraw
void Window_resize(Window* window, int new_w, int new_h)
{
	if (new_w < 2) new_w = 2;
	if (new_h < 2) new_h = 2;
	if (window->flags & WIN_TOPLEVELWIN) {
		if (new_w < 32) new_w = 32;
		if (new_h < WIN_TITLEHEIGHT + 16) new_h = WIN_TITLEHEIGHT + 16;
	}
	int old_w = window->width;
	int old_h = window->height;
	Rect new_window_rect;
	List* replacement_list, * dirty_list, * dirty_windows;

	//To make life a little bit easier, we'll make the not-unreasonable
	//rule that if a window is moved, it must become the top-most window
	Window_raise(window, 0); //Raise it, but don't repaint it yet

	//We'll hijack our dirty rect collection from our existing clipping operations
	//So, first we'll get the visible regions of the original window position
	Window_apply_bound_clipping(window, 0, (List*) 0);

	//Temporarily update the window position
	window->width = new_w;
	window->height = new_h;

	//Calculate the new bounds
	new_window_rect.top = Window_screen_y(window);
	new_window_rect.left = Window_screen_x(window);
	new_window_rect.bottom = new_window_rect.top + window->height - 1;
	new_window_rect.right = new_window_rect.left + window->width - 1;

	//Reset the window position
	window->width = old_w;
	window->height = old_h;

	//Now, we'll get the *actual* dirty area by subtracting the new location of
	//the window
	Context_subtract_clip_rect(window->context, &new_window_rect);

	//Now that the context clipping tools made the list of dirty rects for us,
	//we can go ahead and steal the list it made for our own purposes
	//(yes, it would be cleaner to spin off our boolean rect functions so that
	//they can be used both here and by the clipping region tools, but I ain't
	//got time for that junk)
	if (!(replacement_list = List_new())) {

		Context_clear_clip_rects(window->context);
		return;
	}

	dirty_list = window->context->clip_rects;
	window->context->clip_rects = replacement_list;

	//Now, let's get all of the siblings that we overlap before the move
	dirty_windows = Window_get_windows_below(window->parent, window);

	window->width = new_w;
	window->height = new_h;

	window->resize_function(window, new_w, new_h);

	//And we'll repaint all of them using the dirty rects
	//(removing them from the list as we go for convenience)
	while (dirty_windows->count)
		Window_paint((Window*) List_remove_at(dirty_windows, 0), dirty_list, 1);

	//The one thing that might still be dirty is the parent we're inside of
	Window_paint(window->parent, dirty_list, 0);

	//We're done with the lists, so we can dump them
	while (dirty_list->count)
		free(List_remove_at(dirty_list, 0));

	free(dirty_list);
	free(dirty_windows);


	//With the dirtied siblings redrawn, we can do the final update of
	//the window location and paint it at that new position
	Window_paint(window, (List*) 0, 1);
}

//We're wrapping this guy so that we can handle any needed redraw
void Window_move(Window* window, int new_x, int new_y)
{

	int old_x = window->x;
	int old_y = window->y;
	Rect new_window_rect;
	List* replacement_list, * dirty_list, * dirty_windows;

	//To make life a little bit easier, we'll make the not-unreasonable 
	//rule that if a window is moved, it must become the top-most window
	Window_raise(window, 0); //Raise it, but don't repaint it yet

	//We'll hijack our dirty rect collection from our existing clipping operations
	//So, first we'll get the visible regions of the original window position
	Window_apply_bound_clipping(window, 0, (List*) 0);

	//Temporarily update the window position
	window->x = new_x;
	window->y = new_y;

	//Calculate the new bounds
	new_window_rect.top = Window_screen_y(window);
	new_window_rect.left = Window_screen_x(window);
	new_window_rect.bottom = new_window_rect.top + window->height - 1;
	new_window_rect.right = new_window_rect.left + window->width - 1;

	window->move_function(window, new_x, new_y);

	//Reset the window position
	window->x = old_x;
	window->y = old_y;

	//Now, we'll get the *actual* dirty area by subtracting the new location of
	//the window 
	Context_subtract_clip_rect(window->context, &new_window_rect);

	//Now that the context clipping tools made the list of dirty rects for us,
	//we can go ahead and steal the list it made for our own purposes
	//(yes, it would be cleaner to spin off our boolean rect functions so that
	//they can be used both here and by the clipping region tools, but I ain't 
	//got time for that junk)
	if (!(replacement_list = List_new())) {

		Context_clear_clip_rects(window->context);
		return;
	}

	dirty_list = window->context->clip_rects;
	window->context->clip_rects = replacement_list;

	//Now, let's get all of the siblings that we overlap before the move
	dirty_windows = Window_get_windows_below(window->parent, window);

	window->x = new_x;
	window->y = new_y;

	//And we'll repaint all of them using the dirty rects
	//(removing them from the list as we go for convenience)
	while (dirty_windows->count) {
		Window_paint((Window*) List_remove_at(dirty_windows, 0), dirty_list, 1);
	}

	//The one thing that might still be dirty is the parent we're inside of
	Window_paint(window->parent, dirty_list, 0);

	//We're done with the lists, so we can dump them
	while (dirty_list->count)
		free(List_remove_at(dirty_list, 0));

	free(dirty_list);
	free(dirty_windows);

	//With the dirtied siblings redrawn, we can do the final update of 
	//the window location and paint it at that new position
	Window_paint(window, (List*) 0, 1);
}

//Interface between windowing system and mouse device
void Window_process_mouse(Window* window, uint16_t mouse_x,
						  uint16_t mouse_y, uint8_t mouse_buttons)
{

	int i;
	Window* child;

	int overridenMouse = -1;

	//If we had a button depressed, then we need to see if the mouse was
	//over any of the child windows
	//We go front-to-back in terms of the window stack for free occlusion
	for (i = window->children->count - 1; i >= 0; i--) {

		child = (Window*) List_get_at(window->children, i);

		//If mouse isn't window bounds, we can't possibly be interacting with it 
		if (!(mouse_x >= child->x - 12 && mouse_x < (child->x + child->width) &&
			mouse_y >= child->y - 12 && mouse_y < (child->y + child->height))) {
			continue;
		}

		bool onBottomCorner = !(child->flags & WIN_NODECORATION) && !child->fullscreen &&
			mouse_x >= child->x + child->width - 18 && mouse_x < child->x + child->width &&
			mouse_y >= child->y + child->height - 18 && mouse_y < child->y + child->height;

		bool onRightEdge = !(child->flags & WIN_NODECORATION) && !child->fullscreen &&
			mouse_x >= child->x + child->width - 12 && mouse_x < child->x + child->width &&
			mouse_y >= child->y && mouse_y < child->y + child->height;

		bool onLeftEdge = !(child->flags & WIN_NODECORATION) && !child->fullscreen &&
			mouse_x >= child->x - 12 && mouse_x < child->x + 1 &&
			mouse_y >= child->y && mouse_y < child->y + child->height;

		bool onTopEdge = !(child->flags & WIN_NODECORATION) && !child->fullscreen &&
			mouse_x >= child->x && mouse_x < child->x + child->width &&
			mouse_y >= child->y - 12 && mouse_y < child->y;

		bool onBottomEdge = !(child->flags & WIN_NODECORATION) && !child->fullscreen &&
			mouse_x >= child->x && mouse_x < child->x + child->width &&
			mouse_y >= child->y + child->height - 12 && mouse_y < child->y + child->height;

		bool onTitleBar = !(child->flags & WIN_NODECORATION) &&
			mouse_y >= child->y && mouse_y < (child->y + 28) && !child->fullscreen;

		bool onBottomLeft = !(child->flags & WIN_NODECORATION) && !child->fullscreen &&
			mouse_x >= child->x - 12 && mouse_x < child->x + 3 &&
			mouse_y >= child->y + child->height - 18 && mouse_y < child->y + child->height;

		if (child->flags & WIN_NORESIZING) {
			extern void debugwrite(char* t);

			onBottomCorner = false;
			onBottomLeft = false;

			onBottomEdge = false;
			onLeftEdge = false;
			onRightEdge = false;
			onTopEdge = false;
		}

		if (onBottomCorner) {
			overridenMouse = MOUSE_OFFSET_TLDR;
		} else if (onBottomLeft) {
			overridenMouse = MOUSE_OFFSET_TLDR;
		} else if (onRightEdge) {
			overridenMouse = MOUSE_OFFSET_HORZ;
		} else if (onBottomEdge) {
			overridenMouse = MOUSE_OFFSET_VERT;
		} else if (onLeftEdge) {
			overridenMouse = MOUSE_OFFSET_HORZ;
		} else if (onTopEdge) {
			overridenMouse = MOUSE_OFFSET_VERT;
		}

		window->previousMouseOverride = overridenMouse;

		if ((mouse_x < child->x || mouse_y < child->y) && overridenMouse == -1) {
			continue;
		}

		//Now we'll check to see if we're dragging a titlebar
		if (mouse_buttons && !window->last_button_state) {
			//Let's adjust things so that a raise happens whenever we click inside a 
			//child, to be more consistent with most other GUIs
			Window_raise(child, 1);

			if (!(child->flags & WIN_NODECORATION) &&
				mouse_y >= child->y && mouse_y < (child->y + 28)) {
				if (getNanoSinceBoot() < child->nanoLastClicked + 1000 * 1000 * 300 && !(child->flags & WIN_NORESIZING)) {
					child->nanoLastClicked = 0;

					if (child->fullscreen) {
						Window_resize(child, child->restoreWidth, child->restoreHeight);
						Window_move(child, child->restoreX, child->restoreY);

					} else {
						child->restoreWidth = child->width;
						child->restoreHeight = child->height;
						child->restoreX = child->x;
						child->restoreY = child->y;
						Window_move(child, -3, -3);
						Window_resize(child, desktop->window.width + 6, desktop->window.height + 6);
					}
					child->fullscreen ^= 1;
					break;

				} else {
					child->nanoLastClicked = getNanoSinceBoot();

				}
			}

			if (onBottomCorner) {
				window->drag_off_x = mouse_x - child->width;
				window->drag_off_y = mouse_y - child->height;
				window->drag_child = child;
				window->dragType = DRAG_TYPE_RESIZE_ALL;
				break;
			}

			if (onBottomLeft) {
				window->drag_off_x = mouse_x - child->width;
				window->drag_off_y = mouse_y - child->height;
				window->drag_child = child;
				window->dragType = DRAG_TYPE_RESIZE_ALL_BOTTOM_LEFT;
				break;
			}

			if (onRightEdge) {
				window->drag_off_x = mouse_x - child->width;
				window->drag_off_y = mouse_y - child->height;
				window->drag_child = child;
				window->dragType = DRAG_TYPE_RESIZE_HZ;
				break;
			}

			if (onLeftEdge) {
				window->drag_off_x = mouse_x - child->width;
				window->drag_off_y = mouse_y - child->height;
				window->drag_child = child;
				window->dragType = DRAG_TYPE_RESIZE_HZ_LEFT;
				break;
			}

			if (onBottomEdge) {
				window->drag_off_x = mouse_x - child->width;
				window->drag_off_y = mouse_y - child->height;
				window->drag_child = child;
				window->dragType = DRAG_TYPE_RESIZE_VT;
				break;
			}

			if (onTopEdge) {
				window->drag_off_x = mouse_x - child->width;
				window->drag_off_y = mouse_y - child->height;
				window->drag_child = child;
				window->dragType = DRAG_TYPE_RESIZE_VT_TOP;
				break;
			}

			if (onTitleBar) {
				window->drag_off_x = mouse_x - child->x;
				window->drag_off_y = mouse_y - child->y;
				window->drag_child = child;
				window->dragType = DRAG_TYPE_MOVE;
				break;
			}
		}

		//Found a target, so forward the mouse event to that window and quit looking
		Window_process_mouse(child, mouse_x - child->x, mouse_y - child->y, mouse_buttons);
		break;
	}

	if (overridenMouse == -1) {
		Desktop_set_mouse(desktop, window->currentMouse);
	} else {
		Desktop_set_mouse(desktop, overridenMouse);
	}

	//Moving this outside of the mouse-in-child detection since it doesn't really
	//have anything to do with it
	if (!mouse_buttons) {
		window->drag_child = (Window*) 0;
	}


	//Update drag window to match the mouse if we have an active drag window
	if (window->drag_child) {
		if (window->dragType == DRAG_TYPE_MOVE) {
			Window_move(window->drag_child, mouse_x - window->drag_off_x, mouse_y - window->drag_off_y);
		} else if (window->dragType == DRAG_TYPE_RESIZE_ALL) {
			Window_resize(window->drag_child, mouse_x - window->drag_off_x, mouse_y - window->drag_off_y);
		} else if (window->dragType == DRAG_TYPE_RESIZE_HZ) {
			Window_resize(window->drag_child, mouse_x - window->drag_off_x, window->drag_child->height);
		} else if (window->dragType == DRAG_TYPE_RESIZE_VT) {
			Window_resize(window->drag_child, window->drag_child->width, mouse_y - window->drag_off_y);

		} else if (window->dragType == DRAG_TYPE_RESIZE_ALL_BOTTOM_LEFT) {
			int xmove = window->drag_child->x - mouse_x;
			int oldwidth = window->drag_child->width;

			Window_resize(window->drag_child, window->drag_child->width + xmove, mouse_y - window->drag_off_y);

			//only move if the window could actually be resized (e.g. might become too small)
			if (window->drag_child->width != oldwidth) {
				Window_move(window->drag_child, mouse_x, window->drag_child->y);
			}

		} else if (window->dragType == DRAG_TYPE_RESIZE_HZ_LEFT) {
			int xmove = window->drag_child->x - mouse_x;
			int oldwidth = window->drag_child->width;

			Window_resize(window->drag_child, window->drag_child->width + xmove, window->drag_child->height);

			//only move if the window could actually be resized (e.g. might become too small)
			if (window->drag_child->width != oldwidth) {
				Window_move(window->drag_child, mouse_x, window->drag_child->y);
			}

		} else if (window->dragType == DRAG_TYPE_RESIZE_VT_TOP) {
			int xmove = window->drag_child->y - mouse_y;
			int oldwidth = window->drag_child->height;

			Window_resize(window->drag_child, window->drag_child->width, window->drag_child->height + xmove);

			//only move if the window could actually be resized (e.g. might become too small)
			if (window->drag_child->height != oldwidth) {
				Window_move(window->drag_child, window->drag_child->x, mouse_y);
			}
		}
	}

	//If we didn't find a target in the search, then we ourselves are the target of any clicks
	if (window->mousedown_function && mouse_buttons && !window->last_button_state) {
		window->mousedown_function(window, mouse_x, mouse_y);

	} else if (window->mouseup_function && !mouse_buttons && window->last_button_state) {
		window->mouseup_function(window, mouse_x, mouse_y);

	} else if (window->mousedrag_function && mouse_buttons) {
		window->mousedrag_function(window, mouse_x, mouse_y);

	} else if (window->mousemove_function && !mouse_buttons) {
		window->mousemove_function(window, mouse_x, mouse_y);

	}

	//Update the stored mouse button state to match the current state 
	window->last_button_state = mouse_buttons;
}

//The default handler for window mouse events doesn't do anything
void Window_mousedown_handler(Window* window, int x, int y)
{
	return;
}

void Window_resize_handler(Window* window, int x, int y)
{
	return;
}

void Window_move_handler(Window* window, int x, int y)
{
	return;
}

void Window_update_context(Window* window, Context* context)
{

	int i;

	window->context = context;

	for (i = 0; i < window->children->count; i++)
		Window_update_context((Window*) List_get_at(window->children, i), context);
}

//Quick wrapper for shoving a new entry into the child list
void Window_insert_child(Window* window, Window* child)
{

	child->parent = window;
	List_add(window->children, child);
	child->parent->active_child = child;

	Window_update_context(child, window->context);
}

//A method to automatically create a new window in the provided parent window
Window* Window_create_window(Window* window, int16_t x, int16_t y,
							 uint16_t width, int16_t height, uint16_t flags)
{

	//Attempt to create the window instance
	Window* new_window;
	if (!(new_window = Window_new(x, y, width, height, flags, window->context)))
		return new_window;

	//Attempt to add the window to the end of the parent's children list
	//If we fail, make sure to clean up all of our allocations so far 
	if (!List_add(window->children, (void*) new_window)) {

		free(new_window);
		return (Window*) 0;
	}

	//Set the new child's parent 
	new_window->parent = window;
	new_window->parent->active_child = new_window;

	return new_window;
}

//Assign a string to the title of the window
void Window_set_title(Window* window, char* new_title)
{
	int len, i;

	//Make sure to free any preexisting title 
	if (window->title) {

		for (len = 0; window->title[len]; len++);
		free(window->title);
	}

	//We don't have strlen, so we're doing this manually
	for (len = 0; new_title[len]; len++);

	//Try to allocate new memory to clone the string
	//(+1 because of the trailing zero in a c-string)
	if (!(window->title = (char*) malloc((len + 1) * sizeof(char))))
		return;

	//Clone the passed string into the window's title
	//Including terminating zero
	for (i = 0; i <= len; i++)
		window->title[i] = new_title[i];

	//Make sure the change is reflected on-screen
	if (window->flags & WIN_NODECORATION)
		Window_invalidate(window, 0, 0, window->height - 1, window->width - 1);
	else
		Window_update_title(window);
}
