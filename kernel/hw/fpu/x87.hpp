
#ifndef _X87_HPP_
#define _X87_HPP_

#include <stdint.h>
#include "hal/fpu.hpp"

class x87: public FPU
{
private:

protected:

public:
    x87();

    virtual int open(int, int, void*);            //Opens the device (init code).
    virtual int close(int, int, void*);            //Perform other commands
    
    virtual bool available();
    virtual void save(void* ptr);
    virtual void load(void* ptr);
};

#endif
