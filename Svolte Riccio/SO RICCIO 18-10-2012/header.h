#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>

#define SIZEOUT sizeof(msgOUT)-sizeof(long)
#define SIZEIN sizeof(msgIN)-sizeof(long)

typedef struct{
	long type;
	int v[8];
}msgOUT; //trasmette a,b,c,d ecc

typedef struct{
	long type;
	int i;
	int r;
}msgIN; //trasmette r

