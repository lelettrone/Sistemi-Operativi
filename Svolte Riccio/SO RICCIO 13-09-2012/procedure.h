#include "monitor.h"
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>

#define COND_CONS 0
#define COND_LOW_PROD 1
#define COND_HIGH_PROD 2
typedef struct{
	int buffer[3];

	int nElem;
	int testa;
	int coda;
	Monitor m;
}PriorityProdCons;