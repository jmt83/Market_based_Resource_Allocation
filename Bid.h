/*
	Each Process has a Bid structure within it. The process is given it's process ID at creation and this is used to get and set bid value and balance.
*/

#ifndef BID_H

#define BID_H

#include "BiddingSystemValues.h"

typedef struct Bid {
	int value;
	int balance;
	int state;
}Bid;

#endif
