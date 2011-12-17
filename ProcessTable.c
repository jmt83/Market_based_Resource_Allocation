#ifndef PROCESS_TABLE_C

#define PROCESS_TABLE_C

#include "ProcessTable.h"

#include "Process.h"

#include <stdlib.h>
#include <stdio.h>

void printRunStatsProcessTable(ProcessTable * table){
	int i;
	for(i = 0; i < table->nextProcess; i++){
		printf("\t");
		printRunStatsProcess(&table->table[i]);
	}
}

Process *lookupProcessTable(ProcessTable * table, int processID){
	return &table->table[processID];
}

ProcessTable *initializeProcessTable(){
	int i;
	ProcessTable * table;
	table = (ProcessTable *)malloc(sizeof(ProcessTable));
	table->maxProcesses = MAX_PROCESSES;
	table->nextProcess = 0;
	table->table = (Process *)malloc(sizeof(Process) * table->maxProcesses);
	for(i = 0; i < table->maxProcesses; i++){
		initializeProcess(&table->table[i], i);
	}
	return table;
}

void addToProcessTable(ProcessTable * table, void * function){
	table->table[table->nextProcess].function = function;
	table->nextProcess++;
}
#endif
