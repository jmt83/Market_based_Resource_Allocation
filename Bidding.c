#ifndef BIDDING_C
#define BIDDING_C

#include <stdio.h>

#include "Bid.h"

#include "SchedulerSystem.h"

#include"BidPolicy.h"

extern SchedulerSystem scheduler;

//GetCurrent bid's balance
int getBalance(Bid * bid){
	return bid->balance;
}
//Set current processes bid
int setBid(Bid * bid, int value){
	bid->value = value;
	return validateBid(bid);
}


#endif
