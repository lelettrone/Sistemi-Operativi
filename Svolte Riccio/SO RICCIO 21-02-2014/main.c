//LETTORE SCRITTORE
//STARVATION SCRITTORI
#include "header.h"
int main(){
	srand(time(0));
	int i=0;
	int ret;
	pthread_t threads[14];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	printf("A SORETA\n");
	monitor_treno *mt = (monitor_treno*)malloc(sizeof(monitor_treno)*4);
	//array di monitor_treno
	for(i=0;i<4;i++){
		inizializza(&mt[i]);
	}
	printf("B SORETA\n");



	for(i=0;i<14;i++){
		if(i<=3){
			box *b = (box*)malloc(sizeof(box));
			b->m = &mt[i];
			b->nTreno = i;
			ret = pthread_create(&threads[i],&attr,
                          capotreno, (void*)b);
		}else{
			int k = 0 + rand()%4;
			box *b = (box*)malloc(sizeof(box));
			b->m = &mt[k];
			b->nTreno = k;
			
			ret = pthread_create(&threads[i],&attr,
                          viaggiatore, (void*)b);
		}
	}

	for(i=0;i<14;i++){
		pthread_join(threads[i], NULL);
	}
}