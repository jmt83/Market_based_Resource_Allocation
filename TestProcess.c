//All user processes, each receives a bid struct, which can be edited through Bidding.h

#ifndef TEST_PROCESS_C

#define TEST_PROCESS_C

#include "TestProcess.h"

#include "Bidding.h"

#include <time.h>

#include <stdio.h>
void idle(Bid * bid){
	setBid(bid, -1);
}
void maxBid(Bid * bid){
	setBid(bid, 255);
//	printf("Bidding the max\n");
}
void minBid(Bid * bid){
	setBid(bid, 1);
//	printf("Bid the min\n");
}
void avgBid(Bid * bid){
	setBid(bid, 128);
//	printf("bid the average\n");
}
void randomBid(Bid * bid){
	srand(time(NULL));
	setBid(bid, rand() % 256);
}
#endif
