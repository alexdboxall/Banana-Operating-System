#include "core/common.hpp"
#include "core/kheap.hpp"
#include "thr/prcssthr.hpp"
#include "core/virtmgr.hpp"
#include "core/physmgr.hpp"
#include "libk/string.h"
#include "core/malloc.h"
#include "hw/cpu.hpp"

#define USE_MY_ALLOC

#undef DEBUG 
#pragma GCC optimize ("O1")

extern "C" void* sbrk(ptrdiff_t increment)
{
	static size_t brk = VIRT_SBRK_MIN;
	if (increment == 0) {
		return (void*) brk;

	} else if (increment < 0) {
		kprintf("NEGATIVE SBRK CALLED: WE CAN FREE MEMORY! 0x%X\n", increment);
		return (void*) -1;

	} else {
		size_t oldbrk = brk;
		int pages = (increment + 4095) / 4096;
		for (int i = 0; i < pages; ++i) {
			Virt::getAKernelVAS()->mapPage(Phys::allocatePage(), brk, PAGE_PRESENT | PAGE_ALLOCATED | PAGE_SUPERVISOR);
			brk += 4096;
		}

		CPU::writeCR3(CPU::readCR3());

		return (void*) oldbrk;
	}
}

extern "C" void* mmap(void* addr, size_t length, int prot, int flags, int fd, size_t offset)
{
	panic("MMAP");
	return 0;
}

extern "C" int munmap(void* addr, size_t length)
{
	panic("MUNMAP");
	return 0;
}

int liballoc_lock()
{
	lockScheduler();
	return 0;
}

int liballoc_unlock()
{
	unlockScheduler();
	return 0;
}

size_t liballoc_alloc(int pages)
{
	size_t addr = Virt::getAKernelVAS()->allocatePages(pages, PAGE_PRESENT | PAGE_SUPERVISOR);
	return addr;
}

int liballoc_free(void* ptr, int pages)
{
	Virt::getAKernelVAS()->freeAllocatedPages((size_t) ptr);
	return 0;
}

#ifdef USE_MY_ALLOC

extern "C" void* realloc(void* ptr, size_t size)
{
	return dlrealloc(ptr, size);
}

extern "C" void* malloc(size_t size)
{
	return dlmalloc(size);
}

extern "C" void free(void* __addr)
{
	dlfree(__addr);
}

extern "C" void rfree(void* __addr)
{
	dlfree(__addr);
}

extern "C" void* calloc(size_t nobj, size_t size)
{
	int real_size;
	void* p;

	real_size = nobj * size;

	p = malloc(real_size);

	memset(p, 0, real_size);

	return p;
}

#endif

#ifndef USE_MY_ALLOC
#define LIBALLOC_MAGIC	0xc001c0de
#define MAXCOMPLETE		5
#define MAXEXP	32
#define MINEXP	8	

#define MODE_BEST			0
#define MODE_INSTANT		1

#define MODE	MODE_BEST

#ifdef DEBUG

#endif


struct boundary_tag* l_freePages[MAXEXP];		//< Allowing for 2^MAXEXP blocks
int 				 l_completePages[MAXEXP];	//< Allowing for 2^MAXEXP blocks


#ifdef DEBUG
unsigned int l_allocated = 0;		//< The real amount of memory allocated.
unsigned int l_inuse = 0;			//< The amount of memory in use (malloc'ed). 
#endif


static int l_initialized = 0;			//< Flag to indicate initialization.	
static int l_pageSize = 4096;			//< Individual page size
static int l_pageCount = 4;			//< Minimum number of pages to allocate. (4 on systems with >16MB RAM, else 1)


// ***********   HELPER FUNCTIONS  *******************************

/** Returns the exponent required to manage 'size' amount of memory.
 *
 *  Returns n where  2^n <= size < 2^(n+1)
 */
static inline int getexp(unsigned int size)
{
	if (size < (1 << MINEXP)) {
#ifdef DEBUG
		kprintf("getexp returns -1 for %d less than MINEXP\n", size);
#endif
		return -1;	// Smaller than the quantum.
	}


	int shift = MINEXP;

	while (shift < MAXEXP) {
		if ((1 << shift) > size) break;
		shift += 1;
	}

#ifdef DEBUG
	kprintf("getexp returns %d (%d bytes) for %d size\n", shift - 1, (1 << (shift - 1)), size);
#endif

	return shift - 1;
}


static void* liballoc_memset(void* s, int c, size_t n)
{
	int i;
	for (i = 0; i < n; i++)
		((char*) s)[i] = c;

	return s;
}

static void* liballoc_memcpy(void* s1, const void* s2, size_t n)
{
	char* cdest;
	char* csrc;
	unsigned int* ldest = (unsigned int*) s1;
	unsigned int* lsrc = (unsigned int*) s2;

	while (n >= sizeof(unsigned int)) {
		*ldest++ = *lsrc++;
		n -= sizeof(unsigned int);
	}

	cdest = (char*) ldest;
	csrc = (char*) lsrc;

	while (n > 0) {
		*cdest++ = *csrc++;
		n -= 1;
	}

	return s1;
}



#ifdef DEBUG
static void dump_array()
{
	int i = 0;
	struct boundary_tag* tag = 0;

	kprintf("------ Free pages array ---------\n");
	kprintf("System memory allocated: %d\n", l_allocated);
	kprintf("Memory in used (malloc'ed): %d\n", l_inuse);

	for (i = 0; i < MAXEXP; i++) {
		kprintf("%d(%d): ", i, l_completePages[i]);

		tag = l_freePages[i];
		while (tag != 0) {
			if (tag->split_left != 0) kprintf("*");
			kprintf("%d", tag->real_size);
			if (tag->split_right != 0) kprintf("*");

			kprintf(" ");
			tag = tag->next;
		}
		kprintf("\n");
	}

	kprintf("'*' denotes a split to the left/right of a tag\n");
}
#endif



static inline void insert_tag(struct boundary_tag* tag, int index)
{
	int realIndex;

	if (index < 0) {
		realIndex = getexp(tag->real_size - sizeof(struct boundary_tag));
		if (realIndex < MINEXP) realIndex = MINEXP;
	} else
		realIndex = index;

	tag->index = realIndex;

	if (l_freePages[realIndex] != 0) {
		l_freePages[realIndex]->prev = tag;
		tag->next = l_freePages[realIndex];
	}

	l_freePages[realIndex] = tag;
}

static inline void remove_tag(struct boundary_tag* tag)
{
	if (l_freePages[tag->index] == tag) l_freePages[tag->index] = tag->next;

	if (tag->prev != 0) tag->prev->next = tag->next;
	if (tag->next != 0) tag->next->prev = tag->prev;

	tag->next = 0;
	tag->prev = 0;
	tag->index = -1;
}


static inline struct boundary_tag* melt_left(struct boundary_tag* tag)
{
	struct boundary_tag* left = tag->split_left;

	left->real_size += tag->real_size;
	left->split_right = tag->split_right;

	if (tag->split_right != 0) tag->split_right->split_left = left;

	return left;
}


static inline struct boundary_tag* absorb_right(struct boundary_tag* tag)
{
	struct boundary_tag* right = tag->split_right;

	remove_tag(right);		// Remove right from free pages.

	tag->real_size += right->real_size;

	tag->split_right = right->split_right;
	if (right->split_right != 0)
		right->split_right->split_left = tag;

	return tag;
}

static inline struct boundary_tag* split_tag(struct boundary_tag* tag)
{
	unsigned int remainder = tag->real_size - sizeof(struct boundary_tag) - tag->size;

	struct boundary_tag* new_tag =
		(struct boundary_tag*)((unsigned int) tag + sizeof(struct boundary_tag) + tag->size);

	new_tag->magic = LIBALLOC_MAGIC;
	new_tag->real_size = remainder;

	new_tag->next = 0;
	new_tag->prev = 0;

	new_tag->split_left = tag;
	new_tag->split_right = tag->split_right;

	if (new_tag->split_right != 0) new_tag->split_right->split_left = new_tag;
	tag->split_right = new_tag;

	tag->real_size -= new_tag->real_size;

	insert_tag(new_tag, -1);

	return new_tag;
}


// ***************************************************************




static struct boundary_tag* allocate_new_tag(unsigned int size)
{
	unsigned int pages;
	unsigned int usage;
	struct boundary_tag* tag;

	// This is how much space is required.
	usage = size + sizeof(struct boundary_tag);

	// Perfect amount of space
	pages = usage / l_pageSize;
	if ((usage % l_pageSize) != 0) pages += 1;

	// Make sure it's >= the minimum size.
	if (pages < l_pageCount) pages = l_pageCount;

	tag = (struct boundary_tag*)liballoc_alloc(pages);

	if (tag == 0) return 0;	// uh oh, we ran out of memory.

	tag->magic = LIBALLOC_MAGIC;
	tag->size = size;
	tag->real_size = pages * l_pageSize;
	tag->index = -1;

	tag->next = 0;
	tag->prev = 0;
	tag->split_left = 0;
	tag->split_right = 0;


#ifdef DEBUG
	kprintf("Resource allocated %X of %d pages (%d bytes) for %d size.\n", tag, pages, pages * l_pageSize, size);

	l_allocated += pages * l_pageSize;

	kprintf("Total memory usage = %d KB\n", (int) ((l_allocated / (1024))));
#endif

	return tag;
}




extern "C" void* malloc(size_t size)
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wframe-address"

	kprintf("Malloc %d, 0x%X 0x%X 0x%X\n", size, __builtin_return_address(0), __builtin_return_address(1), __builtin_return_address(2));
#pragma GCC diagnostic pop

	int index;
	void* ptr;
	struct boundary_tag* tag = 0;

	liballoc_lock();

	if (l_initialized == 0) {
		if (Phys::usablePages < 4096) {
			l_pageCount = 1;
		} else {
			l_pageCount = 4;
		}
#ifdef DEBUG
		kprintf("%s\n", "liballoc initializing.");
#endif
		for (index = 0; index < MAXEXP; index++) {
			l_freePages[index] = 0;
			l_completePages[index] = 0;
		}
		l_initialized = 1;
	}

	index = getexp(size) + MODE;
	if (index < MINEXP) index = MINEXP;


	// Find one big enough.
	kprintf("index = %d\n", index);
	tag = l_freePages[index];				// Start at the front of the list.
	while (tag != 0) {
		// If there's enough space in this tag.
		kprintf("Tag search: 0x%X >= 0x%X\n", (tag->real_size - sizeof(struct boundary_tag))
				, (size + sizeof(struct boundary_tag)));
		if ((tag->real_size - sizeof(struct boundary_tag))
			>= (size + sizeof(struct boundary_tag))) {
#ifdef DEBUG
			kprintf("Tag search found %d >= %d\n", (tag->real_size - sizeof(struct boundary_tag)), (size + sizeof(struct boundary_tag)));
#endif
			break;
		}

		tag = tag->next;
	}


	// No page found. Make one.
	if (tag == 0) {
		if ((tag = allocate_new_tag(size)) == 0) {
			liballoc_unlock();
			return 0;
		}

		index = getexp(tag->real_size - sizeof(struct boundary_tag));
	} else {
		remove_tag(tag);

		if ((tag->split_left == 0) && (tag->split_right == 0))
			l_completePages[index] -= 1;
	}

	// We have a free page.  Remove it from the free pages list.

	tag->size = size;

	// Removed... see if we can re-use the excess space.

#ifdef DEBUG
	kprintf("Found tag with %d bytes available (requested %d bytes, leaving %d), which has exponent: %d (%d bytes)\n", tag->real_size - sizeof(struct boundary_tag), size, tag->real_size - size - sizeof(struct boundary_tag), index, 1 << index);
#endif

	unsigned int remainder = tag->real_size - size - sizeof(struct boundary_tag) * 2; // Support a new tag + remainder

	if (((int) (remainder) > 0) /*&& ( (tag->real_size - remainder) >= (1<<MINEXP))*/) {
		int childIndex = getexp(remainder);

		if (childIndex >= 0) {
#ifdef DEBUG
			kprintf("Seems to be splittable: %d >= 2^%d .. %d\n", remainder, childIndex, (1 << childIndex));
#endif

			struct boundary_tag* new_tag = split_tag(tag);

			new_tag = new_tag;	// Get around the compiler warning about unused variables.

#ifdef DEBUG
			kprintf("Old tag has become %d bytes, new tag is now %d bytes (%d exp)\n", tag->real_size, new_tag->real_size, new_tag->index);
#endif
		}
	}



	ptr = (void*) ((unsigned int) tag + sizeof(struct boundary_tag));



#ifdef DEBUG
	l_inuse += size;
	kprintf("malloc: %X,  %d, %d\n", ptr, (int) l_inuse / 1024, (int) l_allocated / 1024);
	dump_array();
#endif


	liballoc_unlock();
#ifdef KERNEL_DEBUG
	memset(ptr, 0xCC, size);
#endif // KERNEL_DEBUG
	return ptr;
}






extern "C" void free(void* ptr)
{	
	int index;
	struct boundary_tag* tag;

	if (ptr == 0) return;

	liballoc_lock();


	tag = (struct boundary_tag*)((unsigned int) ptr - sizeof(struct boundary_tag));

	if (tag->magic != LIBALLOC_MAGIC) {
		liballoc_unlock();		// release the lock
		return;
	}


	kprintf("free: 0x%X\n", tag->size);

#ifdef DEBUG
	l_inuse -= tag->size;
	kprintf("free: %X, %d, %d\n", ptr, (int) l_inuse / 1024, (int) l_allocated / 1024);
#endif


	// MELT LEFT...
	while ((tag->split_left != 0) && (tag->split_left->index >= 0)) {
#ifdef DEBUG
		kprintf("Melting tag left into available memory. Left was %d, becomes %d (%d)\n", tag->split_left->real_size, tag->split_left->real_size + tag->real_size, tag->split_left->real_size);
#endif
		tag = melt_left(tag);
		remove_tag(tag);
	}

	// MELT RIGHT...
	while ((tag->split_right != 0) && (tag->split_right->index >= 0)) {
#ifdef DEBUG
		kprintf("Melting tag right into available memory. This was was %d, becomes %d (%d)\n", tag->real_size, tag->split_right->real_size + tag->real_size, tag->split_right->real_size);
#endif
		tag = absorb_right(tag);
	}


	// Where is it going back to?
	index = getexp(tag->real_size - sizeof(struct boundary_tag));
	if (index < MINEXP) index = MINEXP;

	// A whole, empty block?
	if ((tag->split_left == 0) && (tag->split_right == 0)) {

		if (l_completePages[index] == MAXCOMPLETE) {
			// Too many standing by to keep. Free this one.
			unsigned int pages = tag->real_size / l_pageSize;

			if ((tag->real_size % l_pageSize) != 0) pages += 1;
			if (pages < l_pageCount) pages = l_pageCount;

			liballoc_free(tag, pages);

#ifdef DEBUG
			l_allocated -= pages * l_pageSize;
			kprintf("Resource freeing %X of %d pages\n", tag, pages);
			dump_array();
#endif

			liballoc_unlock();
			return;
		}


		l_completePages[index] += 1;	// Increase the count of complete pages.
	}


	// ..........


	insert_tag(tag, index);

#ifdef DEBUG
	kprintf("Returning tag with %d bytes (requested %d bytes), which has exponent: %d\n", tag->real_size, tag->size, index);
	dump_array();
#endif

	liballoc_unlock();
}


extern "C" void rfree(void* __addr)
{
	free(__addr);
}


extern "C" void* calloc(size_t nobj, size_t size)
{
	int real_size;
	void* p;

	real_size = nobj * size;

	p = malloc(real_size);

	liballoc_memset(p, 0, real_size);

	return p;
}



extern "C" void* realloc(void* p, size_t size)
{
	void* ptr;
	struct boundary_tag* tag;
	int real_size;

	if (size == 0) {
		free(p);
		return 0;
	}
	if (p == 0) return malloc(size);

	tag = (struct boundary_tag*)((unsigned int) p - sizeof(struct boundary_tag));
	real_size = tag->size;

	if (real_size > size) real_size = size;

	ptr = malloc(size);
	liballoc_memcpy(ptr, p, real_size);
	free(p);

	return ptr;
}

#endif