#ifndef BID_POLICY_H

#define BID_POLICY_H

#include "Bid.h"
#include "SchedulerSystem.h"
#include "ProcessTable.h"

int validateBid(Bid *);
void initializeBid(Bid *);
void updateBid(Bid *);
void reValueBids(ProcessTable *);
Process * highBidSchedule(SchedulerSystem *);
Process * secondHighBidSchedule(SchedulerSystem *);
Process * randomBidSchedule(SchedulerSystem *);
Process * roundRobinSchedule(SchedulerSystem *);
#endif
