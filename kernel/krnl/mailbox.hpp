#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef struct Mailbox
{
	void* item;
	int items;
};

Mailbox* mbox KeMailboxCreate();
bool KeMailboxTryPost(Mailbox* mbox, void* item);
void KeMailboxPost(Mailbox* mbox, void* item);
bool KeMailboxTryGet(Mailbox* mbox, void** item);
void KeMailboxGet(Mailbox* mbox, void** item);
void KeMailboxDestroy(Mailbox* mbox);