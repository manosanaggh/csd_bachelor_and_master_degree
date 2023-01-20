#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

struct cell{
	int x;
	int y;
	int num_alive_neigh;
	int curr_state;
	int next_state;
	int last_gen_state;
	struct cell *next;
};

FILE *fp;
int i = 0,x = 0, y = 0;
char c;
int rows,cols,diag1,diag2,gens;
omp_lock_t lock;
struct cell *head = NULL;

int main(int argc, char** argv){
	omp_init_lock(&lock);
	#pragma omp parallel sections
	{
		#pragma omp section
		{
			omp_set_lock(&lock);
			fp = fopen(argv[1],"r");
			while(fscanf(fp,"%c",&c)!= EOF){
				if(i == 0 && c != ' '){
					rows = c - '0';
					printf("%d ",rows);
					i++;
				}
				else if(i == 1 && c != ' '){
					cols = c - '0';
					printf("%d\n",cols);
					i++;
					break;
				}
			}
			omp_unset_lock(&lock);
		}

		#pragma omp section
		{
			omp_set_lock(&lock);

			while(fscanf(fp,"%c",&c)!= EOF){
				if(y == cols){
						x++;
						y = 0;
				}
				if(c == ' '){
					struct cell *new_node = (struct cell*)malloc(sizeof(struct cell));
					new_node->curr_state = 0;
					new_node->num_alive_neigh = 0;
					new_node->next_state = 0;
					new_node->next = NULL;
					new_node->x = x;
					new_node->y = y;
					if(head == NULL) head = new_node;
					else{
						struct cell *temp = head;
						while(temp->next != NULL){
							temp = temp->next;
						}
						temp->next = new_node;
					}
					y++;
				}
				else if(c == '*'){
					struct cell *new_node = (struct cell*)malloc(sizeof(struct cell));
					new_node->curr_state = 1;
					new_node->num_alive_neigh = 0;
					new_node->next_state = 0;
					new_node->next = NULL;
					new_node->x = x;
					new_node->y = y;
					if(head == NULL) head = new_node;
					else{
						struct cell *temp = head;
						while(temp->next != NULL){
							temp = temp->next;
						}
						temp->next = new_node;
					}				
					y++;
				}
			}
			omp_unset_lock(&lock);
		}

		#pragma omp section 
		{
			omp_set_lock(&lock);
			for(gens = 0; gens < atoi(argv[2]); gens++){
				printf("---------------GENERATION %d STARTED----------------\n",gens+1);
				int count = 0;
				struct cell *temp = head;			
				while(temp != NULL){
					if(temp->x > 0 && temp->y > 0){
						diag1 = temp->x - 1;
						diag2 = temp->y - 1;
						while(diag1 > -1 && diag1 < rows && diag2 > -1 && diag2 < cols){
							struct cell *temp2 = head;
							while(temp2 != NULL){
								if(diag1 == temp2->x && diag2 == temp2->y && temp2->curr_state) count++;
								temp2 = temp2->next;
							}
							diag1--;
							diag2--;
						}
					}
					temp->num_alive_neigh += count;
					count = 0;
					temp = temp->next;
				}
				
				count = 0;
				temp = head;			
				while(temp != NULL){
					if(temp->x > 0 && temp->y > 0){
						diag1 = temp->x + 1;
						diag2 = temp->y - 1;
						while(diag1 > -1 && diag1 < rows && diag2 > -1 && diag2 < cols){
							struct cell *temp2 = head;
							while(temp2 != NULL){
								if(diag1 == temp2->x && diag2 == temp2->y && temp2->curr_state) count++;
								temp2 = temp2->next;
							}
							diag1++;
							diag2--;
						}
					}
					temp->num_alive_neigh += count;
					count = 0;
					temp = temp->next;
				}
				
				count = 0;
				temp = head;			
				while(temp != NULL){
					if(temp->x > 0 && temp->y > 0){
						diag1 = temp->x - 1;
						diag2 = temp->y + 1;
						while(diag1 > -1 && diag1 < rows && diag2 > -1 && diag2 < cols){
							struct cell *temp2 = head;
							while(temp2 != NULL){
								if(diag1 == temp2->x && diag2 == temp2->y && temp2->curr_state) count++;
								temp2 = temp2->next;
							}
							diag1--;
							diag2++;
						}
					}
					temp->num_alive_neigh += count;
					count = 0;
					temp = temp->next;
				}
					
				count = 0;
				temp = head;			
				while(temp != NULL){
					if(temp->x > 0 && temp->y > 0){
						diag1 = temp->x + 1;
						diag2 = temp->y + 1;
						while(diag1 > -1 && diag1 < rows && diag2 > -1 && diag2 < cols){
							struct cell *temp2 = head;
							while(temp2 != NULL){
								if(diag1 == temp2->x && diag2 == temp2->y && temp2->curr_state) count++;
								temp2 = temp2->next;
							}
							diag1++;
							diag2++;
						}
					}
					temp->num_alive_neigh += count;
					count = 0;
					temp = temp->next;
				}
				
				count = 0;
				temp = head;			
				while(temp != NULL){
					if(temp->y > 0 ){
						for(diag2 = temp->y - 1; diag2 > -1; diag2--){
							struct cell *temp2 = head;
							while(temp2 != NULL){
								if(temp->x == temp2->x && diag2 == temp2->y && temp2->curr_state) count++;
								temp2 = temp2->next;
							}
						}
					}
					temp->num_alive_neigh += count;
					count = 0;
					temp = temp->next;
				}
				
				count = 0;
				temp = head;			
				while(temp != NULL){
					if(temp->y > 0 ){
						for(diag2 = temp->y + 1; diag2 < cols; diag2++){
							struct cell *temp2 = head;
							while(temp2 != NULL){
								if(temp->x == temp2->x && diag2 == temp2->y && temp2->curr_state) count++;
								temp2 = temp2->next;
							}
						}
					}
					temp->num_alive_neigh += count;
					count = 0;
					temp = temp->next;
				}
				
				count = 0;
				temp = head;		
				while(temp != NULL){
					if(temp->x > 0 ){
						for(diag1 = temp->x - 1; diag1 > -1; diag1--){
							struct cell *temp2 = head;
							while(temp2 != NULL){
								if(diag1 == temp2->x && temp->y == temp2->y && temp2->curr_state) count++;
								temp2 = temp2->next;
							}
						}
					}
					temp->num_alive_neigh += count;
					count = 0;
					temp = temp->next;
				}
					
				count = 0;
				temp = head;
				while(temp != NULL){
					if(temp->x > 0 ){
						for(diag1 = temp->x + 1; diag1 < rows; diag1++){
							struct cell *temp2 = head;
							while(temp2 != NULL){
								if(diag1 == temp2->x && temp->y == temp2->y && temp2->curr_state) count++;
								temp2 = temp2->next;
							}
						}
					}
					temp->num_alive_neigh += count;
					count = 0;
					temp = temp->next;
				}
					
				temp = head;
				if(temp == NULL) printf("NULL\n");
				while(temp != NULL){
					printf("num alive: %d\n",temp->num_alive_neigh);
					printf("prev next state: %d\n",temp->next_state);
					printf("curr state: %d\n",temp->curr_state);
					if(temp->curr_state && temp->num_alive_neigh < 2){
						temp->next_state = 0;
					}
					else if(temp->curr_state && temp->num_alive_neigh > 3){
						temp->next_state = 0;
					}
					else if(temp->curr_state && (temp->num_alive_neigh == 2 || temp->num_alive_neigh == 3)){
						temp->next_state = 1;
					}
					else if(!(temp->curr_state) && temp->num_alive_neigh == 3){
						temp->next_state = 1;
					}
					printf("next state: %d\n\n",temp->next_state);
					temp->last_gen_state = temp->curr_state;
					temp->curr_state = temp->next_state;
					temp->num_alive_neigh = 0;
					temp = temp->next;
				}

			}
			omp_unset_lock(&lock);
		}


		#pragma omp section
		{
			omp_set_lock(&lock);
			fclose(fp);
			fp = fopen(argv[3], "w");
			fprintf(fp,"%d ",rows);
			fprintf(fp,"%d\n",cols);
			struct cell *temp = head;
			while(temp != NULL){
				if(temp->last_gen_state){
					fprintf(fp,"|*");
				}
				else{
					fprintf(fp,"| ");
				}
				if(temp->y == cols-1) fprintf(fp,"|\n");
				temp = temp->next;
			}
			fclose(fp);
			omp_unset_lock(&lock);
		}
	}
	omp_destroy_lock(&lock);
	return 0;
}
