#include "header.h"


int main(){

	int id_cc = shmget(IPC_PRIVATE,sizeof(CodCirc), IPC_CREAT|0664);
	CodCirc* cc = (CodCirc*)shmat(id_cc, NULL, NULL);
	init_CodCirc(cc);
	int i;
	int pid;

	for(i=0;i<6;i++){

		pid = fork();
		if(pid==0){

			if(i==0){
				//printf("SCHEDULER\n");
				int k;
				int* hd = (int*)malloc(sizeof(int)*20);
				int lastPi = 0;
				for(k=0;k<25;k++){
					printf("FIGLIO %p\n", (void*)cc);
					pop_CodCirc(cc, hd, &lastPi);
					printf("K: %d\n", k);
				}
				
				exit(0);
			}else if(i>=1){
				//printf("UTENTE\n");
				printf("FIGLIO %p\n", (void*)cc);
				push_CodCirc(cc);
				push_CodCirc(cc);
				push_CodCirc(cc);
				push_CodCirc(cc);
				push_CodCirc(cc);
				exit(0);
			}
			
		}

	}

	for(i=0;i<6;i++){
		wait(NULL);
	}
	
	exit(0);
}