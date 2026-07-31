#include "sem.h"
#include "queue.h"
#include <unistd.h>
#include <assert.h>

#define T Sem_T

extern void Thread_pause();
extern void myprintf(char*);
extern int critical;
extern int Thread_self();

void Sem_init(T *s, int count){
	//myprintf("---Sem_init---\n");
	assert(s != NULL);
	s->queue = (struct Queue*) createQueue();
	s->count = count;
}

void Sem_wait(T *s){
	//myprintf("---Sem_wait---\n");
	assert(s != NULL);

        struct QNode *temp = NULL;

	if(s->count == 0) enQueue((struct Queue*)s->queue, Thread_self());

	while(s->count == 0 || temp != NULL){
		Thread_pause();
                temp = ((struct Queue*)s->queue)->front;
                while(temp != NULL){
                        if(temp->key == Thread_self()) break;
                        temp = temp->next;
                }
	}

	s->count--;
}

void Sem_signal(T *s){
	//myprintf("---Sem_signal---\n");
	assert(s != NULL);
	deQueue((struct Queue*)s->queue);
	s->count++;
}

