#include "header.h"
//P1
int main(){
	int pid, i;

	srand(getpid());

	int imail_key = ftok(".", 'i');
	int omail_key = ftok(".", 'o');

	int imail_id = msgget(imail_key, NULL);
	int omail_id = msgget(omail_key, NULL);



 	//RICEVO I MESS
 	msgOUT mO1;
 	int c,d,f,e;
 	msgrcv(omail_id, (void*)&mO1, sizeof(msgOUT)-sizeof(long), 3,
                      0); //BLOCCANTE
 	c = mO1.v[2];
 	d = mO1.v[3];
 	e = mO1.v[4];
 	f = mO1.v[5];

 	printf("P3-> c: %d, d: %d, e: %d, f: %d \n",c,d,e,f);

	msgOUT mO2;

	///MANDO A P5
	mO2.type = 5;
	mO2.v[2] = c;
	mO2.v[3] = d;
 	msgsnd(omail_id, (void*)&mO2, sizeof(msgOUT)-sizeof(long), 0);

 	///MANDO A P6
	mO2.type = 6;
	mO2.v[4] = e;
	mO2.v[5] = f;
 	msgsnd(omail_id, (void*)&mO2, sizeof(msgOUT)-sizeof(long), 0);


 	//RICEVO DA P5 E P6
 	msgIN mI;
 	int r2, r[2];

 	for(i=0;i<2;i++){
 		msgrcv(imail_id, (void*)&mI, sizeof(msgIN)-sizeof(long), 3,
                      0); //BLOCCANTE
 		r[mI.i - 4] = mI.r;
 	}
 	
 	r2 = r[0] * r[1];

 	printf("P3-> r2: %d \n", r2);
 	mI.type = 1;
 	mI.i = 2;
 	mI.r = r2;
 	msgsnd(imail_id, (void*)&mI, sizeof(msgIN)-sizeof(long), 0);

	exit(0);
}