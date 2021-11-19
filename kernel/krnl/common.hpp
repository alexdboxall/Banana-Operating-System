#pragma once

#ifndef _COMMON_HPP_
#define _COMMON_HPP_

#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdbool.h>

#include <krnl/main.hpp>
#include <krnl/kheap.hpp>
#include <krnl/terminal.hpp>
#include <krnl/computer.hpp>
#include <dbg/kconsole.hpp>

extern "C" {
#include "libk/string.h"
}

#include <krnl/bootmsg.hpp>

#endif