#include "header.h"

int main(){
	int i;
	int pid;

	srand(time(0));

	int id_meteo = shmget(IPC_PRIVATE, sizeof(meteo), IPC_CREAT|0664);
	meteo *pmeteo = (meteo*)shmat(id_meteo, NULL, NULL);

	init_monitor(&pmeteo->monitor, 2);

	pmeteo->temperatura = 0;
	pmeteo->umidita = 0;
	pmeteo->pioggia = 0;

	pmeteo->nScritt = 0;
	pmeteo->nLett = 0;

	for(i=0;i<11;i++){
		pid = fork();
		if(pid==0){
			if(i>=1){//lett
				for(i=0;i<10;i++){
					L(pmeteo);
					sleep(1);
				}
				exit(0);
			}else if(i==0){//scritt
				for(i=0;i<20;i++){
					M(pmeteo);
					sleep(2);
				}
				exit(0);
			}
		}
		
	}


	for(i=0;i<11;i++){
		wait(NULL);
	}
	remove_monitor(&pmeteo->monitor);
	exit(0);
}