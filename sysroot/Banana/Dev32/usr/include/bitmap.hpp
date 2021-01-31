//
//  bitmap.hpp
//  GUI
//
//  Created by Alex Boxall on 22/2/20.
//  Copyright © 2020 Alex Boxall. All rights reserved.
//

#ifndef bitmap_hpp
#define bitmap_hpp

#include "gdo.hpp"
#include "EasyBMP.h"

class Bitmap : public GDO {
private:
protected:
    BMP internalImg;
    bool hasImage = false;
    
    virtual void paint();

public:
    Bitmap (int x, int y, GDO* parent_, const char* debugName = "Unnamed Bitmap");
    void loadBitmapFromFile(const char* filename);
	uint32_t getPixel(int x, int y);
};

#endif /* bitmap_hpp */
