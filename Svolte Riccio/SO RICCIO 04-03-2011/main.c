
#include "header.h"
int main(){
	int i, pid;
	int rmail_id = msgget(IPC_PRIVATE, IPC_CREAT|0664); //REQUEST
	int amail_id = msgget(IPC_PRIVATE, IPC_CREAT|0664); //ANSWER

	for(i=0;i<4;i++){
		pid = fork();
		if(pid==0){//se sono il figlio
			if(i==0){
				server(rmail_id, amail_id);
				exit(0);
			}else{
				client(rmail_id, amail_id);
				exit(0);
			}
		}else if(pid>0){//sono il padre

		}else{//ERRORE PID<0
			printf("ERRORE FORK\n");
		}
	}

	for(i=0;i<3;i++){
		pid = wait(NULL);
		if(pid<0) printf("ERRORE WAIT\n");
	}

	msgbuf b = {1, -1, -1};
	msgsnd(rmail_id, (void*)&b, SMSG, 0); //MESS DI TERMINAZIONE


	msgctl(rmail_id, IPC_RMID, NULL);
	msgctl(amail_id, IPC_RMID, NULL);


	exit(0);
}