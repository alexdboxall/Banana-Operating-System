#include "core/main.hpp"
#include "hal/partition.hpp"
#include "libk/string.h"
#pragma GCC optimize ("Os")
#pragma GCC optimize ("-fno-strict-aliasing")
#pragma GCC optimize ("-fno-align-labels")
#pragma GCC optimize ("-fno-align-jumps")
#pragma GCC optimize ("-fno-align-loops")
#pragma GCC optimize ("-fno-align-functions")

void makePartition(PhysicalDisk* parent, uint64_t start, uint64_t length)
{
	kprintf("making a partition. start = 0x%X, length = 0x%X\n", (int) start, (int) length);
	char name[256];
	strcpy(name, parent->getName());
	strcat(name, " Partition");

	extern int getIRQNestingLevel();

	LogicalDisk* ld = new LogicalDisk(name, parent, start, length);
	char letter = ld->assignDriveLetter();
	bool couldMount = ld->mount();
	parent->addChild(ld);

	kprintf("Mounted a partition to drive %c:\n", letter);
}

void createPartitionsForDisk(PhysicalDisk* parent)
{
	//not a HDD, so no partitions
	if (parent->sectorSize != 512) {
		makePartition(parent, 0, parent->sizeInKBs * 1024 / parent->sectorSize);
		return;

	} else {
		uint8_t buffer[512];
		parent->read(0, 1, buffer);

		//no boot signature = no MBR
		if (!(buffer[510] == 0x55 && buffer[511] == 0xAA)) {
			makePartition(parent, 0, parent->sizeInKBs * 1024 / parent->sectorSize);
			return;
		}

		//this checks the 'active' flag, and ensures it is 0 when ANDed by 0x7F (which means 0x80 turns into 0)
		//as all of them should equal 0 when ANDed by 0x7F, if when added together they don't equal zero, at least
		//one must be bad
		uint8_t invalidVal = (buffer[0x1BE] & 0x7F) + (buffer[0x1CE] & 0x7F) + (buffer[0x1DE] & 0x7F) + (buffer[0x1EE] & 0x7F);
		if (invalidVal) {
			makePartition(parent, 0, parent->sizeInKBs * 1024 / parent->sectorSize);
			return;
		}

		uint64_t lbas[4];
		uint64_t size[4];
		uint8_t bootable = 0;

		for (int i = 0; i < 4; ++i) {
			bootable = buffer[0x1BE + i * 0x10] == 0x80 ? i : bootable;

			lbas[i] = ((uint32_t) buffer[0x1BE + 8 + i * 0x10] << 0) | ((uint32_t) buffer[0x1BE + 9 + i * 0x10] << 8) | \
				((uint32_t) buffer[0x1BE + 10 + i * 0x10] << 16) | ((uint32_t) buffer[0x1BE + 11 + i * 0x10] << 24);

			size[i] = ((uint32_t) buffer[0x1BE + 12 + i * 0x10] << 0) | ((uint32_t) buffer[0x1BE + 13 + i * 0x10] << 8) | \
				((uint32_t) buffer[0x1BE + 14 + i * 0x10] << 16) | ((uint32_t) buffer[0x1BE + 15 + i * 0x10] << 24);
		}

		//HACK: this little hack allows us to not BSOD without a complete install.
		//      if this is taken out, a MBR and partition table is required.
		//      this is only here for ease of testing, and should be taken out of the final release.
		if (lbas[0] == 1 && size[0] == 1) {
			lbas[0] = 0;
			size[0] = parent->sizeInKBs * 1024 / parent->sectorSize;
		}

		//use 'magic' to ensure that the bootable drive always goes first
		if (bootable != 0) {
			uint64_t tmp = lbas[0];
			lbas[0] = lbas[bootable];
			lbas[bootable] = tmp;

			tmp = size[0];
			size[0] = size[bootable];
			size[bootable] = tmp;
		}

		//copy disk data
		for (int i = 0; i < 4; ++i) {
			if (size[i] && lbas[i]) {
				makePartition(parent, lbas[i], size[i]);
			}
		}
	}
}
