
#include "header.h"
int main(){
	srand(getpid());
	int i, pid;

	int mr_key = ftok(".", 'r'); //request
	int ma_key = ftok(".", 'a'); //answer

	int mr_id = msgget(mr_key, IPC_CREAT|0664);
	int ma_id = msgget(ma_key, IPC_CREAT|0664);

	for(i=0;i<4;i++){
		pid = fork();
		if(pid==0){
			if(i==0){
				execl("./server", "./server", NULL);
				exit(0);
			}else{
				execl("./client", "./client", NULL);
				exit(0);
			}
		}
	}

	for(i=0;i<3;i++){
		wait(NULL);
	}
	sleep(3);
	msgClient m = {getpid(),-1,-1};
	msgsnd(mr_id, (void*)&m, sizeof(msgClient)-sizeof(long), 0);

	wait(NULL);

	msgctl(mr_id,IPC_RMID,NULL);
	msgctl(ma_id,IPC_RMID,NULL);

	exit(0);
}