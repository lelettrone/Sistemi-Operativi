#include "monitor.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <unistd.h>

#define SVC 0
#define SLC 1
#define LC 	2

typedef struct {
    int buffer;     // risorsa condivisa
    int nScrittVel;
    int nScrittLen;
    int nLett;
    Monitor monitor; 
} MonitorLS;

void inizializza(MonitorLS * m);
int lettore(MonitorLS * m);
void scrittore_lento(MonitorLS * m, int valore);
void scrittore_veloce(MonitorLS * m, int valore);