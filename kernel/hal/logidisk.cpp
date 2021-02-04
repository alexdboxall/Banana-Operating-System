#include "core/main.hpp"
#include "hal/logidisk.hpp"
#include "hal/diskphys.hpp"
#include "hal/vcache.hpp"
//#pragma GCC optimize ("Os")

LogicalDisk* disks[MAX_DISK_COUNT];

uint64_t LogicalDisk::absoluteToRelative(uint64_t abs)
{
	uint64_t rel = abs - partitionLBA;

	if (rel > 0xFFFFFFFFFFFFFFFU) {
		return (uint64_t) -1LL;
	}
	if (rel >= partitionLength) {
		return (uint64_t) -1LL;
	}

	return rel;
}

uint64_t LogicalDisk::relativeToAbsolute(uint64_t rel)
{
	if (rel > 0xFFFFFFFFFFFFFFFU) {
		return -1;
	}
	if (rel >= partitionLength) {
		return -1;
	}

	return rel + partitionLBA;
}

LogicalDisk::LogicalDisk(const char* name, PhysicalDisk* phys, uint64_t lowLBA, uint64_t sectors) : Device(name)
{
	mounted = 0;

	deviceType = DeviceType::LogicalDisk;
	partitionLBA = lowLBA;
	partitionLength = sectors;

	physDisk = phys;
	fs = nullptr;
}

LogicalDisk::~LogicalDisk()
{

}

uint64_t diskAssignments = 0;

char LogicalDisk::assignDriveLetter()
{
	char spot = 'C';
	if (physDisk->floppy) {
		spot = 'A';
	}

	for (; (spot - 'A') < MAX_DISK_COUNT; ++spot) {
		if (spot == 'C' && (physDisk->removable || physDisk->floppy)) {
			continue;
		}

		uint64_t bit = 1 << (spot - 'A');
		if (!(diskAssignments & bit)) {
			diskAssignments |= bit;
			mounted = spot;
			disks[spot - 'A'] = this;
			return spot;
		}
	}

	return 0;
}

bool LogicalDisk::mount()
{
	Filesystem* conductor = installedFilesystems;

	fs = nullptr;
	while (conductor) {
		extern int getIRQNestingLevel();
		kprintf("trymount 1 INT STATE = %d\n", getIRQNestingLevel());
		if (conductor->tryMount(this, mounted - 'A')) {
			fs = conductor;
			return true;
		}
		kprintf("trymount 2 INT STATE = %d\n", getIRQNestingLevel());

		conductor = conductor->next;
	}

	return false;
}

void LogicalDisk::unmount()
{
	fs = nullptr;
}

int LogicalDisk::open(int a, int b, void* c)
{
	panic("PLEASE DON'T CALL LogicalDisk::open");
	return -1;
}

int LogicalDisk::close(int a, int b, void* c)
{
	return -1;
}

void LogicalDisk::unassignDriveLetter()
{
	if (!mounted) {
		panic("CANNOT UNASSIGN UNASSIGNED DISK");
		return;
	}
	uint64_t bit = (1 << (mounted - 'A'));
	diskAssignments &= ~bit;
	disks[mounted - 'A'] = nullptr;
	mounted = 0;
}

int LogicalDisk::read(uint64_t lba, int count, void* ptr)
{
	if (lba > 0xFFFFFFFFFFFFFFFU) {
		return (int) DiskError::BadLBA;
	}
	if (lba + count > partitionLength) {
		return (int) DiskError::ParitionBoundError;
	}

	return physDisk->cache->read(lba + partitionLBA, count, ptr);
}
	
int LogicalDisk::write(uint64_t lba, int count, void* ptr)
{
	if (lba > 0xFFFFFFFFFFFFFFFU) {
		return (int) DiskError::BadLBA;
	}
	if (lba + count > partitionLength) {
		return (int) DiskError::ParitionBoundError;
	}

	return physDisk->cache->write(lba + partitionLBA, count, ptr);
}