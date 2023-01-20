#include "avm_and_target.hpp"

unsigned char executionFinished = 0; 
unsigned int	pc = 0;  
unsigned int	currLine = 0;      
unsigned int	codeSize = 0;  
string print_string;
int count_args=0;
int topsp, top, old_top, old_topsp, old_pc;   
int totalActuals=0;  
int curr_function = -1;
int avm_offset = -1;
int avm_local_offset = 0;
bool seen_global = false;
bool active_table = false;
struct instruction *instr = new instruction();
int count_instr = 0;
vector<vmarg>number_table; 
vector<vmarg>string_table; 
vector<vmarg>boolean_table;
vector<vmarg>userfunc_table; 
vector<vmarg>libfunc_table; 
vector<vmarg>global_table;
vector<vmarg>local_table;
vector<vmarg>formal_table;
#define AVM_MAX_INSTRUCTIONS nop_v
#define AVM_ENDING_PC codeSize
#define AVM_TABLE_HASHSIZE 211
#define AVM_NUMACTUALS_OFFSET 	+4
#define AVM_SAVEDPC_OFFSET	+3
#define AVM_SAVEDTOP_OFFSET	+2
#define AVM_SAVEDTOPSP_OFFSET	+1
#define AVM_STACKENV_SIZE 4
#define AVM_END_OF_LOCALS topsp + local_table.size()
#define execute_add execute_arithmetic
#define execute_sub execute_arithmetic
#define execute_mul execute_arithmetic
#define execute_div execute_arithmetic
#define execute_mod execute_arithmetic

typedef enum avm_memcell_t {
  number_m, 	
  string_m,		
  bool_m,		 
  table_m,		
  userfunc_m,	
  libfunc_m,	
  nil_m,		
  undef_m,		
}avm_memcell_t; 

typedef struct avm_table
{
  unsigned int		refCounter;
  struct avm_table_bucket* 	strIndexed[AVM_TABLE_HASHSIZE];
  struct avm_table_bucket*	numIndexed[AVM_TABLE_HASHSIZE];
  unsigned	int	total;
}avm_table;

typedef struct avm_memcells{
  avm_memcell_t type;
  union
  {
    double numVal;
    char* strVal;
    unsigned int boolVal;
    avm_table * tableVal;
    unsigned int funcVal;
    char* libfuncVal;
  }data;
} avm_memcell;
vector<userFunc> RuserFuncs;
void avm_initialize (void);
void avm_initstack(void);
avm_table* avm_newtable();
typedef char * (*tostring_func_t) (avm_memcell*);
unsigned char number_tobool(avm_memcell *);
string typeStrings[]={"number", "string", "bool", "table", "userfunc", "libfunc", "nil", "undef"};
void 			avm_callsaveenvironment (void);
typedef void (*memclear_func_t) (avm_memcell*);
void avm_memcellclear (avm_memcell *m);
void memclear_string(avm_memcell *m);
void memclear_table(avm_memcell *m);

memclear_func_t memclearFuncs[] =
{
  0, /*number*/
  memclear_string,
  0, /*bool*/
  memclear_table,
  0, /*userfunc*/
  0, /*libfunc*/
  0, /*nil */
  0  /*undef*/
}; 

typedef struct avm_table_bucket{
  avm_memcell	*key;
  avm_memcell 	*value;
  struct avm_table_bucket * next;
  avm_table_bucket(avm_memcell *key, avm_memcell *value)
  {
      this->key=key;
      this->value=value;
  }
}avm_table_bucket;

void 			libfunc_print (void);			
void			libfunc_input (void);
void			libfunc_objectmemberkeys (void);
void			libfunc_objecttotalmembers (void);
void			libfunc_objectcopy (void);
void 			libfunc_totalarguments (void);		
void			libfunc_argument (void);
void 			libfunc_typeof (void);			
void			libfunc_strtonum (void);
void			libfunc_sqrt (void);
void			libfunc_cos (void);
void			libfunc_sin (void);
 
instruction*	code = (instruction*) 0;
avm_memcell *ax, *bx, *cx;
avm_memcell *retval;
vector <avm_memcell> avm_stack;
#define AVM_STACKSIZE avm_stack.size()
typedef void (*execute_func_t)(instruction *);
void execute_assign(instruction*);
void execute_add(instruction*); 
void execute_sub(instruction*);
void execute_mul(instruction*);
void execute_div(instruction*);
void execute_mod(instruction*);
void execute_jeq(instruction*);
void execute_jne(instruction*);
void execute_jle(instruction*);
void execute_jge(instruction*);
void execute_jlt(instruction*);
void execute_jgt(instruction*);
void execute_jump(instruction*);
void execute_call(instruction*);
void execute_pusharg(instruction*);
void execute_funcenter(instruction*);
void execute_funcexit(instruction*);
void execute_newtable(instruction*);
void execute_tablegetelem(instruction*);
void execute_tablesetelem(instruction*);
//void execute_nop(instruction*);

execute_func_t executeFuncs[] = {
    execute_assign,  /// 0
    execute_add,
    execute_sub,
    execute_mul,
    execute_div,
    execute_mod,
    0,  // uminus
    0,  // and
    0,  // or
    0,  // not
    execute_jeq,
    execute_jne,
    execute_jgt,
    execute_jlt,
    execute_jge,
    execute_jle,
    execute_jump,
    execute_call,
    execute_funcenter,
    execute_funcexit,
    execute_newtable,
    execute_tablegetelem,
    execute_tablesetelem,
    execute_pusharg
    // execute_nop
};

void avm_dec_top()
{
    if(top < -1)
    {  
        cerr<<"Stack Overflow"<<endl;
        executionFinished=1;
    }
    else
        ++top;
} 

typedef void (*library_func_t)(void);

void memclear_string(avm_memcell *m)
{
  free(m->data.strVal);
}
void avm_tablebucketsdestroy (avm_table_bucket ** p)
{
  unsigned i;
  avm_table_bucket *b;
  avm_table_bucket * del;
  for(i =0; i<AVM_TABLE_HASHSIZE;i++)
  {
    for(b = *p; b;)
    {
      del = b;
      b = b->next;
      avm_memcellclear(del->key);
      avm_memcellclear(del->value);
      free(del);
    }
    p[i] = (avm_table_bucket*) 0;
  }
}

void avm_tabledestroy(avm_table *t)
{
    avm_tablebucketsdestroy(t->strIndexed);
    avm_tablebucketsdestroy(t->numIndexed);
    free(t);
}
void avm_tabledecrefcounter(struct avm_table *a_t){
    if(!--a_t->refCounter)
        avm_tabledestroy(a_t);
}

void memclear_table(avm_memcell *m)
{
  avm_tabledecrefcounter(m->data.tableVal);
}
void execute_jump(instruction *instr)
{
    if(!executionFinished && instr->result ) pc = instr->result->label - 1;
}

char *number_tostring 	(avm_memcell *);
char *string_tostring 	(avm_memcell *);
char *bool_tostring	(avm_memcell *);
char *table_tostring   	(avm_memcell *);
char *userfunc_tostring	(avm_memcell *);
char *libfunc_tostring	(avm_memcell *);
char *nil_tostring	(avm_memcell *);
char *undef_tostring	(avm_memcell *);
tostring_func_t tostringFuncs[]= 
{
  number_tostring,
  string_tostring,
  bool_tostring,
  table_tostring,
  userfunc_tostring,
  libfunc_tostring,
  nil_tostring,
  undef_tostring
};
typedef unsigned char (*tobool_func_t)(avm_memcell*);
unsigned char number_tobool(avm_memcell *m){return m->data.numVal != 0;}
unsigned char string_tobool(avm_memcell *m){return m->data.strVal[0] != 0;}
unsigned char bool_tobool(avm_memcell *m){return m->data.boolVal;}
unsigned char table_tobool(avm_memcell *m){return 1;}
unsigned char userfunc_tobool(avm_memcell *m){return 1;}
unsigned char libfunc_tobool(avm_memcell *m){return 1;}
unsigned char nil_tobool(avm_memcell *m){return 0;}
unsigned char undef_tobool(avm_memcell *m){assert(0); return 0;}

tobool_func_t toboolFuncs[]=
{
  number_tobool,
  string_tobool,
  bool_tobool,
  table_tobool,
  userfunc_tobool,
  libfunc_tobool,
  nil_tobool,
  undef_tobool
};
char *print_table(avm_memcell *m)
{
    avm_memcell *temp=m;
    assert(temp);
    string s="";
    s+="[";
    for(int i=0; i<AVM_TABLE_HASHSIZE; i++)
    {
        if(temp->data.tableVal->strIndexed[i]!=NULL)
        {
            s+="{ ";
            if(temp->data.tableVal->strIndexed[i]->key->type==table_m)
            {
                if(temp->data.tableVal->strIndexed[i]->key!=NULL)
                    s+=print_table(temp->data.tableVal->strIndexed[i]->key);
            }
            else{ 
                if(temp->type==string_m)
                {
                    ostringstream out;
	                out<<s<<temp->data.strVal;
	                s=out.str();
                }
                else if(temp->type==bool_m)
                {
                    ostringstream out;
	                out<<s<<temp->data.boolVal;
	                s=out.str();
                }
                else if(temp->type==userfunc_m)
                {
                    ostringstream out;
	                out<<s<<temp->data.funcVal;
	                s=out.str();
                }
                else if(temp->type==number_m)
                {
                    ostringstream out;
	                out<<s<<temp->data.numVal;
	                s=out.str();
                }
                else if(temp->type==libfunc_m)
                {
                    ostringstream out;
	                out<<s<<temp->data.libfuncVal;
	                s=out.str();
                }
            }
            s+=": ";
            if(temp->data.tableVal->strIndexed[i]->value->type==table_m)
            {
                if(temp->data.tableVal->strIndexed[i]->value)
                    s+=print_table(temp->data.tableVal->strIndexed[i]->value);
            }
            else{
                if(temp->type==string_m)
                {
                    ostringstream out;
	                out<<s<<temp->data.strVal;
	                s=out.str();
                }
                else if(temp->type==bool_m)
                {
                    ostringstream out;
	                out<<s<<temp->data.boolVal;
	                s=out.str();
                }
                else if(temp->type==userfunc_m)
                {
                    ostringstream out;
	                out<<s<<temp->data.funcVal;
	                s=out.str();
                }
                else if(temp->type==number_m)
                {
                    ostringstream out;
	                out<<s<<temp->data.numVal;
	                s=out.str();
                }
                else if(temp->type==libfunc_m)
                {
                    ostringstream out;
	                out<<s<<temp->data.libfuncVal;
	                s=out.str();
                }
            }
            s+="} ";
            temp->data.tableVal->strIndexed[i]=temp->data.tableVal->strIndexed[i]->next;   
        }
        if(temp->data.tableVal->numIndexed[i]!=NULL)
        {
            s+="{ ";
            if(temp->data.tableVal->numIndexed[i]->key->type==table_m)
            {
                if (temp->data.tableVal->numIndexed[i]->key)
                    s+=print_table(temp->data.tableVal->numIndexed[i]->key);
            }
            else{
                if(temp->type==string_m)
                {
                    ostringstream out;
	                out<<s<<temp->data.strVal;
	                s=out.str();
                }
                else if(temp->type==bool_m)
                {
                    ostringstream out;
	                out<<s<<temp->data.boolVal;
	                s=out.str();
                }
                else if(temp->type==userfunc_m)
                {
                    ostringstream out;
	                out<<s<<temp->data.funcVal;
	                s=out.str();
                }
                else if(temp->type==number_m)
                {
                    ostringstream out;
	                out<<s<<temp->data.numVal;
	                s=out.str();
                }
                else if(temp->type==libfunc_m)
                {
                    ostringstream out;
	                out<<s<<temp->data.libfuncVal;
	                s=out.str();
                }
            }
            s+=": ";
            if(temp->data.tableVal->numIndexed[i]->value->type==table_m)
            {
                if(temp->data.tableVal->numIndexed[i]->value)
                    s+=print_table(temp->data.tableVal->numIndexed[i]->value);
            }
            else{
                if(temp->type==string_m)
                {
                    ostringstream out;
	                out<<s<<temp->data.strVal;
	                s=out.str();
                }
                else if(temp->type==bool_m)
                {
                    ostringstream out;
	                out<<s<<temp->data.boolVal;
	                s=out.str();
                }
                else if(temp->type==userfunc_m)
                {
                    ostringstream out;
	                out<<s<<temp->data.funcVal;
	                s=out.str();
                }
                else if(temp->type==number_m)
                {
                    ostringstream out;
	                out<<s<<temp->data.numVal;
	                s=out.str();
                }
                else if(temp->type==libfunc_m)
                {
                    ostringstream out;
	                out<<s<<temp->data.libfuncVal;
	                s=out.str();
                }
            }
            s+="} ";
            temp->data.tableVal->numIndexed[i] = temp->data.tableVal->numIndexed[i]->next;
        }
    }
    s+="]";
	return (char*)s.c_str();
}
char *number_tostring 	(avm_memcell *m)
{
  assert(m &&  m->type == number_m);
  char *buf = (char*)malloc (15*sizeof(char));
  sprintf(buf, "%lf", m->data.numVal);
  return buf;
}
char *string_tostring 	(avm_memcell *m)
{
  assert(m&& m->type == string_m);
  char *buf = (char*)malloc(15*sizeof(char));
  buf = strdup (m->data.strVal);
  return buf;
}
char *bool_tostring	(avm_memcell *m)
{
  assert(m && m->type == bool_m);
  if(m->data.boolVal ==0)
    return "false";
  else
    return "true";
}
void clear_str(char **ar)
{
  int i;
  for(i=0;i<strlen(*ar);i++)
    *ar[i]='\0';
}
char *userfunc_tostring	(avm_memcell *m)
{
  assert(m && m->type == userfunc_m);
  char *buf = (char*)malloc(50*sizeof(char));
  sprintf(buf, "%d", m->data.funcVal);
  return buf;
}
char *libfunc_tostring	(avm_memcell *m)
{
  	assert(m && m->type == libfunc_m);
	char *buf;
	buf = strdup(m->data.libfuncVal);
	return buf;
}
char *nil_tostring	(avm_memcell *m)
{
  assert(m && m->type == nil_m);
  return "nil";
}
char *undef_tostring	(avm_memcell *m)
{
  assert(m && m->type == undef_m);
  return "undef";
}
char *table_tostring   	(avm_memcell *m) 
{
  assert(m && m->type == table_m);
   return print_table(m);
}
unsigned char avm_tobool(avm_memcell *m){
    assert(m->type >= 0 && m->type < undef_m);
    return (*toboolFuncs[m->type])(m);
}
char * avm_tostring(avm_memcell *m){
     assert(m->type>=0 && m->type<=undef_m);
     return (*tostringFuncs[m->type])(m);
}
avm_memcell *avm_translate_operand(vmarg* arg, avm_memcell *reg){
    switch(arg->type){
        //variables
        case global_a:{
            int offset = SymTable_getOffset_GLOBAL((char*)arg->sym.c_str());
            return &avm_stack[offset];
        }
        case local_a:{
            int offset = SymTable_getOffset_LOCAL((char*)arg->sym.c_str());
            return &avm_stack[topsp + offset + 1];
        } 
        case formal_a:{
            int offset = SymTable_getOffset_FORMAL((char*)arg->sym.c_str());
            return &avm_stack[AVM_END_OF_LOCALS + 1 + offset];
        }
        case retval_a:{ 
            avm_offset = SymTable_getOffset_GLOBAL((char*)arg->sym.c_str());
            retval->type = avm_stack[avm_offset].type;
            retval->data.numVal = avm_stack[avm_offset].data.numVal;  
            retval->data.strVal = avm_stack[avm_offset].data.strVal;     
            retval->data.boolVal = avm_stack[avm_offset].data.boolVal; 
            retval->data.funcVal = avm_stack[avm_offset].data.funcVal; 
            retval->data.libfuncVal = avm_stack[avm_offset].data.libfuncVal;  
            retval->data.tableVal = avm_stack[avm_offset].data.tableVal;
            if(avm_offset == -1){
                avm_offset = SymTable_getOffset_LOCAL((char*)arg->sym.c_str());
                avm_offset = topsp + avm_offset + 1;
                retval->type = avm_stack[avm_offset].type;
                retval->data.numVal = avm_stack[avm_offset].data.numVal;  
                retval->data.strVal = avm_stack[avm_offset].data.strVal;     
                retval->data.boolVal = avm_stack[avm_offset].data.boolVal; 
                retval->data.funcVal = avm_stack[avm_offset].data.funcVal; 
                retval->data.libfuncVal = avm_stack[avm_offset].data.libfuncVal;  
                retval->data.tableVal = avm_stack[avm_offset].data.tableVal;
            }
            return retval;
        } 
        //constants
        case number_a:{
            if(reg == ax){
                ax->type = number_m;
                ax->data.numVal = arg->numVal;
            }           
            else if(reg == bx){
                bx->type = number_m;
                bx->data.numVal = arg->numVal;               
            }
            else if(reg = cx){
                cx->type = number_m;
                cx->data.numVal = arg->numVal;
            }
            break;
        } 
        case string_a:{ 
            if(reg == ax){
                ax->type = string_m; 
                ax->data.strVal = (char*)arg->strVal.c_str();
            }           
            else if(reg == bx){
                bx->type = string_m;
                bx->data.strVal = (char*)arg->strVal.c_str();             
            }
            else if(reg = cx){
                cx->type = string_m;
                cx->data.strVal = (char*)arg->strVal.c_str();
            }   
            break;      
        }
        case bool_a:{  
            if(reg == ax){
                ax->type = bool_m;
                ax->data.boolVal = arg->booleanVal; 
            }           
            else if(reg == bx){
                bx->type = bool_m;
                bx->data.boolVal = arg->booleanVal;               
            }
            else if(reg = cx){
                cx->type = bool_m;
                cx->data.boolVal = arg->booleanVal; 
            }   
            break;          
        }
        case nil_a:{
            if(reg == ax){
                ax->type = nil_m;
            }           
            else if(reg == bx){
                bx->type = nil_m;             
            }
            else if(reg = cx){
                cx->type = nil_m;
            }          
            break;
        }
        //functions
        case userfunc_a:{ 
            if(reg == ax){
                ax->type = userfunc_m;
                ax->data.funcVal = arg->numVal; 
                ax->data.strVal = (char*)arg->sym.c_str();
            }           
            else if(reg == bx){
                bx->type = userfunc_m;
                bx->data.funcVal = arg->numVal; 
                bx->data.strVal = (char*)arg->sym.c_str(); 
            }
            else if(reg = cx){
                cx->type = userfunc_m;
                cx->data.funcVal = arg->numVal;  
                cx->data.strVal = (char*)arg->sym.c_str();
            } 
            break;
        }
        case libfunc_a:{
            if(reg == ax){
                ax->type = libfunc_m;
                ax->data.libfuncVal = strdup((char*)arg->sym.c_str());
            }           
            else if(reg == bx){
                bx->type = libfunc_m;
                bx->data.libfuncVal = strdup((char*)arg->sym.c_str());              
            }
            else if(reg = cx){
                cx->type = libfunc_m;
                cx->data.libfuncVal = strdup((char*)arg->sym.c_str()); 
            } 
            break;
        }
        default: break;
    }
}

void avm_push_envvalue(int value)
{
    avm_stack[top].type=number_m;
    avm_stack[top].data.numVal=value;
    avm_dec_top();
}
void avm_callsaveenvironment(){
    old_pc = pc + 1;
    old_top = top;
    old_topsp = topsp;
}

library_func_t avm_getlibraryfunc (char *id){ 
    if(strcmp(id,"print") == 0){
        return libfunc_print;
    }
    else if(strcmp(id,"input") == 0){
        return libfunc_input;
    }
    else if(strcmp(id,"argument") == 0){
        return libfunc_argument;
    }
    else if(strcmp(id,"cos") == 0){
        return libfunc_cos;
    }
    else if(strcmp(id,"objectcopy") == 0){
        return libfunc_objectcopy;
    }
    else if(strcmp(id,"objectmemberkeys") == 0){
        return libfunc_objectmemberkeys;
    }
    else if(strcmp(id,"objecttotalmembers") == 0){
        return libfunc_objecttotalmembers;
    }
    else if(strcmp(id,"sin") == 0){
        return libfunc_sin;
    }
    else if(strcmp(id,"sqrt") == 0){
        return libfunc_sqrt;
    }
    else if(strcmp(id,"strtonum") == 0){
        return libfunc_strtonum;
    }
    else if(strcmp(id,"typeof") == 0){
        return libfunc_typeof;
    }
    else if(strcmp(id,"totalarguments") == 0){
        return libfunc_totalarguments;
    }
    return NULL;
}

void avm_calllibfunc(char *id){ 
    library_func_t f = avm_getlibraryfunc(id);
    if(!f){
        cout<< "unsupported lib func "<<id<<" called! ";
        executionFinished = 1;
    }
    else{
        (*f)();
        if(!executionFinished){
            execute_funcexit(NULL);
        }
    }
}

userFunc *avm_getFuncInfo(string str){ 
    userFunc *new_uf = new userFunc();
    
    new_uf->id = (char*)str.c_str();
    new_uf->localSize = 0;
    new_uf->numArguments = totalActuals;
    int index_start;

    for(int i = 0; i < instructions.size(); i++){
        if(instructions[i].opcode == funcenter_v && !instructions[i].result->sym.compare(str)){
            new_uf->address = i;
            index_start = i;
            break;
        }
    }

    for(int i = index_start+1; i < instructions.size(); i++){
        if(instructions[i].opcode == funcexit_v && !instructions[i].result->sym.compare(str)){
            new_uf->endaddress = instructions[i].srcLine;
            break;
        }
        new_uf->localSize++;
    }
    RuserFuncs.push_back(*new_uf);

    return new_uf;
}

void execute_call(instruction *instr)
{
    if(instr->result->type==userfunc_a)  
        ax->type = userfunc_m;
    else
        ax->type=libfunc_m;    
    ax->data.funcVal = instr->result->numVal;
    ax->data.strVal = (char*)instr->result->sym.c_str();
    ax->data.libfuncVal = (char*)instr->result->sym.c_str();
    switch (ax->type)
    {
        case userfunc_m :
        {
            curr_function++;
            avm_callsaveenvironment();
            userFunc *funcInfo = avm_getFuncInfo(instr->result->sym); 
            pc = funcInfo->address;
            execute_funcenter(instr);
            break;
        }
        case string_m :
            avm_calllibfunc(ax->data.strVal);
            break;
        case libfunc_m:
            avm_calllibfunc(ax->data.libfuncVal);
            break;
        default:
        {
            char *s = avm_tostring(ax);
            cerr<<"\nError: call : cannot bind \"%s\" to function! \n"<<s;
            free(s);
            executionFinished=1;
            break;
        }
    }
}

void execute_funcenter(struct instruction *in){
    totalActuals = 0;
}
unsigned avm_get_envvalue(unsigned i)
{
    unsigned val = (unsigned) avm_stack[i].data.numVal;
    return val;
}
 
void execute_funcexit(instruction* unused){
    curr_function--;
    top = old_top;
    pc = old_pc;
    topsp = old_topsp;
    for(int i=avm_stack.size()-1; i>avm_stack.size()-1-count_args; i--)
    {
        avm_stack[i].type=undef_m;
    }
    count_args=0;
}
void avm_assign(avm_memcell *lv, avm_memcell *rv)
{
    lv->type = rv->type;
    lv->data.strVal = rv->data.strVal;
    lv->data.numVal = rv->data.numVal;

    if(lv->type==string_m){
        lv->data.strVal=strdup(rv->data.strVal);
    }
    else if(lv->type==table_m)
    {
        lv->data.tableVal->refCounter++;
    }    

    if(avm_offset >= 0){
        avm_stack[avm_offset].type = lv->type;
        avm_stack[avm_offset].data.strVal = lv->data.strVal;
        avm_stack[avm_offset].data.numVal = lv->data.numVal;
    }
    avm_offset = -1;
}
void execute_pusharg(struct instruction *in){
    count_args++;
    avm_memcell *rv1 = new avm_memcell();
    if(in->result->type == 1 || in->result->type == 2 || in->result->type == 3 || in->result->type == 10){
        rv1 = avm_translate_operand(in->result, NULL);
    }
    else {
        avm_translate_operand(in->result, ax);
        rv1->type = ax->type;
        rv1->data.numVal = ax->data.numVal;  
        rv1->data.strVal = ax->data.strVal;
        //print_string=ax->data.strVal;
        rv1->data.boolVal = ax->data.boolVal; 
        rv1->data.funcVal = ax->data.funcVal; 
        rv1->data.libfuncVal = ax->data.libfuncVal;  
        rv1->data.tableVal = ax->data.tableVal;
    }
    assert(rv1); 
    avm_offset = AVM_END_OF_LOCALS + totalActuals + 1;
    avm_assign(&avm_stack[AVM_END_OF_LOCALS + totalActuals + 1], rv1);  
    ++totalActuals;
}

void execute_assign(instruction* in)
{
    avm_memcell *lv = avm_translate_operand(in->result, NULL);

    if(in->result->type == 1){
        avm_offset = SymTable_getOffset_GLOBAL((char*)in->result->sym.c_str());
    }
    else if(in->result->type == 3){
        avm_offset = SymTable_getOffset_LOCAL((char*)in->result->sym.c_str());
        avm_offset = topsp + avm_offset + 1;
    }
    else if(in->result->type == 10){
        avm_offset = SymTable_getOffset_GLOBAL((char*)in->result->sym.c_str());
        if(avm_offset == -1){
            avm_offset = SymTable_getOffset_LOCAL((char*)in->result->sym.c_str());
            avm_offset = topsp + avm_offset + 1;
        }
    }

	avm_memcell *rv1 = new avm_memcell();
    if(in->arg1->type == 1 || in->arg1->type == 2 || in->arg1->type == 3 || in->arg1->type == 10){
        rv1 = avm_translate_operand(in->arg1, NULL);
    }
    else {
        avm_translate_operand(in->arg1, ax);
        rv1->type = ax->type;
        rv1->data.numVal = ax->data.numVal;  
        rv1->data.strVal = ax->data.strVal;     
        rv1->data.boolVal = ax->data.boolVal; 
        rv1->data.funcVal = ax->data.funcVal; 
        rv1->data.libfuncVal = ax->data.libfuncVal;  
        rv1->data.tableVal = ax->data.tableVal;
    }
    avm_assign(lv, rv1);

}

void avm_memcellclear(avm_memcell *avm)
{
    assert(avm);
    memclear_func_t f;
    if(avm->type!=undef_m)
    {
        f=memclearFuncs[avm->type];
        if(f)
            (*f)(avm);
        avm->type=undef_m;
    }
}
void execute_jeq(instruction *in)
{
	avm_memcell *rv1 = new avm_memcell();
    if(in->arg1->type == 1 || in->arg1->type == 2 || in->arg1->type == 3 || in->arg1->type == 10){
        rv1 = avm_translate_operand(in->arg1, NULL);
    }
    else {
        avm_translate_operand(in->arg1, ax);
        rv1->type = ax->type;
        rv1->data.numVal = ax->data.numVal;  
        rv1->data.strVal = ax->data.strVal;     
        rv1->data.boolVal = ax->data.boolVal; 
        rv1->data.funcVal = ax->data.funcVal; 
        rv1->data.libfuncVal = ax->data.libfuncVal; 
        rv1->data.tableVal = ax->data.tableVal; 
    }

    avm_memcell *rv2 = new avm_memcell();
    if(in->arg2->type == 1 || in->arg2->type == 2 || in->arg2->type == 3 || in->arg2->type == 10){
        rv2 = avm_translate_operand(in->arg2, NULL);
    }
    else {
        avm_translate_operand(in->arg2, bx);
        rv2->type = bx->type;
        rv2->data.numVal = bx->data.numVal;   
        rv2->data.strVal = bx->data.strVal;     
        rv2->data.boolVal = bx->data.boolVal; 
        rv2->data.funcVal = bx->data.funcVal; 
        rv2->data.libfuncVal = bx->data.libfuncVal;   
        rv2->data.tableVal = bx->data.tableVal;    
    }
    int result;
    if(rv1->type==undef_m || rv2->type==undef_m)
    {
        cerr<<"jeq undefined"<<endl;     
        executionFinished=1;
    }
    else if(rv1->type==nil_m || rv2->type==nil_m)
        result=(rv1->type==nil_m && rv2->type==nil_m);
    else if(rv1->type==bool_m||rv2->type==bool_m)
        result = (avm_tobool(rv1) == avm_tobool(rv2));
    else if(rv1->type!=rv2->type)
    {
        cerr<<"\033[1;31mjeq illegal types\033[0m"<< rv1->type << " " << rv2->type << endl;
        executionFinished=1;
    }
    else{
        if(rv1->type==number_m && rv2->type==number_m){
            result=rv1->data.numVal==rv2->data.numVal;
        }
        if(rv1->type==string_m)
            result=!strcmp(rv1->data.strVal,rv2->data.strVal);
        if(rv1->type==table_m)
            result=(rv1->data.tableVal==rv2->data.tableVal);
        if(rv1->type==userfunc_m)
            result=(rv1->data.funcVal == rv2->data.funcVal);
        if(rv1->type==libfunc_m)
            result=!strcmp(rv1->data.libfuncVal,rv2->data.strVal);
    }
    if(!executionFinished && result){
        pc=in->result->label - 1; 
    }
}
void execute_jne(instruction *in)
{
	avm_memcell *rv1 = new avm_memcell();
    if(in->arg1->type == 1 || in->arg1->type == 2 || in->arg1->type == 3 || in->arg1->type == 10){
        rv1 = avm_translate_operand(in->arg1, NULL);
    }
    else {
        avm_translate_operand(in->arg1, ax);
        rv1->type = ax->type;
        rv1->data.numVal = ax->data.numVal;  
        rv1->data.strVal = ax->data.strVal;     
        rv1->data.boolVal = ax->data.boolVal; 
        rv1->data.funcVal = ax->data.funcVal; 
        rv1->data.libfuncVal = ax->data.libfuncVal;  
        rv1->data.tableVal = ax->data.tableVal;
    }

    avm_memcell *rv2 = new avm_memcell();
    if(in->arg2->type == 1 || in->arg2->type == 2 || in->arg2->type == 3 || in->arg2->type == 10){
        rv2 = avm_translate_operand(in->arg2, NULL);
    }
    else {
        avm_translate_operand(in->arg2, bx);
        rv2->type = bx->type;
        rv2->data.numVal = bx->data.numVal;   
        rv2->data.strVal = bx->data.strVal;     
        rv2->data.boolVal = bx->data.boolVal; 
        rv2->data.funcVal = bx->data.funcVal; 
        rv2->data.libfuncVal = bx->data.libfuncVal;   
        rv2->data.tableVal = bx->data.tableVal;    
    }
    int result=false;
    if(rv1->type==undef_m || rv2->type==undef_m)
    {
        cerr<<"jne undefined"<<endl;     
        executionFinished=1;
    }
    else if(rv1->type==nil_m || rv2->type==nil_m)
        result=(rv1->type==nil_m && rv2->type==nil_m);
    else if(rv1->type==bool_m||rv2->type==bool_m)
        result = (avm_tobool(rv1) == avm_tobool(rv2));
    else if(rv1->type!=rv2->type)
    {
        cerr<<"\033[1;31mjne illegal types\033[0m" << rv1->type << " " << rv2->type << endl;
        executionFinished=1;
    }
    else{
        if(rv1->type==number_m && rv2->type==number_m)
            result=rv1->data.numVal!=rv2->data.numVal;
        if(rv1->type==string_m)
            result=strcmp(rv1->data.strVal,rv2->data.strVal);
        if(rv1->type==table_m)
            result=(rv1->data.tableVal!=rv2->data.tableVal);
        if(rv1->type==userfunc_m)
            result=(rv1->data.funcVal != rv2->data.funcVal);
        if(rv1->type==libfunc_m)
            result=strcmp(rv1->data.libfuncVal,rv2->data.strVal);
    }
    if(!executionFinished && result){
        pc=in->result->label - 1; 
    }
}
void execute_jle(instruction *in)
{
	avm_memcell *rv1 = new avm_memcell();
    if(in->arg1->type == 1 || in->arg1->type == 2 || in->arg1->type == 3 || in->arg1->type == 10){
        rv1 = avm_translate_operand(in->arg1, NULL);
    }
    else {
        avm_translate_operand(in->arg1, ax);
        rv1->type = ax->type;
        rv1->data.numVal = ax->data.numVal;  
        rv1->data.strVal = ax->data.strVal;     
        rv1->data.boolVal = ax->data.boolVal; 
        rv1->data.funcVal = ax->data.funcVal; 
        rv1->data.libfuncVal = ax->data.libfuncVal;  
        rv1->data.tableVal = ax->data.tableVal;
    }

    avm_memcell *rv2 = new avm_memcell();
    if(in->arg2->type == 1 || in->arg2->type == 2 || in->arg2->type == 3 || in->arg2->type == 10){
        rv2 = avm_translate_operand(in->arg2, NULL);
    }
    else {
        avm_translate_operand(in->arg2, bx);
        rv2->type = bx->type;
        rv2->data.numVal = bx->data.numVal;   
        rv2->data.strVal = bx->data.strVal;     
        rv2->data.boolVal = bx->data.boolVal; 
        rv2->data.funcVal = bx->data.funcVal; 
        rv2->data.libfuncVal = bx->data.libfuncVal;   
        rv2->data.tableVal = bx->data.tableVal;    
    }
    int result;
    if(rv1->type==undef_m || rv2->type==undef_m)
    {
        cerr<<"jle undefined"<<endl;     
        executionFinished=1;
    }
    else if(rv1->type==nil_m || rv2->type==nil_m)
        result=(rv1->type==nil_m && rv2->type==nil_m);
    else if(rv1->type==bool_m||rv2->type==bool_m)
        result = (avm_tobool(rv1) == avm_tobool(rv2));
    else if(rv1->type!=rv2->type)
    {
        cerr<<"\033[1;31mjle illegal types\033[0m" << rv1->type << " " << rv2->type << endl; 
        executionFinished=1;
    }
    else{
        if(rv1->type==number_m && rv2->type==number_m)
            result=rv1->data.numVal<=rv2->data.numVal;
        if(rv1->type==string_m)
            result=strcmp(rv1->data.strVal,rv2->data.strVal);
        if(rv1->type==table_m)
            result=(rv1->data.tableVal<=rv2->data.tableVal);
        if(rv1->type==userfunc_m)
            result=(rv1->data.funcVal <= rv2->data.funcVal);
        if(rv1->type==libfunc_m)
            result=strcmp(rv1->data.libfuncVal,rv2->data.strVal);
    }
    if(!executionFinished && result){
        pc=in->result->label - 1; 
    }
}
void execute_jge(instruction *in)
{
	avm_memcell *rv1 = new avm_memcell();
    if(in->arg1->type == 1 || in->arg1->type == 2 || in->arg1->type == 3 || in->arg1->type == 10){
        rv1 = avm_translate_operand(in->arg1, NULL);
    }
    else {
        avm_translate_operand(in->arg1, ax);
        rv1->type = ax->type;
        rv1->data.numVal = ax->data.numVal;  
        rv1->data.strVal = ax->data.strVal;     
        rv1->data.boolVal = ax->data.boolVal; 
        rv1->data.funcVal = ax->data.funcVal; 
        rv1->data.libfuncVal = ax->data.libfuncVal;  
        rv1->data.tableVal = ax->data.tableVal;
    }

    avm_memcell *rv2 = new avm_memcell();
    if(in->arg2->type == 1 || in->arg2->type == 2 || in->arg2->type == 3 || in->arg2->type == 10){
        rv2 = avm_translate_operand(in->arg2, NULL);
    }
    else {
        avm_translate_operand(in->arg2, bx);
        rv2->type = bx->type;
        rv2->data.numVal = bx->data.numVal;   
        rv2->data.strVal = bx->data.strVal;     
        rv2->data.boolVal = bx->data.boolVal; 
        rv2->data.funcVal = bx->data.funcVal; 
        rv2->data.libfuncVal = bx->data.libfuncVal;   
        rv2->data.tableVal = bx->data.tableVal;    
    }
    int result;
    if(rv1->type==undef_m || rv2->type==undef_m)
    {
        cerr<<"jge undefined"<<endl;     
        executionFinished=1;
    }
    else if(rv1->type==nil_m || rv2->type==nil_m)
        result=(rv1->type==nil_m && rv2->type==nil_m);
    else if(rv1->type==bool_m||rv2->type==bool_m)
        result = (avm_tobool(rv1) == avm_tobool(rv2));
    else if(rv1->type!=rv2->type)
    {
        cerr<<"\033[1;31mjge illegal type\033[0m" << rv1->type << " " << rv2->type << endl;
        executionFinished=1;
    }
    else{
        if(rv1->type==number_m && rv2->type==number_m)
            result=rv1->data.numVal>=rv2->data.numVal;
        if(rv1->type==string_m)
            result=strcmp(rv1->data.strVal,rv2->data.strVal);
        if(rv1->type==table_m)
            result=(rv1->data.tableVal>=rv2->data.tableVal);
        if(rv1->type==userfunc_m)
            result=(rv1->data.funcVal>=rv2->data.funcVal);
        if(rv1->type==libfunc_m)
            result=strcmp(rv1->data.libfuncVal,rv2->data.strVal);
    }
    if(!executionFinished && result){
        pc=in->result->label - 1; 
    }
}
void execute_jlt(instruction *in)
{
	avm_memcell *rv1 = new avm_memcell();
    if(in->arg1->type == 1 || in->arg1->type == 2 || in->arg1->type == 3 || in->arg1->type == 10){
        rv1 = avm_translate_operand(in->arg1, NULL);
    }
    else {
        avm_translate_operand(in->arg1, ax);
        rv1->type = ax->type;
        rv1->data.numVal = ax->data.numVal;  
        rv1->data.strVal = ax->data.strVal;     
        rv1->data.boolVal = ax->data.boolVal; 
        rv1->data.funcVal = ax->data.funcVal; 
        rv1->data.libfuncVal = ax->data.libfuncVal;  
        rv1->data.tableVal = ax->data.tableVal;
    }

    avm_memcell *rv2 = new avm_memcell();
    if(in->arg2->type == 1 || in->arg2->type == 2 || in->arg2->type == 3 || in->arg2->type == 10){
        rv2 = avm_translate_operand(in->arg2, NULL);
    }
    else {
        avm_translate_operand(in->arg2, bx);
        rv2->type = bx->type;
        rv2->data.numVal = bx->data.numVal;   
        rv2->data.strVal = bx->data.strVal;     
        rv2->data.boolVal = bx->data.boolVal; 
        rv2->data.funcVal = bx->data.funcVal; 
        rv2->data.libfuncVal = bx->data.libfuncVal;   
        rv2->data.tableVal = bx->data.tableVal;    
    }
    int result;
    if(rv1->type==undef_m || rv2->type==undef_m)
    {
        cout<<"jlt undefined"<<endl;     
        executionFinished=1;
    }
    else if(rv1->type==nil_m || rv2->type==nil_m)
        result=(rv1->type==nil_m && rv2->type==nil_m); 
    else if(rv1->type==bool_m||rv2->type==bool_m)
        result = (avm_tobool(rv1) == avm_tobool(rv2));
    else if(rv1->type!=rv2->type)
    {
        cerr<<"jlt illegal types " << rv1->type << " " << rv2->type << endl;
        executionFinished=1;
    }
    else{
        if(rv1->type==number_m && rv2->type==number_m)
            result=rv1->data.numVal<rv2->data.numVal;
        if(rv1->type==string_m)
            result=strcmp(rv1->data.strVal,rv2->data.strVal);
        if(rv1->type==table_m)
            result=(rv1->data.tableVal<rv2->data.tableVal);
        if(rv1->type==userfunc_m)
            result=(rv1->data.funcVal < rv2->data.funcVal);
        if(rv1->type==libfunc_m)
            result=strcmp(rv1->data.libfuncVal,rv2->data.strVal);
    }
    if(!executionFinished && result){
        pc=in->result->label - 1; 
    }
}
void execute_jgt(instruction *in)
{
	avm_memcell *rv1 = new avm_memcell();
    if(in->arg1->type == 1 || in->arg1->type == 2 || in->arg1->type == 3 || in->arg1->type == 10){
        rv1 = avm_translate_operand(in->arg1, NULL);
    }
    else {
        avm_translate_operand(in->arg1, ax);
        rv1->type = ax->type;
        rv1->data.numVal = ax->data.numVal;  
        rv1->data.strVal = ax->data.strVal;     
        rv1->data.boolVal = ax->data.boolVal; 
        rv1->data.funcVal = ax->data.funcVal; 
        rv1->data.libfuncVal = ax->data.libfuncVal;  
        rv1->data.tableVal = ax->data.tableVal;
    }

    avm_memcell *rv2 = new avm_memcell();
    if(in->arg2->type == 1 || in->arg2->type == 2 || in->arg2->type == 3 || in->arg2->type == 10){
        rv2 = avm_translate_operand(in->arg2, NULL);
    }
    else {
        avm_translate_operand(in->arg2, bx);
        rv2->type = bx->type;
        rv2->data.numVal = bx->data.numVal;   
        rv2->data.strVal = bx->data.strVal;     
        rv2->data.boolVal = bx->data.boolVal; 
        rv2->data.funcVal = bx->data.funcVal; 
        rv2->data.libfuncVal = bx->data.libfuncVal;   
        rv2->data.tableVal = bx->data.tableVal;    
    }
    int result;
    if(rv1->type==undef_m || rv2->type==undef_m)
    {
        cout<<"jgt undefined"<<endl;     
        executionFinished=1;
    }
    else if(rv1->type==nil_m || rv2->type==nil_m) 
        result=(rv1->type==nil_m && rv2->type==nil_m);
    else if(rv1->type==bool_m||rv2->type==bool_m)
        result = (avm_tobool(rv1) == avm_tobool(rv2));
    else if(rv1->type!=rv2->type)
    {
        cerr<<"jgt illegal types " << rv1->type << " " << rv2->type << endl;
        executionFinished=1;
    }
    else{
        if(rv1->type==number_m && rv2->type==number_m)
            result=rv1->data.numVal>rv2->data.numVal;
        if(rv1->type==string_m)
            result=strcmp(rv1->data.strVal,rv2->data.strVal);
        if(rv1->type==table_m)
            result=(rv1->data.tableVal>rv2->data.tableVal);
        if(rv1->type==userfunc_m)
            result=(rv1->data.funcVal>rv2->data.funcVal);
        if(rv1->type==libfunc_m)
            result=strcmp(rv1->data.libfuncVal,rv2->data.strVal);
    }
    if(!executionFinished && result){
        pc=in->result->label - 1; 
    }
}

void execute_newtable(instruction *in){
    active_table = true;
    if(in->result->type == 1){
        avm_offset = SymTable_getOffset_GLOBAL((char*)in->result->sym.c_str());
    }
    else if(in->result->type == 3){
        avm_offset = SymTable_getOffset_LOCAL((char*)in->result->sym.c_str());
        avm_offset = topsp + avm_offset + 1;
    }
    else if(in->result->type == 10){
        avm_offset = SymTable_getOffset_GLOBAL((char*)in->result->sym.c_str());
        if(avm_offset == -1){
            avm_offset = SymTable_getOffset_LOCAL((char*)in->result->sym.c_str());
            avm_offset = topsp + avm_offset + 1;
        }
    }

    if(avm_offset >= 0){
        avm_stack[avm_offset].data.tableVal=avm_newtable(); 
        avm_stack[avm_offset].data.tableVal->refCounter++; 
        avm_stack[avm_offset].type = table_m; 
    }
    avm_offset = -1;
}

unsigned int avm_totalactuals(){
    return avm_get_envvalue(topsp + AVM_NUMACTUALS_OFFSET); 
}

avm_memcell* avm_getactual (unsigned int i)
{
  assert (i < avm_totalactuals());
  return &avm_stack[topsp + AVM_STACKENV_SIZE + 1 + i];
}

void libfunc_input()
{
    string s;
    cout<<"Dwse input: ";
    cin>>s;
    bool flag=false;
    if(s[0]=='"' && s[s.size()-1]=='"')
    {
        retval->type=string_m;
        retval->data.strVal=strdup((char*)s.c_str());
    }
    else if(s.compare("true")==0 || s.compare("false")==0)
    {
        retval->type=bool_m;
        if(s.compare("true")==0)
        {
            retval->data.boolVal=1;
        }
        else
        {
            retval->data.boolVal=0;
        }
    }
    else if(isdigit(s[0]))
    {
        for(int i=0; i<s.size(); i++)
        {
            if(isalpha(s[i]))
            {
                flag=true;
                break;
            }
        }
        if(!flag)
        {
            retval->data.numVal=atoi((char*)s.c_str());
            retval->type=number_m;
        }
        else
        {
            retval->type=nil_m;
            cerr<<"Wrong input"<<endl;
        }
    }
    else{
        retval->type=nil_m;
        cerr<<"Wrong input"<<endl;
    }
}
avm_table *avm_newtable()
{
    avm_table *new_table = new avm_table();

    new_table->refCounter=new_table->total=0;
    for(int i=0; i<AVM_TABLE_HASHSIZE; i++)
    {
        new_table->numIndexed[i]=NULL;
        new_table->strIndexed[i]=NULL;
    }
    return new_table;

}
void libfunc_objectmemberkeys() 
{
    avm_memcell *cell=avm_getactual(0);
    int i=avm_totalactuals();
    if(cell->type!=table_m)
    {
        cerr<<"Invalid type argument"<<endl;
        executionFinished=1;
        return;
    }
    if(i!=1)
    {
        cerr<<"One argument expected"<<endl;
        executionFinished=1;
    }
    retval->type=table_m;
}

void libfunc_objectcopy()
{
    retval->type = avm_getactual(0)->type;
    retval->data.numVal = avm_getactual(0)->data.numVal;    
    retval->data.strVal = avm_getactual(0)->data.strVal; 
    retval->data.tableVal = avm_getactual(0)->data.tableVal; 
    retval->data.boolVal = avm_getactual(0)->data.boolVal; 
    retval->data.funcVal = avm_getactual(0)->data.funcVal; 
    retval->data.libfuncVal = avm_getactual(0)->data.libfuncVal; 
}

void libfunc_argument() 
{
    unsigned int n=avm_totalactuals();
    unsigned int p_topsp =avm_get_envvalue (topsp + AVM_SAVEDTOP_OFFSET);
    if(n!=1)
    {
        cerr<<"One argument expected"<<endl;
        executionFinished=1;
        return;
    }
    avm_memcell *c=avm_getactual(0);
    if(c->type!=number_m)
    {
        cerr<<"error"<<endl;
        executionFinished=1;
        return;
    }
    char* s=strdup(avm_tostring(c));
    int result=atoi(s);
    if(result<0 ||result>avm_get_envvalue(p_topsp + 2*AVM_NUMACTUALS_OFFSET))
    {
        retval->type=nil_m;
        retval->data.strVal="nil_m";
    }
    else{
        if(!p_topsp)
        {
            cerr<<"Error, not in function scope"<<endl;
            retval->type=nil_m;
        }
        else{
            retval->type=number_m;
            retval->data.numVal=avm_get_envvalue(p_topsp+2*AVM_NUMACTUALS_OFFSET+result+1);
        }
    }

}

void libfunc_objecttotalmembers()
{
    avm_memcell *cell=avm_getactual(0);
    int j=avm_totalactuals();
    if(cell->type!=table_m)
        cerr<<"Invalid argument type"<<endl;    
    if(j!=1)
    {
        executionFinished=1;
        cerr<<"Only one argument expected"<<endl;
    }
    else{
        retval->type=number_m;
        retval->data.numVal=cell->data.tableVal->total;
    }    
}

void libfunc_sqrt()
{
    retval->type = number_m;
    retval->data.numVal = sqrt(avm_getactual(0)->data.numVal);
}

void libfunc_cos()
{
    retval->type = number_m;
    retval->data.numVal = cos(avm_getactual(0)->data.numVal);
}

void libfunc_sin()
{
    retval->type = number_m;
    retval->data.numVal = sin(avm_getactual(0)->data.numVal);
}

void libfunc_print()
{
    if(print_string!="")
        cout<<print_string<<endl;
    
}

void libfunc_typeof(){
    unsigned int n = totalActuals;

    if(n != 1) 
        cerr << "one argument (not " << n << ") expected in 'typeof'!" << endl;
    else{
        retval->type = string_m;
        retval->data.strVal = strdup((char*)typeStrings[avm_getactual(0)->type].c_str()); 
    }
}


void libfunc_totalarguments(){
    free(retval);
    retval->type = number_m;
    retval->data.numVal = RuserFuncs[curr_function].numArguments;
}

void libfunc_strtonum(){
    stringstream s_stream(avm_getactual(0)->data.strVal);
    
    double x = 0;

    s_stream >> x;

    retval->type = number_m;
    retval->data.numVal = x;
}



void avm_initialize()
{
    avm_initstack();
}

typedef double (*arithmetic_func_t) (double x, double y);
double add_impl(double x, double y){return x + y;}
double sub_impl(double x, double y){return x - y;}
double mul_impl(double x, double y){return x * y;}
double div_impl(double x, double y){
    if(y != 0) return x / y; 
    else cout << "ERROR: ***cannot divide by 0***" << endl;
}
double mod_impl(double x, double y){return ((unsigned int) x) % ((unsigned int) y);}
arithmetic_func_t arithmeticFuncs[] = {
    add_impl,
    sub_impl,
    mul_impl,
    div_impl,
    mod_impl
};
void execute_arithmetic(struct instruction *in){
    avm_memcell *lv = avm_translate_operand(in->result, NULL);
    if(in->result->type == 1){
        avm_offset = SymTable_getOffset_GLOBAL((char*)in->result->sym.c_str());
    }
    else if(in->result->type == 3){
        avm_offset = SymTable_getOffset_LOCAL((char*)in->result->sym.c_str());
        avm_offset = topsp + avm_offset + 1;
    }

	avm_memcell *rv1 = new avm_memcell();
    if(in->arg1->type == 1 || in->arg1->type == 2 || in->arg1->type == 3 || in->arg1->type == 10){
        rv1 = avm_translate_operand(in->arg1, NULL);
    }
    else {
        avm_translate_operand(in->arg1, ax);
        rv1->type = ax->type;
        rv1->data.numVal = ax->data.numVal;  
        rv1->data.strVal = ax->data.strVal;     
        rv1->data.boolVal = ax->data.boolVal; 
        rv1->data.funcVal = ax->data.funcVal; 
        rv1->data.libfuncVal = ax->data.libfuncVal;  
        rv1->data.tableVal = ax->data.tableVal;
    }

	avm_memcell *rv2 = new avm_memcell();
    if(in->arg2->type == 1 || in->arg2->type == 2 || in->arg2->type == 3 || in->arg2->type == 10){
        rv2 = avm_translate_operand(in->arg2, NULL);
    }
    else {
        avm_translate_operand(in->arg2, bx);
        rv2->type = bx->type;
        rv2->data.numVal = bx->data.numVal;  
        rv2->data.strVal = bx->data.strVal;     
        rv2->data.boolVal = bx->data.boolVal; 
        rv2->data.funcVal = bx->data.funcVal; 
        rv2->data.libfuncVal = bx->data.libfuncVal;  
        rv2->data.tableVal = bx->data.tableVal;
    }

    if(rv1->type == string_m && rv2->type == string_m){
        lv->type = string_m;
        strcat(rv1->data.strVal,rv2->data.strVal);
        lv->data.strVal = rv1->data.strVal;
        avm_stack[avm_offset].type = lv->type;
        avm_stack[avm_offset].data.strVal = lv->data.strVal;
        avm_stack[avm_offset].data.numVal = lv->data.numVal;
    }
    else if(rv1->type != number_m || rv2->type != number_m){
        cerr << "\033[1;31mNot a number in arithmetic\033[0m" << endl;
        executionFinished = 1;
    }
    else{
        arithmetic_func_t op = arithmeticFuncs[in->opcode - add_v];
        lv->type = number_m;
        lv->data.numVal = (*op)(rv1->data.numVal, rv2->data.numVal);
        avm_stack[avm_offset].type = lv->type;
        avm_stack[avm_offset].data.strVal = lv->data.strVal;
        avm_stack[avm_offset].data.numVal = lv->data.numVal;
    }
}

int avm_hashfunc(avm_memcell *index){
    if(index->type == string_m){
        unsigned int ui;
        size_t uiHash = 0;
        int a;
        for (ui = 0; index->data.strVal[ui] != '\0'; ui++){
                a = index->data.strVal[ui]-'0';
                uiHash = ((uiHash * 10) + a) % AVM_TABLE_HASHSIZE;
        }
        return uiHash;        
    }
    else if(index->type == number_m){
        return (int)((int)index->data.numVal % AVM_TABLE_HASHSIZE);         
    }
    return -1;
} 

avm_memcell  *avm_tablegetelem(avm_table *table, avm_memcell *index){
    unsigned int i;
   	avm_table_bucket* curr;
	avm_memcell* tmp;
	i = avm_hashfunc(index);
	int a,b;
   	if(i<0){
	  cerr<<"invalid array index!\n";
   	}
   	else{
        if(index->type == number_m){
            curr = table->numIndexed[i];
            while(curr){
            tmp = (avm_memcell*)curr->key;
            if(tmp->data.numVal==index->data.numVal)
                return (avm_memcell*)curr->value;
            curr = curr->next;
            }
        }
        else{
            curr = table->strIndexed[i];
            tmp =(avm_memcell*) curr->key;
            while(curr!=NULL){
                if(!strcmp(tmp->data.strVal,index->data.strVal))
                return (avm_memcell*)curr->value;
                curr = curr->next;
            }
        }
	}
   return 0;
}

void execute_tablegetelem(struct instruction *in){
    avm_memcell *lv = avm_translate_operand(in->result, NULL);
    avm_memcell *t = avm_translate_operand(in->arg1, NULL);
    avm_translate_operand(in->arg2, ax);
    avm_memcell *i = new avm_memcell();
    if(in->arg2->type == 1 || in->arg2->type == 2 || in->arg2->type == 3 || in->arg2->type == 10){
        i = avm_translate_operand(in->arg2, NULL);
    }
    else {
        avm_translate_operand(in->arg2, ax);
        i->type = ax->type;
        i->data.numVal = ax->data.numVal;  
        i->data.strVal = ax->data.strVal;     
        i->data.boolVal = ax->data.boolVal; 
        i->data.funcVal = ax->data.funcVal; 
        i->data.libfuncVal = ax->data.libfuncVal;  
        i->data.tableVal = ax->data.tableVal;
    }

    lv->type = nil_m;
    if(t->type != table_m){
        cerr << "illegal use of type " << typeStrings[t->type] <<" as table!" << endl; 
    }
    else{
        avm_memcell *content = avm_tablegetelem(t->data.tableVal, i); 
        if(content){
            if(in->result->type == 1){
                avm_offset = SymTable_getOffset_GLOBAL((char*)in->result->sym.c_str());
            }
            else if(in->result->type == 3){
                avm_offset = SymTable_getOffset_LOCAL((char*)in->result->sym.c_str());
                avm_offset = topsp + avm_offset + 1;
            }

            avm_assign(lv, content);
        }
        else{
            char* ts = avm_tostring(t); 
            char* is = avm_tostring(i);
            cerr << ts << "[" << is << "] not found!" << endl; 
            free(ts);
            free(is);
        }
    }
}
void avm_tablesetelem(avm_table *table, avm_memcell* index, avm_memcell* content)
{
    unsigned int i;
   	avm_table_bucket* curr = new avm_table_bucket(index, content);
	i = avm_hashfunc(index);

   	if(i<0){
	  cerr<<"invalid array index!\n";
   	}
   	else{
	  if(index->type == number_m){  
        if(table->numIndexed[i] == NULL){ 
            curr->next = table->numIndexed[i];
            table->numIndexed[i] = curr;
        }
        else table->numIndexed[i]->value = content;

	  }
	  else{
        if(table->strIndexed[i] == NULL){ 
            curr->next = table->strIndexed[i];
            table->strIndexed[i] = curr;
        }
        else table->strIndexed[i]->value = content;
	  }
	}   
}
void execute_tablesetelem(instruction *in){
    avm_memcell *t = avm_translate_operand(in->result, NULL);
    if(in->result->type == 1){
        avm_offset = SymTable_getOffset_GLOBAL((char*)in->result->sym.c_str());
    }
    else if(in->result->type == 3){
        avm_offset = SymTable_getOffset_LOCAL((char*)in->result->sym.c_str());
        avm_offset = topsp + avm_offset + 1;
    }
    else if(in->result->type == 10){
        avm_offset = SymTable_getOffset_GLOBAL((char*)in->result->sym.c_str());
        if(avm_offset == -1){
            avm_offset = SymTable_getOffset_LOCAL((char*)in->result->sym.c_str());
            avm_offset = topsp + avm_offset + 1;
        }
    }
    avm_memcell *i = new avm_memcell();
    if(in->arg1->type == 1 || in->arg1->type == 2 || in->arg1->type == 3 || in->arg1->type == 10){
        i = avm_translate_operand(in->arg1, NULL);
    }
    else {
        avm_translate_operand(in->arg1, ax);
        i->type = ax->type;
        i->data.numVal = ax->data.numVal;  
        i->data.strVal = ax->data.strVal;     
        i->data.boolVal = ax->data.boolVal; 
        i->data.funcVal = ax->data.funcVal; 
        i->data.libfuncVal = ax->data.libfuncVal;  
        i->data.tableVal = ax->data.tableVal;
    }
    avm_memcell *c = new avm_memcell();
    if(in->arg2->type == 1 || in->arg2->type == 2 || in->arg2->type == 3 || in->arg2->type == 10){
        c = avm_translate_operand(in->arg2, NULL);
    }
    else {
        avm_translate_operand(in->arg2, bx);
        c->type = bx->type;
        c->data.numVal = bx->data.numVal;  
        c->data.strVal = bx->data.strVal;     
        c->data.boolVal = bx->data.boolVal; 
        c->data.funcVal = bx->data.funcVal; 
        c->data.libfuncVal = bx->data.libfuncVal;  
        c->data.tableVal = bx->data.tableVal;
    }
    assert(i && c);   
    if(t->type != table_m){
        cout << "illegal use of type " << typeStrings[t->type] << " as table!" << endl;
    }   
    else{
        avm_tablesetelem(t->data.tableVal, i, c);
    }
}

void avm_initstack(){
    top = -1;
    topsp = 0;
    ax = new avm_memcell();
    bx = new avm_memcell();
    cx = new avm_memcell();
    retval = new avm_memcell();
}