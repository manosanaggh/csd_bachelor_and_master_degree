/*
Anagnostakis Emmanouil
csd3618
*/

#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void *chef_function();
void *cook_function(void *id);
void createANDconsume();


int s = 0;
int cooks[3] = {1,1,1};

sem_t mutex;

void *chef_function(){
	int number;
	int cook_numbers1[2] = {1,2};
	int cook_numbers2[2] = {1,3};
	int cook_numbers3[2] = {2,3};

	while(1){
		if(s == 0){
			sem_wait(&mutex);
			s = -1;
			if(cooks[0] == 1 && cooks[1] == 1 && cooks[2] == 1){
				number = rand() % 3;
				cooks[number] = 0;
			}

                        if(cooks[0] == 1 && cooks[1] == 1 && cooks[2] == 0){
                                number = rand() % 2;
                                cooks[cook_numbers1[number]-1] = 0;
                        }
                        else if(cooks[0] == 1 && cooks[1] == 0 && cooks[2] == 1){
                                number = rand() % 2;
                                cooks[cook_numbers2[number]-1] = 0;
                        }
                        else if(cooks[0] == 0 && cooks[1] == 1 && cooks[2] == 1){
                                number = rand() % 2;
                                cooks[cook_numbers3[number]-1] = 0;
                        }

                        if(cooks[0] == 1 && cooks[1] == 0 && cooks[2] == 0){
				cooks[0] = 0;
				printf("Chef is putting french fries on the table...\n");
				printf("Chef is putting pies on the table...\n");
				s = 1;
                        }
                        else if(cooks[0] == 0 && cooks[1] == 1 && cooks[2] == 0){
				cooks[1] = 0;
				printf("Chef is putting meat on the table...\n");
				printf("Chef is putting pies on the table...\n");
                                s = 2;
                        }
                        else if(cooks[0] == 0 && cooks[1] == 0 && cooks[2] == 1){
				cooks[2] = 0;
				printf("Chef is putting meat on the table...\n");
				printf("Chef is putting french fries on the table...\n");
				s = 3;
                        }
			sem_post(&mutex);
		}
	}
}

void *cook_function(void *id){
	int* n = (int*)id;

	while(1){
		if(*n == 1){
			if(s == 1){
				sem_wait(&mutex);
				s = -1;
				printf("Cook 1 is collecting french fries and pies from the table...\n");
				printf("Cook 1 is creating gyros using meat and the ingredients he collected...\n");
				printf("Cook 1 is consuming gyros...\n\n");
				createANDconsume();
				sem_post(&mutex);
			}
		}
		else if(*n == 2){
                        if(s == 2){
				sem_wait(&mutex);
				s = -1;
                                printf("Cook 2 is collecting meat and pies from the table...\n");
                                printf("Cook 2 is creating gyros using french fries and the ingredients he collected...\n");
                                printf("Cook 2 is consuming gyros...\n\n");
                                createANDconsume();
				sem_post(&mutex);
                        }

		}
		else if(*n == 3){
                        if(s == 3){
				sem_wait(&mutex);
				s = -1;
                                printf("Cook 3 is collecting meat and french fries from the table...\n");
                                printf("Cook 3 is creating gyros using pies and the ingredients he collected...\n");
                                printf("Cook 3 is consuming gyros...\n\n");
                                createANDconsume();
				sem_post(&mutex);
                        }
		}
	}
}

void createANDconsume(){
	cooks[0] = 1;
	cooks[1] = 1;
	cooks[2] = 1;
	sleep(5);
	printf("Jumping back to the chef...\n\n");
	s = 0;
}

int main(){
	pthread_t chef_thread, cook1_thread, cook2_thread, cook3_thread;
	int chef_rc, cook1_rc, cook2_rc, cook3_rc;

	int number1 = 1,number2 = 2,number3 = 3;

	time_t t;
	srand((unsigned) time(&t));

	sem_init(&mutex, 0, 1);

	chef_rc = pthread_create(&chef_thread, NULL, chef_function, NULL);
	cook1_rc = pthread_create(&cook1_thread, NULL, cook_function, &number1);
	cook2_rc = pthread_create(&cook2_thread, NULL, cook_function, &number2);
	cook3_rc = pthread_create(&cook3_thread, NULL, cook_function, &number3);

	pthread_join(chef_thread,NULL);
	pthread_join(cook1_thread,NULL);
	pthread_join(cook2_thread,NULL);
	pthread_join(cook3_thread,NULL);

	sem_destroy(&mutex);

	return 0;
}
