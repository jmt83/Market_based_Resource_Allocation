#ifndef PROCESS_C

#define PROCESS_C

#include <stdio.h>

#include "Process.h"
#include "BidPolicy.h"

void initializeProcess(Process * process, int id){
	initializeBid(&process->bid);
	process->id = id;
	process->runCount = 0;
	process->lastRun = 0;
	process->waitTime = 0;
	process->ready = 0;
	process->function = NULL;
}
void printRunStatsProcess(Process * process){
	printf("ID: %d Runs: %d bid: %d waitTime: %d Avg Wait: %f\n", process->id, process->runCount, process->bid.value, process->waitTime, (double)process->waitTime / (double)process->runCount);
}


#endif
