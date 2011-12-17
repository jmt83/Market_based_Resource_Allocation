#ifndef PROCESS_H

#define PROCESS_H

#include "Bid.h"

typedef struct Process {
	Bid bid;
	int id;
	int runCount;
	int lastRun;
	int waitTime;
	int ready;
	void (*function)(Bid *);
	//void (*function)(int args, void ** argv);
} Process;

void initializeProcess(Process*, int);
void printRunStatsProcess(Process*);

#endif

