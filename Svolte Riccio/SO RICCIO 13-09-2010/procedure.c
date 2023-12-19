#include "header.h"

void fornitore(magazzino* mag){
	int i;
	enter_monitor(&mag->m);
	while(mag->slot_liberi==0){
		wait_condition(&mag->m, FORNI_COND); //mi metto in attesa 
	}
	//HO IL MUTEX, QUALCUNO MI HA SVEGLIATO
	//C'È POSTO
	int pos=-1;
	for(i=0;i<100;i++){
		if(mag->scaffali[i].stato==LIBERO){
			pos = i;
			break;
		}
	}
	//i sicuramente è != -1, poichè
	//se mi hanno svegliato ed ho superato il while
	//di sicuro c'è posto
	mag->scaffali[pos].stato = IN_USO;
	mag->slot_liberi--;
	//c'è uno slot libero in meno
	//ma non ho ancora aumentato fornitura
	//perchè ancora non l'ho messo a OCCUPATO
	leave_monitor(&mag->m);

	//sleep(2);

	enter_monitor(&mag->m);
	mag->scaffali[pos].id_fornitore = getpid();
	mag->livello_scorte++;
	mag->scaffali[pos].stato = OCCUPATO;
	printf("[FOR %d->PONGO IN OCCUPATO %d]\n", getpid(), pos);
	signal_condition(&mag->m, CLIEN_COND); //sceto un consumatore
	leave_monitor(&mag->m);
}

void cliente(magazzino* mag){
	int i;
	enter_monitor(&mag->m);
	while( mag->livello_scorte == 0){
		wait_condition(&mag->m, CLIEN_COND); //mi metto in attesa 
	}
	//HO IL MUTEX, QUALCUNO MI HA SVEGLIATO
	//C'È POSTO
	int pos=-1;
	for(i=0;i<100;i++){
		if(mag->scaffali[i].stato==OCCUPATO){
			pos = i;
			break;
		}
	}
	//i sicuramente è != -1, poichè
	//se mi hanno svegliato ed ho superato il while
	//di sicuro c'è posto
	mag->scaffali[pos].stato = IN_USO;
	mag->livello_scorte--;
	//ci sta una scorta in meno
	//ma non ho ancora fatto slot_liberi++
	//poichè non lìho ancora messo a LIBERO
	//printf("[CLI %d->PONGO IN USO %d]\n", getpid(), pos);
	leave_monitor(&mag->m);

	//sleep(2);

	enter_monitor(&mag->m);
	mag->scaffali[pos].stato = LIBERO;
	mag->slot_liberi++;
	printf("[CLI %d->PONGO IN LIBERO %d]\n", getpid(), pos);
	signal_condition(&mag->m, FORNI_COND);
	leave_monitor(&mag->m);

}