#ifndef BIDDING_SYSTEM_VALUES_C

#define BIDDING_SYSTEM_VALUES_C

#include <stdlib.h>
#include <stdio.h>

#include "BiddingSystemValues.h"

void initializeBiddingSystemValues(BiddingSystemValues * vals, int steps, int maxbid, int minbid, int maxvalue, int minvalue, int revalue, int illegal, int defaultBid){
	vals->stepsToRevalue = steps;
	vals->maxBid = maxbid;
	vals->minBid = minbid;
	vals->maxValue = maxvalue;
	vals->minValue = minvalue;
	vals->reValue = revalue;
	vals->illegal = illegal;
	vals->defaultBid = defaultBid;
};

void copyBiddingSystemValues(BiddingSystemValues * system, BiddingSystemValues * vals){
	vals->stepsToRevalue = system->stepsToRevalue;
	vals->maxBid = system->maxBid;
	vals->minBid = system->minBid;
	vals->maxValue = system->maxValue;
	vals->minValue = system->minValue;
	vals->reValue = system->reValue;
	vals->illegal = system->illegal;
	vals->defaultBid = system->defaultBid;
}

#endif
