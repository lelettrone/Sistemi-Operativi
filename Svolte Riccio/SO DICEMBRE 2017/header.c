#include "header.h"

void *cliente(void *p){
	int i = 0;
	int k = 0;

	ClientiSportellistaMon *c = (ClientiSportellistaMon*)p;

	for(i=0;i<4;i++){

		scrivi_cliente(c, 1+rand()%50, 1+rand()%50, 1+rand()%50);

		sleep(4);
	}

	pthread_exit(0);
}

void *operatore(void *p){
	int i = 0;
	int k = 0;
	ClientiSportellistaMon *c = (ClientiSportellistaMon*)p;

	for(i=0;i<16;i++){

		leggi_job(c);

		sleep(1);

	}
	pthread_exit(0);
}
void scrivi_cliente(ClientiSportellistaMon *c, int job_value1, int job_value2, int job_value3){
	int id = syscall(__NR_gettid);
	pthread_mutex_lock(&c->mutex);
	while(c->nScritt >= 1 || c->nLett >=1){
		c->nScrittWait++;
		pthread_cond_wait(&c->ok_lett, &c->mutex);
		c->nScrittWait--;
	}
	c->nScritt++;
	pthread_mutex_unlock(&c->mutex);

	c->job_id[0] = job_value1;
	c->job_id[1] = job_value2;
	c->job_id[2] = job_value3;
	printf("[%d SCRIVO: %d, %d, %d]\n", id, c->job_id[0],c->job_id[1],c->job_id[2]);

	pthread_mutex_lock(&c->mutex);
	
	c->nScritt--;
	if(c->nScrittWait==0){//SE NON CI SONO SCRITT IN WAIT
		pthread_cond_broadcast(&c->ok_lett);//sveglio tutti i lettori
	}else{
		pthread_cond_signal(&c->ok_scritt); //sveglio uno scrittore in wait
	}

	pthread_mutex_unlock(&c->mutex);
}

void leggi_job(ClientiSportellistaMon *c){
	int id = syscall(__NR_gettid);
	pthread_mutex_lock(&c->mutex);
	while(c->nScritt >= 1){
		c->nLettWait++;
		pthread_cond_wait(&c->ok_lett, &c->mutex);
		c->nLettWait--;
	}
	c->nLett++;
	pthread_mutex_unlock(&c->mutex);

	printf("[%d LEGGO: %d, %d, %d]\n", id, c->job_id[0],c->job_id[1],c->job_id[2]);

	pthread_mutex_lock(&c->mutex);
	c->nLett--;
	if(c->nLett==0){//SE SONO L'ULTIMO
		pthread_cond_signal(&c->ok_scritt);//sveglio uno scritt
	}
	pthread_mutex_unlock(&c->mutex);
}