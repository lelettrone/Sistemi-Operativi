#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>

#define DIM 3

typedef struct{
	int job_id[DIM];

	int nLett;
	int nScritt;
	int nLettWait;
	int nScrittWait;
	pthread_mutex_t mutex;

	pthread_cond_t ok_lett;
	pthread_cond_t ok_scritt;

}ClientiSportellistaMon;
void *cliente(void *p);
void *operatore(void *p);
void inizializza_ClientiOperatoriMon(ClientiSportellistaMon *p);
void scrivi_cliente(ClientiSportellistaMon *p, int job_value1, int job_value2, int job_value3);
void leggi_job(ClientiSportellistaMon *p);
void rimuovi_ClientiOperatoriMon(ClientiSportellistaMon *p);