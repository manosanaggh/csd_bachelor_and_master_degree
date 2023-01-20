#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct node{
        long number;
        long indegree;
        long outdegree;
	long degree;
        struct node *next;
};

struct node *head = NULL, *head2 = NULL;
long x;
pthread_mutex_t mutex;
FILE *fp;

void *read_graph(){
        pthread_mutex_lock(&mutex);
        struct node *new_node, *new_node2, *temp;
        int exists = 0;
	fp = fopen("in_email.txt","r");
        while((char)(fscanf(fp,"%ld",&x)) != EOF){
                new_node = (struct node*)malloc(sizeof(struct node));
                new_node2 = (struct node*)malloc(sizeof(struct node));
                temp = head;
                while(temp != NULL){
                        if(temp->number == x){
                                exists = 1;
                                break;
                        }
                        temp = temp->next;
                }
                new_node2->number = x;
                new_node2->next = head2;
                head2 = new_node2;
                if(!exists){
                        new_node->number = x;
                        new_node->indegree = 0;
                        new_node->outdegree = 0;
                        new_node->next = head;
                        head = new_node;
                }
                else exists = 0;
        }
	fclose(fp);
        pthread_mutex_unlock(&mutex);

        return NULL;
}

void *create_in_out_degree(){
        int counter = 0, i, plithos = 0;
        long max;
        struct node *temp, *temp2;
        pthread_mutex_lock(&mutex);
        temp2 = head2;
        while(temp2 != NULL){
                if(counter == 0){
                        temp = head;
                        while(temp != NULL){
                                if(temp->number == temp2->number){
                                        temp->indegree++;
                                        break;
                                }
                                temp = temp->next;
                        }
                        counter++;
                }
                else counter = 0;
                temp2 = temp2->next;
        }
        pthread_mutex_unlock(&mutex);

        pthread_mutex_lock(&mutex);
        temp = head;
        max = temp->indegree;
        while(temp != NULL){
                if(temp->indegree > max) max = temp->indegree;
                temp = temp->next;
        }
        pthread_mutex_unlock(&mutex);

        pthread_mutex_lock(&mutex);
        fp = fopen("indegree.csv", "w");
        for(i = 0; i <= max; i++){
                temp = head;
                plithos = 0;
                while(temp != NULL){
                        if(i == temp->indegree) plithos++;
                        temp = temp->next;
                }
                fprintf(fp,"%d, %d\n",i,plithos);
        }
        fclose(fp);
        pthread_mutex_unlock(&mutex);

        pthread_mutex_lock(&mutex);
        counter = 0;
        plithos = 0;
        temp2 = head2;
        while(temp2 != NULL){
                if(counter == 1){
                        temp = head;
                        while(temp != NULL){
                                if(temp->number == temp2->number){
                                        temp->outdegree++;
                                        break;
                                }
                                temp = temp->next;
                        }
                        counter = 0;
                }
                else counter++;
                temp2 = temp2->next;
        }
        pthread_mutex_unlock(&mutex);

        pthread_mutex_lock(&mutex);
        temp = head;
        max = temp->outdegree;
        while(temp != NULL){
                if(temp->outdegree > max) max = temp->outdegree;
                temp = temp->next;
        }
        pthread_mutex_unlock(&mutex);

        pthread_mutex_lock(&mutex);
        fp = fopen("outdegree.csv", "w");
        for(i = 0; i <= max; i++){
                temp = head;
                plithos = 0;
                while(temp != NULL){
                        if(i == temp->outdegree) plithos++;
                        temp = temp->next;
                }
                fprintf(fp,"%d, %d\n",i,plithos);
        }
        fclose(fp);
        pthread_mutex_unlock(&mutex);

        return NULL;
}

void *create_degree(){
        int i, plithos = 0;
        long max;
        struct node *temp;
        pthread_mutex_lock(&mutex);
        plithos = 0;
                        temp = head;
                        while(temp != NULL){
                                temp->degree = temp->indegree + temp->outdegree;
                                temp = temp->next;
                        }
        pthread_mutex_unlock(&mutex);

        pthread_mutex_lock(&mutex);
        temp = head;
        max = temp->degree;
        while(temp != NULL){
                if(temp->degree > max) max = temp->degree;
                temp = temp->next;
        }
        pthread_mutex_unlock(&mutex);

        pthread_mutex_lock(&mutex);
        fp = fopen("degree.csv", "w");
        for(i = 0; i <= max; i++){
                temp = head;
                plithos = 0;
                while(temp != NULL){
                        if(i == temp->degree) plithos++;
                        temp = temp->next;
                }
                fprintf(fp,"%d, %d\n",i,plithos);
        }
        fclose(fp);
        pthread_mutex_unlock(&mutex);

        return NULL;
}

int main(){
        pthread_t tid_1,tid_2,tid_3;
	double sec;
	clock_t start, end;

	start = clock();

        pthread_mutex_init(&mutex, NULL);

        pthread_create(&tid_1, NULL, read_graph, NULL);
        pthread_join(tid_1, NULL);

        pthread_create(&tid_2, NULL, create_in_out_degree, NULL);
        pthread_join(tid_2, NULL);

        pthread_create(&tid_3, NULL, create_degree, NULL);
        pthread_join(tid_3, NULL);

        end = clock()-start;
        sec = ((double)end) / CLOCKS_PER_SEC;
        printf("program was running for %f sec\n",sec);

        return 0;
}

