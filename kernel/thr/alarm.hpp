
#pragma once

#include <thr/prcssthr.hpp>
#include <stdint.h>

uint64_t KeAlarm(ThreadControlBlock* thr, uint64_t millitenth);
void KeCheckAlarm(ThreadControlBlock* thr);