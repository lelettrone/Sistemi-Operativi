#include "header.h"

void swap(struct DVD *d1, struct DVD *d2){
	struct DVD dtemp = *d1;
	*d1 = *d2;
	*d2 = dtemp;
}

int main(){
	int i;
	pthread_t threads[6];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	struct Monitor *m = (struct Monitor*)malloc(sizeof(struct Monitor));
	pthread_mutex_init(&m->mutex, NULL);
	for(i=0;i<3;i++){
		pthread_cond_init(&m->f[i], NULL);
	}
	struct DVD dvd[6];
	int film = 1;
	int copia = 1;
	for(i=0;i<6;i++){
		m->dvd[i].identificativo_film = film;
		m->dvd[i].identificativo_copia = copia;
		m->dvd[i].stato = DISPONIBILE;

		if(i==1 || i==3){ film++;}
		if(copia==1){copia=0;}
		else{copia = 1;}
	}

	/*m->dvd[0] = dvd[0];
	m->dvd[1] = dvd[5];
	m->dvd[2] = dvd[3];
	m->dvd[3] = dvd[2];
	m->dvd[4] = dvd[1];
	m->dvd[5] = dvd[4];*/
	srand(time(0));
	for(i=0;i<28;i++){
		swap(&m->dvd[rand()%6], &m->dvd[rand()%6]);
	}

	for(i=0;i<5;i++){
		if(i==0){
			pthread_create(&threads[i], &attr, stampa, (void*)m);
		}else{
			pthread_create(&threads[i], &attr, carocchia, (void*)m);	
		}
	}

	for(i=0;i<5;i++){
		pthread_join(threads[i], NULL);
	}
	pthread_mutex_destroy(&m->mutex);
	for(i=0;i<3;i++){
		pthread_cond_destroy(&m->f[i]);
	}
	free(m);
}