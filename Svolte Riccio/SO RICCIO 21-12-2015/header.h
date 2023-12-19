#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
typedef struct {
	int indirizzo;
	int dato;
} Buffer;

typedef struct {
	Buffer vettore[10];
	int coda;
	int testa;
	int nElem;

	pthread_mutex_t mutex;
	pthread_cond_t ok_prod;

} GestioneIO;

void Inizializza(GestioneIO * g);
void Produci(GestioneIO * g, Buffer * b);
int Consuma(GestioneIO * g, Buffer * b);

void* prod(void* p);
void* cons(void* p);