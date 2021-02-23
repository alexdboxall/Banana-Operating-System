#ifndef __LINKED_LIST_HPP__
#define __LINKED_LIST_HPP__

#include <stdint.h>
#include "dbg/kconsole.hpp"

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
	}

	void removeFirst()
	{
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