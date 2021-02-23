#ifndef __REGISTRY_HPP__
#define __REGISTRY_HPP__

#include <stddef.h>
#include <stdint.h>

#define REGISTRY_TYPE_SYSTEM	0
#define REGISTRY_TYPE_USER		1

namespace Reg
{
	bool readBool(char* path, char* key, bool* out);												//WARNING: TRASHES INPUT ARRAYS!!
	bool readInt(char* path, char* key, int* out);													//WARNING: TRASHES INPUT ARRAYS!!
	bool readString(char* path, char* key, char* out, int maxLen);									//WARNING: TRASHES INPUT ARRAYS!!

	bool readBoolWithDefault(char* path, char* key, bool defaultVal);								//WARNING: TRASHES INPUT ARRAYS!!
	int readIntWithDefault(char* path, char* key, int defaultVal);									//WARNING: TRASHES INPUT ARRAYS!!
	char* readStringWithDefault(char* path, char* key, char* buffer, int maxLen, char* defaultVal);	//WARNING: TRASHES INPUT ARRAYS!!
}


#endif