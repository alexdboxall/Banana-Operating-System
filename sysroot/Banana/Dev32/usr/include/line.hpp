//
//  line.hpp
//  GUI
//
//  Created by Alex Boxall on 24/2/20.
//  Copyright © 2020 Alex Boxall. All rights reserved.
//

#ifndef line_hpp
#define line_hpp

#include "gdo.hpp"

class Line : public GDO {
private:
protected:
    virtual void paint();
    
    uint32_t outlineCol;
    int outlineWidth;
    
public:
    void setOutline(uint32_t);
    uint32_t getOutline();
    
    int _x1;
    int _y1;
    int _x0;
    int _y0;
    
    
    void setOutlineWidth(int);
    int getOutlineWidth();
    
    Line (int x1, int y1, int x2, int y2, GDO* parent_, uint32_t colour = 0, int lineWidth = 0, const char* debugName = "Unnamed Line");
};

#endif /* line_hpp */
