
#include "procedure.h"
#include "monitor.h"

void inizializza_prod_cons(PriorityProdCons * p){
	printf("C\n");
	p->testa = 0;
	p->coda = 0;
	p->nElem = 0;

	init_monitor(&p->m, 3);
}
void produci_bassa_prio(PriorityProdCons * p){

	enter_monitor(&p->m);

	while(p->nElem==3 || queue_condition(&p->m, COND_HIGH_PROD)>0){ //SE QUALCUNO HA PIÙ PRIO DI ME
						  //OPPURE SE IL BUFF È FULL
		wait_condition(&p->m, COND_LOW_PROD);

	}
	//SONO QUI HO MUTEX, E POSSO SCRIVERE
	int val = 13 + rand()%13;
	p->nElem++;
	p->buffer[p->coda] = val;
	p->coda = (p->coda+1)%3; 
	printf("LOW PRODUCO: %d\n", val);
	signal_condition(&p->m, COND_CONS);
	leave_monitor(&p->m);
}

void produci_alta_prio(PriorityProdCons * p){
	enter_monitor(&p->m);

	while(p->nElem==3){ 
						  //OPPURE SE IL BUFF È FULL
		wait_condition(&p->m, COND_HIGH_PROD);

	}
	//SONO QUI HO MUTEX, E POSSO SCRIVERE
	int val = 0 + rand()%13;
	p->nElem++;
	p->buffer[p->coda] = val;
	p->coda = (p->coda+1)%3; 
printf("HIGH PRODUCO: %d\n", val);
	signal_condition(&p->m, COND_CONS);
	leave_monitor(&p->m);
}

void consuma(PriorityProdCons * p){
	enter_monitor(&p->m);

	while(p->nElem==0){ 
						  //OPPURE SE IL BUFF È FULL
		wait_condition(&p->m, COND_CONS);

	}
	//SONO QUI HO MUTEX, E POSSO LEGGERE
	p->nElem--;
	int val;
	val = p->buffer[p->testa];
	p->testa = (p->testa+1)%3; 
	printf("CONSUMO: %d\n", val);

	int h = queue_condition(&p->m, COND_HIGH_PROD);
	int l = queue_condition(&p->m, COND_LOW_PROD);
	printf("H: %d, L:%d\n",h,l);
	if(h>0){

		signal_condition(&p->m, COND_HIGH_PROD);

	}else{

		signal_condition(&p->m, COND_LOW_PROD);

	}
	

	leave_monitor(&p->m);
}


void rimuovi_prod_cons(PriorityProdCons * p){
	remove_monitor(&p->m);
}