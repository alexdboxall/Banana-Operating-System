#ifndef SGTTY_H_
#define SGTTY_H_

struct sgttyb
{
	char sg_ispeed;
	char sg_ospeed;
	char sg_erase;
	char sg_kill;
	int sg_flags;

};

int gtty(int filedes, struct sgttyb* attributes);
int stty(int filedes, struct sgttyb* attributes);

#endif