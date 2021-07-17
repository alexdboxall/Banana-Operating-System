//
//  rectangle.hpp
//  GUI
//
//  Created by Alex Boxall on 22/2/20.
//  Copyright © 2020 Alex Boxall. All rights reserved.
//

#ifndef rectangle_hpp
#define rectangle_hpp

#include "gdo.hpp"

class Rectangle : public GDO {
private:
protected:
    virtual void paint();
    
    uint32_t bgCol;
    uint32_t outlineCol;
    int outlineWidth;
    
public:
    void setColour(uint32_t);
    uint32_t getColour();
    
    void setOutline(uint32_t);
    uint32_t getOutline();
    
    void setOutlineWidth(int);
    int getOutlineWidth();
    
    Rectangle (int x, int y, int w, int h, GDO* parent_, uint32_t colour = 0, const char* debugName = "Unnamed Rectangle");
};

#endif /* rectangle_hpp */
