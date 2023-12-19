 #include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct{
	long type;
	int val1;
	int val2;
}msgClient;

typedef struct{
	int t;
	int c;
	int nElem;
	msgClient buff[3];

	pthread_cond_t ok_scritt;
	pthread_cond_t ok_cons;
	pthread_mutex_t mutex;

}bufCirc;

typedef struct{
	int mr_id;
	int ma_id;
	bufCirc *coda;
}box;

typedef struct{
	int mr_id;
	int ma_id;
	bufCirc *coda;
	pthread_t w1;
	pthread_t w2;
}box2;

