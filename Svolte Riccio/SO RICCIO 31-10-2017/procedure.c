#include "header.h"

void _signal(int sem_id, int n){

	struct sembuf sops;
	sops.sem_num = n;  /* semaphore number */
    sops.sem_op = 1;   /* semaphore operation */
    sops.sem_flg = NULL;  /* operation flags */

	semop(sem_id, &sops, 1);

}

void _wait(int sem_id, int n){

	struct sembuf sops;
	sops.sem_num = n;  /* semaphore number */
    sops.sem_op = -1;   /* semaphore operation */
    sops.sem_flg = NULL;  /* operation flags */

	semop(sem_id, &sops, 1);

}

void client(int mail_id){
	printf("CLIENT %d\n", getpid());
	int i;
	msg m;
	m.type = 1;

	for(i=0;i<9;i++){
		m.val = 1+rand()%10;
		msgsnd(mail_id,(void*)&m, SIZEMESS, 0);
		printf("CLIENT %d-> SND: %d\n", getpid(), m.val);
		sleep(2);
	}
	
}

void slave(int mail_id, buff *b, int sem_id){
	int i;
	printf("SLAVE %d\n", getpid());
	msg m;
	for(i=0;i<3;i++){
		msgrcv(mail_id, (void*)&m,SIZEMESS,1,
                      0); //BLOCCANTE
		printf("SLAVE %d-> RCV: %d\n", getpid(), m.val);

		_wait(sem_id, MUTEX);
		while(b->nElem == 1){ // E' PIENO
			//printf()
			_signal(sem_id, MUTEX);
			_wait(sem_id, PROD_COND);
			_wait(sem_id, MUTEX);
		}
		//TENEMOS MUTEX, POSSO SCRIVERE
		b->nElem++;
		b->val = m.val;
		printf("SLAVE %d-> SETBUFF: %d\n", getpid(), b->val);
		_signal(sem_id, CONS_COND); // SCETO UN CONSUMATORE
		_signal(sem_id, MUTEX);

	}
}
 // COMSUMA : 3
 // PRODUCI : 4
 // nElem : 0

void master(buff *b, int sem_id){
	int i;
	printf("MASTER %d\n", getpid());
	msg m;
	int val;
	for(i=0;i<9;i++){

		_wait(sem_id, MUTEX);
		while(b->nElem==0){ // E' VUOTO
			_signal(sem_id, MUTEX);
			_wait(sem_id, CONS_COND);
			_wait(sem_id, MUTEX);
		}
		//TENEMOS MUTEX, POSSO CONSUMARE
		b->nElem--;
		val = b->val;
		printf("MASTER %d-> GETBUFF: %d\n", getpid(), val);
		_signal(sem_id, PROD_COND);
		_signal(sem_id, MUTEX);


	}

}