#include <stdlib.h>
#include "queue.h"

extern void *mymalloc(size_t);
extern int critical;
extern void myfree(void**);

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
	struct Queue *q = (struct Queue*)mymalloc(sizeof(struct Queue));
	//critical = 0;
	q->front = q->rear = NULL;
	return q;
}

void enQueue(struct Queue* q, int k)
{
	struct QNode* temp = newNode(k);

	if (q->rear == NULL) {
		q->front = q->rear = temp;
		return;
	}

	q->rear->next = temp;
	q->rear = temp;
}

void deQueue(struct Queue* q)
{
	if (q->front == NULL)
		return;

	q->front = q->front->next;

	if (q->front == NULL)
		q->rear = NULL;
}



