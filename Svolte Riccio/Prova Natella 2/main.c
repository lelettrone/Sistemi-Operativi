#include "header.h"

int main(){
	int i, pid;
	
	int m_id = shmget(IPC_PRIVATE, sizeof(MonitorLS), IPC_CREAT|0664);

	MonitorLS *ls = (MonitorLS*)shmat(m_id, 0, 0);

	inizializza(ls);

	for(i=0;i<7;i++){
		pid = fork();
		if(pid==0){
			if(i<=2){
				//printf("LETT\n");
				srand(getpid());
				int k;
				for(k=0;k<3;k++){
					lettore(ls);
					sleep(3);
				}	
				exit(0);
			}else if(i>=3 && i<=4){
				//printf("SCRITT LEN\n");
				srand(getpid());
				int k;
				for(k=0;k<3;k++){
					scrittore_lento(ls, rand()%11);
					sleep(3);
				}	
				exit(0);
			}else{
			//	printf("SCRITT VEL\n");
				srand(getpid());
				int k;
				for(k=0;k<3;k++){
					scrittore_veloce(ls, rand()%11);
					sleep(3);
				}	
				exit(0);
			}
		}else if(pid<0){
			printf("NDOOJJ ERRORE");
		}
	}

	for(i=0;i<7;i++){

		wait(NULL);
		printf("WAIT");
	}
	remove_monitor(&ls->monitor);
	shmctl(m_id,IPC_RMID,0);
	exit(0);

}