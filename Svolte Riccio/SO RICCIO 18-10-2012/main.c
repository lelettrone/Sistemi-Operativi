#include "header.h"

int main(){
	int pid, i;
	printf("HELLO\n");
	int imail_key = ftok(".", 'i');
	int omail_key = ftok(".", 'o');

	int imail_id = msgget(imail_key, IPC_CREAT|0664);
	int omail_id = msgget(omail_key, IPC_CREAT|0664);

	printf("HELLO2\n");

	for(i=0;i<6;i++){
		pid = fork();
		if(pid==0){
			char s[10];
			sprintf(s, "p%d", i+1);
			printf("%s\n", s);
			execl(s, s, NULL);
			exit(0);
		}
	}

	for(i=0;i<6;i++){
		wait(NULL);
	}

	msgctl(imail_id, IPC_RMID, NULL);
	msgctl(omail_id, IPC_RMID, NULL);

	exit(0);
}