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

 	msgrcv(omail_id, (void*)&mO, sizeof(msgOUT)-sizeof(long), 4,
                      0); //BLOCCANTE

 	int g,h;
 	g = mO.v[6];
 	h = mO.v[7];
 	int r3 = g*h;	

 	printf("P4-> g: %d * h: %d  -> r3: %d\n",g,h,r3);

 	///MANDO A P1

	msgIN mI;
	mI.type = 1;
	mI.i = 3;
	mI.r = r3;
 	msgsnd(imail_id, (void*)&mI, sizeof(msgIN)-sizeof(long), 0);
	exit(0);
}