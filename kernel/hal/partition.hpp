#ifndef _PARTITION_HPP_
#define _PARTITION_HPP_

#include <stdint.h>
#include <stddef.h>
#include "hal/device.hpp"
#include "hal/diskphys.hpp"
#include "hal/logidisk.hpp"
#include "fs/vfs.hpp"

void createPartitionsForDisk(PhysicalDisk* parent);
void makePartition(PhysicalDisk* parent, uint64_t start, uint64_t length);

#endif