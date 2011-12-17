//Main function of the simulator

#include <stdio.h>

#include "SchedulerSystem.h"
#include "TestProcess.h"
#include "Cpu.h"
#include "ProcessTable.h"
#include "BiddingSystemValues.h"
#include "BidPolicy.h"

#include <pthread.h>
#include <time.h>
#include <stdlib.h>

#define NUMBER_OF_CPU 4
//declare these so they can be externed to others
SchedulerSystem scheduler;
BiddingSystemValues * constants = &(scheduler.systemBidValues);
CPU cpu[NUMBER_OF_CPU];
int roundRobinPrevious;

int main() {
	int i;
	void * status;
	//Initialize and add all processes
	srand(time(NULL));
	roundRobinPrevious = 0;
	initializeSchedulerSystem(&scheduler);
	addProcessToSchedulerSystem(&scheduler, &maxBid);
	addProcessToSchedulerSystem(&scheduler, &minBid);
	addProcessToSchedulerSystem(&scheduler, &avgBid);
	addProcessToSchedulerSystem(&scheduler, &maxBid);
	addProcessToSchedulerSystem(&scheduler, &minBid);
	addProcessToSchedulerSystem(&scheduler, &avgBid);
	addProcessToSchedulerSystem(&scheduler, &randomBid);
	addProcessToSchedulerSystem(&scheduler, &randomBid);
	//Pick scheduling algorithm, all are found in BidPolicy.h
	scheduler.function = &secondHighBidSchedule;
	for(i = 0; i < NUMBER_OF_CPU; i++){
		cpu[i].id = i;
		cpu[i].scheduler = &scheduler;
	}
	//Start each CPU thread
	for(i = 0; i < NUMBER_OF_CPU; i++){
		//printf("initialize CPU %d\n", i);
		initializeCPU(&cpu[i]);
	}
	//Join to all CPU threads
	for(i = 0; i < NUMBER_OF_CPU; i++){
		pthread_join(cpu[i].execution, &status);
	}
	while(1){	
	}
	return 0;
}
