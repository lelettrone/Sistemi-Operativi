#include "header.h"

int main(){

	srand(getpid());

	int i, pid = getpid();

	int mr_key = ftok(".", 'r'); //request
	int ma_key = ftok(".", 'a'); //answer

	int mr_id = msgget(mr_key, IPC_CREAT|0664);
	int ma_id = msgget(ma_key, IPC_CREAT|0664);

	msgClient m;
	m.type = pid;

	for(i=0;i<5;i++){
		m.val1 = rand() % 11;
		m.val2 = rand() % 11;
		
		msgsnd(mr_id, (void*)&m, sizeof(msgClient)-sizeof(long), 0);

		printf("[%d CLIENT-> SEND: %d, %d]\n", getpid(), m.val1, m.val2);
		
       	msgrcv(ma_id, (void*)&m, sizeof(msgClient)-sizeof(long), pid,
                      0);
       	printf("[%d CLIENT-> REC: %d]\n", getpid(), m.val1);
       	//in val1 client riceve il prodotto
		sleep(1);
	}

	exit(0);
}