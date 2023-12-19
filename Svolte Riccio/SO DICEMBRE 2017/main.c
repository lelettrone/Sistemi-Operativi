#include "header.h"

int main(){

	int i;
	srand(time(0));
	pthread_t threads[6];
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	ClientiSportellistaMon *c =
		(ClientiSportellistaMon*)malloc(sizeof(ClientiSportellistaMon));

	pthread_mutex_init(&c->mutex, NULL);
	pthread_cond_init(&c->ok_lett, NULL);
	pthread_cond_init(&c->ok_scritt, NULL);
	c->nLett = 0;
	c->nScritt = 0;
	c->nLettWait = 0;
	c->nScrittWait = 0;

	for(i=0;i<6;i++){
		if(i<=3){
			pthread_create(&threads[i], &attr, cliente, (void*)c);
		}else{
			pthread_create(&threads[i], &attr, operatore, (void*)c);
		}
	}


	for(i=0;i<6;i++){
		pthread_join(threads[i], NULL);
	}
	pthread_mutex_destroy(&c->mutex);
	pthread_cond_destroy(&c->ok_lett);
	pthread_cond_destroy(&c->ok_scritt);
	free(c);
	return 0;
}