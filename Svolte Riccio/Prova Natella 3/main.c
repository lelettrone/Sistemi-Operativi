#include "header.h"

int main(){

	int pid;
	int i;
	int m_key = ftok(".", 'm');
	int p_key = ftok(".", 'p');
	int c_key = ftok(".", 'c');

	int rts_key = ftok(".", 'r');
	int ots_key = ftok(".", 'o');

	int m_id = shmget(m_key, sizeof(int), IPC_CREAT|0664);
	int p_id = msgget(p_key, IPC_CREAT|0664);
	int c_id = msgget(c_key, IPC_CREAT|0664);

	int rts_id = msgget(rts_key, IPC_CREAT|0664);
	int ots_id = msgget(ots_key, IPC_CREAT|0664);

	for(i=0;i<2;i++){
		pid = fork();
		if(pid==0){

			if(i==0){
				execl("./produttore","./produttore",NULL);
				exit(0);
			}else{
				execl("./consumatore","./consumatore",NULL);
				exit(0);
			}

		}else if(pid<0){
			printf("[ERRORE FORK]\n");
		}
	}

	for(i=0;i<2;i++){
		wait(NULL);
		printf("[WAIT]\n");
	}
	exit(0);
}