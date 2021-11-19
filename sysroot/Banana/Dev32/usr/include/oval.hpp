//
//  oval.hpp
//  GUI
//
//  Created by Alex Boxall on 22/2/20.
//  Copyright © 2020 Alex Boxall. All rights reserved.
//

#ifndef oval_hpp
#define oval_hpp

#include "gdo.hpp"
class Oval : public GDO {
private:
protected:
    uint32_t bgCol;
    uint32_t outlineCol;
    
    virtual void paint();

public:
    void setColour(uint32_t);
    uint32_t getColour();
    
    Oval (int x, int y, int w, int h, GDO* parent_, uint32_t colour = 0, const char* debugName = "Unnamed Oval");
};

#endif /* oval_hpp */
