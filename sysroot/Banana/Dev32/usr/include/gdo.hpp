//
//  gdo.hpp
//  GUI
//
//  Created by Alex Boxall on 22/2/20.
//  Copyright © 2020 Alex Boxall. All rights reserved.
//

#ifndef gdo_hpp
#define gdo_hpp

//#include "SDL2.framework/Headers/SDL.h"

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void deinitFramebuffer();
void initFramebuffer(int w, int h);
void writeToFramebuffer (uint8_t* pixels, int w, int h);

class GDO {
private:
    
protected:
    uint32_t* buffer = nullptr;
    
    GDO* parent = nullptr;
    GDO* next = nullptr;
    GDO* firstChild = nullptr;
    GDO* lastChild = nullptr;
    
    char name[16];
    
    bool dirty = false;
	bool hasDirtyChild = false;
	bool justResized = false;
    int relX = 0;
    int relY = 0;
    int width = 0;
    int height = 0;
    
    virtual void paint();       //paints image to back buffer
    void blitOn(uint32_t* buffer, int x, int y, int w, int h);
    virtual void upBlit();      //only Region should override this
    
    void oops(const char* msg);
    
    void addChild (GDO* c);
    void removeChild (GDO* c);

public:
	bool isDirty();
	bool isAChildDirty();
	void sendDirtyChildUpward();

    virtual void setX(int x);
	virtual int getX();
	virtual void setY(int y);
	virtual int getY();
	virtual void setWidth(int w);
	virtual int getWidth();
	virtual void setHeight(int h);
	virtual int getHeight();
    
    GDO (int x, int y, int w, int h, GDO* parent_, const char* debugName = "Unnamed Object");
	~GDO();

    void updateNoUpBlit();
    void update();

	void playInTheMud();
};

#endif /* gdo_hpp */
