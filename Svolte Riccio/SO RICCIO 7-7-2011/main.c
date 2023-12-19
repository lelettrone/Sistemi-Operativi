#include "header.h"


void* thread_func_insert(void* p){
	Stack* s = (Stack*)p;
	int i;
	Elem e;
	for(i=0;i<4;i++){
			e = 0 + rand()%10; 
			StackPush(s, e);
			sleep(1);
	}
	pthread_exit(0);
}
void* thread_func_remove(void* p){
	Stack* s = (Stack*)p;
	int i;
	Elem e1,e2;
	for(i=0;i<10;i++){
		e1 = StackPop(s);
		e2 = StackPop(s);
		printf("SOMMA %d + %d: %d\n",e1,e2, e1+e2);
	}
	pthread_exit(0);
}
int main(){
	srand(time(0));
	printf("A\n");
	pthread_t threads[5];
	pthread_attr_t attr;
	int i, ret;
	Stack* s = (Stack*)malloc(sizeof(Stack));
	StackInit(s, DIM);
	
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);


	for(i=0;i<6;i++){
		if(i==0){
			ret = pthread_create(&threads[i], &attr, thread_func_remove, (void*)s);
		}else{
			ret = pthread_create(&threads[i], &attr, thread_func_insert, (void*)s);
		}
		
	}


	for(i=0;i<6;i++){
		 pthread_join(threads[i], NULL);
	}
	pthread_attr_destroy(&attr);
	pthread_exit(0);

}