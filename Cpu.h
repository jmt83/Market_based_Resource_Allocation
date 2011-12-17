#ifndef CPU_H

#define CPU_H

#include "Process.h"
#include "SchedulerSystem.h"

#include <pthread.h>

typedef struct CPU {
	pthread_t execution;
	SchedulerSystem * scheduler;
	int id;
}CPU;

void run(CPU *, Process *);
void *startCPU(void *);

#endif
