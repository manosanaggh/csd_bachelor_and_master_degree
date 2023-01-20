/*Anagnostakis Manos
symtablelist.c*/
#include "symtable.h"

struct SymTable{
	unsigned int numOfBindings;
	binding *head;
};

/*Creates a new SymTable. Takes no parameters.
Reads nothing from stdin and writes nothing to stdout.*/
SymTable_T SymTable_new(){
	SymTable_T oSymTable;
	oSymTable = (SymTable_T)malloc(sizeof(struct SymTable));
	oSymTable->numOfBindings = 0;
	oSymTable->head = NULL;
        return oSymTable;
}

/*Frees the memory pointed by oSymTable argument. Returns 0
if oSymTable==NULL.
Reads nothing from stdin and writes nothing to stdout.*/
void SymTable_free(SymTable_T oSymTable){
    	binding *temp;
	binding *tbf;
	if(oSymTable == NULL) return;
	temp = oSymTable->head;
	while(temp != NULL){
		tbf = temp;
		free(tbf);
		temp = temp->next;
	}
        free(oSymTable);
}

/*Returns the number of bindings of the oSymTable argument.
It's a checked runtime error for oSymTable to be NULL.
Reads nothing from stdin and writes nothing to stdout.*/
unsigned int SymTable_getLength(SymTable_T oSymTable){
    assert(oSymTable);
    return oSymTable->numOfBindings;
}

/*Checks if the oSymTable contains a binding with pcKey.
Returns 1 if yes or 0 if not found.
It's a checked runtime error for oSymTable and pcKey to be NULL.
Reads nothing from stdin and writes nothing to stdout.*/
int SymTable_contains(SymTable_T oSymTable,const char *pcKey){
        binding *temp;
        assert(oSymTable && pcKey);
	temp = oSymTable->head;
    while(temp != NULL){
        if(strcmp(temp->pcKey,pcKey) == 0){
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}


/*Creates a new binding in the oSymTable with pcKey and pvValue.
Returns 1 if done or 0 if not done.
It's a checked runtime error for oSymTable and pcKey to be NULL.
Reads nothing from stdin and writes nothing to stdout.*/
int SymTable_put(SymTable_T oSymTable,const char *pcKey,const void *pvValue){
        binding *node;
	assert(oSymTable && pcKey);
	if(SymTable_contains(oSymTable,pcKey)){
            return 0;
        }
	node = (binding*)malloc(sizeof(binding));
	node->pcKey = pcKey;
	node->pvValue = pvValue;
	oSymTable->numOfBindings++;
	if(oSymTable->head == NULL) oSymTable->head = node;
	else{
		node->next = oSymTable->head;
		oSymTable->head = node;
	}
        return 1;
}

/*Removes the binding with pcKey from the oSymTable.
Returns 1 if done or 0 if not done.
It's a checked runtime error for oSymTable and pcKey to be NULL.
Reads nothing from stdin and writes nothing to stdout.*/
int SymTable_remove(SymTable_T oSymTable,const char *pcKey){
        binding *temp;
        binding *temp2;
        assert(oSymTable && pcKey);
	temp = oSymTable->head;
        while(temp != NULL){
        	if(strcmp(temp->next->pcKey,pcKey) == 0){
        		temp2 = temp;
	    		temp2->next = temp->next->next;
	        free(temp->next);
		oSymTable->numOfBindings--;
	    	return 1;
        }
        temp = temp->next;
    }
    return 0;
}

/*Returns the pvValue of the binding with pcKey.
Returns NULL if not found.
It's a checked runtime error for oSymTable and pcKey to be NULL.
Reads nothing from stdin and writes nothing to stdout.*/
void *SymTable_get(SymTable_T oSymTable,const char *pcKey){
        binding *temp;
        assert(oSymTable && pcKey);
	temp = oSymTable->head;
    	while(temp != NULL){
        	if(strcmp(temp->pcKey,pcKey) == 0) return (void*)temp->pvValue;
        	temp = temp->next;
    	}
    	return NULL;
}

/*Applies the function pointed by pfApply including the pvExtra
argument to all the bindings of oSymTable.
It's a checked runtime error for oSymTable to be NULL.
Reads nothing from stdin and writes nothing to stdout.*/
void SymTable_map(SymTable_T oSymTable,void (*pfApply)(const char *pcKey,void *pvValue,void *pvExtra),const void *pvExtra){
    	binding *temp;
        assert(oSymTable && pfApply);
	temp = oSymTable->head;
    while(temp != NULL){
        (*pfApply)(temp->pcKey,(void*)temp->pvValue,(void*)pvExtra);
        temp = temp->next;
    }
}
