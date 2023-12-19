#include "header.h"
//P2
int main(){
	int pid, i;

	srand(getpid());

	int imail_key = ftok(".", 'i');
	int omail_key = ftok(".", 'o');

	int imail_id = msgget(imail_key, NULL);
	int omail_id = msgget(omail_key, NULL);

	//RICEVO I MESS
 	msgOUT mO;

 	msgrcv(omail_id, (void*)&mO, sizeof(msgOUT)-sizeof(long), 2,
                      0); //BLOCCANTE

 	int a,b;
 	a = mO.v[0];
 	b = mO.v[1];
 	int r1 = a*b;	

 	printf("P2-> a: %d * b: %d  -> r1: %d\n",a,b, r1);

 	///MANDO A P1

	msgIN mI;
	mI.type = 1;
	mI.i = 1;
	mI.r = r1;
 	msgsnd(imail_id, (void*)&mI, sizeof(msgIN)-sizeof(long), 0);
	exit(0);
}