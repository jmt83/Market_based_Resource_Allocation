#ifndef CPU_C

#define CPU_C

#include "Cpu.h"

#include"SchedulerSystem.h"

#include "Process.h"

#include <pthread.h>
#include <stdio.h>

void run(CPU * cpu, Process * process){
	if(process != NULL){
		process->runCount++;
		process->waitTime += cpu->scheduler->time - process->lastRun;
		process->lastRun = cpu->scheduler->time;
		(*process->function)(&(process->bid));
	}
}

void initializeCPU(CPU * cpu){
	pthread_create(&(cpu->execution), NULL, startCPU, (void *)cpu);
}

void *startCPU(void * threadArg){
	CPU * cpu = (CPU *)threadArg;
	int running = 0;
	Process * current;
	current = schedule(cpu->scheduler);
	while(1){
		running++;
		if(running == 1000000){
			printf("CPU: %d\n", cpu->id);
			printRunStatsProcessTable(cpu->scheduler->processes);
			running = 0;
		}
		run(cpu, current);
		reListProcessInSchedulerSystem(cpu->scheduler, current);
		current = schedule(cpu->scheduler);
	}
	pthread_exit(NULL);
}

#endif
