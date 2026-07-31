#include <stdlib.h>
#include "queue.h"

extern void *mymalloc(size_t);
extern int critical;
extern void _thread_critical_enter(void);
extern void _thread_critical_leave(void);

struct QNode* newNode(int k)
{
	struct QNode *temp = (struct QNode*)mymalloc(sizeof(struct QNode));
	//critical = 0;
	temp->key = k;
	temp->next = NULL;
	return temp;
}

struct Queue* createQueue()
{
	struct Queue *q;

	_thread_critical_enter();
	q = (struct Queue*)mymalloc(sizeof(struct Queue));
	//critical = 0;
	q->front = q->rear = NULL;
	_thread_critical_leave();
	return q;
}

void enQueue(struct Queue* q, int k)
{
	struct QNode* temp;

	/*
	 * Queue operations update linked-list pointers. Block the timer while
	 * doing that so the preemptive scheduler cannot observe a half-updated
	 * queue.
	 */
	_thread_critical_enter();
	temp = newNode(k);

	if (q->rear == NULL) {
		q->front = q->rear = temp;
		_thread_critical_leave();
		return;
	}

	q->rear->next = temp;
	q->rear = temp;
	_thread_critical_leave();
}

void deQueue(struct Queue* q)
{
	struct QNode *old_front;

	_thread_critical_enter();
	if (q->front == NULL)
	{
		_thread_critical_leave();
		return;
	}

	old_front = q->front;
	q->front = q->front->next;

	if (q->front == NULL)
		q->rear = NULL;

	/* Fix leak: the removed QNode is no longer reachable.
	 * Use free() directly here. Passing &old_front as void** to myfree()
	 * was type-punning a struct QNode** through void**, which is undefined
	 * behaviour and triggered invalid-pointer frees in sieve2.
	 */
	free(old_front);
	_thread_critical_leave();
}



