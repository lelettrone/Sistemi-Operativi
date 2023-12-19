#include "monitor.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdlib.h>


#define OK_M 0
#define OK_L 1
/*
	Lettori-Scrittori, 
	starvation Scrittori
	più lettori contemporaneamente

*/

typedef struct {
	int temperatura;
	unsigned int umidita;
	unsigned short pioggia;

	Monitor monitor;
	int nScritt;
	int nLett;

} meteo;

void M(meteo *pmeteo);

void L(meteo *pmeteo);