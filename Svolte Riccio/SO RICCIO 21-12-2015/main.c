 #include "header.h"

int main(){
	int i;
	srand(time(0));
	pthread_t threads[6];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	GestioneIO *g = (GestioneIO*)malloc(sizeof(GestioneIO));
	Inizializza(g);


	int ret;
	for(i=0;i<6;i++){
		if(i<=3){
			ret = pthread_create(&threads[i], &attr, prod, (void*)g);
		}else{
			ret = pthread_create(&threads[i], &attr, cons, (void*)g);
		}
	}


	for(i=0;i<6;i++){
		pthread_join(threads[i], NULL);
	}


	pthread_mutex_destroy(&g->mutex);
	pthread_cond_destroy(&g->ok_prod);
	g->coda = 0;
	g->testa = 0;
	g->nElem = 0;
	exit(0);
}