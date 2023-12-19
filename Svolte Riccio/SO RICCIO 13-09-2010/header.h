#include "monitor_signal_continue.h"
#include <sys/types.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>

#define LIBERO 0
#define OCCUPATO 1
#define IN_USO 2

#define FORNI_COND 0
#define CLIEN_COND 1

typedef struct{
	unsigned int id_fornitore;
	unsigned int stato;
}scaffale;

typedef struct{
	scaffale scaffali[100];
	int livello_scorte; //scorte occupate
	int slot_liberi;
	/*Serve in_uso, perchè livello_scorte
	non tiene conto di quelli in_uso
	perciò non può essere usato per
	controllare gli spazi liberi
	invece-> spazi_liberi = 100-livello_scorte-in_uso */
	Monitor m;
}magazzino;