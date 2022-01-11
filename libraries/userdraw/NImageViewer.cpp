//
//  NImageViewer.cpp
//  NGUI
//
//  Created by Alex Boxall on 16/9/21.
//  Copyright © 2021 Alex Boxall. All rights reserved.
//

#include <stdint.h>

#include "NImageViewer.hpp"

#include <string.h>
#include <stdlib.h>

int standardImageViewerHandler(NRegion* _self)
{
    NImageViewer* self = (NImageViewer*) _self;
    Context_draw_bitmap(self->getContext(), self->bmp->data, 0, 0, self->bmp->width, self->bmp->height);
    return 0;
}

int NImageViewer::getWidth()
{
    return bmp->width;
}

int NImageViewer::getHeight()
{
    return bmp->height;
}

NImageViewer::NImageViewer(int x, int y, NTopLevel* context, NLoadedBitmap* bmp) : NImageViewer(x, y, context->getContext(), bmp)
{

}

NImageViewer::NImageViewer(int x, int y, NRegion* context, NLoadedBitmap* bmp) : NImageViewer(x, y, context->getContext(), bmp)
{

}

NImageViewer::NImageViewer(int x, int y, Context* context, NLoadedBitmap* _bmp) :
	NRegion(x, y, getWidth(), getHeight(), context)
{
    bmp = _bmp;
	paintHandler = standardImageViewerHandler;
}

NImageViewer::~NImageViewer()
{       
    delete bmp;
}