#pragma once

#include "LinkedList.hpp"
#include "krnl/main.hpp"
#include "krnl/terminal.hpp"
#include "krnl/physmgr.hpp"
#include "thr/prcssthr.hpp"
#include "sys/syscalls.hpp"
#include "hal/intctrl.hpp"
#include "hw/acpi.hpp"
#include "fs/vfs.hpp"
#include "krnl/kheap.hpp"
#include <hal/video.hpp>
extern "C" {
#include "libk/string.h"
}

#include "Region.hpp"
#include "Font.hpp"
#include "Mouse.hpp"
#include "Main.hpp"
#include "Video.hpp"
#include "Primatives.hpp"

#define NFRAME_DEFAULT_FLAGS					(0)
#define NFRAME_DEFAULT_NON_DECORATED_FLAGS		(NFRAME_FLAG_DISABLE_TITLE_BAR | NFRAME_FLAG_DISABLE_SHADOW)

#define NFRAME_FLAG_DISABLE_TITLE_BAR			1
#define NFRAME_FLAG_HIDE_CLOSE_BUTTON			2
#define NFRAME_FLAG_DISABLE_SHADOW				4
#define NFRAME_FLAG_DISABLE_DEFAULT_PAINTER		8
#define NFRAME_FLAG_DISABLE_CLOSE_BUTTON		16

#pragma GCC optimize ("O0")

class NFrame
{
protected:
	LinkedList2<NFrame*> children;
	NFrame* parent;
	Region rgn;
	Region dragFrameRgn;		//only valid after calling startDragState()
	Region dirtyRgn;
	bool hidden = false;
	bool dragState = false;
	int flags = NFRAME_DEFAULT_FLAGS;
	bool fullscreen = false;
	int restoreX = 10;
	int restoreY = 10;
	int restoreW = 100;
	int restoreH = 75;

	struct Graphics
	{
		Screen scr;
		Region clipRegion;

		Graphics(Screen s, Region r)
		{
			scr = s;
			clipRegion = r;
		}
	};

	void paintClippedCommon(Region willBeFreedBeforeReturning, Graphics g, uint32_t col)
	{
		Region combined = getRegionIntersection(g.clipRegion, willBeFreedBeforeReturning);

		fillRegion(g.scr, combined, col);

		free(willBeFreedBeforeReturning.data);
		free(combined.data);
	}

	void markRegionAsDirty(Region r)
	{
		if (parent) {
			parent->markRegionAsDirty(r);
		} else {
			Region newDirtyRgn = getRegionUnion(dirtyRgn, r);
			free(dirtyRgn.data);
			dirtyRgn = newDirtyRgn;
		}
	}

	void invalidateRectangularBoundingBox()
	{
		Region rgn2 = createRectangleRegion(getAbsX(), getAbsY(), rgn.width, rgn.height);
		markRegionAsDirty(rgn2);
	}

	void invalidate()
	{
		Region rgn2 = rgn;
		rgn2.relX = getAbsX();
		rgn2.relY = getAbsY();
		markRegionAsDirty(rgn2);
	}

	bool raiseChild(NFrame* child)
	{
		if (!children.head_ || !children.head_->data) return false;

		if (children.head_->data == child) {
			// already on top
			return false;
		}

		children.deleteNodesByValue(child);
		addChild(child);

		return true;
	}

	// called after we are resized, useful to override for chopping off the corners of the
	// region to create, e.g. shadows
	virtual void postResizeCleanup()
	{
		tryInvalidate();
	}

	virtual void paintHandler(Graphics g) = 0;

public:
	NFrame* getPixelOwner(Screen scr, int x, int y, bool collapseIntoToplevel)
	{
		Region drawRgn = getDrawRegion();
		drawRgn.relX = getAbsX();
		drawRgn.relY = getAbsY();

		if (isPointInRegion(drawRgn, x, y)) {
			free(drawRgn.data);
			return this;
		}

		free(drawRgn.data);

		auto iterator = children.head_;
		while (iterator) {
			auto const& child = iterator->data;
			iterator = iterator->next;

			if (child->hidden) {
				continue;
			}

			NFrame* childResult = child->getPixelOwner(scr, x, y, collapseIntoToplevel);
			if (childResult != nullptr) {
				return (collapseIntoToplevel && parent != nullptr) ? this : childResult;
			}
		}

		return nullptr;
	}

	Region repaintAux(Screen scr, Region parentBound, bool clearDirtyRgn = true)
	{
		Region drawRgn = getDrawRegion();

		drawRgn.relX = getAbsX();
		drawRgn.relY = getAbsY();

		Region drawRgnClipped = getRegionIntersection(drawRgn, parentBound);
		free(drawRgn.data);

		paintHandler(Graphics(scr, drawRgnClipped));

		Region rgn2 = rgn;
		rgn2.relX = getAbsX();
		rgn2.relY = getAbsY();

		Region childClip = getRegionIntersection(parentBound, rgn2);

		NFrame* dragChild = nullptr;

		auto iterator = children.head_;
		while (iterator) {
			auto const& child = iterator->data;
			iterator = iterator->next;

			if (child->hidden) {
				if (child->dragState) {
					dragChild = child;
				}
				continue;
			}

			Region childClipRgn = child->repaintAux(scr, childClip);

			Region newDrawRgnClipped = getRegionUnion(drawRgnClipped, childClipRgn);
			free(drawRgnClipped.data);
			drawRgnClipped = newDrawRgnClipped;

			Region newChildClip = getRegionDifference(childClip, drawRgnClipped);
			free(childClip.data);
			childClip = newChildClip;

			free(childClipRgn.data);
		}

		free(childClip.data);

		if (parent == nullptr && clearDirtyRgn) {
			free(dirtyRgn.data);
			dirtyRgn = createRectangleRegion(0, 0, 0, 1);
		}

		if (dragChild) {
			Region rgn2 = dragChild->dragFrameRgn;
			rgn2.relX += getAbsX();		// child abs X = child->rgn.relX + our abs X
			rgn2.relY += getAbsY();

			fillRegion(scr, rgn2, 0x000000);
		}

		return drawRgnClipped;
	}


	NFrame(Region preciseArea)
	{
		dirtyRgn = createRectangleRegion(0, 0, 0, 1);
		parent = nullptr;
		rgn = preciseArea;

		//assert(rgn.width >= 0);
	}

	NFrame(int x, int y, int w, int h)
	{
		parent = nullptr;
		dirtyRgn = createRectangleRegion(0, 0, 0, 1);
		rgn = createRectangleRegion(x, y, w, h);
		//assert(rgn.width >= 0);
	}

	~NFrame()
	{
		free(rgn.data);

		if (dragState) {
			dragState = false;
			free(dragFrameRgn.data);
		}

		free(dirtyRgn.data);
	}

	bool isHidden()
	{
		return hidden;
	}

	void unhide()
	{
		hide(false);
	}

	void hide(bool val = true)
	{
		if (val != hidden) {
			hidden = val;
			if (hidden) {
				invalidate();
			} else {
				// the 'ants' around the rectangular frame of the window need to be completely cleared
				invalidateRectangularBoundingBox();
			}
		}
	}

	void addChild(NFrame* child)
	{
		children.prependNode(child);
		child->parent = this;
	}

	Region getDirtyRegion()
	{
		return dirtyRgn;
	}

	Region _getRegion()
	{
		return rgn;
	}

	Region getDrawRegion()
	{
		Region combinedChildRegions = createRectangleRegion(rgn.relX, rgn.relY, 0, 1);

		auto iterator = children.head_;
		while (iterator) {
			auto const& child = iterator->data;
			iterator = iterator->next;

			if (child->hidden) {
				continue;
			}

			Region childDrawRegion = child->rgn;
			childDrawRegion.relX += rgn.relX;
			childDrawRegion.relY += rgn.relY;

			Region recombined = getRegionUnion(combinedChildRegions, childDrawRegion);
			free(combinedChildRegions.data);
			combinedChildRegions = recombined;
		}

		Region availableDrawArea = getRegionDifference(rgn, combinedChildRegions);
		free(combinedChildRegions.data);
		return availableDrawArea;
	}

	int getWidth()
	{
		return rgn.width;
	}

	int getHeight()
	{
		return rgn.height;
	}

	void startDragState()
	{
		//assert(!dragState);
		hide();
		dragFrameRgn = createAntRegion(rgn.relX, rgn.relY, rgn.width, rgn.height, 2);
		dragState = true;
	}

	void endDragState()
	{
		//assert(dragState);
		dragState = false;
		free(dragFrameRgn.data);
		unhide();
	}

	virtual void regenerateRegion()
	{
		Region oldRgn = rgn;
		rgn = createRectangleRegion(oldRgn.relX, oldRgn.relY, oldRgn.width, oldRgn.height);
		free(oldRgn.data);

		if (dragState) {
			oldRgn = dragFrameRgn;
			dragFrameRgn = createAntRegion(rgn.relX, rgn.relY, rgn.width, rgn.height, 2);
			free(oldRgn.data);
		}
	}
	
	bool setSize(int w, int h)
	{
		if (w < 1) w = 1;
		if (h < 1) h = 1;
		if (hasTitleBar()) {
			if (w < 75) w = 75;
			if (h < 40) h = 40;
		}

		if (w != rgn.width || h != rgn.height) {
			tryInvalidate();
			rgn.width = w;
			rgn.height = h;
			regenerateRegion();
			postResizeCleanup();
			return true;
		}

		return false;
	}

	void setWidth(int w)
	{
		setSize(w, rgn.height);
	}

	bool hasTitleBar()
	{
		return !((flags & NFRAME_FLAG_DISABLE_DEFAULT_PAINTER) || (flags & NFRAME_FLAG_DISABLE_TITLE_BAR));
	}

	bool isCloseButtonEnabled()
	{
		return !((flags & NFRAME_FLAG_DISABLE_DEFAULT_PAINTER) || (flags & NFRAME_FLAG_DISABLE_TITLE_BAR) || (flags & NFRAME_FLAG_HIDE_CLOSE_BUTTON) || (flags & NFRAME_FLAG_DISABLE_CLOSE_BUTTON));
	}

	bool isHiddenOverall() {
		return hidden || (parent && parent->isHiddenOverall());
	}

	void tryInvalidate()
	{
		if (dragState) {
			Region rgn2 = dragFrameRgn;
			rgn2.relX = getAbsX();
			rgn2.relY = getAbsY();
			markRegionAsDirty(rgn2);
			return;
		}

		if (!isHiddenOverall()) {
			invalidate();
		}
	}

	void setHeight(int h)
	{
		setSize(rgn.width, h);
	}

	int getX()
	{
		return rgn.relX;
	}

	int getY()
	{
		return rgn.relY;
	}

	int getAbsX()
	{
		if (parent) {
			return parent->getAbsX() + rgn.relX;
		} else {
			return rgn.relX;
		}
	}

	int getAbsY()
	{
		if (parent) {
			return parent->getAbsY() + rgn.relY;
		} else {
			return rgn.relY;
		}
	}

	void setPosition(int x, int y)
	{
		if (x != rgn.relX || y != rgn.relY) {
			tryInvalidate();
			if (hidden) {
				dragFrameRgn.relX += x - rgn.relX;
				dragFrameRgn.relY += y - rgn.relY;
			}
			rgn.relX = x;
			rgn.relY = y;
			if (!hidden) {
				tryInvalidate();
			}
		}
	}

	void setX(int x)
	{
		setPosition(x, rgn.relY);
	}

	void setY(int y)
	{
		setPosition(rgn.relX, y);
	}

	void raise()
	{
		if (parent) {
			bool gotARaise = parent->raiseChild(this);
			if (gotARaise) invalidate();
		}
	}

	void repaintCursorRegion(Screen scr, Region mouseRgn)
	{
		//free(repaintAux(scr, mouseRgn, false).data);
	}

	void repaint(Screen scr, Region mouseRgn)
	{
		free(repaintAux(scr, getDirtyRegion()).data);

		//Region drawRgn = getRegionDifference(getDirtyRegion(), mouseRgn);
		//free(repaintAux(scr, drawRgn).data);
		//free(drawRgn.data);
	}

	void paintSolid(Graphics g, uint32_t col)
	{
		fillRegion(g.scr, g.clipRegion, col);
	}

	void paintEllipse(Graphics g, int x, int y, int w, int h, uint32_t col)
	{
		paintClippedCommon(createEllipseRegion(x + getAbsX(), y + getAbsY(), w, h), g, col);
	}

	void paintRectangle(Graphics g, int x, int y, int w, int h, uint32_t col)
	{
		paintClippedCommon(createRectangleRegion(x + getAbsX(), y + getAbsY(), w, h), g, col);
	}

	bool isFullscreen()
	{
		return fullscreen;
	}

	void toggleFullscreen(Screen scr)
	{
		if (fullscreen) {
			fullscreen = false;

			setSize(restoreW, restoreH);
			setPosition(restoreX, restoreY);

		} else {
			fullscreen = true;
			
			restoreX = rgn.relX;
			restoreY = rgn.relY;
			restoreW = rgn.width;
			restoreH = rgn.height;

			hidden = true;
			setPosition(0, 0);
			hidden = false;
			setSize(scr->getWidth(), scr->getHeight());
		}

	}

	void paintText(Graphics g, int x, int y, const char* text, uint32_t col, int fontHandle = -1)
	{
		if (fontHandle == -1) {
			fontHandle = getFontHandle(FontStyle{ "*SYSTEM", 12 });
		}
		x += getAbsX();
		y += getAbsY();

		int baseX = x;

		int highest = 0;
		for (int i = 0; text[i]; ++i) {
			if (text[i] == '\n') {
				y += highest;
				highest = 0;
				x = baseX;
				continue;
			}

			uint32_t wh = drawFontCharacter(g.scr, g.clipRegion, fontHandle, text[i], x, y, col);
			x += (wh & 0xFFFF);
			int h = wh >> 16;
			if (h > highest) {
				highest = h;
			}
		}
	}

	const int TITLEBAR_HEIGHT = 24;

	int getTitlebarHeight()
	{
		return hasTitleBar() ? TITLEBAR_HEIGHT : 0;
	}
};

class NWindow : public NFrame
{
public:
	int SHADOW_SIZE = 3;
	char* title;

	NWindow(int x, int y, int w, int h, const char* title_ = "Untitled Window", int flags_ = NFRAME_DEFAULT_FLAGS) : NFrame(createRectangleRegion(x, y, w, h))
	{
		char dummyTitle[] = "";

		flags = flags_;

		if (title_ == nullptr) {
			title_ = dummyTitle;
		}
		title = (char*) malloc(strlen(title_) + 1);
		strcpy(title, title_);

		clipCornersIfNeededToMakeShadows();
	}

	~NWindow()
	{
		free(title);
	}

	void clipCornersIfNeededToMakeShadows()
	{
		if (!(flags & NFRAME_FLAG_DISABLE_SHADOW) && !fullscreen) {
			SHADOW_SIZE = 3;

			Region cornerClipA = createRectangleRegion(rgn.relX + rgn.width - SHADOW_SIZE, rgn.relY, SHADOW_SIZE, SHADOW_SIZE);
			Region cornerClipB = createRectangleRegion(rgn.relX, rgn.relY + rgn.height - SHADOW_SIZE, SHADOW_SIZE, SHADOW_SIZE);

			Region newRgnA = getRegionDifference(rgn, cornerClipB);
			Region newRgn = getRegionDifference(newRgnA, cornerClipA);

			free(rgn.data);
			free(newRgnA.data);
			free(cornerClipA.data);
			free(cornerClipB.data);

			rgn = newRgn;


		} else {
			SHADOW_SIZE = 0;
		}
	}

	virtual void postResizeCleanup() override
	{
		clipCornersIfNeededToMakeShadows();
		tryInvalidate();
	}

	void setTitle(const char* title_)
	{
		if (title_ != nullptr) {
			free(title);
			title = (char*) malloc(strlen(title_) + 1);
			strcpy(title, title_);
		}
	}

	void paintHandler(Graphics g)
	{
		if (flags & NFRAME_FLAG_DISABLE_DEFAULT_PAINTER) {
			return;
		}

		const int BUTTON_SIZE = 24;

		const int SHADOW_COLOUR						= 0x000000;
		const int OUTLINE_COLOUR					= 0x000000;
		const int WINDOW_COLOUR						= 0xC0C0C0;
		const int TITLEBAR_COLOUR					= 0xFFFFFF;
		const int CLOSE_BUTTON_COLOUR				= TITLEBAR_COLOUR;
		const int TITLEBAR_TEXT_COLOUR				= 0x000000;
		const int CLOSE_BUTTON_TEXT_COLOUR			= 0x000000;
		const int CLOSE_BUTTON_TEXT_COLOUR_DISABLED	= 0xC0C0C0;

		if (!(flags & NFRAME_FLAG_DISABLE_TITLE_BAR)) {
			paintRectangle(g, 0, TITLEBAR_HEIGHT, rgn.width, rgn.height - TITLEBAR_HEIGHT, WINDOW_COLOUR);

			if (!(flags & NFRAME_FLAG_HIDE_CLOSE_BUTTON)) {
				paintRectangle(g, 0, 0, rgn.width - SHADOW_SIZE - BUTTON_SIZE, TITLEBAR_HEIGHT, TITLEBAR_COLOUR);
				paintRectangle(g, rgn.width - BUTTON_SIZE - SHADOW_SIZE, 0, BUTTON_SIZE, TITLEBAR_HEIGHT, CLOSE_BUTTON_COLOUR);

				paintText(g, rgn.width - BUTTON_SIZE - SHADOW_SIZE + 8, 6, "X", (flags & NFRAME_FLAG_DISABLE_CLOSE_BUTTON) ? CLOSE_BUTTON_TEXT_COLOUR_DISABLED : CLOSE_BUTTON_TEXT_COLOUR);

			} else {
				paintRectangle(g, 0, 0, rgn.width - SHADOW_SIZE, TITLEBAR_HEIGHT,  TITLEBAR_COLOUR);
			}

			paintText(g, 8, 6, title, TITLEBAR_TEXT_COLOUR);
		
		} else {
			paintSolid(g, WINDOW_COLOUR);
		}
		
		if (!(flags & NFRAME_FLAG_DISABLE_SHADOW)) {
			paintRectangle(g, rgn.width - SHADOW_SIZE, 0, SHADOW_SIZE, rgn.height, SHADOW_COLOUR);
			paintRectangle(g, 0, rgn.height - SHADOW_SIZE, rgn.width, SHADOW_SIZE, SHADOW_COLOUR);
			paintRectangle(g, 0, 0, rgn.width, 1, OUTLINE_COLOUR);
			paintRectangle(g, 0, 0, 1, rgn.height, OUTLINE_COLOUR);
			paintRectangle(g, 0, rgn.height - 1 - SHADOW_SIZE, rgn.width, 1, OUTLINE_COLOUR);
			paintRectangle(g, rgn.width - 1 - SHADOW_SIZE, 0, 1, rgn.height, OUTLINE_COLOUR);
		}
	}
};


class NDesktopWindow : public NFrame
{
public:
	int col;
	NDesktopWindow() : NFrame(0, 0, 1, 1)
	{

	}

	NDesktopWindow(int x, int y, int w, int h, int c = 0x008080) : NFrame(x, y, w, h)
	{
		col = c;
	}

	void paintHandler(Graphics g)
	{
		paintRectangle(g, 0, 0, rgn.width, rgn.height, col);

	}
};

class NButton : public NFrame
{
public:

	NButton() : NFrame(0, 0, 1, 1)
	{

	}

	NButton(int x, int y, int w, int h) : NFrame(x, y, w, h)
	{
		
	}

	void paintHandler(Graphics g)
	{
		paintRectangle(g, 0, 0, rgn.width, rgn.height, 0xC0C0C0);

		/*paintText(g, 0, 0, "The quick brown fox jumps over a lazy dog.", 0x000000, getFontHandle(FontStyle("Serif", 12)));
		paintText(g, 0, 25, "The quick brown fox jumps over a lazy dog.", 0x000000, getFontHandle(FontStyle("Serif", 12, FONT_FLAG_BOLD)));
		paintText(g, 0, 50, "The quick brown fox jumps over a lazy dog.", 0x000000, getFontHandle(FontStyle("Serif", 12, FONT_FLAG_ITALIC)));
		paintText(g, 0, 75, "The quick brown fox jumps over a lazy dog.", 0x000000, getFontHandle(FontStyle("Serif", 12, FONT_FLAG_BOLD | FONT_FLAG_ITALIC)));

		paintText(g, 0, 100, "The quick brown fox jumps over a lazy dog.", 0x000000, getFontHandle(FontStyle("Serif", 16)));
		paintText(g, 0, 130, "The quick brown fox jumps over a lazy dog.", 0x000000, getFontHandle(FontStyle("Serif", 24)));
		paintText(g, 0, 170, "The quick brown fox jumps over a lazy dog.", 0x000000, getFontHandle(FontStyle("Serif", 24, FONT_FLAG_ITALIC)));
		paintText(g, 0, 210, "The quick brown fox jumps over a lazy dog.", 0x000000, getFontHandle(FontStyle("Serif", 36)));
		paintText(g, 0, 270, "The quick brown fox jumps over a lazy dog.", 0x000000, getFontHandle(FontStyle("Serif", 48)));
		paintText(g, 0, 320, "The quick brown fox jumps over a lazy dog.", 0x000000, getFontHandle(FontStyle("Serif", 72)));
		paintText(g, 0, 400, "The quick brown fox jumps over a lazy dog.", 0x000000, getFontHandle(FontStyle("Serif", 144)));*/


		paintText(g, 0, 0, "The quick brown fox jumps over a lazy dog.", 0x000000, getFontHandle(FontStyle("Serif", 12)));
		paintText(g, 0, 25, "1>C:/Users/Alex/Desktop/Banana/kernel/libk/string.h(36,8): warning GAE4BF799: declaration of 'char* strchr(char*, int)' conflicts with built-in declaration 'char* strchr(const char*, int)' [-Wbuiltin-declaration-mismatch]", 0x000000, getFontHandle(FontStyle("Serif", 12)));
		paintText(g, 0, 50, "NButton(int x, int y, int w, int h) : NFrame(x, y, w, h)", 0x000000, getFontHandle(FontStyle("Serif", 12)));
		paintText(g, 0, 75, "paintRectangle(g, 0, 0, rgn.width, rgn.height, col);", 0x000000, getFontHandle(FontStyle("Serif", 12)));

		paintText(g, 0, 100, "The quick brown fox jumps over a lazy dog.", 0x000000, getFontHandle(FontStyle("Serif", 16)));
		paintText(g, 0, 130, "The quick brown fox jumps over a lazy dog.", 0x000000, getFontHandle(FontStyle("Serif", 24)));
	}
};