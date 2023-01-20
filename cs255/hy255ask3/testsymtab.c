/*Anagnostakis Manos
testsymtab.c*/
#include "symtable.h"

/*a function for testing SymTable_map*/
void printAll(const char *pcKey, void *pvValue, void *pvExtra){
	if(pcKey != NULL) printf("pcKey = %s\n",pcKey);
	if(pvValue != NULL)printf("pvValue = %d\n",*(int*)pvValue);
	if(pvExtra != NULL)printf("pvValue + pvExtra = %d\n",*(int*)pvValue+*(int*)pvExtra);
	printf("--------------------------------\n");
}

/*The main function which includes some tests of the functions provided in symtable.h
and their two definitions. No checked runtime errors.
Reads nothing from stdin and writes nothing to stdout.
Comment PrintList or myPrint calls and uncomment the other to use print functions for
list or hashtable.*/
int main(){
    /*new*/
	SymTable_T st;
    const char* s = "manos";
    int x = 1;
	int pvExtra = 10;

    st = SymTable_new();

    /*put*/
    if(SymTable_put(st,s,&x)){
        printf("put successful of key: %s and value: %d\n",s,x);
    }
    else{
        fprintf(stderr, "error key is already in the table\n");
    }

    s = "kwstas";
    x = 2;
    if(SymTable_put(st,s,&x)){
        printf("put successful of key: %s and value: %d\n",s,x);
    }
    else{
        fprintf(stderr,"error key is already in the table\n");
    }

    s = "aggelos";
    x = 3;
    if(SymTable_put(st,s,&x)){
        printf("put successful of key: %s and value: %d\n",s,x);
    }
    else{
        fprintf(stderr,"error key is already in the table\n");
    }



	/*testing contains by put*/
	s = "manos";
	x = 1;
    if(SymTable_put(st,s,&x)){
        printf("put successful of key: %s and value: %d\n",s,x);
    }
    else{
        fprintf(stderr, "error key is already in the table\n");
    }

    s = "kwstas";
    x = 2;
    if(SymTable_put(st,s,&x)){
        printf("put successful of key: %s and value: %d\n",s,x);
    }
    else{
        fprintf(stderr,"error key is already in the table\n");
    }

    s = "aggelos";
    x = 3;
    if(SymTable_put(st,s,&x)){
        printf("put successful of key: %s and value: %d\n",s,x);
    }
    else{
        fprintf(stderr,"error key is already in the table\n");
    }

    /*get*/
	if(SymTable_get(st,"manos") != NULL) printf("pvValue of manos is %d\n",*((int*)SymTable_get(st,"manos")));
	else printf("there is no such binding to get\n");
        if(SymTable_get(st,"john") != NULL) printf("pvValue of john is %d\n",*((int*)SymTable_get(st,"john")));
        else printf("there is no such binding to get\n");
    /*getLength*/
    printf("length is %d\n",SymTable_getLength(st));
    /*remove*/
    if(SymTable_remove(st,"manos")){
        printf("manos removed\n");
    }
    else{
        fprintf(stderr,"no such binding to remove\n");
    }
    printf("length is %d\n",SymTable_getLength(st));
        SymTable_map(st,printAll,&pvExtra);
    /*free*/
    SymTable_free(st);
    printf("Memory freed\n");
    return 0;
}
