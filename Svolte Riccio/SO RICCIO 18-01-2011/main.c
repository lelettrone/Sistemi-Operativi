#include "header.h"

int main(){
	int i, pid;

	//int mailbox_key = ftok(".","m");

	int mailcb_id = msgget(IPC_PRIVATE, IPC_CREAT|0664);

	int mailbs_id = msgget(IPC_PRIVATE, IPC_CREAT|0664);


	for(i=0;i<12;i++){
		pid = fork();
		if(pid==0){
			if(i<=7){//CLIENT
				client(mailcb_id);
				exit(0);
			}else if(i>=8 && i<=10){//SERVER
				server(mailbs_id, i-7);
				exit(0);
			}else if(i==11){//BALANCER
				balancer( mailcb_id ,mailbs_id);
				exit(0);
			}
		}
		
	}


	for(i=0;i<12;i++){
		wait(NULL);
	}

	msgctl(mailcb_id,IPC_RMID, NULL);
	msgctl(mailbs_id,IPC_RMID, NULL);
	
	exit(0);
}