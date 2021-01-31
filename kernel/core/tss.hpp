#pragma once

#ifndef _TSS_HPP_
#define _TSS_HPP_

#include <stdint.h>
#include <stddef.h>

class TSS
{
private:

protected:
	uint16_t* ptr;

public:
	TSS();
	void setESP(size_t esp);
	void setup(size_t esp);
};

#endif