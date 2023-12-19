#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>


typedef struct {
	int stazione;

	pthread_cond_t cond_capi;
	pthread_cond_t cond_lett;

	
	pthread_mutex_t mutex;//server per gestire nLett

	
	int nCapi; //al max 1
	int nViagg;

	int nCapiWait; //al max 1
	int nViaggWait;


}monitor_treno;

typedef struct{
	monitor_treno *m;
	int nTreno;
}box;
void inizializza(monitor_treno* m);
void rimuovi(monitor_treno * m);
int leggi_stazione(monitor_treno * m);
void scrivi_stazione(monitor_treno * m, int stazione);


void* viaggiatore(void *p);
void* capotreno(void *p);