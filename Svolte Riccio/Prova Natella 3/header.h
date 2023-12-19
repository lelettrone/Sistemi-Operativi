#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

#define MSIZE sizeof(msg)-sizeof(long)
#define ASIZE sizeof(ack)-sizeof(long)
typedef struct{
	long type;
}msg;

typedef struct{
	long type;
}ack;
