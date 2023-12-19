
#include "header.h"

void buffIns(MonitorElaborazioni* m){
	int i;
	pthread_mutex_lock(&m->mutex); 
	while( m->nLib == 0 ){
		pthread_cond_wait(&m->cond_prod, &m->mutex);
	}
	//SONO QUI HO IL MUTEX, E C'È POSTO
	int pos = getLibero(m->vett_stato);//NON DOVREBBE MAI DARE -1
	m->nLib--;
	m->vett_stato[pos] = IN_USO;

	
	pthread_mutex_unlock(&m->mutex);

	printf("[POS:%d INSERISCO ", pos);
	buffer b;
	int n = 2 + rand()%2;
	for(i=0;i<n;i++){
		b.operandi[i] = 0 + rand()%10;
		printf("%d ", b.operandi[i]);
	}
	printf("]\n");
	b.totale_operandi = n;

	pthread_mutex_lock(&m->mutex); 
	m->vett_stato[pos] = OCCUPATO;
	m->nOcc++;
	m->elaborazioni[pos] = b;

	pthread_cond_signal(&m->cond_cons);//sceto un consumatore

	pthread_mutex_unlock(&m->mutex);
}

void buffRem(MonitorElaborazioni* m){
	int i;

	pthread_mutex_lock(&m->mutex); 
	while( m->nOcc == 0 ){
		pthread_cond_wait(&m->cond_cons, &m->mutex);
	}
	//SONO QUI HO IL MUTEX, E C'E' UN ELEM DA CONSUMARE
	int pos = selBuff(m);//-1 RIP
	m->nOcc--;
	m->vett_stato[pos] = IN_USO;
	pthread_mutex_unlock(&m->mutex);

	buffer b;
	int size = m->elaborazioni[pos].totale_operandi;
	//sleep(size);
	int sum = 0;
	printf("[POS:%d SOMMA ",pos);
	for(i=0;i<size;i++){
		printf("%d ", m->elaborazioni[pos].operandi[i]);
		sum+=m->elaborazioni[pos].operandi[i];
	}
	printf(": %d]\n", sum);

	//sleep(size);

	pthread_mutex_lock(&m->mutex); 

	m->vett_stato[pos] = LIBERO;
	m->nLib++;
	pthread_cond_signal(&m->cond_prod);

	pthread_mutex_unlock(&m->mutex);
}

int getLibero(int* vett_stato){
	int i;
	for(i=0;i<5;i++){
		if(vett_stato[i]==LIBERO)
			return i;
	}
	return -1;
}

int selBuff(MonitorElaborazioni* m){
	int k = -1, min = 5;
	int i;
	for(i=0;i<5;i++){
		if(m->vett_stato[i]==OCCUPATO && 
			m->elaborazioni[i].totale_operandi < min){

			min = m->elaborazioni[i].totale_operandi;
			k = i;

		}
	}
	if(k==-1){
		//printf("ERRORE SELBUFF -1");
	}
	return k;
}
