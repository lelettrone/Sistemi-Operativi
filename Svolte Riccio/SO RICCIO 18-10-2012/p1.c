#include "header.h"
//P1
int main(){
	int pid, i;

	srand(getpid());

	int imail_key = ftok(".", 'i');
	int omail_key = ftok(".", 'o');

	int imail_id = msgget(imail_key, NULL);
	int omail_id = msgget(omail_key, NULL);

	int v[8];
	for(i=0;i<8;i++){
		v[i] = rand()%10;
	}
	printf("P1-> a %d, b %d, c %d, d %d, e %d, f %d, g %d, h %d\n", 
			v[0],v[1],v[2],v[3],v[4],v[5],v[6],v[7]);


	printf("P1 RIS TEORICO: %d\n",(v[0]*v[1]) + (v[2]+v[3])*(v[4]+v[5]) + (v[6]*v[7]));
	msgOUT mO;

	///MANDO A P2
	mO.type = 2;
	for(i=0;i<2;i++){
		mO.v[i] = v[i];
	}
 	msgsnd(omail_id, (void*)&mO, sizeof(msgOUT)-sizeof(long), 0);
 	///MANDO A P3
	mO.type = 3;
	for(i=2;i<6;i++){
		mO.v[i] = v[i];
	}
 	msgsnd(omail_id, (void*)&mO, sizeof(msgOUT)-sizeof(long), 0);

 	///MANDO A P4
	mO.type = 4;
	for(i=6;i<8;i++){
		mO.v[i] = v[i];
	}
 	msgsnd(omail_id, (void*)&mO, sizeof(msgOUT)-sizeof(long), 0);


 	//RICEVO I MESS
 	msgIN mI;
 	int r[3];

 	for(i=0;i<3;i++){
 		msgrcv(imail_id, (void*)&mI, sizeof(msgIN)-sizeof(long), 1,
                      0); //BLOCCANTE
 		r[mI.i - 1] = mI.r;
 	}

 	printf("P1 RIS REALE: %d + %d + %d -> %d \n",r[0], r[1], r[2], r[0]+ r[1]+r[2]);
 	

	exit(0);
}