#include "header.h"

void inizializza(MonitorLS * m){
	init_monitor(&m->monitor, 3);
	m->buffer = 0;
	m->nScrittLen = 0;
	m->nScrittVel = 0;
	m->nLett = 0;
}

int lettore(MonitorLS *m){
	int val;
	enter_monitor(&m->monitor);
	while((m->nScrittVel > 0 || m->nScrittLen > 0)){
		wait_condition(&m->monitor, LC);
	}
	m->nLett++;
	leave_monitor(&m->monitor);

	val = m->buffer;
	printf("[LETT %d -> VAL: %d]\n", getpid(), val);

	enter_monitor(&m->monitor);
	m->nLett--;
	//printf("[LETT %d -> NLETT: %d]\n", getpid(), m->nLett);
	if(m->nLett==0){
		if(queue_condition(&m->monitor, SVC)>0){//SE CI SONO SCRITT VELOCI
			signal_condition(&m->monitor, SVC);
		//	printf("[LETT %d -> SCETO SCRITTVEL]\n", getpid());
		}else if(queue_condition(&m->monitor, SLC)>0){
			signal_condition(&m->monitor, SLC);
		//	printf("[LETT %d -> SCETO SCRITTLENTO]\n", getpid());
		}
	}
	leave_monitor(&m->monitor);
	return val;
}

void scrittore_lento(MonitorLS *m, int valore){
	enter_monitor(&m->monitor);
	while(m->nScrittVel > 0 || m->nLett > 0 
		|| m->nScrittLen > 0 || queue_condition(&m->monitor, SVC)>0){
		wait_condition(&m->monitor, SLC);
	}
	m->nScrittLen++;
	leave_monitor(&m->monitor);

	m->buffer = valore;
	sleep(2);
	printf("[SCRITT LEN %d -> VAL: %d]\n", getpid(), valore);
	enter_monitor(&m->monitor);
	m->nScrittLen--;
	if(queue_condition(&m->monitor, SVC) > 0){
		signal_condition(&m->monitor, SVC);
	//	printf("[SCRITT LEN %d -> SCETO SCRITT VEL]\n", getpid());
	}else if(queue_condition(&m->monitor, SLC) > 0){
		signal_condition(&m->monitor, SLC);
	//	printf("[SCRITT LEN %d -> SCETO SCRITT LEN]\n", getpid());
	}else{
		signal_all(&m->monitor, LC);
	//	printf("[SCRITT LEN %d -> SCETO ALL LETTORI]\n", getpid());
	}
	leave_monitor(&m->monitor);

}

void scrittore_veloce(MonitorLS *m, int valore){
	enter_monitor(&m->monitor);
	while(m->nScrittVel > 0 || m->nLett > 0 || m->nScrittLen > 0){
		wait_condition(&m->monitor, SVC);
	}
	m->nScrittVel++;
	leave_monitor(&m->monitor);

	m->buffer = valore;
	sleep(1);
	printf("[SCRITT VEL %d -> VAL: %d]\n", getpid(), valore);
	enter_monitor(&m->monitor);
	m->nScrittVel--;
	if(queue_condition(&m->monitor, SVC) > 0){
		signal_condition(&m->monitor, SVC);
		//printf("[SCRITT VEL %d -> SCETO SCRITT VEL %d]\n", getpid());
	}else if(queue_condition(&m->monitor, SLC) > 0){
		signal_condition(&m->monitor, SLC);
		//printf("[SCRITT VEL %d -> SCETO SCRITT LEN %d]\n", getpid());
	}else{
		signal_all(&m->monitor, LC);
		//printf("[SCRITT VEL %d -> SCETO ALL LETTORI %d]\n", getpid());
	}
	leave_monitor(&m->monitor);

}