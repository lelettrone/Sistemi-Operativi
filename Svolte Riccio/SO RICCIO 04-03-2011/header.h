#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>

#define SMSG sizeof(msgbuf)-sizeof(long)
typedef struct{
	long type;
	int val1;
	int val2;
}msgbuf;

typedef struct{
	msgbuf msg;
	int amail_id;
}box;

void client(int, int);
void server(int, int);
void *thr(void*);