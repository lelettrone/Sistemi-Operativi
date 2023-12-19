#include "header.h"

void inserisci(MonitorSpedizioni * m, int quantita){

	pthread_mutex_lock(&m->mutex);
	while(m->nElem==MAX){
		pthread_cond_wait(&m->cond_prod, &m->mutex);
	}
	m->ordini[m->coda] = quantita;
	m->coda = (m->coda + 1)%MAX;
	m->nElem++;
	printf("[INSERISCO %d: QNT: %d]\n",
		syscall(__NR_gettid),quantita);

	pthread_cond_signal(&m->cond_cons);
	pthread_mutex_unlock(&m->mutex);

}

int preleva(MonitorSpedizioni * m, int quantita_minima){
	int i, somma=0;
	pthread_mutex_lock(&m->mutex);
	while(!((sum(m)>=quantita_minima) || m->nElem==MAX)){
		/*printf("[PRELEVO %d: SUM: %d, NELEM: %d]\n",
		syscall(__NR_gettid),sum(m), m->nElem);*/
			pthread_cond_wait(&m->cond_cons, &m->mutex);
	}
	for(i=0;i<m->nElem;i++){
		somma+=m->ordini[m->testa];
		m->testa = (m->testa+1)%MAX;
		pthread_cond_signal(&m->cond_prod);
	}
	printf("[PRELEVO %d: SOM: %d, SIZE: %d]\n",
		syscall(__NR_gettid),somma, m->nElem);
	m->coda = m->testa;
	m->nElem=0;

	
	pthread_mutex_unlock(&m->mutex);
	return somma;
}
int sum(MonitorSpedizioni * m){
	int i=0, somma=0;
	int testa = m->testa;
	for(i=0;i<m->nElem;i++){
		somma+=m->ordini[testa];
		testa = (testa+1)%MAX;
	}
	return somma;
}
void init_(MonitorSpedizioni * m){
	m->testa = 0;
	m->coda = 0;
	m->nElem = 0;
	pthread_mutex_init(&m->mutex, NULL);
	pthread_cond_init(&m->cond_prod, NULL);
	pthread_cond_init(&m->cond_cons, NULL);
}
void destroy_(MonitorSpedizioni * m){
	pthread_mutex_destroy(&m->mutex);
	pthread_cond_destroy(&m->cond_prod);
	pthread_cond_destroy(&m->cond_cons);
}

void *cons(void *p){
	printf("[CONS START %d]\n", syscall(__NR_gettid));
	MonitorSpedizioni * m = (MonitorSpedizioni*)p;
	int sQnt = 0;
	while(sQnt<45){
		sQnt += preleva(m, 4);
	}
	pthread_exit(0);
}
void *prod(void *p){
	printf("[PROD START]\n");
	MonitorSpedizioni * m = (MonitorSpedizioni*)p;
	int i=0;
	for(i=0;i<5;i++){
		inserisci(m, i+1);
		sleep(1);
	}
	pthread_exit(0);
}