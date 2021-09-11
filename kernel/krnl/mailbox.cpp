#include <krnl/mailbox.hpp>
#include <thr/prcssthr.hpp>
#include <core/kheap.hpp>

bool KeMailboxTryPost(Mailbox* mbox, void* itm)
{
	lockScheduler();

	bool res = false;

	if (mbox->items == 0) {
		mbox->item = itm;
		mbox->items++;
		res = true;
	}

	unlockScheduler();
	return res;
}

bool KeMailboxTryGet(Mailbox* mbox, void** itm)
{
	lockScheduler();

	bool res = false;

	if (mbox->items == 1) {
		*itm = mbox->item;
		mbox->items--;
		res = true;
	}

	unlockScheduler();
	return res;
}

Mailbox* KeMailboxCreate()
{
	Mailbox* m = (Mailbox*) malloc(sizeof(Mailbox));
	m->item = 0;
	m->items = 0;
	return m;
}

void KeMailboxPost(Mailbox* mbox, void* item)
{
	bool posted = false;
	do {
		posted = KeMailboxTryPost(mbox, item);

		if (!got) {
			lockScheduler();
			schedule();
			unlockScheduler();
		}

	} while (!posted);
}

void KeMailboxGet(Mailbox* mbox, void** item)
{
	bool got = false;
	do {
		got = KeMailboxTryGet(mbox, item);

		if (!got) {
			lockScheduler();
			schedule();
			unlockScheduler();
		}

	} while (!got);
}

void KeMailboxDestroy(Mailbox* mbox)
{
	free(mbox);
}