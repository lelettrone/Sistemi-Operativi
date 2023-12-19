#include "header.h"


void snd(int rts_id, int ots_id){
	ack a;
	a.type = 1;
	msgsnd(rts_id, (void*)&a, ASIZE, 0);
	msgrcv(ots_id, (void*)&a, ASIZE, 0, 0);
}

void rcv(int rts_id, int ots_id){
	ack a;
	a.type = 1;
	msgrcv(rts_id, (void*)&a, ASIZE, 0, 0);
	msgsnd(ots_id, (void*)&a, ASIZE, 0);
	
}