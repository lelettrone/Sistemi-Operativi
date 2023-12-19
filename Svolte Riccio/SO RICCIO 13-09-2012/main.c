#include "procedure.h"
#include "monitor.h"

int main(){

	printf("A\n");
	key_t id_shm = 
		shmget(IPC_PRIVATE,sizeof(PriorityProdCons),IPC_CREAT|0664);
	PriorityProdCons* ppc = (PriorityProdCons*)shmat(id_shm, NULL, 0);

	printf("B\n");	
	inizializza_prod_cons(ppc);

	int i = 0;
	int k = 0;
	int pid;
	for(i=0;i<5;i++){
		pid = fork();

		if(pid==0){

			if(i==0){
				//printf("FIGLIO HIGH\n");
				srand(time(0));
				for(k=0;k<3;k++){
					produci_alta_prio(ppc);
					sleep(2);
				}
				exit(0);
			}else if(i>=1 && i<=3){
				//printf("FIGLIO LOW\n");
				srand(time(0));
				for(k=0;k<3;k++){
					produci_bassa_prio(ppc);
					sleep(1);
				}
				exit(0);
			}else if(i==4){
				//printf("FIGLIO CONSU\n");
				srand(time(0));
				for(k=0;k<12;k++){
					consuma(ppc);
					sleep(1);
				}
				exit(0);
			}

		}
	}

	for(i=0;i<5;i++){
		wait(NULL);
		//printf("MORTO FIGLIO\n");
	}

	rimuovi_prod_cons(ppc);

	exit(0);
}