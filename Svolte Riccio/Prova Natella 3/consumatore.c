#include "header.h"

int main(){
	srand(getpid());
	int m_key = ftok(".", 'm');
	int p_key = ftok(".", 'p');
	int c_key = ftok(".", 'c');

	int rts_key = ftok(".", 'r');
	int ots_key = ftok(".", 'o');

	int m_id = shmget(m_key, sizeof(int), 0);
	int p_id = msgget(p_key, 0);
	int c_id = msgget(c_key, 0);

	int rts_id = msgget(rts_key, 0);
	int ots_id = msgget(ots_key, 0);

	int *pInt = (int*)shmat(m_id, 0, 0);

	int i = 0;
	int val = 0;
	msg m;
	m.type = 1;
	for(i=0;i<5;i++){
		snd(rts_id, ots_id);
		msgsnd(p_id, (void*)&m, MSIZE, 0);
		//invio richiesta prod
		rcv(rts_id, ots_id);
		msgrcv(c_id, (void*)&m ,MSIZE,0,0);
		//ho ricevuto richiesta di cons
		val = *pInt;
		//ho consumatore
		printf("[CONSUMATORE-> GET: %d]\n", val);
		

	}

	exit(0);
}