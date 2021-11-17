
#ifndef _THR_EXEC_HPP_
#define _THR_EXEC_HPP_

#include <stdint.h>
#include <stddef.h>
#include "krnl/main.hpp"
#include "krnl/virtmgr.hpp"

int KeProcessExec(Process* prcss, const char* filename);

#endif