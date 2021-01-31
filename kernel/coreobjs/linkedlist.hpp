#ifndef __LINKED_LIST_HPP__
#define __LINKED_LIST_HPP__

#include <stdint.h>

extern void kputs(const char* c);
extern void kprintf(const char* c, ...);

template <class T>
class LinkedList
{
private:

protected:
	T* first = nullptr;
	T* last = nullptr;
	int debugLength = 0;

public:
	LinkedList()
	{
		first = nullptr;
		last = nullptr;
		debugLength = 0;
		kprintf("L.L. CONSTRUCTOR CALLED\n");
	}

	~LinkedList()
	{

	}

	T* getNext(T* start)
	{
		return start->next;
	}

	/*
	
	NOTICE: VERY BAD STUFF HAPPENS IF YOU TRY TO ADD AN ITEM WHICH IS ALREADY IN THE LIST, AS THE ->next POINTER WILL BE THE SAME!!!!
	
	*/


	void addElement(T* element)
	{
		extern void panic(const char* p);
		//lock.lock();

		//kprintf("Adding element 0x%X to list 0x%X\n", element, this);

#ifdef KERNEL_DEBUG
		//SHOULD ONLY BE USED FOR DEBUGGING, AS IT ITERATES OVER THE LIST
		if (1) {
			T* f = getFirstElement();
			while (f) {
				//kprintf("Existing element: 0x%X\n", f);
				if (f == element) {
					kprintf("ERROR: ALREADY ON LIST");
					//return;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wframe-address"
					/*kprintf("A '0x%X'\n", __builtin_return_address(0));
					kprintf("B '0x%X'\n", __builtin_return_address(1));
					kprintf("C '0x%X'\n", __builtin_return_address(2));
					kprintf("D '0x%X'\n", __builtin_return_address(3));*/

#pragma GCC diagnostic pop

					panic("ELEMENT ALREADY ON LIST");
				}
				f = getNext(f);
			}
		}
#endif

		if (element == nullptr) {
			panic("Null element added to linked list");
		}

		if (first && last) {
			last->next = element;
			last = element;
			last->next = nullptr;

		} else if (first == nullptr && last == nullptr) {
			first = element;
			last = element;
			last->next = nullptr;		//it took me until the 5th of September 2020 to add this line!

			if (debugLength != 0) {
				panic("Whoa... 3");
			}

		} else {
			panic("addElement");
		}

		++debugLength;

		//lock.unlock();
	}

	void removeFirst()
	{
		extern void panic(const char* p);

		//lock.lock();

		extern void panic(const char* p);

		if (first == nullptr) {
			panic("ERROR: removing from empty list...\n");
			return;
		}
		if (last->next != nullptr) {
			panic("Whoa...");
		}

		if (first->next == nullptr) {
			first = nullptr;
			last = nullptr;
			if (debugLength != 1) {
				panic("first->next == nullptr, but length = 1");
			}

		} else {
			first = first->next;
		}

		--debugLength;

		//lock.unlock();
	}

	bool isEmpty()
	{
		return first == nullptr && last == nullptr;
	}

	int getLength()
	{
		return debugLength;
	}

	T* getLastElement()
	{
		return last;
	}

	T* getFirstElement()
	{
		return first;
	}
};


#endif