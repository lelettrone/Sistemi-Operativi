#include "prodcons.h"

#include <stdio.h>


void inizializza(MonitorStreaming * m) {

    /* TBD: Inizializzare il monitor */
    pthread_mutex_init(&m->mutex, NULL);
    pthread_cond_init(&m->prod_cond, NULL);
    pthread_cond_init(&m->cons_cond, NULL);
    //pthread_cond_init(&m->buff_cond, NULL);
    m->nElem = 0;
    m->testa = 0;
    m->coda = 0;
    m->nBuffWait = 0;
}

void produci(MonitorStreaming * m, Frame f) {

    /* TBD: Completare il metodo, con la sincronizzazione */
    pthread_mutex_lock(&m->mutex);
    while(m->nElem == DIM){//se buffer pieno
        pthread_cond_wait(&m->prod_cond, &m->mutex);//wait prod
    }
    //posso inserire
    printf("Produzione frame: { %d, %d, %d, %d }\n", f[0][0], f[0][1], f[1][0], f[1][1]);

    m->vettore[m->testa][0][0] = f[0][0];
    m->vettore[m->testa][0][1] = f[0][1];
    m->vettore[m->testa][1][0] = f[1][0];
    m->vettore[m->testa][1][1] = f[1][1];

    m->nElem++; //incremento numero elementi
    m->testa = (m->testa + 1)%DIM; //incremento testa circolare

    if(m->nBuffWait > 0){ //se il cons ha chiamato bufferizza()
        if(m->nElem >= N){//se ci sono almeno N frame
            pthread_cond_signal(&m->cons_cond);
            //sveglio il cons dalla bufferizzazione
        }
    }else{
        pthread_cond_signal(&m->cons_cond);
    }
    
    pthread_mutex_unlock(&m->mutex);

}

void consuma(MonitorStreaming * m, Frame f) {

    /* TBD: Completare il metodo, con la sincronizzazione */
    pthread_mutex_lock(&m->mutex);
    while(m->nElem == 0){//se buffer vuoto
        pthread_cond_wait(&m->cons_cond, &m->mutex);
    }

    f[0][0] = m->vettore[m->coda][0][0];
    f[0][1] = m->vettore[m->coda][0][1];
    f[1][0] = m->vettore[m->coda][1][0];
    f[1][1] = m->vettore[m->coda][1][1];

    printf("Consumazione frame: { %d, %d, %d, %d }\n", f[0][0], f[0][1], f[1][0], f[1][1]);
    m->nElem--;
    m->coda = (m->coda + 1)%DIM;

   
    pthread_cond_signal(&m->prod_cond);
    pthread_mutex_unlock(&m->mutex);
}

void bufferizza(MonitorStreaming * m, int n) {

    /* TBD: Completare il metodo */
    pthread_mutex_lock(&m->mutex);
    while(m->nElem < N){//se buffer non ha almeno n elementi
        m->nBuffWait++;
        pthread_cond_wait(&m->cons_cond, &m->mutex);
        m->nBuffWait--;
    }

    pthread_mutex_unlock(&m->mutex);

}

void distruggi(MonitorStreaming * m) {

    /* TBD: Completare il metodo */
    pthread_mutex_destroy(&m->mutex);
    pthread_cond_destroy(&m->prod_cond);
    pthread_cond_destroy(&m->cons_cond);
}