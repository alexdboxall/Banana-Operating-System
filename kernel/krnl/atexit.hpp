#pragma once

#include <stdint.h>

void KeRegisterAtexit(void (*handler)(void*), void* context);
void KeExecuteAtexit();
void KeInitialiseAtexit();