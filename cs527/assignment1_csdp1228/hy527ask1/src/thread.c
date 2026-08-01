#define _GNU_SOURCE

#include "thread.h"
#include <stdio.h>
#include "queue.h"
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <assert.h>
#include <ucontext.h>
#include <stdint.h>

#define INTERVAL 0.5
#define NUM_THREADS 1000000
/*
 * 16KB was too small for recursive workloads once SIGVTALRM signal frames
 * are placed on the custom thread stack. 64KB is still modest but avoids the
 * intermittent quicksort stack corruption seen with the old size.
 */
#define STACK_SIZE (64 * 1024)

extern void _swtch(void *from, void *to);
extern void _thrstart(void);
extern void _ENDMONITOR(void);
extern int main(void*);
extern void _STARTMONITOR(void);
extern char _start, _etext;

struct T{
	void *esp;
	unsigned int id;
	int (*func)(void*);
	void *args;
	void *stack_start;
	struct Queue *join_q;
	int state;
	int exit_code;
	int in_ready;
};

enum {
	THREAD_UNUSED = 0,
	THREAD_RUNNABLE,
	THREAD_RUNNING,
	THREAD_BLOCKED,
	THREAD_EXITED
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
struct itimerval timer;

/*
 * Marker used by the signal handler: everything between _STARTMONITOR and
 * _ENDMONITOR belongs to the threading runtime and must not be preempted as
 * if it were user code. Keep this before all helper functions.
 */
void _STARTMONITOR(){return;}

/*
 * The old scheduler used running_q for the ready queue. That queue allocates
 * QNode objects on every enqueue, so using it from the SIGVTALRM handler is
 * unsafe: malloc/free/printf are not async-signal-safe.
 *
 * The preemptive ready queue below is a fixed-size circular queue of thread
 * ids. The signal handler only touches this array and thread_table fields; it
 * does not allocate memory and does not print.
 */
static int ready_q[NUM_THREADS];
static int ready_head = 0;
static int ready_tail = 0;
static int ready_count = 0;

/*
 * pending_stack_reap is freed by the next thread that enters the library.
 * A thread cannot free its own stack before switching away from it.
 */
static int pending_stack_reap = -1;
static int timer_ready = 0;
static int critical_depth = 0;

static int valid_tid(int tid);

static void ready_push(int tid)
{
	/*
	 * Avoid duplicate/stale ready entries. Without this, Thread_join(0) can
	 * mark the caller BLOCKED while an older copy of its id is still in ready_q;
	 * the scheduler may then run the blocked joiner too early.
	 */
	if (!valid_tid(tid) || ready_count == NUM_THREADS)
		return;
	if (thread_table[tid - 1]->state != THREAD_RUNNABLE)
		return;
	if (thread_table[tid - 1]->in_ready)
		return;

	ready_q[ready_tail] = tid;
	ready_tail = (ready_tail + 1) % NUM_THREADS;
	ready_count++;
	thread_table[tid - 1]->in_ready = 1;
}

static int ready_pop(void)
{
	int tid;

	/* Skip entries that became BLOCKED/EXITED after being enqueued. */
	while (ready_count > 0) {
		tid = ready_q[ready_head];
		ready_head = (ready_head + 1) % NUM_THREADS;
		ready_count--;

		if (!valid_tid(tid))
			continue;
		thread_table[tid - 1]->in_ready = 0;
		if (thread_table[tid - 1]->state == THREAD_RUNNABLE)
			return tid;
	}
	return -1;
}

static int ready_empty(void)
{
	return ready_count == 0;
}

/*
 * Real critical sections must block SIGVTALRM. The nested critical_depth
 * counter lets helper functions call each other without accidentally
 * unblocking the timer too early.
 *
 * These helpers are intentionally exported (not static) because queue.c uses
 * them too. That protects semaphore/join queues from preemption while their
 * linked-list pointers are being modified.
 */
void _thread_critical_enter(void)
{
	if (timer_ready && critical_depth == 0)
		sigprocmask(SIG_BLOCK, &new_set, NULL);
	critical_depth++;
}

void _thread_critical_leave(void)
{
	if (critical_depth > 0)
		critical_depth--;
	if (critical_depth == 0) {
		if (timer_ready)
			sigprocmask(SIG_UNBLOCK, &new_set, NULL);
	}
}

static int valid_tid(int tid)
{
	return tid > 0 && tid <= thread_id && thread_table[tid - 1] != NULL;
}

static void reap_previous_stack(void)
{
	if (pending_stack_reap >= 1 && valid_tid(pending_stack_reap)) {
		free(thread_table[pending_stack_reap - 1]->stack_start);
		thread_table[pending_stack_reap - 1]->stack_start = NULL;
		pending_stack_reap = -1;
	}
}

static int alive_thread_except(int tid)
{
	int i;

	for (i = 0; i < thread_id; i++) {
		if (thread_table[i] == NULL)
			continue;
		if ((int)thread_table[i]->id == tid)
			continue;
		if (thread_table[i]->state != THREAD_EXITED)
			return 1;
	}
	return 0;
}

static void wake_joiners(struct T *t)
{
	while (t->join_q->front != NULL) {
		int tid = t->join_q->front->key;
		deQueue(t->join_q);
		if (valid_tid(tid) && thread_table[tid - 1]->state == THREAD_BLOCKED) {
			thread_table[tid - 1]->state = THREAD_RUNNABLE;
			ready_push(tid);
		}
	}
}

static void wake_join_all_if_done(void)
{
	if (thread_join_0_id == -1)
		return;
	if (!valid_tid(thread_join_0_id))
		return;
	if (thread_table[thread_join_0_id - 1]->state != THREAD_BLOCKED)
		return;
	if (alive_thread_except(thread_join_0_id))
		return;

	thread_table[thread_join_0_id - 1]->state = THREAD_RUNNABLE;
	ready_push(thread_join_0_id);
}

static int switch_to_ready(int enqueue_current)
{
	int current = Thread_self();
	int next;

	if (enqueue_current && valid_tid(current)
	&& thread_table[current - 1]->state == THREAD_RUNNING) {
		thread_table[current - 1]->state = THREAD_RUNNABLE;
		ready_push(current);
	}

	if (ready_empty())
		return -1;

	next = ready_pop();
	if (!valid_tid(next))
		return -1;

	running_thread_id = next;
	thread_table[next - 1]->state = THREAD_RUNNING;

	/*
	 * Unblock the timer before running the next thread. If a timer fires in
	 * this small window, the monitor-address check in handler() ignores it
	 * because execution is still inside the threading library.
	 */
	_thread_critical_leave();
	_swtch(&thread_table[current - 1]->esp, &thread_table[next - 1]->esp);
	return 0;
}

void myprintf(char *to_print){
	_thread_critical_enter();
	printf("%s", to_print);
	_thread_critical_leave();
}

void myprintf_int(char *to_print, int x, int y){
	_thread_critical_enter();
	printf(to_print,x,y);
	_thread_critical_leave();
}

void mysigprocmask(int x, sigset_t n_s, sigset_t o_s){
	sigprocmask(x, &n_s, &o_s);
}

void handler(int sig, siginfo_t *info, void *ucontext) {
	ucontext_t *ctxt = (ucontext_t*)ucontext;
	uintptr_t eip;
	int current;
	int next;

	(void)sig;
	(void)info;

#ifdef REG_EIP
	eip = (uintptr_t)ctxt->uc_mcontext.gregs[REG_EIP];
#else
	eip = (uintptr_t)ctxt->uc_mcontext.gregs[14];
#endif
	/*
	 * Do not preempt while execution is inside libc/other shared libraries.
	 * User code often calls printf/malloc/etc.; switching away from those
	 * non-reentrant functions can corrupt their internal state.
	 */
	if(eip < (uintptr_t)&_start || eip > (uintptr_t)&_etext){ return; }
	if(((uintptr_t)_STARTMONITOR <= eip
	&& eip  <= (uintptr_t)_ENDMONITOR)){ return; }
	if(critical_depth > 0){ return; }
	if(!timer_ready || ready_empty()){ return; }
	count_signals++;

	current = running_thread_id;
	if(!valid_tid(current) || thread_table[current - 1]->state != THREAD_RUNNING)
		return;

	thread_table[current - 1]->state = THREAD_RUNNABLE;
	ready_push(current);
	next = ready_pop();
	if(!valid_tid(next)) {
		thread_table[current - 1]->state = THREAD_RUNNING;
		return;
	}
	if(next == current) {
		thread_table[current - 1]->state = THREAD_RUNNING;
		return;
	}

	running_thread_id = next;
	thread_table[next - 1]->state = THREAD_RUNNING;
	sigprocmask(SIG_UNBLOCK, &new_set, NULL);
	_swtch(&thread_table[current - 1]->esp, &thread_table[next - 1]->esp);
}

void set_alarm(){
	memset(&act, 0, sizeof(struct sigaction));
	act.sa_sigaction = handler;
	act.sa_flags = SA_SIGINFO;
	ret = sigaction(SIGVTALRM, &act, NULL);
	assert(ret == 0);
	sigemptyset( &new_set );
	sigaddset( &new_set, SIGVTALRM );
	timer_ready = 1;

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

	timer_ready = 0;
	critical_depth = 0;
	running_q = createQueue();
	temp_q = createQueue();
	exitted_q = createQueue();
	thread_id = 0;
	running_thread_id = 1;
	ready_head = ready_tail = ready_count = 0;
	pending_stack_reap = -1;
	for(i = 0; i < NUM_THREADS; i++){
		thread_table[i] = NULL;
	}

	/*
	 * Create the thread descriptor for the original main thread before the
	 * timer starts. Otherwise SIGVTALRM can arrive while thread_table[0] is
	 * still NULL/half-initialized.
	 */
	Thread_new(main,A,sizeof(A));

	set_alarm(); //preemptive

	return;
}

void *mymalloc(size_t nbytes){
	void *p;

	_thread_critical_enter();
	p = malloc(nbytes);
	_thread_critical_leave();
	return p;
}

void mymemcpy(void **dest, void *src, size_t nbytes){
	_thread_critical_enter();
	memcpy(*dest, src, nbytes);
	_thread_critical_leave();
}

int Thread_new(int func(void *), void *args, size_t nbytes, ...){
	char *stack_top;
	uintptr_t aligned_top;
	struct T *t;

	if(args == NULL || func == NULL){/*myprintf("new error\n");*/ return -1;}

	_thread_critical_enter();
	reap_previous_stack();
	if(thread_id == NUM_THREADS) {
		_thread_critical_leave();
		return -1;
	}

	//myprintf("NEW start\n");

	thread_id++;

	t = (struct T*)malloc(sizeof(struct T));
	if(t == NULL) {
		thread_id--;
		_thread_critical_leave();
		return -1;
	}
	thread_table[thread_id-1] = t;

	t->id = thread_id;
	t->join_q = createQueue();
	t->func = func;
	t->state = (thread_id == 1) ? THREAD_RUNNING : THREAD_RUNNABLE;
	t->exit_code = 0;
	t->in_ready = 0;

	t->args = malloc(nbytes);
	if(t->args == NULL || t->join_q == NULL) {
		free(t->args);
		free(t->join_q);
		free(t);
		thread_table[thread_id-1] = NULL;
		thread_id--;
		_thread_critical_leave();
		return -1;
	}
	memcpy(t->args, args, nbytes);

	t->stack_start = malloc(STACK_SIZE);
	if(t->stack_start == NULL) {
		free(t->args);
		free(t->join_q);
		free(t);
		thread_table[thread_id-1] = NULL;
		thread_id--;
		_thread_critical_leave();
		return -1;
	}

	/*
	 * Do stack arithmetic on char pointers/uintptr_t, not void*. Also keep the
	 * top aligned instead of using "... - 1", which misaligned every new stack.
	 */
	stack_top = (char*)t->stack_start + STACK_SIZE;
	aligned_top = ((uintptr_t)stack_top) & ~(uintptr_t)0xF;
	t->esp = (void*)aligned_top;

	t->esp = (char*)t->esp - 4;
	*(int*)(t->esp) = (int)_thrstart;
	t->esp = (char*)t->esp - 4;
	*(int*)(t->esp) = 0;
	t->esp = (char*)t->esp - 4;
	*(int*)(t->esp) = (int)t->args;
	t->esp = (char*)t->esp - 4;
	*(int*)(t->esp) = (int)t->func;
	t->esp = (char*)t->esp - 4;
	*(int*)(t->esp) = 0;

	if(thread_id >= 2) ready_push(thread_id);

	//myprintf("NEW end\n");

	_thread_critical_leave();
	return t->id;
}

void myfree(void **p){
	_thread_critical_enter();
	free(*p);
	*p = NULL;
	_thread_critical_leave();
}

void Thread_exit(int code){
	int current = Thread_self();
	int next;

	_thread_critical_enter();
	reap_previous_stack();

	if(!valid_tid(current)) {
		_thread_critical_leave();
		exit(code);
	}

	/*
	 * Store exit_code in the thread object. The previous global join_ret was
	 * overwritten by unrelated exiting threads.
	 */
	thread_table[current - 1]->exit_code = code;
	thread_table[current - 1]->state = THREAD_EXITED;
	enQueue(exitted_q, current);
	wake_joiners(thread_table[current - 1]);
	wake_join_all_if_done();

	if(ready_empty()){
		_thread_critical_leave();
		exit(code);
	}

	next = ready_pop();
	running_thread_id = next;
	thread_table[next - 1]->state = THREAD_RUNNING;
	pending_stack_reap = current;

	_thread_critical_leave();
	_swtch(&thread_table[current - 1]->esp, &thread_table[next - 1]->esp);

	/* Exited threads must never be scheduled again. */
	exit(code);
}

int Thread_join(int tid){
	int current = Thread_self();
	int ret_code;

	//myprintf("-----Start of Thread_join.-----\n");

	_thread_critical_enter();
	reap_previous_stack();

	if(tid == Thread_self()){
		//myprintf("!!!!!tid == Thread_self(). A thread cannot join itself.!!!!!\n");
		_thread_critical_leave();
		return -1;
	}

	if(tid == 0 && thread_join_0_id != -1){
		//myprintf("!!!!!Thread_join(0) cannot be called twice.!!!!!\n");
		_thread_critical_leave();
		return -1;
	}

	if(tid >= 1){
		if(!valid_tid(tid)){
			_thread_critical_leave();
			return -1;
		}
		if(thread_table[tid - 1]->state == THREAD_EXITED){
			ret_code = thread_table[tid - 1]->exit_code;
			_thread_critical_leave();
			return ret_code;
		}

		thread_table[current - 1]->state = THREAD_BLOCKED;
		enQueue(thread_table[tid-1]->join_q, current);
		if(switch_to_ready(0) == -1) {
			/* No runnable thread can make progress, so undo the block. */
			thread_table[current - 1]->state = THREAD_RUNNING;
			_thread_critical_leave();
			return -1;
		}
		//myprintf("-----Thread_join resumes.-----\n");
		_thread_critical_enter();
		ret_code = thread_table[tid - 1]->exit_code;
		_thread_critical_leave();
		return ret_code;
	}
	else if(tid == 0){
		if(!alive_thread_except(current)) {
			_thread_critical_leave();
			return 0;
		}
		thread_table[current - 1]->state = THREAD_BLOCKED;
		thread_join_0_id = current;
		if(switch_to_ready(0) == -1) {
			thread_table[current - 1]->state = THREAD_RUNNING;
			thread_join_0_id = -1;
			_thread_critical_leave();
			return -1;
		}
		_thread_critical_enter();
		thread_join_0_id = -1;
		//myprintf("-----Thread_join(0) resumes.-----\n");
		_thread_critical_leave();
		return 0;
	}
	_thread_critical_leave();
	return -1;
}

int Thread_self(void){
	return running_thread_id;
}

void Thread_pause(void){
	_thread_critical_enter();
	reap_previous_stack();

	/*
	 * pause/yield must not terminate the process. If there is no other
	 * runnable thread, the current thread simply keeps running.
	 */
	if(ready_empty()) {
		_thread_critical_leave();
		return;
	}

	if(switch_to_ready(1) == -1)
		_thread_critical_leave();
}




