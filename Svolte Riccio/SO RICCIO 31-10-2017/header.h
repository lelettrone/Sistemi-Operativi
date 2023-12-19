#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/shm.h>

#define SIZEMESS sizeof(msg)-sizeof(long)
#define MUTEX 0
#define CONS_COND 1
#define PROD_COND 2
typedef struct{
	int val;
	int nElem;
}buff;

typedef struct{
	long type;
	int val;
}msg;

void _signal(int sem_id, int n);
void _wait(int sem_id, int n);
void client(int mail_id);
void slave(int mail_id, buff *b, int sem_id);
void master(buff *b, int sem_id);
