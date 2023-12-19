#include "header.h"

//STARVATION DI ENTRAMBI


void M(meteo *pmeteo){

	enter_monitor(&pmeteo->monitor);

	while(pmeteo->nLett >= 1 || pmeteo->nScritt >= 1){
		//pmeteo->nScritWait++;
		wait_condition(&pmeteo->monitor, OK_M);
		//pmeteo->nScritWait--;
		//ill num di gente che wait, la mantiene il monitor
		//in questo caso dei processi
	}

	pmeteo->nScritt++;

	leave_monitor(&pmeteo->monitor);

	pmeteo->temperatura = (0 + rand()%101) - 50;
	pmeteo->umidita = 0 + rand()%101;
	pmeteo->pioggia = 0 + rand()%1;

	enter_monitor(&pmeteo->monitor);

	

	printf("[SCRIVO %d -> %d, %d, %d]\n", getpid(), 
			pmeteo->temperatura, pmeteo->umidita, pmeteo->pioggia);

	pmeteo->nScritt--;

	/*if(queue_condition(&pmeteo->monitor, OK_M) >= 1){	//se ci sono scirtt in wait
		signal_condition(&pmeteo->monitor, OK_M);
	}else{*/
		int i = 0;
		int nLettWait = queue_condition(&pmeteo->monitor, OK_L);
		for(i=0;i<nLettWait;i++){
			signal_condition(&pmeteo->monitor, OK_L);
		}
	//}
	leave_monitor(&pmeteo->monitor);

}

void L(meteo *pmeteo){
	enter_monitor(&pmeteo->monitor);

	while(pmeteo->nScritt >= 1){
		//pmeteo->nLettWait++;
		wait_condition(&pmeteo->monitor, OK_L);
		//pmeteo->nLettWait--;
		//ill num di gente che wait, la mantiene il monitor
		//in questo caso dei processi
	}

	pmeteo->nLett++;

	leave_monitor(&pmeteo->monitor);


	enter_monitor(&pmeteo->monitor);
	
	printf("[LEGGO %d -> %d, %d, %d]\n", getpid(), 
			pmeteo->temperatura, pmeteo->umidita, pmeteo->pioggia);

	pmeteo->nLett--;

	if(pmeteo->nLett == 0){	//se dentro non ci sono altri lettori
		int i = 0;
		int nScrittWait = queue_condition(&pmeteo->monitor, OK_M);
		for(i=0;i<nScrittWait;i++){
			signal_condition(&pmeteo->monitor, OK_M);
		}
	}
	leave_monitor(&pmeteo->monitor);
	
}