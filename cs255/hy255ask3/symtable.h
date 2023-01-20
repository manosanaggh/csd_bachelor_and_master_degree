/*Anagnostakis Manos
symtable.h*/
#ifndef SYMTABLE_H_
#define SYMTABLE_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct SymTable *SymTable_T;
unsigned int buckets;

typedef struct binding{
    const char *pcKey;
    const void *pvValue;
    struct binding *next;
}binding;

/*Creates a new SymTable. Takes no parameters.
Reads nothing from stdin and writes nothing to stdout.*/
SymTable_T SymTable_new(void);

/*Frees the memory pointed by oSymTable argument. Returns
if oSymTable==NULL.
Reads nothing from stdin and writes nothing to stdout.*/
void SymTable_free(SymTable_T oSymTable);

/*Returns the number of bindings of the oSymTable argument.
It's a checked runtime error for oSymTable to be NULL.
Reads nothing from stdin and writes nothing to stdout.*/
unsigned int SymTable_getLength(SymTable_T oSymTable);

/*Creates a new binding in the oSymTable with pcKey and pvValue.
Returns 1 if done or 0 if not done.
It's a checked runtime error for oSymTable and pcKey to be NULL.
Reads nothing from stdin and writes nothing to stdout.*/
int SymTable_put(SymTable_T oSymTable, const char *pcKey,const void *pvValue);

/*Removes the binding with pcKey from the oSymTable.
Returns 1 if done or 0 if not done.
It's a checked runtime error for oSymTable and pcKey to be NULL.
Reads nothing from stdin and writes nothing to stdout.*/
int SymTable_remove(SymTable_T oSymTable, const char *pcKey);

/*Checks if the oSymTable contains a binding with pcKey.
Returns 1 if yes or 0 if not found.
It's a checked runtime error for oSymTable and pcKey to be NULL.
Reads nothing from stdin and writes nothing to stdout.*/
int SymTable_contains(SymTable_T oSymTable, const char *pcKey);

/*Returns the pvValue of the binding with pcKey.
Returns NULL if not found.
It's a checked runtime error for oSymTable and pcKey to be NULL.
Reads nothing from stdin and writes nothing to stdout.*/
void *SymTable_get(SymTable_T oSymTable, const char *pcKey);

/*Applies the function pointed by pfApply including the pvExtra
argument to all the bindings of oSymTable.
It's a checked runtime error for oSymTable to be NULL.
Reads nothing from stdin and writes nothing to stdout.*/
void SymTable_map(SymTable_T oSymTable,void (*pfApply)(const char *pcKey, void *pvValue,void *pvExtra),const void *pvExtra);

#endif
