#include "header.h"

void *fattorino(void *p){
	printf("FATTORINO %d\n", syscall(__NR_gettid));
	int i;
	int pos;
	Monitor *m = (Monitor*)p;
	consegna c;
	for(i=0;i<5;i++){
		pos = inizia_consegna(m);
		//sleep(3);
		fine_consegna(m, pos);
		
	}
	pthread_exit(0);
}
void *pizzaziolo(void *p){
	printf("PIZZAIOLO %d\n", syscall(__NR_gettid));
	int i;
	int cliente = 0;
	Monitor *m = (Monitor*)p;
	consegna c;
	for(i=0;i<15;i++){
		cliente++;
		aggiungi_consegna(m,  1+rand()%2, cliente);
	}
	pthread_exit(0);
}

void aggiungi_consegna(Monitor *m, int pizza, int cliente){

	pthread_mutex_lock(&m->mutex);

	while(m->nVuoto==0){ //Se non ci sono posti liberi
		pthread_cond_wait(&m->ok_pizzaiolo, &m->mutex);
	}

	m->nVuoto--;

	int pos = -1;
	int i;
	for(i=0;i<5;i++){
		if(m->c[i].stato == VUOTO){
			pos = i;
		}
	}
	m->c[pos].stato = PRONTO;
	m->c[pos].cliente = cliente;
	m->c[pos].pizza = pizza;

	m->nPronto++;

	if(m->c[pos].pizza == MARGHERITA){
		printf("[%d-> E' PRONT A PIZZ POS: %d, CLIENTE: %d]\n",syscall(__NR_gettid), pos, cliente);
	}else{
		printf("[%d-> E' PRONT O CALZON POS: %d, CLIENTE: %d]\n",syscall(__NR_gettid), pos, cliente);
	}
	
	pthread_cond_signal(&m->ok_fattorino);
	pthread_mutex_unlock(&m->mutex);

}
int inizia_consegna(Monitor *m){
	pthread_mutex_lock(&m->mutex);
	while(m->nPronto == 0){
		pthread_cond_wait(&m->ok_fattorino, &m->mutex);
	}
	int pos = -1;
	int i;
	for(i=0;i<5;i++){
		if(m->c[i].stato == PRONTO){
			pos = i;
		}
	}
	m->nPronto--;
	m->c[pos].stato = IN_CONSEGNA;

	if(m->c[pos].pizza == MARGHERITA){
		printf("[%d-> CUNSEGN A PIZZ POS: %d, CLIENTE: %d]\n",syscall(__NR_gettid), pos, m->c[pos].cliente);
	}else{
		printf("[%d-> CUNSEGN O CALZON POS: %d, CLIENTE: %d]\n",syscall(__NR_gettid), pos, m->c[pos].cliente);
	}

	pthread_mutex_unlock(&m->mutex);
	return pos;
}
void fine_consegna(Monitor *m, int indice_consegna){
	pthread_mutex_lock(&m->mutex);

	m->c[indice_consegna].stato = VUOTO;
	m->nVuoto++;

	pthread_cond_signal(&m->ok_pizzaiolo);
	pthread_mutex_unlock(&m->mutex);
}