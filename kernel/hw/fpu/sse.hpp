
#ifndef _SSE_HPP_
#define _SSE_HPP_

#include <stdint.h>
#include "hal/fpu.hpp"

class SSE: public FPU
{
private:

protected:

public:
    SSE();

    virtual int open(int, int, void*);            //Opens the device (init code).
    virtual int close(int, int, void*);            //Perform other commands
    
    virtual bool available();
    virtual void save(void* ptr);
    virtual void load(void* ptr);
};

#endif
