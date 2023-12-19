#include "header.h"


void* viaggiatore(void *p){
	box *b = (box*)p;
	monitor_treno *m = (monitor_treno*)b->m;
	int i = 0;
	
	for(i=0;i<3;i++){
		printf("LEGGO{TH: %d ->TRENO: %d, STAZIONE: %d}\n",syscall(__NR_gettid),b->nTreno,leggi_stazione(m));
		sleep(1+rand()%6);
	}
}
int leggi_stazione(monitor_treno * m){

	pthread_mutex_lock(&m->mutex);
	
	while(m->nCapi>=1 /*|| m->nViagg>=1*/){//COMMENTATO PERCHÈ I VIAGG(LETTORI)
											//Possono accedere insieme
		m->nViaggWait++;
		pthread_cond_wait(&m->cond_lett, &m->mutex);
		m->nViaggWait--;
	}
	m->nViagg++;
	pthread_mutex_unlock(&m->mutex);

	int k = m->stazione;



	pthread_mutex_lock(&m->mutex);

	m->nViagg--;
	if(m->nViagg==0){//se sono l'ultimo lettore
		pthread_cond_broadcast(&m->cond_capi); //sceto tutti i capi //anche se ne è solo 1
	}
	pthread_mutex_unlock(&m->mutex);
	
	return k;

}

void* capotreno(void *p){
	box *b = (box*)p;
	monitor_treno *m = (monitor_treno*)b->m;
	int i = 0;
	
	for(i=0;i<10;i++){
		scrivi_stazione(m, i);
		printf("SCRIVO{TH:%d->TRENO: %d, STAZIONE: %d}\n",syscall(__NR_gettid),b->nTreno,i);
		sleep(3);

	}

}
void scrivi_stazione(monitor_treno * m, int stazione){
	pthread_mutex_lock(&m->mutex);
	while(m->nViagg>=1 || m->nCapi>=1){ //se ci sono lettori, mi waito
										//oppure se ci sono altri capi, ma in questo caso è solo 1, si potrebbe levare
		m->nCapiWait++;
		pthread_cond_wait(&m->cond_capi, &m->mutex);
		m->nCapiWait--;
	}
	m->nCapi++;
	pthread_mutex_unlock(&m->mutex);
	//posso anche rilasciare il lock, tanto nCapi>=1,
	//sia altri Capi che Viaggiatori NON ENTRANO 
	m->stazione = stazione;

	pthread_mutex_lock(&m->mutex);
	m->nCapi--;
	pthread_cond_broadcast(&m->cond_lett);
	pthread_mutex_unlock(&m->mutex);
	
	
}



void inizializza(monitor_treno* m){
	m->nCapiWait = 0;
	m->nViaggWait = 0;
	m->stazione = 0;
	pthread_mutex_init(&m->mutex, NULL);
	pthread_cond_init(&m->cond_capi, NULL);
	pthread_cond_init(&m->cond_lett, NULL);
}
void rimuovi(monitor_treno * m){
	m->nCapiWait = 0;
	m->nViaggWait = 0;
	m->stazione = 0;
	pthread_mutex_destroy(&m->mutex);
	pthread_cond_destroy(&m->cond_capi);
	pthread_cond_destroy(&m->cond_lett);
}
