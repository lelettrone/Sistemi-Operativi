#include "pthread.h"
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>

#define VUOTO 0
#define PRONTO 1
#define IN_CONSEGNA 2
#define MARGHERITA 1
#define CALZONE 2

typedef struct {
	int pizza; //MARGHERITA=1, CALZONE = 2
	int stato; //VUOTO=0, PRONTO=1, IN_CONSEGNA=2
	int cliente;

}consegna;

typedef struct {
 	consegna c[5];

 	int nVuoto;
 	int nPronto;
 	pthread_mutex_t mutex;
 	pthread_cond_t ok_pizzaiolo;
 	pthread_cond_t ok_fattorino;

}Monitor;

void aggiungi_consegna(Monitor *m, int pizza, int cliente);
int inizia_consegna(Monitor *m);
void fine_consegna(Monitor *m, int indice_consegna);

void *fattorino(void *p);
void *pizzaziolo(void *p);