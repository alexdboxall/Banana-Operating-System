#ifndef _GDT_HPP_
#define _GDT_HPP_

#include <stdint.h>
#include <stddef.h>

struct GDTEntry
{
	union
	{
		struct
		{
			uint64_t limitLow : 16;
			uint64_t baseLow : 24;

			uint64_t accessed : 1;
			uint64_t readWrite : 1;
			uint64_t directionAndConforming : 1;
			uint64_t executable : 1;
			uint64_t type : 1;
			uint64_t priv : 2;
			uint64_t present : 1;

			uint64_t limitHigh : 4;
			uint64_t : 1;
			uint64_t bit64: 1;
			uint64_t size : 1;
			uint64_t gran : 1;

			uint64_t baseHigh : 8;
		};

		struct
		{
			uint64_t  : 16;
			uint64_t  : 24;

			uint64_t access : 8;

			uint64_t  : 4;
			uint64_t flags: 4;

			uint64_t  : 8;
		};

		uint64_t val;
	};
	

	void setBase (uint32_t val);
	void setLimit (uint32_t val);
};

#pragma pack(push,1)
struct GDTDescriptor
{
	uint16_t size;
	size_t offset;

};

#pragma pack(pop)

class GDT
{
private:

protected:
	int entryCount = 0;
	uint64_t entries[256];

public:
	GDT();
};


#endif