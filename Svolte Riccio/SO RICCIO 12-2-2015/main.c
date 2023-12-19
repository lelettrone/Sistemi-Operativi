#include "header.h"


void* prod(void* p){
	MonitorElaborazioni* m = (MonitorElaborazioni*)p;
	buffIns(m);
	buffIns(m);
	buffIns(m);

}

void* cons(void* p){
	MonitorElaborazioni* m = (MonitorElaborazioni*)p;
	buffRem(m);
	buffRem(m);
	buffRem(m);
	buffRem(m);
	buffRem(m);
	buffRem(m);

}

int main(void){
	srand(time(0));
	
	int i;	
	MonitorElaborazioni* me =
		 (MonitorElaborazioni*)malloc(sizeof(MonitorElaborazioni));
	for(i=0;i<5; i++){
		me->vett_stato[i] = LIBERO;

	}
	me->nOcc = 0;
	me->nLib = 5;

	pthread_t threads[6];
	pthread_attr_t attr;

	pthread_mutex_init(&me->mutex, NULL);
	pthread_cond_init(&me->cond_prod, NULL);
	pthread_cond_init(&me->cond_cons, NULL);
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);


	for(i=0;i<6;i++){
		if(i<4){
			pthread_create(&threads[i],&attr,prod,(void*)me);
		}else{
			pthread_create(&threads[i],&attr,cons,(void*)me);
		}
		
	}


	for(i=0;i<6;i++){
		pthread_join(threads[i], NULL);
	}

	pthread_mutex_destroy(&me->mutex);
	pthread_cond_destroy(&me->cond_prod);
	pthread_cond_destroy(&me->cond_cons);
	pthread_attr_destroy(&attr);
}

