#pragma once

#ifndef _COMMON_HPP_
#define _COMMON_HPP_

#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdbool.h>

#include "core/main.hpp"
#include "core/kheap.hpp"
#include "core/terminal.hpp"
#include "core/computer.hpp"
#include "debugger/debug.hpp"

extern "C" {
	#include "libk/string.h"
}

#endif