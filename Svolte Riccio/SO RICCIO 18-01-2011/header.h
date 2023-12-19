#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>

#define TYPE_ALL 0
#define TYPE_CLIENT 100

#define TYPE_SERVER1 1
#define TYPE_SERVER2 2
#define TYPE_SERVER3 3

typedef struct{
	long type;
	int value;
}msgbuf;

void client(int mailcb_id);
void server(int mailbs_id, int type);
void balancer(int mailcb_id ,int mailbs_id);