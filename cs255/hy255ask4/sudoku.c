/********************************************************************
   sudoku.c

   Contains the declarations of the functions defined in sudoku.h
   and the main function.
*********************************************************************/

#include "sudoku.h"

/* Read a sudoku grid from stdin and return an object Grid_T
   initialized to these values. The input has the format:

1 2 3 4 5 6 7 8 9
4 5 6 7 8 9 1 2 3
7 8 9 1 2 3 4 5 6
2 3 4 5 6 7 8 9 1
5 6 7 8 9 1 2 3 4
8 9 1 2 3 4 5 6 7
3 4 5 6 7 8 9 1 2
6 7 8 9 1 2 3 4 5
9 1 2 3 4 5 6 7 8

   Each number is followed by a space. Each line is terminated with
   \n. Values of 0 indicate empty grid cells.
*/
Grid_T sudoku_read(void){
        Grid_T g;
        char c;
        int i,j;
	int x;
        i = 0;
        j = 0;
	c = getchar();
        while(c != EOF){
		if(c == '\n' || c == ' '){c = getchar(); continue;}
		x = c - '0';
		grid_update_value(&g,i,j,x);
                if(j == PUZZLE_DIMENSION - 1){
                        j = 0;
                        i++;
                }
		else j++;
		c = getchar();
        }
        return g;
}

/* Print the sudoku puzzle defined by g to stream s in the same format
   as expected by sudoku_read(). */
void sudoku_print(FILE* s, Grid_T g){
   int i,j;
   int x;
   for(i = 0; i < PUZZLE_DIMENSION; i++){
      for(j = 0; j < PUZZLE_DIMENSION; j++){
         x = grid_read_value(g,i,j);
         fprintf(s,"%d",x);
         if(j != PUZZLE_DIMENSION - 1) fprintf(s," ");
      }
      fprintf(s,"\n");
   }
   printf("\n");
}

/* Prints Errors, if any */
void sudoku_print_errors(Grid_T g){
    int i, j, k, l, num;
    for (i = 0; i<PUZZLE_DIMENSION; i++){
        for (j = 0; j<PUZZLE_DIMENSION; j++){
            num = grid_read_value(g,i,j);
            if (num == 0) continue;
            for (k = 0; k<PUZZLE_DIMENSION; k++){
                if (num == grid_read_value(g, i, k) && k!=j)/*    ROW    */
                    printf("fault in pair: [%d , %d] , [%d , %d]\n",i,j,i,l);
                if (num == grid_read_value(g, k, j) && k!=i)/*  COLUMN  */
                    printf("fault in pair: [%d , %d] , [%d , %d]\n",i,j,k,j);
            }
            for (k = (i/SUBGRID_DIMENSION)*SUBGRID_DIMENSION; k<(i/SUBGRID_DIMENSION)*SUBGRID_DIMENSION+SUBGRID_DIMENSION; k++){
                for (l = (j/SUBGRID_DIMENSION)*SUBGRID_DIMENSION; l<(j/SUBGRID_DIMENSION)*SUBGRID_DIMENSION+SUBGRID_DIMENSION; l++){
                    if ( (((k!=i) && (l==j))||((k==i) && (l!=j))) && num == grid_read_value(g, k, l))/* 3x3 BOX */
                        printf("fault in pair: [%d,%d] - [%d,%d]\n",i, j, k, l);
                }
            }
        }
    }
}

/* Return true iff puzzle g is correct. */
int sudoku_is_correct(Grid_T g){
    int i, j, k, l, num;
    int flag = 1;
    for (i = 0; i<PUZZLE_DIMENSION; i++){
        for (j = 0; j<PUZZLE_DIMENSION; j++){
            num = grid_read_value(g,i,j);
            if (num == 0) continue;
            for (k = 0; k<PUZZLE_DIMENSION; k++){
                if (num == grid_read_value(g, i, k) && k!=j) flag = 0;
                if (num == grid_read_value(g, k, j) && k!=i) flag = 0;
            }
            for (k = (i/SUBGRID_DIMENSION)*SUBGRID_DIMENSION; k < (i/SUBGRID_DIMENSION)*SUBGRID_DIMENSION+SUBGRID_DIMENSION; k++)
                for (l = (j/SUBGRID_DIMENSION)*SUBGRID_DIMENSION; l < (j/SUBGRID_DIMENSION)*SUBGRID_DIMENSION+SUBGRID_DIMENSION; l++)
                    if ( (((k!=i) && (l==j))||((k==i) && (l!=j)))&& num == grid_read_value(g, k, l)) flag = 0;
        }
   }
    return flag;
}

/*
 * fix all choices for every cell in Grid
 */
void sudoku_init_choices(Grid_T *g){
    int i, j, k, l, m;
    grid_set_unique(g);
    for (i = 0; i<PUZZLE_DIMENSION; i++) {
        for (j = 0; j<PUZZLE_DIMENSION; j++){
            grid_set_count(g,i,j);
            grid_clear_choice(g,i,j,0);
            for (m = 1; m<PUZZLE_DIMENSION+1; m++){ grid_set_choice(g, i, j, m);}
        }
    }/*all choices set*/
    for (i = 0; i<PUZZLE_DIMENSION; i++) {
        for (j = 0; j<PUZZLE_DIMENSION; j++){
            m = grid_read_value(*g,i,j);
            if (m != 0){      /* cell not empty */
                grid_clear_count(g,i,j);
                for (m=1; m<PUZZLE_DIMENSION + 1; m++) {grid_clear_choice(g, i, j, m);}
                continue;
            } /* if cell is taken clear all choices */
            else{           /* cell is empty */
                for (k = 0; k<PUZZLE_DIMENSION; k++){
                    m = grid_read_value(*g, k, j);
                    grid_remove_choice(g, i, j, m); /* clear all in COLUMN */
            	    m = grid_read_value(*g, i, k);
                    grid_remove_choice(g, i, j, m); /* clear all in ROW */
                }
                for (k = (i/SUBGRID_DIMENSION)*SUBGRID_DIMENSION; k < (i/SUBGRID_DIMENSION)*SUBGRID_DIMENSION+SUBGRID_DIMENSION; k++){
                    for (l = (j/SUBGRID_DIMENSION)*SUBGRID_DIMENSION; l < (j/SUBGRID_DIMENSION)*SUBGRID_DIMENSION+SUBGRID_DIMENSION; l++){
                        m = grid_read_value(*g, k, l);
                        grid_remove_choice(g, i, j, m);/* remove all in 3x3 */
                    }
		}
            }
        }
    }
}

/*
 * finds a unique choice-cell and returns answer
 * or returns answer to cell with minimum choices
 */
static int sudoku_try_next(Grid_T g, int *row, int *col){
    int i, j, k, n;
    int nchoice = PUZZLE_DIMENSION + 1;
    for (i = 0; i < PUZZLE_DIMENSION; i++) { 
    	for (j = 0; j < PUZZLE_DIMENSION; j++){
        	n = grid_read_count(g, i, j);
        	if (n > 0 && n < nchoice) nchoice = n;
    	}
    }/* nchoice is the least choices in grid */
    while (nchoice < PUZZLE_DIMENSION + 1) {
    	i = rand()%PUZZLE_DIMENSION;
    	j = rand()%PUZZLE_DIMENSION;
    	n = grid_read_count(g, i, j);
    	if (n == nchoice) {
        	while (1) {
        		k = rand()%PUZZLE_DIMENSION + 1;
        		if (grid_choice_is_valid(g, i, j, k)) { /* apply random choices */
            			*row = i;
            			*col = j;
            			return k;
        		}
        	}
    	}
    }
    return 0;
}

/*
 * Updates (ROW, COLUMN, 3x3) choices after removal of value
 */
static void sudoku_eliminate_choice(Grid_T *g, int r, int c, int n){
  int k, l;
  for (k = 0; k < PUZZLE_DIMENSION; k++) {
    grid_remove_choice(g, r, k, n);        /* remove from row */
    grid_remove_choice(g, k, c, n);        /* remove from column */
  }
  /* compute sub-grid */
  for (k = (r/SUBGRID_DIMENSION)*SUBGRID_DIMENSION; k < (r/SUBGRID_DIMENSION)*SUBGRID_DIMENSION+SUBGRID_DIMENSION; k++){
    for (l = (c/SUBGRID_DIMENSION)*SUBGRID_DIMENSION; l < (c/SUBGRID_DIMENSION)*SUBGRID_DIMENSION+SUBGRID_DIMENSION; l++){ grid_remove_choice(g, k, l, n);}      /* remove from sub-grid */
  }
}

/* Remove value from grid */
static int sudoku_remove_choice(Grid_T *g, int i, int j, int n){
  int nchoice;
  nchoice = grid_read_count(*g, i, j);
  grid_remove_choice(g, i, j, n);
  return nchoice;
}

/* Sovle puzzle g and return the solved puzzle; if the puzzle has
   multiple solutions, return one of the possible solutions. */
Grid_T sudoku_solve(Grid_T g){
    int i, j, n, choice;
    Grid_T tmp, solved;
    while ((n = sudoku_try_next(g, &i, &j))){
        choice = sudoku_remove_choice(&g, i, j, n);
        if (choice == 1){
            grid_update_value(&g, i, j, n);
            sudoku_eliminate_choice(&g, i, j, n);
        }
        else {
            grid_clear_unique(&g);  /* Single way */
            tmp = g;
            grid_update_value(&tmp, i, j, n);
            solved = sudoku_solve(tmp);
            if (sudoku_is_correct(solved)) return solved;
        }
    }
    return g;
}


static Grid_T sudoku_generate_complete(void){
   Grid_T g;
   int i,j;

   for(i = 0; i < 9; i++){
      for(j = 0; j < 9; j++){
          grid_update_value(&g,i,j,0);
      }
   }
   sudoku_init_choices(&g);
   g = sudoku_solve(g);
   return g;
}

Grid_T sudoku_generate(int nelts){
   Grid_T g;
   int i,j,counter=0;
   g = sudoku_generate_complete();
	while(counter < 81-nelts){
        	i = rand()%8;
		j = rand()%8;
		if(grid_read_value(g,i,j) != 0){
			grid_update_value(&g,i,j,0);
			counter++;
		}
	}
   return g;
}

int main(int argc,char** argv){
  Grid_T init, final;
  int n, flag = 1;
  srand(getpid());
  switch (argc) {
    case 1:         /* sudoku */
      init = sudoku_read();
	fprintf(stderr,"New Puzzle:\n");
      sudoku_print(stderr, init);
      sudoku_init_choices(&init);
      final = sudoku_solve(init);
      if (sudoku_is_correct(final)) {
        if (grid_read_unique(final))
          fprintf(stderr, "Puzzle has a unique solution:\n");
        else
          fprintf(stderr, "Puzzle has a solution:\n");
      }
      else {
        fprintf(stderr, "Puzzle does not have solution:\n");
      }
      sudoku_print(stdout, final);
      sudoku_print_errors(final);
      break;
    case 2:         /* check if sudoku is correct (sudoku -c) */
      if (argv[1][0] == '-' &&
          argv[1][1] == 'c' &&
          argv[1][2] == '\0') {
        init = sudoku_read();
	fprintf(stderr,"New Puzzle:\n");
        sudoku_print(stderr, init);
        if (sudoku_is_correct(init))
            fprintf(stderr, "Puzzle solution is correct.\n");
        else
          fprintf(stderr, "Puzzle solution is not correct.\n");
        sudoku_print_errors(init);
      }
      break;
    case 3: /* generator */
      if (argv[1][0] == '-' && argv[1][1] == 'g' && argv[1][2] == '\0') {
        n = 0;
        while (argv[2][n] != '\0')
          if (!isdigit((int)argv[2][n++])) {
            flag = 0;
        }
        if (flag) {
          n = atoi(argv[2]);
          init = sudoku_generate(n);
          sudoku_print(stdout, init);
        }
      }
      break;
    default:
      fprintf(stderr,"Expected format:\nsudoku -c | -g nelts");
  }

  return 0;
}
