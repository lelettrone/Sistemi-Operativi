#include "header.h"


void StackInit(Stack* s, int dim){
	s->dati = (Elem*)malloc(sizeof(int)*dim);
	s->dim = dim;
	s->nElem = 0;
	//inizializzo MUTEX e COND

	pthread_mutex_init(&s->mutex, 0);
	pthread_cond_init(&s->cond_full, 0);
	pthread_cond_init(&s->cond_empty, 0);
}

void StackRemove(Stack* s){
	pthread_mutex_lock(&s->mutex);
	free(s->dati);
	//dealloco MUTEX e COND
	pthread_mutex_unlock(&s->mutex);

	pthread_cond_destroy(&s->cond_full);
	pthread_cond_destroy(&s->cond_empty);
	pthread_mutex_destroy(&s->mutex);
}
void StackPush(Stack* s, Elem e){

	pthread_mutex_lock(&s->mutex);
	
	while(s->nElem == s->dim){
		pthread_cond_wait(&s->cond_full, &s->mutex);
	}
	//HO IL MUTEX, C'È POSTO PER SCRIVERE
	s->dati[s->nElem] = e;
	s->nElem++;
	printf("%d HO INSERITO:%d\n",syscall(__NR_gettid),e);

	pthread_cond_signal(&s->cond_empty);

	pthread_mutex_unlock(&s->mutex);
}
Elem StackPop(Stack* s){
	pthread_mutex_lock(&s->mutex);
	
	while(s->nElem == 0){
		pthread_cond_wait(&s->cond_empty, &s->mutex);
	}
	//HO IL MUTEX, C'E' QUALCOSA DA POPPARE
	Elem e = s->dati[s->nElem-1];
	s->nElem--;

	pthread_cond_signal(&s->cond_full);

	pthread_mutex_unlock(&s->mutex);

	return e;

}

int StackSize(Stack* s){
	return s->nElem;
}