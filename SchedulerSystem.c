#ifndef SCHEDULER_SYSTEM_C

#define SCHEDULER_SYSTEM_C

#include <stdio.h>
#include <stdlib.h>

#include "SchedulerSystem.h"
#include "ProcessTable.h"
#include "BiddingSystemValues.h"
#include "BiddingConstants.h"
#include "Bid.h"
#include "Process.h"
#include "BidPolicy.h"
#include "TestProcess.h"

void initializeSchedulerSystem(SchedulerSystem * scheduler){
	scheduler->processes = initializeProcessTable();
	initializeProcess(&scheduler->idle, -1);
	scheduler->idle.function = &idle;
	scheduler->runs = 0;
	scheduler->time = 0;
	scheduler->idle.ready = 1;
	initializeBiddingSystemValues(&scheduler->systemBidValues, STEPS_TO_REVALUE, MAX_BID, MIN_BID, MAX_VALUE, MIN_VALUE, REVALUE, ILLEGAL, DEFAULT_BID);
}
void addProcessToSchedulerSystem(SchedulerSystem *scheduler, void (*function)(Bid *)){
	scheduler->processes->table[scheduler->processes->nextProcess].function = function;
	initializeBid(&(scheduler->processes->table[scheduler->processes->nextProcess].bid));
	scheduler->processes->table[scheduler->processes->nextProcess].ready = 1;
	scheduler->processes->nextProcess++;
	if(scheduler->processes->maxProcesses == scheduler->processes->nextProcess){
		printf("ProcessTable is full\n");
	}
}
void incrementSchedulerSystemStats(SchedulerSystem * scheduler){
	scheduler->runs++;
	scheduler->time++;
	if(scheduler->runs >= scheduler->systemBidValues.stepsToRevalue){
		//printf("--------------------REVALUE-----------------------");
		reValueBids(scheduler->processes);
		scheduler->runs = 0;
	}
}
//run function to choose process to run, remove from list of ready processes
Process *schedule(SchedulerSystem * scheduler){
	Process * toRun = (*scheduler->function)(scheduler);
	if(toRun == NULL || toRun->id < 0){
		toRun = &scheduler->idle;
	}
	else{
		toRun->ready = 0;
		updateBid(&(toRun->bid));
	}
	//printf("Scheduling %d bid of %d balance %d\n", toRun->id, toRun->bid.value, toRun->bid.balance);
	incrementSchedulerSystemStats(scheduler);
	return toRun;
}
void reListProcessInSchedulerSystem(SchedulerSystem * scheduler, Process * process){
	process->ready = 1;
}

#endif

