#include "header.h"

void client(int rmail_id, int amail_id){
	srand(getpid());

	int i, pid = getpid();
	msgbuf bR;
	msgbuf bS;
	bS.type = pid;
	for(i=0;i<5;i++){
		bS.val1 = rand()%101;
		bS.val2 = rand()%101;

		msgsnd(rmail_id, (void*)&bS, SMSG, 0); //MESS DI TERMINAZIONE
		printf("[CLIENT %d: SND: %d, %d, PID: %d]\n", pid, bS.val1, bS.val2, bS.type);
		msgrcv(amail_id, (void*)&bR, SMSG, pid, 0);
		printf("[CLIENT %d: RCV: %d]\n",pid,  bR.val1);

	}
}

void server(int rmail_id, int amail_id){
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	int i, pid = getpid();

	msgbuf bR;
	pthread_t t;
	
	while(1){
		msgrcv(rmail_id, (void*)&bR, SMSG, 0, 0);
		printf("[SERVER %d: RCV: %d, %d, PID: %d]\n", pid, bR.val1, bR.val2, bR.type);
		if(bR.val1==-1 && bR.val2==-1)break;
		box *bx = (box*)malloc(sizeof(box));
		bx->amail_id = amail_id;
		bx->msg = bR;
		if(pthread_create(&t, &attr, thr, (void*)bx)!=0){
			printf("ERRORE THREAD\n");

		}
	}
	pthread_attr_destroy(&attr);
	exit(0);
}

void *thr(void *p){
	box *bx = (box*)p;
	msgbuf b = bx->msg;
	int amail_id = bx->amail_id;
	int sum = b.val1 + b.val2;
	b.val1 = sum;
	msgsnd(amail_id, (void*)&b, SMSG, 0); //MESS DI TERMINAZIONE
	printf("[THREAD: SND: %d, PID: %d]\n", b.val1, b.type);
	free(bx);
	pthread_exit(0);
}