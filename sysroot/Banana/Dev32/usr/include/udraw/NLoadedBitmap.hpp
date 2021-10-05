//
//  NButton.hpp
//  NGUI
//
//  Created by Alex Boxall on 16/9/21.
//  Copyright © 2021 Alex Boxall. All rights reserved.
//

#ifndef NLoadedBitmap_hpp
#define NLoadedBitmap_hpp

#include <stdint.h>

struct NLoadedBitmap
{
public:
	int width;
	int height;
	uint32_t* data;
	uint32_t* data2;

	NLoadedBitmap(const char* file);
	~NLoadedBitmap();
};

#endif