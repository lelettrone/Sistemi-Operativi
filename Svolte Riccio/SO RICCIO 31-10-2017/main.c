#include "header.h"

int main(){
	srand(time(NULL));
	int pid, i;
	int mail_id = msgget(IPC_PRIVATE, IPC_CREAT|0664);
	int sem_id = semget(IPC_PRIVATE, 3, IPC_CREAT|0664);
	int shm_id = shmget(IPC_PRIVATE, sizeof(buff), IPC_CREAT|0664);

	buff *b = (buff*)shmat(shm_id, NULL, NULL);
	b->val = 0;
	b->nElem = 0;

	semctl(sem_id, MUTEX, SETVAL, 1);
	semctl(sem_id, CONS_COND, SETVAL, 0);
	semctl(sem_id, PROD_COND, SETVAL, 1);

	for(i=0;i<5;i++){
		pid = fork();
		if(pid==0){
			if(i==0){
				master(b, sem_id);
				exit(0);
			}else if(i>=1 && i<=3){
				slave(mail_id,b, sem_id);
				exit(0);
			}else if(i==4){
				client(mail_id);
				exit(0);
			}
		}
	}

	for(i=0;i<5;i++){
		wait(NULL);
	}
	msgctl(mail_id, IPC_RMID, NULL);
	semctl(sem_id, 0, IPC_RMID);
	shmctl(shm_id, IPC_RMID, NULL);
	exit(0);
}