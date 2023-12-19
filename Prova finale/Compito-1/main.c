#include "prodcons.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void * Produttore(void *);
void * Consumatore(void *);

int main() {
    int e, i;
    /* TBD: Avviare i thread produttore e consumatore */
    pthread_t threads[2];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    MonitorStreaming *m = (MonitorStreaming*)malloc(sizeof(MonitorStreaming));
    inizializza(m);

    for(i=0;i<2;i++){
        if(i==0){
            e = pthread_create(&threads[i], &attr, Consumatore, (void*)m);
        }else if(i==1){
            e = pthread_create(&threads[i], &attr, Produttore, (void*)m);
        }
        
        if(e!=0){
            printf("ERRORE PTHREAD_CREATE\n");
            exit(0);
        }
    }
    
    for(i=0;i<2;i++){
        e = pthread_join(threads[i], NULL);
        if(e!=0){
            printf("ERRORE PTHREAD_JOIN\n");
            exit(0);
        }
    }
    distruggi(m);
    exit(0);


}

void * Produttore(void * p) {
    MonitorStreaming * m = (MonitorStreaming*)p;

    for(int i=0; i<10; i++) {

        Frame f;
        f[0][0] = rand() % 11;
        f[0][1] = rand() % 11;
        f[1][0] = rand() % 11;
        f[1][1] = rand() % 11;

        /* TBD: Chiamare il metodo "produci()" del monitor */
        produci(m , f);

        sleep(1);
    }

    pthread_exit(NULL);
}

void * Consumatore(void * p) {
    MonitorStreaming * m = (MonitorStreaming*)p;


    /* TBD: Chiamare il metodo "bufferizza()" del monitor */
    bufferizza(m, N);

    for(int i=0; i<10; i++) {

        Frame f;

        /* TBD: Chiamare il metodo "consuma()" del monitor */
        consuma(m , f);

        sleep(1);
    }

    pthread_exit(NULL);
}