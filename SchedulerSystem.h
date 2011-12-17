#ifndef SCHEDULER_SYSTEM_H
#define SCHEDULER_SYSTEM_H

#include "Bid.h"
#include "ProcessTable.h"

typedef struct SchedulerSystem {
	int runs;
	int time;
	ProcessTable * processes;
	Process idle;
	BiddingSystemValues systemBidValues;
	Process *(*function)(struct SchedulerSystem *);
}SchedulerSystem;

void initializeSchedulerSystem(SchedulerSystem *);

void addProcessToSchedulerSystem(SchedulerSystem *, void (*)(Bid*));

Process *schedule(SchedulerSystem *);

void reListProcessInSchedulerSystem(SchedulerSystem *, Process *);


#endif
