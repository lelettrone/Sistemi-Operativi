#include "header.h"


void init_CodCirc(CodCirc* cc){
	cc->testa = 0;
	cc->coda = 0;
	cc->nElem = 0;
	init_monitor(&cc->m, 2);
}
void destroy_CodCirc(CodCirc* cc){
	cc->testa = 0;
	cc->coda = 0;
	cc->nElem = 0;
	remove_monitor(&cc->m);
}

void push_CodCirc(CodCirc* cc){
	enter_monitor(&cc->m);

	if(cc->nElem==MAXSIZE){//E' HOARE
		//VADO IN WAIT

		wait_condition(&cc->m, COND_UT);
	//quandoesco dal wait, qualcuno mi ha fatto signal,
	//poichè la cond che aspettavo è diventata vera
	//e mi ha ceduto il suo posto, quindi passo da codawait
	//direttamente in exec, senza passare per la entry_set
	//QUINDI NESSUNO HA POTUTO MODIFICARE LA COND, SONO SICURO
	//CHE E' VERA
	}
	richiesta r;
	r.posizione = 0 + rand()%20;
	r.processo = getpid();
	cc->rvett[cc->coda] = r;
	cc->coda = (cc->coda+1)%MAXSIZE;
	cc->nElem++;
	printf("[HO SCRITTO pos:%d, pid:%d]\n", r.posizione, r.processo);
	signal_condition(&cc->m, COND_SC); //segnalo al CONSU
	leave_monitor(&cc->m);
}
void pop_CodCirc(CodCirc* cc, int* hd, int* lastPi){
	
	enter_monitor(&cc->m);
	if(cc->nElem==0){//E' HOARE
		//VADO IN WAIT
		wait_condition(&cc->m, COND_SC);
	//QUANDO ESCO SICURO CHE LA COND E' TRUE
	}
	richiesta r;
	r = cc->rvett[cc->testa];
	cc->testa = (cc->testa+1)%MAXSIZE;
	cc->nElem--;
	//sleep(r.posizione-*lastPi);
	hd[r.posizione] = r.processo; 
	
	printf("[PRELEVATO pos:%d, pid:%d, sl:%d]\n", r.posizione, r.processo, r.posizione-*lastPi);
	*lastPi = r.posizione;
	signal_condition(&cc->m, COND_UT); //segnalo al CONSU
	leave_monitor(&cc->m);
}

