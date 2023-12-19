#include "header.h"

int main(){

	int i;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	pthread_t threads[4];

	Monitor *m = (Monitor*)malloc(sizeof(Monitor));
	m->nVuoto = 5;
	m->nPronto = 0;
	for(i=0;i<5;i++){
		m->c[i].stato = VUOTO;
	}
	pthread_mutex_init(&m->mutex, NULL);
	pthread_cond_init(&m->ok_pizzaiolo, NULL);
	pthread_cond_init(&m->ok_fattorino, NULL);

	printf("HELaaLO\n");

	for(i=0;i<4;i++){
		if(i<=2){

			pthread_create(&threads[i], &attr, fattorino, (void*)m);
		}else{
			pthread_create(&threads[i], &attr, pizzaziolo, (void*)m);
		}
	}

	for(i=0;i<4;i++){
		pthread_join(threads[i], NULL);
	}

	pthread_mutex_destroy(&m->mutex);
	pthread_cond_destroy(&m->ok_fattorino);
	pthread_cond_destroy(&m->ok_pizzaiolo);

	return 0;
}