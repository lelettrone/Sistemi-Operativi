#include "header.h"


int main(){

	int i, pid = 0;

	int s_id = shmget(IPC_PRIVATE, sizeof(magazzino), IPC_CREAT|0664);
	magazzino *mag = (magazzino*)shmat(s_id, NULL, NULL);
	mag->livello_scorte = 0;
	mag->slot_liberi = 100;
	init_monitor(&mag->m, 2); //2 condition
	for(i=0;i<100;i++){
		mag->scaffali[i].stato = LIBERO;
	}

	for(i=0;i<20;i++){
		pid = fork();
		if(pid==0){
			if(i%2==0){
				for(i=0;i<15;i++){
					fornitore(mag);
				}
				
				exit(0);
			}else{
				for(i=0;i<15;i++){
					cliente(mag);
				}
				exit(0);
			}
		}
	}	

	for(i=0;i<20;i++){
		wait(NULL);
	}
	remove_monitor(&mag->m);
	exit(0);
}