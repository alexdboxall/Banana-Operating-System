
#ifndef _FPU_HPP_
#define _FPU_HPP_

#include <stdint.h>
#include <stddef.h>
#include "hal/device.hpp"

class FPU : public Device
{
private:

protected:

public:
    FPU(const char* name);
    virtual ~FPU();

    virtual void save(void* ptr) = 0;
    virtual void load(void* ptr) = 0;
    virtual bool available() = 0;
};

FPU* setupFPU();

#endif
