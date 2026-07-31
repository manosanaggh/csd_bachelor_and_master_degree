#include "thread.h"
#include <stdio.h>
#include "queue.h"
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define __USE_GNU

#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <assert.h>
#include <ucontext.h>

#define INTERVAL 0.5
#define NUM_THREADS 1000000

extern void _swtch(void *from, void *to);
extern void _thrstart(void);
extern void _ENDMONITOR(void);
extern int main(void*);
extern void _STARTMONITOR(void);

struct T{
	void *esp;
	unsigned int id;
	int (*func)(void*);
	void *args;
	void *stack_start;
	struct Queue *join_q;
};

struct T *thread_table[NUM_THREADS];
int thread_id;
struct Queue *running_q = NULL;
struct Queue *temp_q = NULL;
struct Queue *exitted_q = NULL;
int running_thread_id;
struct sigaction act;
clockid_t clock_id;
timer_t timer_id;
struct sigevent clock_sig_event;
struct itimerspec timer_value;
int ret;
sigset_t new_set, old_set;
int count_signals = 0;
int join_ret = 1;
int waiting_join_id = -1;
int thread_join_0_id = -1;
int returned_from_join_and_queue_empty = 0;
int waiting_join_id_after = -1;
int prev_id = 0;
int critical = 0;
struct itimerval timer;

void _STARTMONITOR(){return;}

void myprintf(char *to_print){
	critical = 1;
	printf(to_print);
}

void myprintf_int(char *to_print, int x, int y){
        critical = 1;
        printf(to_print,x,y);
}

void mysigprocmask(int x, sigset_t n_s, sigset_t o_s){
	critical = 1;
	sigprocmask( SIG_UNBLOCK, &n_s, &o_s);
}

void handler(int sig, siginfo_t *info, void *ucontext) {
	ucontext_t *ctxt = (ucontext_t*)ucontext;
	int eip = ctxt->uc_mcontext.gregs[14];
        if(((int)_STARTMONITOR <= eip
        && eip  <= (int)_ENDMONITOR)){/*myprintf("Library.\n");*/ return;}
	if(critical == 1){ /*myprintf("my-functions\n");*/ critical = 0; return;}
	count_signals++;
	myprintf("=====Signal passed eip check.=====\n");

        int j;

        if(running_q->front == NULL){Thread_exit(0);}

        if(running_q->front != NULL){
                        if(waiting_join_id == -1) enQueue(running_q, running_thread_id);
                        else waiting_join_id = -1;

                        j = running_thread_id-1;
                        running_thread_id = running_q->front->key;
                        deQueue(running_q);
			myprintf_int("Context switching from thread %d to thread %d in handler...\n", j+1, running_thread_id);
			mysigprocmask( SIG_UNBLOCK, new_set, old_set);
                        _swtch(&thread_table[j]->esp, &thread_table[running_thread_id-1]->esp);
        }
}

void set_alarm(){
        memset(&act, 0, sizeof(struct sigaction));
	act.sa_sigaction = handler;
	act.sa_flags = SA_SIGINFO;
	ret = sigaction(SIGVTALRM, &act, NULL);
        assert(ret == 0);
	sigemptyset( &new_set );
        sigaddset( &new_set, SIGVTALRM );

        clock_id = CLOCK_MONOTONIC;
        memset(&clock_sig_event, 0, sizeof( struct sigevent));
        clock_sig_event.sigev_notify = SIGEV_SIGNAL;
        clock_sig_event.sigev_signo = SIGVTALRM;
        clock_sig_event.sigev_notify_attributes = NULL;

        ret = timer_create(clock_id, &clock_sig_event, &timer_id);
        assert(ret == 0);

        memset(&timer_value, 0, sizeof(struct itimerspec));
        timer_value.it_interval.tv_sec = 0;
        timer_value.it_interval.tv_nsec = INTERVAL * 1000000;

        timer_value.it_value.tv_sec = 0;
        timer_value.it_value.tv_nsec = INTERVAL * 1000000;

        ret = timer_settime(timer_id, 0, &timer_value, NULL);
        assert(ret == 0);

  /*timer.it_interval.tv_usec = INTERVAL * 1000;
  timer.it_interval.tv_sec = 0;
  timer.it_value.tv_usec = INTERVAL * 1000;
  timer.it_value.tv_sec = 0;
  setitimer (ITIMER_VIRTUAL, &timer, NULL);*/
}

void Thread_init(void){
	int i;
	int A[] = {1,2};

	running_q = createQueue();
	temp_q = createQueue();
	exitted_q = createQueue();
	thread_id = 0;
	running_thread_id = 1;
	for(i = 0; i < NUM_THREADS; i++){
		thread_table[i] = NULL;
	}

	set_alarm(); //preemptive

	Thread_new(main,A,sizeof(A));

	return;
}

void *mymalloc(size_t nbytes){
	critical = 1;
	return malloc(nbytes);
}

void mymemcpy(void **dest, void *src, size_t nbytes){
	critical = 1;
	memcpy(*dest, src, nbytes);
}

int Thread_new(int func(void *), void *args, size_t nbytes, ...){
	if(args == NULL || func == NULL || nbytes < 0){/*myprintf("new error\n");*/ return -1;}
	if(thread_id == NUM_THREADS) return -1;

	//myprintf("NEW start\n");

	thread_id++;

	thread_table[thread_id-1] = (struct T*)mymalloc(sizeof(struct T));
	//critical = 0;

	thread_table[thread_id-1]->id = thread_id;
	thread_table[thread_id-1]->join_q = createQueue();
	thread_table[thread_id-1]->func = func;

	thread_table[thread_id-1]->args = mymalloc(nbytes);
	//critical = 0;
	mymemcpy(&thread_table[thread_id-1]->args, args, nbytes);
	//critical = 0;

	thread_table[thread_id-1]->stack_start = mymalloc(4 * 4096);
	//critical = 0;
	thread_table[thread_id-1]->esp = thread_table[thread_id-1]->stack_start;

	thread_table[thread_id-1]->esp += 4 * 4096 - 1;

	thread_table[thread_id-1]->esp -= 4;
	*(int*)(thread_table[thread_id-1]->esp) = (int)_thrstart;
	thread_table[thread_id-1]->esp -= 4;
	*(int*)(thread_table[thread_id-1]->esp) = 0;
	thread_table[thread_id-1]->esp -= 4;
	*(int*)(thread_table[thread_id-1]->esp) = (int)thread_table[thread_id-1]->args;
	thread_table[thread_id-1]->esp -= 4;
	*(int*)(thread_table[thread_id-1]->esp) = (int)thread_table[thread_id-1]->func;
	thread_table[thread_id-1]->esp -= 4;
	*(int*)(thread_table[thread_id-1]->esp) = 0;

	if(thread_id >= 2) enQueue(running_q,thread_id);

	//myprintf("NEW end\n");

	return thread_table[thread_id-1]->id;
}

void myfree(void **p){
	critical = 1;
	free(*p);
	*p = NULL;
}

void Thread_exit(int code){
        int j;

	if(prev_id >= 1){
		myfree(&thread_table[prev_id-1]->stack_start);
		//critical = 0;
		prev_id = 0;
	}

	enQueue(exitted_q, Thread_self());

	//myprintf("+++++thread just exitted!+++++\n");

		if(thread_table[Thread_self()-1]->join_q->front != NULL){
			//myprintf("Some thread is waiting thread that just exitted.\n");
			while(running_q->front != NULL){
				enQueue(temp_q, running_q->front->key);
				deQueue(running_q);
			}
			while(thread_table[Thread_self()-1]->join_q->front != NULL){
				enQueue(running_q, thread_table[Thread_self()-1]->join_q->front->key);
				deQueue(thread_table[Thread_self()-1]->join_q);
			}
			while(temp_q->front != NULL){
				enQueue(running_q, temp_q->front->key);
				deQueue(temp_q);
			}
			join_ret = code;
                }

	if(Thread_self() == 1 && running_q->front != NULL){
		//myprintf("MAIN thread exitted but waiting queue is not empty.\n");
	}

        if(running_q->front == NULL){
		if(thread_join_0_id != -1){
                        //myprintf("Context switching from thread to thread in Thread_exit...\n");
			j = Thread_self()-1;

                        running_thread_id = thread_join_0_id;

                        _swtch(&thread_table[j]->esp, &thread_table[Thread_self()-1]->esp);

		}
		if(running_q->front == NULL){
                	myprintf("Waiting queue is empty. There are not any threads that are waiting to finish. Thread_exit is exiting program from thread.\n");
			exit(0);
		}
		else{
			mysigprocmask( SIG_UNBLOCK, new_set, old_set);
		}
        }


	if(running_q->front != NULL){
                        //myprintf("Context switching from thread to thread in Thread_exit...\n");

			prev_id = Thread_self();
                        running_thread_id = running_q->front->key;
                        deQueue(running_q);

                        _swtch(&thread_table[prev_id-1]->esp, &thread_table[Thread_self()-1]->esp);
        }
}

int Thread_join(int tid){
	struct QNode *temp;

	//myprintf("-----Start of Thread_join.-----\n");

	if(tid == Thread_self()){
		//myprintf("!!!!!tid == Thread_self(). A thread cannot join itself.!!!!!\n");
		return -1;
	}

	if(tid == 0 && thread_join_0_id != -1){
		//myprintf("!!!!!Thread_join(0) cannot be called twice.!!!!!\n");
		return -1;
	}

	if(tid > 0 && thread_table[tid-1] == NULL){/*myprintf("!!!!!tid does not exist.!!!!!\n");*/ return -1;}

	temp = exitted_q->front;
	while(temp != NULL){
		if(tid == temp->key){/*myprintf("!!!!!tid already exitted.!!!!!\n");*/ return -1;}
		temp = temp->next;
	}

	if(tid >= 1){
		waiting_join_id = Thread_self();
		enQueue(thread_table[tid-1]->join_q, Thread_self());
		Thread_pause();
		//myprintf("-----Thread_join resumes.-----\n");
		return join_ret;
	}
	else if(tid == 0){
		waiting_join_id = Thread_self();
		thread_join_0_id = Thread_self();
		Thread_pause();
		thread_join_0_id = -1;
		//myprintf("-----Thread_join(0) resumes.-----\n");
		return 0;
	}
	return -1;
}

int Thread_self(void){
	return running_thread_id;
}

void Thread_pause(void){
	int j;

	if(running_q->front == NULL) Thread_exit(0);

	if(running_q->front != NULL){
			if(waiting_join_id == -1) enQueue(running_q, Thread_self());
			else waiting_join_id = -1;

                        //myprintf("Context switching from thread to thread in Thread_pause...\n");

			j = Thread_self()-1;
                        running_thread_id = running_q->front->key;
                        deQueue(running_q);

                        _swtch(&thread_table[j]->esp, &thread_table[Thread_self()-1]->esp);
	}
}




