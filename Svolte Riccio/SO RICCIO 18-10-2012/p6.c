#include "header.h"
//P4
int main(){
	int pid, i;

	srand(getpid());

	int imail_key = ftok(".", 'i');
	int omail_key = ftok(".", 'o');

	int imail_id = msgget(imail_key, NULL);
	int omail_id = msgget(omail_key, NULL);

	//RICEVO I MESS
 	msgOUT mO;

 	msgrcv(omail_id, (void*)&mO, sizeof(msgOUT)-sizeof(long), 6,
                      0); //BLOCCANTE

 	int e,f;
 	e = mO.v[4];
 	f = mO.v[5];
 	int r5 = e+f;	

 	printf("P6-> e: %d + f: %d  -> r5: %d\n",e,f,r5);

 	///MANDO A P3

	msgIN mI;
	mI.type = 3;
	mI.i = 5;
	mI.r = r5;
 	msgsnd(imail_id, (void*)&mI, sizeof(msgIN)-sizeof(long), 0);
	exit(0);
}