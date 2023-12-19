#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>

#define DIM 5
typedef int Elem;

typedef struct Stack{
	Elem* dati;
	int dim;
	int nElem;

	pthread_mutex_t mutex;
	pthread_cond_t cond_full;
	pthread_cond_t cond_empty;
} Stack;

void StackInit(Stack* s, int dim);
void StackRemove(Stack* s);
void StackPush(Stack* s, Elem e);
Elem StackPop(Stack* s);
int StackSize(Stack* s);