#include <stdio.h> 
#include <stdlib.h>   
#include <iostream>   
#include <fstream>    
#include <string>    
#include <typeinfo>   
#include <ctype.h>
#include <cstring>     
#include <string.h>    
#include <sstream> 
#include <vector>
#include <utility>  
#include <bits/stdc++.h> 
#include <boost/algorithm/string.hpp> 
using namespace std;

int currInstr=1; 
vector<struct instruction> instructions;  
int str_counter = 0, num_counter = 0, user_func_counter = 0, lib_func_counter = 0, bool_counter = 0, var_counter = 0, t_counter = 0;
unsigned int buckets = 509;
int for_scope=-1;
int while_scope=-1;
int if_scope=-1;
int scope = 0;

struct SymTable *oSymTable=NULL;
struct SymTable{
		unsigned int numOfBindings;
		struct binding **table;
	};
	enum Type{
		GLOBAL, __LOCAL, FORMAL, USERFUNCT, LIBFUNC, USERMETHOD
	};
	struct binding{
		char* pcKey;
		int scope;
		int isActive;
		int scope_space; //0 for program variable, 1 for function local, 2 for formal argument
		int offset; //offset in own scope space
		enum Type type;
		int lineno;
		struct binding *next;
	};
	void SymTable_new(){
        int i;
        oSymTable = (struct SymTable*)malloc(1*sizeof(struct SymTable));
        buckets = 509;
        oSymTable->numOfBindings = 0;
        oSymTable->table = (struct binding**)malloc(1*buckets*sizeof(struct binding*));
        for(i = 0; i < buckets; i++) oSymTable->table[i] = NULL;
	}

	void SymTable_free(){
			if(oSymTable == NULL) return;	
			free(oSymTable);
	}
	
	size_t SymTable_hash(char* pcKey){
        unsigned int ui;
        size_t uiHash = 0;
        int a;
        for (ui = 0; pcKey[ui] != '\0'; ui++){
                a = pcKey[ui]-'0';
                uiHash = ((uiHash * 10) + a)%buckets;
        }
        return uiHash;
    }

	void SymTable_change_visibility(const char *pcKey, int hide)
	{
		struct binding *current_node;
		size_t pos_hash;
		pos_hash=SymTable_hash(strdup(pcKey));
		current_node=oSymTable->table[pos_hash];
		while(current_node!=NULL)
		{
			if(strcmp(current_node->pcKey, pcKey)==0)
			{
				if(hide==0)
				{
					current_node->isActive=1;
				}
				if(hide==1)
				{
					current_node->isActive=0;
				}
			}	
			current_node=current_node->next;
		}	
	}

	void SymTable_find_by_type(enum Type type, int scope)
	{
		struct binding *current;
		for(int i=0; i<buckets; i++)
		{
			current=oSymTable->table[i];
		while(current!=NULL)
			{
				if(current->type==type && current->scope==scope)
				{
					SymTable_change_visibility(current->pcKey, 1);
				}
				current=current->next;
			}
		}
	}

	int SymTable_contains_no_scope(char* pcKey){
        struct binding *temp;
		size_t i;
		i=SymTable_hash(strdup(pcKey));
		temp = oSymTable->table[i];
        while(temp != NULL){
            if(strcmp(temp->pcKey, pcKey) == 0) return 1;
            temp = temp->next;
        }
        return 0;
    }

	int SymTable_contains(char* pcKey){
        struct binding *temp;
		size_t i;
		i=SymTable_hash(strdup(pcKey));
		temp = oSymTable->table[i];
        while(temp != NULL){
            if(strcmp(temp->pcKey, pcKey) == 0 && scope == temp->scope && temp->isActive == 1) return 1;
            temp = temp->next;
        }
        return 0;
    }

	int SymTable_LIBRARY_contains(const char* pcKey){
        struct binding *temp;
		size_t i;
		i=SymTable_hash(strdup(pcKey));
		temp = oSymTable->table[i];
        while(temp != NULL){
			if(strcmp(temp->pcKey, pcKey) == 0 && temp->type == LIBFUNC){ return 1;}
            temp = temp->next;
        }
        return 0;
    }

	int SymTable_contains_isACTIVE(char* pcKey){
        struct binding *temp;
		size_t i;
		i=SymTable_hash(strdup(pcKey));
		temp = oSymTable->table[i];
        while(temp != NULL){
            if(strcmp(temp->pcKey, pcKey) == 0 && temp->isActive == 1 && (temp->type == USERFUNCT || temp->type == FORMAL)) return 1;
            temp = temp->next;
        }
        return 0;
    }

	int SymTable_LOCAL_GLOBAL_isActive_contains(char *pcKey){
        struct binding *temp;
		size_t i;
		i=SymTable_hash(strdup(pcKey));
		temp = oSymTable->table[i];
        while(temp != NULL){
            if(strcmp(temp->pcKey, pcKey) == 0 && temp->isActive == 1 && (temp->type == __LOCAL || temp->type == GLOBAL)) return 1;
            temp = temp->next;
        }
        return 0;		
	}

	int SymTable_GLOBAL_isActive_contains(char *pcKey){
        struct binding *temp;
		size_t i;
		i=SymTable_hash(strdup(pcKey));
		temp = oSymTable->table[i];
        while(temp != NULL){
            if(strcmp(temp->pcKey, pcKey) == 0 && temp->isActive == 1 && temp->type == GLOBAL) return 1;
            temp = temp->next;
        }
        return 0;		
	}

	int SymTable_LOCAL_prev_scope_isActive_contains(char *pcKey){
        struct binding *temp;
		size_t i;
		i=SymTable_hash(strdup(pcKey));
		temp = oSymTable->table[i];
        while(temp != NULL){
            if(strcmp(temp->pcKey, pcKey) == 0 && temp->isActive == 1 && temp->type == __LOCAL && temp->scope == scope-1) return 1;
            temp = temp->next;
        }
        return 0;		
	}

	int SymTable_FORMAL_prev_scope_isActive_contains(char *pcKey){
        struct binding *temp;
		size_t i;
		i=SymTable_hash(strdup(pcKey));
		temp = oSymTable->table[i];
        while(temp != NULL){
            if(strcmp(temp->pcKey, pcKey) == 0 && temp->isActive == 1 && temp->type == FORMAL && temp->scope == scope-1) return 1;
            temp = temp->next;
        }
        return 0;		
	}

	int SymTable_LOCAL_all_prev_scope_isActive_contains(char *pcKey){
        struct binding *temp;
		size_t i;
		i=SymTable_hash(strdup(pcKey));
		temp = oSymTable->table[i];
        while(temp != NULL){
            if(strcmp(temp->pcKey, pcKey) == 0 && temp->isActive == 1 && temp->type == __LOCAL && temp->scope >= scope+2) return 1;
            temp = temp->next;
        }
        return 0;		
	}	

	int SymTable_LOCAL_isActive_contains(char *pcKey){
        struct binding *temp;
		size_t i;
		i=SymTable_hash(strdup(pcKey));
		temp = oSymTable->table[i];
        while(temp != NULL){
            if(strcmp(temp->pcKey, pcKey) == 0 && temp->isActive == 1 && temp->type == __LOCAL) return 1;
            temp = temp->next;
        }
        return 0;		
	}

	int SymTable_USERFUNCT_contains(char *pcKey){
        struct binding *temp;
		size_t i;
		i=SymTable_hash(strdup(pcKey));
		temp = oSymTable->table[i];
        while(temp != NULL){
			if(strcmp(temp->pcKey, pcKey) == 0 && temp->type == USERFUNCT){ return 1;}
            temp = temp->next;
        }
        return 0;		
	}

	int SymTable_prev_USERFUNCT_contains(char *pcKey){
        struct binding *temp;
		size_t i;
		i=SymTable_hash(strdup(pcKey));
		temp = oSymTable->table[i];
        while(temp != NULL){
			if(strcmp(temp->pcKey, pcKey) == 0 && temp->type == USERFUNCT && temp->scope == scope-1){ return 1;}
            temp = temp->next;
        }
        return 0;		
	}

	int SymTable_FORMAL_sameSCOPE_contains(char* pcKey){
        struct binding *temp;
		size_t i;
		i=SymTable_hash(strdup(pcKey));
		temp = oSymTable->table[i];
        while(temp != NULL){
            if(strcmp(temp->pcKey, pcKey) == 0 && scope == temp->scope && temp->isActive == 1 && temp->type == FORMAL) return 1;
            temp = temp->next;
        }
        return 0;
    }

	int SymTable_WHILE_FOR_IF_ELSE_contains(char *pcKey){
        struct binding *temp;
		size_t i;
		i=SymTable_hash(strdup(pcKey));
		temp = oSymTable->table[i];
        while(temp != NULL){
            if(strcmp(temp->pcKey, pcKey) == 0 && (scope == while_scope+1 ||scope == for_scope+1 ||scope == if_scope+1)) return 1;
            temp = temp->next;
        }
        return 0;		
	}

	int SymTable_getOffset(char *pcKey){
        struct binding *temp;
		size_t i;
		i=SymTable_hash(strdup(pcKey));
		temp = oSymTable->table[i];
        while(temp != NULL){
            if(strcmp(temp->pcKey, pcKey) == 0) return temp->offset;
            temp = temp->next;
        }
        return -1;		 
	}	

	int SymTable_getOffset_GLOBAL(char *pcKey){
        struct binding *temp;
		size_t i;
		i=SymTable_hash(strdup(pcKey));
		temp = oSymTable->table[i];
        while(temp != NULL){
            if(strcmp(temp->pcKey, pcKey) == 0 && temp->type == GLOBAL) return temp->offset;
            temp = temp->next;
        }
        return -1;		 
	}

	int SymTable_getOffset_LOCAL(char *pcKey){
        struct binding *temp;
		size_t i;
		i=SymTable_hash(strdup(pcKey));
		temp = oSymTable->table[i];
        while(temp != NULL){
            if(strcmp(temp->pcKey, pcKey) == 0 && temp->type == __LOCAL) return temp->offset;
            temp = temp->next;
        }
        return -1;		 
	}

	int SymTable_getOffset_FORMAL(char *pcKey){
        struct binding *temp;
		size_t i;
		i=SymTable_hash(strdup(pcKey));
		temp = oSymTable->table[i];
        while(temp != NULL){
            if(strcmp(temp->pcKey, pcKey) == 0 && temp->type == FORMAL) return temp->offset;
            temp = temp->next;
        }
        return -1;		 
	}

	int SymTable_getScopeSpace(char *pcKey){
        struct binding *temp;
		size_t i;
		i=SymTable_hash(strdup(pcKey));
		temp = oSymTable->table[i];
        while(temp != NULL){
            if(strcmp(temp->pcKey, pcKey) == 0) return temp->scope_space;
            temp = temp->next; 
        }
        return -1;		
	}

	int SymTable_getAdress(char *pcKey){
        struct binding *temp;
		size_t i;
		i=SymTable_hash(strdup(pcKey));
		temp = oSymTable->table[i];
        while(temp != NULL){
            if(strcmp(temp->pcKey, pcKey) == 0) return temp->lineno;
            temp = temp->next;
        }
        return -1;		
	}

enum vmarg_t{
    label_a = 0,
    global_a = 1,
    formal_a = 2,
    local_a = 3,
    number_a = 4,
    string_a = 5,
    bool_a = 6,
    nil_a = 7,
    userfunc_a = 8,
    libfunc_a = 9,
    retval_a=10
};

	struct binding *SymTable_getBinding(char *pcKey, enum vmarg_t t){
		int i = SymTable_hash(strdup(pcKey));
		struct binding *curr = oSymTable->table[i];
		while(curr != NULL){
			if(t == 1){
				if(strcmp(curr->pcKey, pcKey) == 0 && curr->type == GLOBAL) return curr;
			}
			else if(t == 2){
				if(strcmp(curr->pcKey, pcKey) == 0 && curr->type == FORMAL) return curr;
			}
			else if(t == 3){
				if(strcmp(curr->pcKey, pcKey) == 0 && curr->type == __LOCAL) return curr;
			}
			else if(t == 8){
				if(strcmp(curr->pcKey, pcKey) == 0 && curr->type == USERFUNCT) return curr;
			}
			else if(t == 9){
				if(strcmp(curr->pcKey, pcKey) == 0 && curr->type == LIBFUNC) return curr;
			}
			curr = curr->next;
		}
		return NULL;
	}

	void SymTable_put(int scope, int lineno, enum Type type, char* pcKey, int scope_space, int offset){
			struct binding *node;
			size_t pos;
			switch(oSymTable->numOfBindings){
					case 509:
							buckets = 1021;
							oSymTable->table = (struct binding**)realloc(oSymTable->table,1*buckets*sizeof(struct binding*));
							break;
					case 1021:
							buckets = 2053;
							oSymTable->table = (struct binding**)realloc(oSymTable->table,1*buckets*sizeof(struct binding*));
							break;
					case 2053:
							buckets = 4093;
							oSymTable->table = (struct binding**)realloc(oSymTable->table,1*buckets*sizeof(struct binding*));
							break;
					case 4093:
							buckets = 8191;
							oSymTable->table = (struct binding**)realloc(oSymTable->table,1*buckets*sizeof(struct binding*));
							break;
					case 8191:
							buckets = 16381;
							oSymTable->table = (struct binding**)realloc(oSymTable->table,1*buckets*sizeof(struct binding*));
							break;
					case 16381:
							buckets = 32771;
							oSymTable->table = (struct binding**)realloc(oSymTable->table,1*buckets*sizeof(struct binding*));
							break;
					case 32771:
							buckets = 65521;
							oSymTable->table = (struct binding**)realloc(oSymTable->table,1*buckets*sizeof(struct binding*));
							break;
					default:
							break;
			}
			pos = SymTable_hash(strdup(pcKey));
			node = (struct binding*)malloc(sizeof(struct binding));
			node->scope = scope;
			node->lineno = lineno;
			node->type = type;
			node->pcKey = strdup(pcKey);
			node->scope_space = scope_space;
			node->offset = offset;
			oSymTable->numOfBindings++; 
			if(oSymTable->table[pos] == NULL){
				oSymTable->table[pos] = node;
				node->next = NULL;
			}
			else{
					struct binding* temp;
					temp = oSymTable->table[pos];
					while(temp->next != NULL){
						temp=temp->next;
					}
					temp->next = node;
					node->next = NULL;
			}
	} 

	void SymTable_PRINT()
	{
		struct binding *current;
		int max_scope=0;
		for(int i=0; i<buckets; i++)
		{
			current=oSymTable->table[i];
			
			while(current != NULL) 
			{
				if(current->scope>max_scope )
				{
					max_scope=current->scope; 

				}
				current=current->next;
				
			}
		}
		for(int i=0; i<=max_scope; i++)
		{
			int lala=0;
			for(int j=0; j<buckets; j++)
			{
				current=oSymTable->table[j];
				while(current!=NULL)
				{
					if(current->scope==i)
					{
						if(lala==0)
						{
							std::cout<<"\033[1;32m";
							std::cout<<"-----\tScope "<<i<<"\t-----"<<std::endl;
							std::cout<<"\033[0m";
							lala++;
						}
						
						if(current->type==LIBFUNC)
						{
							std::cout<<"\""<<current->pcKey<<"\""<<"  [library function]  "<<"(line-address "<<current->lineno<<")"<<"  (scope "<<current->scope<<")"<<std::endl;
						}
						if(current->type==USERFUNCT)
						{
							std::cout<<"\""<<current->pcKey<<"\""<<"  [user function]  "<<"(line-address "<<current->lineno<<")"<<"  (scope "<<current->scope<<")"<<
							"  (total function local variables "<<current->offset<<")"<<std::endl;
						}
						if(current->type==FORMAL)
						{
							std::cout<<"\""<<current->pcKey<<"\""<<"  [formal argument]  "<<"(line "<<current->lineno<<")"<<"  (scope "<<current->scope<<")"<<
							"  (formal scope space)  (offset "<<current->offset<<")"<<std::endl;
						}
						if(current->type==GLOBAL)
						{
							std::cout<<"\""<<current->pcKey<<"\""<<"  [global variable]  "<<"(line "<<current->lineno<<")"<<"  (scope "<<current->scope<<")"<<
							"  (program scope space)  (offset "<<current->offset<<")"<<std::endl;
						}
						if(current->type==__LOCAL)
						{
							if(current->scope_space == 0) std::cout<<"\""<<current->pcKey<<"\""<<"  [local variable]  "<<"(line "<<current->lineno<<")"<<
							"  (scope "<<current->scope<<")"<<"  (program scope space)  (offset "<<current->offset<<")"<<std::endl;
							else if(current->scope_space == 1) std::cout<<"\""<<current->pcKey<<"\""<<"  [local variable]  "<<"(line "<<current->lineno<<")"<<
							"  (scope "<<current->scope<<")"<<"  (function scope space)  (offset "<<current->offset<<")"<<std::endl;

						}
					}
					current=current->next; 
				}
			}
		}
	}
  
enum vmopcode   
{	assign_v,	add_v,  	sub_v,
	mul_v, 		div_v, 		mod_v,  
	uminus_v, 	and_v, 		or_v,
	not_v, 		jeq_v, 		jne_v,
	jgt_v, 		jlt_v, 		jge_v,
	jle_v, 		jump_v, 	call_v, 
	funcenter_v, 	funcexit_v, 	newtable_v,
	tablegetelem_v,	tablesetelem_v,	pusharg_v,
	nop_v
};

typedef struct vmarg__{
    enum vmarg_t type;
	struct binding *sym_table_binding;
    string sym;
    double numVal;
	string strVal;
    bool booleanVal;
    int label;
    int index;
    
    vmarg__(vmarg_t type, string sym, double numVal, string strVal,bool booleanVal, int label)
    {
       this->type=type;
       this->sym.assign(sym);
       this->numVal=numVal;
	   this->strVal=strVal;
       this->booleanVal=booleanVal;
       this->label=label; 
    }
    vmarg__()
    {
        
    }
}vmarg;
 
struct instruction {
    vmopcode opcode;
    vmarg *result;
    vmarg *arg1;
    vmarg *arg2;
    int srcLine;
    instruction(vmopcode opcode, vmarg *result, vmarg *arg1, vmarg *arg2, int srcLine)
    {
        this->opcode=opcode;
        this->result=result;
        this->arg1=arg1;
        this->arg2=arg2;
        this->srcLine=srcLine;
    }

	instruction(){}
}; 

typedef struct userFuncs
{
  unsigned address;
  unsigned endaddress;
  unsigned numArguments;
  unsigned localSize;
  char*	   id;
}userFunc;