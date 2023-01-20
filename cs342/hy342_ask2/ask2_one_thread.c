#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

struct cell{
        int num_alive_neigh;
        int curr_state;
        int next_state;
        int last_gen_state;
};

FILE *fp;
int i = 0,x = 0, y = 0;
char c;
int rows,cols,diag1,diag2,gens;

int main(int argc, char** argv){
        #pragma omp parallel
        {
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


                struct cell *world[rows][cols];

                while(fscanf(fp,"%c",&c)!= EOF){
                                if(y == cols){
                                        x++;
                                        y = 0;
                                }
                                if(c == ' '){
                                world[x][y] = (struct cell*)malloc(sizeof(struct cell));
                                (world[x][y])->curr_state = 0;
                                (world[x][y])->num_alive_neigh = 0;
                                (world[x][y])->next_state = 0;
                                //printf("row = %d, col = %d, curr_state = %d\n",x,y,(world[x][y])->curr_state);
                                y++;
                                }
                                else if(c == '*'){
                                world[x][y] = (struct cell*)malloc(sizeof(struct cell));
                                (world[x][y])->curr_state = 1;
                                (world[x][y])->num_alive_neigh = 0;
                                (world[x][y])->next_state = 0;
                                //printf("row = %d, col = %d, curr_state = %d\n",x,y,(world[x][y])->curr_state);
                                y++;
                                }
                }

                for(gens = 0; gens < atoi(argv[2]); gens++){
                printf("---------------GENERATION %d STARTED----------------\n",gens+1);
                int count = 0;
                for(x = 0; x < rows; x++){
                        for(y = 0; y < cols; y++){
                                if(x > 0 && y > 0 ){
                                        diag1 = x - 1;
                                        diag2 = y - 1;
                                        while(diag1 > -1 && diag1 < rows && diag2 > -1 && diag2 < cols){
                                                //printf("upper left diagonal = %d\n",(world[diag1][diag2])->curr_state);
                                                if((world[diag1][diag2])->curr_state) count++;
                                                diag1--;
                                                diag2--;
                                        }
                                }
                                (world[x][y])->num_alive_neigh += count;
                                //printf("count = %d\n",(world[x][y])->num_alive_neigh);
                                //printf("count = %d\n",count);
                                count = 0;
                                //printf("------------------------------------------\n");
                        }
                }
                count = 0;
                for(x = 0; x < rows; x++){
                        for(y = 0; y < cols; y++){
                                if(x > 0 && y > 0 ){
                                        diag1 = x + 1;
                                        diag2 = y - 1;
                                        while(diag1 > -1 && diag1 < rows && diag2 > -1 && diag2 < cols){
                                                //printf("bottom left diagonal = %d\n",(world[diag1][diag2])->curr_state);
                                                if((world[diag1][diag2])->curr_state) count++;
                                                diag1++;
                                                diag2--;
                                        }
                                }
                                (world[x][y])->num_alive_neigh += count;
                                //printf("count = %d\n",(world[x][y])->num_alive_neigh);
                                count = 0;
                                //printf("------------------------------------------\n");
                        }
                }

                count = 0;
                for(x = 0; x < rows; x++){
                        for(y = 0; y < cols; y++){
                                if(x > 0 && y > 0 ){
                                        diag1 = x - 1;
                                        diag2 = y + 1;
                                        while(diag1 > -1 && diag1 < rows && diag2 > -1 && diag2 < cols){
                                                //printf("upper right diagonal = %d\n",(world[diag1][diag2])->curr_state);
                                                if((world[diag1][diag2])->curr_state) count++;
                                                diag1--;
                                                diag2++;
                                        }
                                }
                                (world[x][y])->num_alive_neigh += count;
                                //printf("count = %d\n",(world[x][y])->num_alive_neigh);
                                count = 0;
                                //printf("------------------------------------------\n");
                        }
                }
                count = 0;
                for(x = 0; x < rows; x++){
                        for(y = 0; y < cols; y++){
                                if(x > 0 && y > 0 ){
                                        diag1 = x + 1;
                                        diag2 = y + 1;
                                        while(diag1 > -1 && diag1 < rows && diag2 > -1 && diag2 < cols){
                                                //printf("bottom right diagonal = %d\n",(world[diag1][diag2])->curr_state);
                                                if((world[diag1][diag2])->curr_state) count++;
                                                diag1++;
                                                diag2++;
                                        }
                                }
                                (world[x][y])->num_alive_neigh += count;
                                //printf("count = %d\n",(world[x][y])->num_alive_neigh);
                                count = 0;
                                //printf("------------------------------------------\n");
                        }
                }

                count = 0;
                for(x = 0; x < rows; x++){
                        for(y = 0; y < cols; y++){
                                if(y > 0 ){
                                        for(diag2 = y - 1; diag2 > -1; diag2--){
                                                //printf("left row = %d\n",(world[x][diag2])->curr_state);
                                                if((world[x][diag2])->curr_state) count++;
                                        }
                                }
                                (world[x][y])->num_alive_neigh += count;
                                //printf("count = %d\n",(world[x][y])->num_alive_neigh);
                                count = 0;
                                //printf("------------------------------------------\n");
                        }
                }
                count = 0;
                for(x = 0; x < rows; x++){
                        for(y = 0; y < cols; y++){
                                if(y > 0 ){
                                        for(diag2 = y + 1; diag2 < cols; diag2++){
                                               //printf("right row = %d\n",(world[x][diag2])->curr_state);
                                                if((world[x][diag2])->curr_state) count++;
                                        }
                                }
                                (world[x][y])->num_alive_neigh += count;
                                //printf("count = %d\n",(world[x][y])->num_alive_neigh);
                                count = 0;
                                //printf("------------------------------------------\n");
                        }
                }

                count = 0;
                for(x = 0; x < rows; x++){
                        for(y = 0; y < cols; y++){
                                if(x > 0 ){
                                        for(diag1 = x - 1; diag1 > -1; diag1--){
                                                //printf("upper col = %d\n",(world[diag1][y])->curr_state);
                                                if((world[diag1][y])->curr_state) count++;
                                        }
                                }
                                (world[x][y])->num_alive_neigh += count;
                                //printf("count = %d\n",(world[x][y])->num_alive_neigh);
                                count = 0;
                                //printf("------------------------------------------\n");
                        }
                }
                count = 0;
                for(x = 0; x < rows; x++){
                        for(y = 0; y < cols; y++){
                                if(x > 0 ){
                                        for(diag1 = x + 1; diag1 < rows; diag1++){
                                                //printf("bottom col = %d\n",(world[diag1][y])->curr_state);
                                                if((world[diag1][y])->curr_state) count++;
                                        }
                                }
                                (world[x][y])->num_alive_neigh += count;
                                //printf("count = %d\n",(world[x][y])->num_alive_neigh);
                                //printf("count = %d\n",(world[x][y])->num_alive_neigh);
                                count = 0;
                                //printf("------------------------------------------\n");
                        }
		}

                for(x = 0; x < rows; x++){
                        for(y = 0; y < cols; y++){
                                printf("num alive: %d\n",(world[x][y])->num_alive_neigh);
                                printf("prev next state: %d\n",(world[x][y])->next_state);
                                printf("curr state: %d\n",(world[x][y])->curr_state);
                                if((world[x][y])->curr_state && (world[x][y])->num_alive_neigh < 2){
                                        (world[x][y])->next_state = 0;
                                }
                                else if((world[x][y])->curr_state && (world[x][y])->num_alive_neigh > 3){
                                        (world[x][y])->next_state = 0;
                                }
                                else if((world[x][y])->curr_state && ((world[x][y])->num_alive_neigh == 2 || (world[x][y])->num_alive_neigh == 3)){
                                        (world[x][y])->next_state = 1;
                                }
                                else if(!((world[x][y])->curr_state) && (world[x][y])->num_alive_neigh == 3){
                                        (world[x][y])->next_state = 1;
                                }
                                printf("next state: %d\n\n",(world[x][y])->next_state);
                                (world[x][y])->last_gen_state = (world[x][y])->curr_state;
                                (world[x][y])->curr_state = (world[x][y])->next_state;
                                (world[x][y])->num_alive_neigh = 0;
                        }
                }

                }



        fclose(fp);
        fp = fopen(argv[3], "w");
        fprintf(fp,"%d ",rows);
        fprintf(fp,"%d\n",cols);
                for(x = 0; x < rows; x++){
                        for(y = 0; y < cols; y++){
                                if((world[x][y])->last_gen_state){
                                        fprintf(fp,"|*");
                                }
                                else{
                                        fprintf(fp,"| ");
                                }
                        }
                        fprintf(fp,"|\n");
                }
        fclose(fp);

        }

        return 0;
}

