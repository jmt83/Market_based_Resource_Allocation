#ifndef BID_POLICY_C
#define BID_POLICY_C

#include <stdio.h>
#include <stdlib.h>

#include "BidPolicy.h"
#include "Bid.h"
#include "BiddingSystemValues.h"

extern BiddingSystemValues * constants;
extern int roundRobinPrevious;

//If process has sufficient balance, then bid is valid, if bid == 0 or insufficient balance, then penalize bidder
//Called each time a bid is changed
int validateBid(Bid * bid){
	if(bid->value >= constants->minBid && bid->value <= constants->maxBid && bid->value <= bid->balance){
		return 0;
	}
	else{
		//bid->value = constants->illegal;
		return -1;
	}
}

//Initialize bid value to -1, when value == -1, random bid wins
//Called once at Process creation
void initializeBid(Bid * bid){
	bid->value = constants->initialBid;
	bid->balance = constants->reValue;
	bid->state = 0;
}
//subtract bid from balance and set bid to -1, therefore process must update its bid during execution
//Called at each run of Process associated with bid argument
void updateBid(Bid * bid){
	//free run if process in init state
	if(bid->state == 0){
		bid->state = 1;
		return;
	}
	bid->balance = bid->balance - bid->value;
	if(bid->balance <= 0){
		bid->balance = constants->illegal;
		bid->state = 2;
	}
}
//restart all balances to initial value
//Called each time all process runs == reValue steps
void reValueBids(ProcessTable * table){
	int i;
	for(i = 0; i < table->nextProcess; i++){
		table->table[i].bid.balance = constants->reValue;
		table->table[i].bid.state = 1;
	}
}
Process *randomBidSchedule(SchedulerSystem * scheduler){
	ProcessTable * table = scheduler->processes;
	return &(table->table[rand() % table->nextProcess]);
}
Process *roundRobinSchedule(SchedulerSystem * scheduler){
	Process * current = NULL;
	int i;
	if(roundRobinPrevious >= scheduler->processes->nextProcess){
		roundRobinPrevious = 0;
	}
	for(i = roundRobinPrevious; i < scheduler->processes->nextProcess; i++){
		current = &scheduler->processes->table[i];
		if(current->ready == 1){
			roundRobinPrevious++;
			return current;
		}
	}
	for(i = 0; i <= roundRobinPrevious; i++){
		current = &scheduler->processes->table[i];
		if(current->ready == 1){
			roundRobinPrevious++;
			return current;
		}
	}
	return &scheduler->idle;
}

Process *highBidSchedule(SchedulerSystem * scheduler){
	ProcessTable * processes = scheduler->processes;
	Process * current, * highest;
	highest = (Process *)malloc(sizeof(Process));
	highest->bid.value = constants->illegal;
	highest->bid.state = 2;
	highest->id = -100;
	int i;
	int allWait = 1;
	int allBroke = 1;
	for(i = 0; i < processes->nextProcess; i++){
		current = &(processes->table[i]);
		//Process has never run
		if(current->bid.state == 0 && current->ready == 1){
			return current;
		}
		//Process is runnable
		else if(current->bid.state == 1 && current->ready == 1){
			if(current->bid.value > highest->bid.value){
				if(validateBid(&current->bid) == 0){
					highest = current;
				}
			}
		}
		if(current->ready == 1){
			allWait = 0;
		}
		if(current->bid.state == 1){
			allBroke = 0;
		}
	}
	if(allWait == 1){
		return &scheduler->idle;
	}
	else if(allBroke == 1) {
		highest = randomBidSchedule(scheduler);
		while(highest->ready == 0){
			highest = randomBidSchedule(scheduler);
		}
		return highest;
	}
	else{
		return highest;
	}
}




Process *secondHighBidSchedule(SchedulerSystem * scheduler){
	ProcessTable * processes = scheduler->processes;
	Process * current, * highest, * second;
	highest = (Process *)malloc(sizeof(Process));
	highest->bid.value = constants->illegal;
	highest->bid.state = 2;
	highest->id = -100;
	int i;
	int allWait = 1;
	int allBroke = 1;
	second = highest;
	for(i = 0; i < processes->nextProcess; i++){
		current = &(processes->table[i]);
		//Process has never run
		if(current->bid.state == 0 && current->ready == 1){
			return current;
		}
		//Process is runnable
		else if(current->bid.state == 1 && current->ready == 1){
			if(current->bid.value > highest->bid.value){
				if(validateBid(&current->bid) == 0){
					second = highest;
					highest = current;
				}
			}
		}
		if(current->ready == 1){
			allWait = 0;
		}
		if(current->bid.state == 1){
			allBroke = 0;
		}
	}
	if(allWait == 1){
		return &scheduler->idle;
	}
	else if(allBroke == 1) {
		highest = randomBidSchedule(scheduler);
		while(highest->ready == 0){
			highest = randomBidSchedule(scheduler);
		}
		return highest;
	}
	else{
		if(second->id == -100){
			return highest;
		}
		return second;
	}
}
#endif
