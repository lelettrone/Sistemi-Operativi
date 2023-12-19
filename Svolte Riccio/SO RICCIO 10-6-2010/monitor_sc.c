/*************************************Monitor*************************************************/
// Implementazione di un Monitor Signal and Continue 


#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include "monitor.h"


//Funzioni di utilita' private alla libreria Monitor

static void Wait_Sem(int, int);
static void Signal_Sem (int,int);
static int Queue_Sem (int,int);   //restituisce il num di processi in attesa su un semaforo


/********************IMPLEMENTAZIONE DELLE PROCEDURE***********************/

void init_monitor (Monitor *M, int num_var){

    /*key_t chiavek = ftok(".", 'k');
    M->id_k = shmget(chiavek,sizeof(int),IPC_CREAT|0664);
    M->k = (int*) (shmat(M->id_k,NULL,0));
    (*(M->k))++;
    //printf("K: %d\n", *(M->k));*/


    int i;

    //alloca e inizializza il mutex per l'accesso al monitor
    M->mutex=semget(IPC_PRIVATE,1,IPC_CREAT|0664);

    semctl(M->mutex,0,SETVAL,1);


    //alloca e inizializza i semafori con cui realizzare le var.condition
    M->id_conds=semget(IPC_PRIVATE,num_var,IPC_CREAT|0664);

    for (i=0;i<num_var;i++)
         semctl(M->id_conds,i,SETVAL,0);


    //alloca un contatore per ogni var.condition

    M->id_shared=shmget(IPC_PRIVATE,num_var*sizeof(int),IPC_CREAT|0664);

    //effettua l'attach all'array di contatori appena allocato
    M->cond_counts=(int*) (shmat(M->id_shared,NULL,0));
    M->num_var_cond = num_var;


    //inizializza i contatori per le var.condition
    
    /*for (i=0; i<num_var; i++){
        M->cond_counts[i]=0;
      }*/
} 



void enter_monitor(Monitor * M){

    Wait_Sem(M->mutex,0);

}


void leave_monitor(Monitor* M){

#ifdef DEBUG_
    printf("<%d> Uscito dal monitor  \n", getpid());
    printf("<%d> -Monitor- signal sul mutex del monitor \n", getpid());
#endif 

    Signal_Sem(M->mutex,0);
}


void remove_monitor(Monitor* M){
    semctl(M->mutex,0,IPC_RMID,0);
    semctl(M->id_conds,M->num_var_cond,IPC_RMID,0);
    shmctl(M->id_shared,IPC_RMID,0);

    //shmctl(M->id_k,IPC_RMID,0);
}

void wait_condition(Monitor* M,int id_var){

      //printf("%d, LLL::%d\n", id_var, M->cond_counts[id_var]);
      M->cond_counts[id_var]++;
      //printf("%d, LLL::%d\n",id_var, M->cond_counts[id_var]);

      Signal_Sem(M->mutex,0);
    
      Wait_Sem(M->id_conds,id_var);
   	  Wait_Sem(M->mutex,0);
}

void signal_condition(Monitor* M,int id_var){

   if(M->cond_counts[id_var] > 0){
	     M->cond_counts[id_var]--;
	     Signal_Sem(M->id_conds,id_var);
   }
}


int queue_condition(Monitor * M, int id_var){
	return M->cond_counts[id_var];
}


/********************IMPLEMENTAZIONE DELLE PROCEDURE SEMAFORICHE***********************/

void Wait_Sem(int id_sem, int numsem)     {
       struct sembuf sem_buf;

       sem_buf.sem_num=numsem;
       sem_buf.sem_flg=0;
       sem_buf.sem_op=-1;
       semop(id_sem,&sem_buf,1);   //semaforo rosso
}

// restituisce il numero di processi in attesa sul semaforo
int Queue_Sem(int id_sem, int numsem)     {
	return (semctl(id_sem,numsem,GETNCNT,NULL));
}

void Signal_Sem (int id_sem,int numsem)     {
       struct sembuf sem_buf;

       sem_buf.sem_num=numsem;
       sem_buf.sem_flg=0;
       sem_buf.sem_op=1;
       semop(id_sem,&sem_buf,1);   //semaforo verde
}
