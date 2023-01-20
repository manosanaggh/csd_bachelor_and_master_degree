/*Anagnostakis Manos
symtablehash.c*/
#include "symtable.h"

struct SymTable{
	unsigned int numOfBindings;
	binding **table;
};

/*Creates a new SymTable. Takes no parameters.
Reads nothing from stdin and writes nothing to stdout.*/
SymTable_T SymTable_new(){
	int i;
	SymTable_T oSymTable = (SymTable_T)malloc(sizeof(struct SymTable));
	buckets = 509;
	oSymTable->numOfBindings = 0;
	oSymTable->table = (binding**)malloc(buckets*sizeof(binding*));
	for(i = 0; i < buckets; i++) oSymTable->table[i] = NULL;
    	return oSymTable;
}

/*Frees the memory pointed by oSymTable argument. Returns 0
if oSymTable==NULL.
Reads nothing from stdin and writes nothing to stdout.*/
void SymTable_free(SymTable_T oSymTable){
    	if(oSymTable == NULL) return;

	free(oSymTable);
}

/*Returns the number of bindings of the oSymTable argument.
It's a checked runtime error for oSymTable to be NULL.
Reads nothing from stdin and writes nothing to stdout.*/
unsigned int SymTable_getLength(SymTable_T oSymTable){
    	assert(oSymTable);
	return oSymTable->numOfBindings;
}

/* Return a hash code for pcKey. */
size_t SymTable_hash(const char *pcKey){
  	size_t ui;
  	size_t uiHash = 0;
	int a;
  	for (ui = 0; pcKey[ui] != '\0'; ui++){
		a = pcKey[ui]-'0';
        	uiHash = ((uiHash * 10) + a)%buckets;
  	}
  	return uiHash;
}

/*Checks if the oSymTable contains a binding with pcKey.
Returns 1 if yes or 0 if not found.
It's a checked runtime error for oSymTable and pcKey to be NULL.
Reads nothing from stdin and writes nothing to stdout.*/
int SymTable_contains(SymTable_T oSymTable,const char* pcKey){
        size_t pos;
        binding *temp;
    	assert(oSymTable && pcKey);
	pos = SymTable_hash(pcKey);
	temp = oSymTable->table[pos];
        while(temp != NULL){
                if(strcmp(temp->pcKey,pcKey) == 0) return 1;
                temp = temp->next;
        }
    	return 0;
}

/*Creates a new binding in the oSymTable with pcKey and pvValue.
Returns 1 if done or 0 if not done.
It's a checked runtime error for oSymTable and pcKey to be NULL.
Reads nothing from stdin and writes nothing to stdout.*/
int SymTable_put(SymTable_T oSymTable,const char *pcKey, const void *pvValue){
        binding *node;
        size_t pos;
	assert(oSymTable && pcKey);
	if(SymTable_contains(oSymTable,pcKey)) return 0;
	switch(oSymTable->numOfBindings){
		case 509:
			buckets = 1021;
			oSymTable->table = (binding**)realloc(oSymTable->table,buckets*sizeof(binding*));
			break;
		case 1021:
                        buckets = 2053;
                        oSymTable->table = (binding**)realloc(oSymTable->table,buckets*sizeof(binding*));
                        break;
		case 2053:
                        buckets = 4093;
                        oSymTable->table = (binding**)realloc(oSymTable->table,buckets*sizeof(binding*));
                        break;
		case 4093:
                        buckets = 8191;
                        oSymTable->table = (binding**)realloc(oSymTable->table,buckets*sizeof(binding*));
                        break;
		case 8191:
                        buckets = 16381;
                        oSymTable->table = (binding**)realloc(oSymTable->table,buckets*sizeof(binding*));
                        break;
		case 16381:
                        buckets = 32771;
                        oSymTable->table = (binding**)realloc(oSymTable->table,buckets*sizeof(binding*));
                        break;
		case 32771:
                        buckets = 65521;
                        oSymTable->table = (binding**)realloc(oSymTable->table,buckets*sizeof(binding*));
                        break;
		default:
			break;
	}
	pos = SymTable_hash(pcKey);
	node = (binding*)malloc(sizeof(binding));
	node->pcKey = pcKey;
        node->pvValue = pvValue;
	oSymTable->numOfBindings++;
	if(oSymTable->table[pos] == NULL) oSymTable->table[pos] = node;
        else{
		node->next = oSymTable->table[pos];
        	oSymTable->table[pos] = node;
	}
	return 1;
}

/*Removes the binding with pcKey from the oSymTable.
Returns 1 if done or 0 if not done.
It's a checked runtime error for oSymTable and pcKey to be NULL.
Reads nothing from stdin and writes nothing to stdout.*/
int SymTable_remove(SymTable_T oSymTable,const char *pcKey){
        size_t pos;
        binding *temp;
        binding *prev;
        assert(oSymTable && pcKey);
	pos = SymTable_hash(pcKey);
	temp = oSymTable->table[pos];
        while(temp != NULL && strcmp(temp->pcKey,pcKey) != 0){
		prev = temp;
		temp = temp->next;
	}
	if(temp != NULL && strcmp(temp->pcKey,pcKey) == 0){
		prev->next = temp->next;
		free(temp);
		oSymTable->numOfBindings--;
		return 1;
	}
        return 0;
}

/*Returns the pvValue of the binding with pcKey.
Returns NULL if not found.
It's a checked runtime error for oSymTable and pcKey to be NULL.
Reads nothing from stdin and writes nothing to stdout.*/
void *SymTable_get(SymTable_T oSymTable,const char *pcKey){
        size_t pos;
        binding *temp;
    	assert(oSymTable && pcKey);
	pos = SymTable_hash(pcKey);
	temp = oSymTable->table[pos];
        while(temp != NULL && strcmp(temp->pcKey,pcKey) != 0) temp = temp->next;
        if(temp != NULL && strcmp(temp->pcKey,pcKey) == 0) return (void*)temp->pvValue;
	return NULL;
}

/*Applies the function pointed by pfApply including the pvExtra
argument to all the bindings of oSymTable.
It's a checked runtime error for oSymTable or pfApply to be NULL.
Reads nothing from stdin and writes nothing to stdout.*/
void SymTable_map(SymTable_T oSymTable,void (*pfApply)(const char* pcKey,void* pvValue,void* pvExtra),const void* pvExtra){
    	int i;
	binding *temp;
    	assert(oSymTable && pfApply);
        for(i = 0; i < buckets; i++){
		temp = oSymTable->table[i];
		while(temp != NULL){
			(*pfApply)(temp->pcKey,(void*)temp->pvValue,(void*)pvExtra);
			temp = temp->next;
		}
	}
}


