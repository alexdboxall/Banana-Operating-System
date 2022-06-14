
extern "C" {
	#include <libk/math.h>
}

#include <krnl/panic.hpp>

// make the compiler actually include some math functions instead
// of stripping them all away
//
//			CLIPDRAW.DLL needs sqrt
//

void* keMathFunctionTable[] = {
	(void*) sinh,
	(void*) cosh,
	(void*) tanh,
	(void*) asin,
	(void*) acos,
	(void*) atan,
	(void*) atan2,
	(void*) sin,
	(void*) cos,
	(void*) tan,
	(void*) sqrt,
	(void*) pow,
	(void*) frexp,
	(void*) ldexp,
	(void*) exp,
	(void*) log,
	(void*) log10,
	(void*) ceil,
	(void*) floor,
	(void*) round,
	(void*) fmod,
	(void*) modf,
};