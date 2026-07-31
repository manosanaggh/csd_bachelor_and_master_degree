#include <stdio.h>
#include "thread.h"
#include <time.h>
#include <unistd.h>

#define NUM_THREADS 1000000

extern void set_alarm();

int h(void *args){
        int *A = (int*)args;

        //printf("h called\n");

        Thread_pause();

    time_t starttime = time(NULL);
    time_t seconds = 1;
    time_t endtime = starttime + seconds;

    while (starttime < endtime) {
        sleep(1);
        starttime = time(NULL);
    }

         //printf("h returns.\n");
        return A[1] * A[0];

}


int f(void *args){
	int *A = (int*)args;

	//printf("f called\n");

	Thread_pause();

//if(Thread_new(h, A, sizeof(A)) == -1){printf("-----Thread_new ERROR: h == NULL or args == NULL or nbytes < 0.-----\n");}
//if(Thread_new(h, A, sizeof(A)) == -1){printf("-----Thread_new ERROR: h == NULL or args == NULL or nbytes < 0.-----\n");}
//if(Thread_new(h, A, sizeof(A)) == -1){printf("-----Thread_new ERROR: h == NULL or args == NULL or nbytes < 0.-----\n");}

        Thread_join(0);
	Thread_join(5);
        //printf("Resuming after Thread_join...\n");

    time_t starttime = time(NULL);
    time_t seconds = 1;
    time_t endtime = starttime + seconds;

    while (starttime < endtime) {
        sleep(1);
        starttime = time(NULL);
    }

if(Thread_new(h, A, sizeof(A)) == -1){printf("-----Thread_new ERROR: h == NULL or args == NULL or nbytes < 0.-----\n");}
if(Thread_new(h, A, sizeof(A)) == -1){printf("-----Thread_new ERROR: h == NULL or args == NULL or nbytes < 0.-----\n");}
if(Thread_new(h, A, sizeof(A)) == -1){printf("-----Thread_new ERROR: h == NULL or args == NULL or nbytes < 0.-----\n");}

	//printf("f returns.\n");
	return A[0] + A[1];
}

int g(void *args){
        int *A = (int*)args;

	//printf("g called\n");

	Thread_pause();
	Thread_join(7);
	//printf("Resuming after Thread_join...\n");
    time_t starttime = time(NULL);
    time_t seconds = 1;
    time_t endtime = starttime + seconds;

    while (starttime < endtime) {
        sleep(1);
        starttime = time(NULL);
    }

if(Thread_new(h, A, sizeof(A)) == -1){printf("-----Thread_new ERROR: h == NULL or args == NULL or nbytes < 0.-----\n");}
if(Thread_new(h, A, sizeof(A)) == -1){printf("-----Thread_new ERROR: h == NULL or args == NULL or nbytes < 0.-----\n");}
if(Thread_new(h, A, sizeof(A)) == -1){printf("-----Thread_new ERROR: h == NULL or args == NULL or nbytes < 0.-----\n");}

	//printf("g returns.\n");
        return A[1] - A[0];
}

int main(int argc, char *argv[]){
	int A[] = {1,2};
	int i;
	Thread_init();
	if(Thread_new(f, NULL, 0) == -1){printf("-----Thread_new ERROR: f == NULL or args == NULL or nbytes < 0.-----\n");}
	if(Thread_new(g, A, sizeof(A)) == -1){printf("-----Thread_new ERROR: f == NULL or args == NULL or nbytes < 0.-----\n");}

	for(i = 0; i < 20000; i++){
		if(Thread_new(f, A, sizeof(A)) == -1){printf("-----Thread_new ERROR: g == NULL or args == NULL or nbytes < 0.-----\n");}
	}

	Thread_pause();

	Thread_exit(0);
}
