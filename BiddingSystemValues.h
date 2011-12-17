#ifndef BIDDING_SYSTEM_VALUES_H

#define BIDDING_SYSTEM_VALUES_H

typedef struct BiddingSystemValues {
	int stepsToRevalue;
	int maxBid;
	int minBid;
	int maxValue;
	int minValue;
	int reValue;
	int illegal;
	int initialBid;
	int defaultBid;
} BiddingSystemValues;

void initializeBiddingSystemValues(BiddingSystemValues*, int, int, int, int, int, int, int, int);

void copyBiddingSystemValues(BiddingSystemValues *, BiddingSystemValues *);

#endif
