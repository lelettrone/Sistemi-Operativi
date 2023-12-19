#include "header.h"


void *manager(void *p){
	box2 *b = (box2*)p;
	bufCirc *coda = (bufCirc*)b->coda;
	int mr_id = b->mr_id;
	int ma_id = b->ma_id;
	msgClient m;
	while(1){

		while(msgrcv(mr_id, (void*)&m, sizeof(msgClient)-sizeof(long), 0, IPC_NOWAIT)<=0){
			sleep(1);
		}
		printf("[MANAGER-> TYPE: %ld,  REC: %d, %d]\n", m.type, m.val1, m.val2);
		if(m.val1 == -1 && m.val2 == -1){
			pthread_cancel(b->w1);
			pthread_cancel(b->w2);
			//printf("[MANAGER KILLO]\n");
			pthread_exit(0);
		}
		pthread_mutex_lock(&coda->mutex);

		while(coda->nElem == 3){
			pthread_cond_wait(&coda->ok_scritt, &coda->mutex);
		}
		coda->buff[coda->c] = m;
		coda->c = (coda->c+1)%3;
		coda->nElem++;

		pthread_cond_signal(&coda->ok_cons); 

		pthread_mutex_unlock(&coda->mutex);
	}
	
}
void *worker(void *p){
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
	box *b = (box*)p;
	bufCirc *coda = (bufCirc*)b->coda;
	int mr_id = b->mr_id;
	int ma_id = b->ma_id;

	msgClient m;
	while(1){
		pthread_mutex_lock(&coda->mutex);

		while(coda->nElem == 0){
			pthread_cond_wait(&coda->ok_cons, &coda->mutex);
		}
		m = coda->buff[coda->t];
		coda->t = (coda->t+1)%3;
		coda->nElem--;

		pthread_cond_signal(&coda->ok_scritt);

		pthread_mutex_unlock(&coda->mutex);

		m.val1 = m.val1 * m.val2;
		msgsnd(ma_id, (void*)&m, sizeof(msgClient)-sizeof(long), 0);
	}
	
}

int main(){
	srand(getpid());

	int i, pid = getpid();

	int mr_key = ftok(".", 'r'); //request
	int ma_key = ftok(".", 'a'); //answer

	int mr_id = msgget(mr_key, IPC_CREAT|0664);
	int ma_id = msgget(ma_key, IPC_CREAT|0664);


	pthread_t w1, w2, man;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	bufCirc *coda = (bufCirc*)malloc(sizeof(bufCirc));
	coda->nElem = 0;
	coda->t = 0;
	coda->c = 0;
	pthread_mutex_init(&coda->mutex, NULL);
	pthread_cond_init(&coda->ok_scritt, NULL);
	pthread_cond_init(&coda->ok_cons, NULL);

	box b = {mr_id, ma_id, coda};

	pthread_create(&w1, &attr, worker, (void*)&b);
	pthread_create(&w2, &attr, worker, (void*)&b);
	box2 b2 = {mr_id, ma_id, coda, w1, w2};
	pthread_create(&man, &attr, manager, (void*)&b2);


	pthread_join(man, NULL);
	printf("MAN KILLATO\n");
	

	pthread_mutex_destroy(&coda->mutex);
	pthread_cond_destroy(&coda->ok_scritt);
	pthread_cond_destroy(&coda->ok_cons);

	free(coda);

	exit(0);
}