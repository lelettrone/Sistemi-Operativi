#include "header.h"

void* prod(void* p){
	//printf("[PRODUTTORE %d]\n", syscall(__NR_gettid));
	GestioneIO* g = (GestioneIO*)p;
	int i = 0;
	Buffer b;
	b.indirizzo = 1 + rand()%11;
	b.dato = 1 + rand()%11;
	for(i=0;i<3;i++){
		Produci(g, &b);
		sleep(1);
		b.indirizzo++;
		b.dato++;
	}
	
	pthread_exit(0);
}

void* cons(void* p){
	//printf("[CONSUMATORE %d]\n", syscall(__NR_gettid));
	GestioneIO* g = (GestioneIO*)p;
	int i = 0;
	Buffer b;

	for(i=0;i<4;i++){
		while( Consuma(g, &b) == 0){//finchè è pieno
			sleep(3);
		}
	}

	pthread_exit(0);
}

void Inizializza(GestioneIO * g){
	pthread_mutex_init(&g->mutex, NULL);
	pthread_cond_init(&g->ok_prod, NULL);
	g->coda = 0;
	g->testa = 0;
	g->nElem = 0;
}

void Produci(GestioneIO * g, Buffer * b){
	pthread_mutex_lock(&g->mutex);
	while(g->nElem == 10){
		pthread_cond_wait(&g->ok_prod, &g->mutex);
	}
	//QUALCUNO MI HA SCETATO, 
	//C'È POSTO POSSO PRODURRE, HO ANCHE IL MUTEX
	printf("[%d->PRODUCO IN %d]\n", syscall(__NR_gettid), g->coda);
	g->vettore[g->coda] = *b;
	g->nElem++;
	g->coda = (g->coda+1)%10;
	pthread_mutex_unlock(&g->mutex);
}

int Consuma(GestioneIO * g, Buffer * b){
	int k = 1;
	pthread_mutex_lock(&g->mutex);
	if(g->nElem >= 1){
		k = 0;
		printf("[%d->CONSUMO DA %d]\n", syscall(__NR_gettid), g->testa);
		*b = g->vettore[g->testa];
		g->testa = (g->testa+1)%10;
		g->nElem--;
	}else{
		printf("[%d->BUFFER VUOTO]\n", syscall(__NR_gettid));
	}

	pthread_cond_signal(&g->ok_prod);
	//ho liberato un posto, quindi
	//un produttore può essere risvegliato
	pthread_mutex_unlock(&g->mutex);

	return k;
}