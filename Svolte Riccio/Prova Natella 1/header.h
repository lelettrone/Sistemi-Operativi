#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <pthread.h>

#define MAX 4

typedef struct {
    int ordini[MAX];
    int testa;
    int coda;
    int nElem;
    //coda circolare
  	
  	pthread_mutex_t mutex;
  	pthread_cond_t cond_prod;
  	pthread_cond_t cond_cons;
} MonitorSpedizioni;

void *cons(void *p);
void *prod(void *p);
void destroy_(MonitorSpedizioni * m);
void init_(MonitorSpedizioni * m);
void inserisci(MonitorSpedizioni * m, int quantita);
int preleva(MonitorSpedizioni * m, int quantita_minima);