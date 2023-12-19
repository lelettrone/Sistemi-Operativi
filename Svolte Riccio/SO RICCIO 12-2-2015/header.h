#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>


#define LIBERO 0
#define OCCUPATO 1
#define IN_USO 2
typedef struct{
	int operandi[4];
	int totale_operandi;
	
}buffer;

typedef struct{
	buffer elaborazioni[5];
	int vett_stato[5];
	int nOcc;
	int nLib;

	pthread_mutex_t mutex;
	pthread_cond_t cond_prod;
	pthread_cond_t cond_cons;
	
}MonitorElaborazioni;


void buffIns();
void buffRem();