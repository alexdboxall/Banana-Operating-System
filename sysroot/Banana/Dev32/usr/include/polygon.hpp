//
//  polygon.hpp
//  GUI
//
//  Created by Alex Boxall on 25/2/20.
//  Copyright © 2020 Alex Boxall. All rights reserved.
//

#ifndef polygon_hpp
#define polygon_hpp

#include "gdo.hpp"

class Polygon : public GDO {
private:
protected:
    virtual void paint();
    
    uint32_t bgCol;
    uint32_t outlineCol;
    int outlineWidth;
    
    double* xPoints;
    double* yPoints;
    int numPoints;
        
    int calcTopLeftX(int* points, int num);
    int calcWidth(int* points, int num);
    
public:
    void setColour(uint32_t);
    uint32_t getColour();
        
    void setOutline(uint32_t);
    uint32_t getOutline();
        
    void setOutlineWidth(int);
    int getOutlineWidth();
    
    int noPoints;
    
    Polygon (int* xPos, int* yPos, int points, GDO* parent_, uint32_t colour = 0, const char* debugName = "Unnamed Polygon");
};

#endif /* polygon_hpp */
