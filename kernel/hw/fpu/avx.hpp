
#ifndef _AVX_HPP_
#define _AVX_HPP_

#include <stdint.h>
#include "hal/fpu.hpp"

class AVX: public FPU
{
private:

protected:

public:
    AVX();

    virtual int open(int, int, void*);            //Opens the device (init code).
    virtual int close(int, int, void*);            //Perform other commands
    
    virtual bool available();
    virtual void save(void* ptr);
    virtual void load(void* ptr);
};

#endif
