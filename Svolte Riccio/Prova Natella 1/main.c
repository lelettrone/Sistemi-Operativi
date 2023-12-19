#include "header.h"

int main(){
	printf("[MAIN START]\n");
	int i=0, s;
	pthread_t threads[4];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	MonitorSpedizioni *m =
		 (MonitorSpedizioni*)malloc(sizeof(MonitorSpedizioni));
	init_(m);

	for(i=0;i<4;i++){
		if(i==0){
			s = pthread_create(&threads[i], &attr, cons,(void*)m);
		}else{
			s = pthread_create(&threads[i], &attr, prod,(void*)m);
		}
		if(s!=0){
			printf("ERRORE THREAD %d\n", i);
		}
	}

	for(i=0;i<4;i++){
		pthread_join(threads[i], NULL);
	}
	printf("[MAIN END]\n");

	destroy_(m);
	return 0;
}