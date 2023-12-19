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

 	msgrcv(omail_id, (void*)&mO, sizeof(msgOUT)-sizeof(long), 5,
                      0); //BLOCCANTE

 	int c,d;
 	c = mO.v[2];
 	d = mO.v[3];
 	int r4 = c+d;	

 	printf("P5-> c: %d + d: %d  -> r4: %d\n",c,d,r4);

 	///MANDO A P3

	msgIN mI;
	mI.type = 3;
	mI.i = 4;
	mI.r = r4;
 	msgsnd(imail_id, (void*)&mI, sizeof(msgIN)-sizeof(long), 0);
	exit(0);
}