#ifndef _HEADER_H_
#define _HEADER_H_

#include <pthread.h>

#define DIM 6
#define N 4

typedef int Frame[2][2];

typedef struct {

    Frame vettore[DIM];
    int testa;
    int coda;
    int nElem;

    int nBuffWait;
    /* TBD: Completare la struttura dati monitor */
    pthread_mutex_t mutex;
    pthread_cond_t cons_cond;
    //pthread_cond_t buff_cond;
    pthread_cond_t prod_cond;

} MonitorStreaming;

void inizializza(MonitorStreaming * m);
void produci(MonitorStreaming * m, Frame f);
void consuma(MonitorStreaming * m, Frame f);
void bufferizza(MonitorStreaming * m, int n);
void distruggi(MonitorStreaming * m);

#endif

