
#ifndef _MMX_HPP_
#define _MMX_HPP_

#include <stdint.h>
#include "hal/fpu.hpp"

class MMX: public FPU
{
private:

protected:

public:
	MMX();

    virtual int open(int, int, void*);            //Opens the device (init code).
    virtual int close(int, int, void*);            //Perform other commands
    
    virtual bool available();
    virtual void save(void* ptr);
    virtual void load(void* ptr);
};

#endif
