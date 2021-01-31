//
//  region.hpp
//  GUI
//
//  Created by Alex Boxall on 23/2/20.
//  Copyright © 2020 Alex Boxall. All rights reserved.
//

#ifndef region_hpp
#define region_hpp

#include "gdo.hpp"
#include "D:/Users/Alex/Desktop/Banana/kernel/core/syscalls.hpp"

class Region : public GDO {
private:
protected:
    virtual void paint();
    
    virtual void upBlit();

public:   
	WindowProtocol sdlWindow;                    // Declare a pointer

    Region (int x, int y, int w, int h, const char* debugName = "Unnamed Window");
	void updateWindow(int _x, int _y, int _w, int _h, bool canClose);
};

extern uint64_t SystemCall(size_t a, size_t b, size_t c, size_t d);

#endif /* region_hpp */
