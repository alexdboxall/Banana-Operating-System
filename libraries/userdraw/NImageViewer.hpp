//
//  NButton.hpp
//  NGUI
//
//  Created by Alex Boxall on 16/9/21.
//  Copyright © 2021 Alex Boxall. All rights reserved.
//

#ifndef NImageViewer_hpp
#define NImageViewer_hpp

#include "NRegion.hpp"
#include "NToplevel.hpp"
#include "NLoadedBitmap.hpp"

class NImageViewer : public NRegion
{
protected:
	friend int standardImageViewerHandler(NRegion* self);

	NLoadedBitmap* bmp;

	int getWidth();
	int getHeight();

public:
	NImageViewer(int x, int y, NTopLevel* context, NLoadedBitmap* bmp);
	NImageViewer(int x, int y, NRegion* context, NLoadedBitmap* bmp);

	NImageViewer(int x, int y, Context* context, NLoadedBitmap* bmp);
	~NImageViewer();
};

#endif