#ifndef _BUZZER_HPP_
#define _BUZZER_HPP_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "hal/device.hpp"

void KeBeep(int hertz, int millisecs, bool blocking = true);

#endif