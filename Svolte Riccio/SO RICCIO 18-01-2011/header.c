#include "header.h"

void client(int mailcb_id){
	int i=0;

	msgbuf *b = (msgbuf*)malloc(sizeof(msgbuf));

	b->value = getpid();
	b->type = TYPE_CLIENT;

	for(i=0;i<15;i++){
		
		msgsnd(mailcb_id, (void*)b, sizeof(msgbuf)-sizeof(long), 
							0);
		//E' ASINCRONA, SE NON CI STA SPAZIO ALLORA SI BLOCCA
		printf("[%d CLIENT-> SND: %d]\n", getpid(), b->value);
		sleep(1);
	}

	free(b);
	

}
void server(int mailbs_id, int type){
	msgbuf *b = (msgbuf*)malloc(sizeof(msgbuf));

	int i = 0;

	for(i=0;i<40;i++){
		msgrcv(mailbs_id, (void*)b, sizeof(msgbuf)-sizeof(long), type,
                      0); //VOGLIO BLOCCANTE
		printf("[%d SERVER-> REC: %d]\n", getpid(), b->value);
	}

	free(b);
	

}
void balancer(int mailcb_id ,int mailbs_id){

	msgbuf *b = (msgbuf*)malloc(sizeof(msgbuf));
	int i = 0;
	int server_type = 1;
	for(i=0;i<120;i++){

		msgrcv(mailcb_id, (void*)b, sizeof(msgbuf)-sizeof(long), TYPE_ALL,
                      0); //VOGLIO BLOCCANTE

		b->type = server_type;

		msgsnd(mailbs_id, (void*)b, sizeof(msgbuf)-sizeof(long), 
							0);

		printf("[%d BALANCER-> FROM: %d, TO: %d]\n", getpid(), b->value, server_type);

		server_type++;
		if(server_type == 4) server_type = 1;
	}

	free(b);


}