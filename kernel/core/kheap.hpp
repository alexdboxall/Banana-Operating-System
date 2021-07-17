#ifndef _LIBALLOC_H
#define _LIBALLOC_H

#include <stddef.h>

	/** This is a boundary tag which is prepended to the
	 * page or section of a page which we have allocated. It is
	 * used to identify valid memory blocks that the
	 * application is trying to free.
	 */
	struct	boundary_tag
	{
		unsigned int magic;			//< It's a kind of ...
		unsigned int size; 			//< Requested size.
		unsigned int real_size;		//< Actual size.
		int index;					//< Location in the page table.

		struct boundary_tag* split_left;	//< Linked-list info for broken pages.	
		struct boundary_tag* split_right;	//< The same.

		struct boundary_tag* next;	//< Linked list info.
		struct boundary_tag* prev;	//< Linked list info.
	};


	extern int liballoc_lock();
	extern int liballoc_unlock();
	extern size_t liballoc_alloc(int);
	extern int liballoc_free(void*, int);

#ifdef __cplusplus
	extern "C" {
#endif

	//C definitions

	void* malloc(size_t);				//< The standard function.
	void  free(void*);					//< The standard function.
	void  rfree(void*);					//< The standard function.
	void* realloc(void*, size_t);

#ifdef __cplusplus
}
#endif

#endif