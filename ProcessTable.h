#ifndef PROCESS_TABLE_H

#define PROCESS_TABLE_H

#define MAX_PROCESSES 100

#include "Process.h"

typedef struct ProcessTable {
	int maxProcesses;
	int nextProcess;
	Process * table;
}ProcessTable;

Process *lookupProcessTable(ProcessTable *, int);

ProcessTable *initializeProcessTable();

void addToProcessTable(ProcessTable *, void *);

void printRunStatsProcessTable(ProcessTable *);

#endif
