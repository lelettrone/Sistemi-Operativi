#include "header.h"

int affitta(struct Monitor * m, int id_film){
	pthread_mutex_lock(&m->mutex);
	int i;
	do{
		for(i=0;i<6;i++){
			if(m->dvd[i].identificativo_film == id_film && 
					m->dvd[i].stato==DISPONIBILE){
					break;
			}
		}
		if(i==6){
			printf("[ASPETT A OMAR DVD: %d]\n", id_film);
			pthread_cond_wait(&m->f[id_film], &m->mutex);}
	}while(i==6);//finchè non lo trova
	//CI STA ALLO MO PIGL

	m->dvd[i].stato = AFFITTATO;
	int id_copia = m->dvd[i].identificativo_copia;
	printf("[UE OMAR BELL STU DVD: %d, COPIA: %d]\n", id_film, id_copia);
	pthread_mutex_unlock(&m->mutex);
	return id_copia;
}

void restituisci(struct Monitor * m, int id_film, int id_copia){
	pthread_mutex_lock(&m->mutex);
	int i;
	for(i=0;i<6;i++){
		if(m->dvd[i].identificativo_film == id_film
			&& m->dvd[i].identificativo_copia == id_copia){
			m->dvd[i].stato = DISPONIBILE;
		}
	}
	printf("[PIGLIATELL OMAR DVD: %d, COPIA: %d]\n", id_film, id_copia);
	pthread_cond_signal(&m->f[id_film]);
	pthread_mutex_unlock(&m->mutex);
}

void* stampa(void *p){
	struct Monitor * m = (struct Monitor*)p;
	int k=0;
	for(k=0;k<10;k++){
		pthread_mutex_lock(&m->mutex);
		int i;
		for(i=0;i<6;i++){
			printf("[DVD: %d, COPIA: %d, STATO: %d]\n", 
				m->dvd[i].identificativo_film, 
				m->dvd[i].identificativo_copia,
				m->dvd[i].stato);
		}
		pthread_mutex_unlock(&m->mutex);
		sleep(1);
	}
	
}

void* carocchia(void *p){
	int i;
	int id_copia;
	struct Monitor *m = (struct Monitor*)p;
	for(i=0;i<3;i++){
		id_copia =  affitta(m, i+1);
		sleep(1);
		restituisci(m, i+1, id_copia);
	}

}