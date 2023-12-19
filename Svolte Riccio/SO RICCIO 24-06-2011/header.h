
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "monitor_hoare.h"
#define MAXSIZE 10
#define COND_UT 0
#define COND_SC 1

typedef struct {
	unsigned int posizione;
	pid_t processo;
} richiesta;

typedef struct{

	richiesta rvett[MAXSIZE];
	int testa;
	int coda;
	int nElem;

	Monitor m;
}CodCirc;

void init_CodCirc(CodCirc* cc);
void push_CodCirc(CodCirc* cc);
void pop_CodCirc(CodCirc* cc, int* hd, int* lastPi);
void destroy_CodCirc(CodCirc* cc);

