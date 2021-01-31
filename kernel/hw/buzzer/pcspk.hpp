
#ifndef _PCSPK7_HPP_
#define _PCSPK7_HPP_

#include <stdint.h>
#include "hal/buzzer.hpp"

class Beep: public Buzzer
{
private:

protected:

public:
    Beep();

    void start(int hertz);

    int open(int, int, void*);
    int close(int, int, void*);
};

#endif
