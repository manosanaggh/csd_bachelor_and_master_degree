#include "sem.h"
#include "queue.h"
#include <unistd.h>
#include <assert.h>

#define T Sem_T

extern void Thread_pause();
extern void myprintf(char*);
extern int critical;
extern int Thread_self();
extern void _thread_critical_enter(void);
extern void _thread_critical_leave(void);

void Sem_init(T *s, int count){
	//myprintf("---Sem_init---\n");
	assert(s != NULL);

	/* The semaphore owns a wait queue. Initialize count and queue while the
	 * timer is blocked so no thread observes a half-initialized semaphore. */
	_thread_critical_enter();
	s->queue = (struct Queue*) createQueue();
	s->count = count;
	_thread_critical_leave();
}

void Sem_wait(T *s){
	//myprintf("---Sem_wait---\n");
	assert(s != NULL);

	/*
	 * The old code scanned s->queue without masking SIGVTALRM. That allowed a
	 * different thread to run Sem_signal(), deQueue() and free the node while
	 * this function still held a pointer to it. Result: use-after-free and
	 * eventually "free(): invalid pointer" in sieve2.
	 *
	 * Keep all count/queue inspection under the thread critical section, but
	 * leave the critical section before Thread_pause() so other threads can run.
	 */
	int queued = 0;
	int self = Thread_self();

	for (;;) {
		struct QNode *temp;
		int still_queued = 0;

		_thread_critical_enter();

		if (!queued && s->count == 0) {
			enQueue((struct Queue*)s->queue, self);
			queued = 1;
		}

		if (queued) {
			temp = ((struct Queue*)s->queue)->front;
			while (temp != NULL) {
				if (temp->key == self) {
					still_queued = 1;
					break;
				}
				temp = temp->next;
			}
		}

		if (s->count != 0 && !still_queued) {
			s->count--;
			_thread_critical_leave();
			return;
		}

		_thread_critical_leave();
		Thread_pause();
	}
}

void Sem_signal(T *s){
	//myprintf("---Sem_signal---\n");
	assert(s != NULL);

	/* Count and wait-queue update must be atomic with respect to preemption. */
	_thread_critical_enter();
	deQueue((struct Queue*)s->queue);
	s->count++;
	_thread_critical_leave();
}

