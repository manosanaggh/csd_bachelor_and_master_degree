#include "my_header.hpp"
vector<struct vmarg__> vmargs;  
vector<int> funcstart_labels;
int funcstart_labels_counter=0;  
typedef void (*generator_func_t) (struct quad*);    
  
 
struct incomplete_jump
{ 
	unsigned int instrNo; /* The jump instruction number. */
	unsigned int iaddress; /* The i-code jump-target address */
	struct incomplete_jumps *next; /* A trivial linked list */
};

int make_binary_file(){
    ofstream wf2("target_code.txt", ios::out | ios::binary);

    if(!wf2){
        cout << "Cannot open file!" << endl;
        return 1;
    } 
     
    unsigned int magic_num = 340200501;

    wf2 << magic_num << "\n";

    wf2 << "\n";

    wf2 << "Number table: \n";

    wf2 << num_counter <<" \n";
    for(int i = 0; i < vmargs.size(); i++){
        if(vmargs[i].type == 4){
            wf2 << vmargs[i].numVal << "\n";
        }
    }

    wf2 << "String table: \n";

    wf2 << str_counter << "\n";

    for(int i = 0; i < vmargs.size(); i++){
        if(vmargs[i].type == 5){
            wf2 << vmargs[i].strVal << "\n";
        }
    }

    wf2 << "Boolean table: \n";

    wf2 <<bool_counter<< "\n";
 
    for(int i = 0; i < vmargs.size(); i++){
        if(vmargs[i].type == 6){
            wf2 << vmargs[i].booleanVal<< "\n";
        }
    }

    wf2 << "User function table: \n";

    wf2 << user_func_counter << "\n";

    for(int i = 0; i < vmargs.size(); i++){
        if(vmargs[i].type == 8){
            wf2 << vmargs[i].sym<< "\n";
        }
    }

    wf2 << "Library function table: \n";

    wf2 << lib_func_counter << "\n";

    for(int i = 0; i < buckets; i++){
        struct binding *curr = oSymTable->table[i];
        while(curr != NULL){
            if(curr->type == LIBFUNC){
                wf2 << curr->pcKey << "\n";
            }
            curr = curr->next;
        }
    }

    wf2 << "Global table: \n";

    wf2 << var_counter <<" \n";

    int max = 0;
    for(int i = 0; i < buckets; i++){
        struct binding *curr = oSymTable->table[i];
        while(curr != NULL){
            if(curr->type == GLOBAL && curr->offset > max) max = curr->offset;
            curr = curr->next;
        }
    }

    for(int off = 0; off <= max; off++){
        for(int i = 0; i < buckets; i++){
            struct binding *curr = oSymTable->table[i];
            while(curr != NULL){
                if(curr->type == GLOBAL && curr->offset == off){
                     wf2 << curr->pcKey << "\n";
                }
                curr = curr->next;
            }
        }        
    }

    wf2 << "Local table: \n";
    wf2 << var_counter <<" \n";

    max = 0;
    for(int i = 0; i < buckets; i++){
        struct binding *curr = oSymTable->table[i];
        while(curr != NULL){
            if(curr->type == __LOCAL && curr->offset > max) max = curr->offset;
            curr = curr->next;
        }
    }

    for(int off = 0; off <= max; off++){
        for(int i = 0; i < buckets; i++){
            struct binding *curr = oSymTable->table[i];
            while(curr != NULL){
                if(curr->type == __LOCAL && curr->offset == off){
                     wf2 << curr->pcKey << "\n";
                }
                curr = curr->next;
            }
        }        
    }

    wf2 << "Formal table: \n";
    wf2 << var_counter <<" \n";

    max = 0;
    for(int i = 0; i < buckets; i++){
        struct binding *curr = oSymTable->table[i];
        while(curr != NULL){
            if(curr->type == FORMAL && curr->offset > max) max = curr->offset;
            curr = curr->next;
        }
    }

    for(int off = 0; off <= max; off++){
        for(int i = 0; i < buckets; i++){
            struct binding *curr = oSymTable->table[i];
            while(curr != NULL){
                if(curr->type == FORMAL && curr->offset == off){
                     wf2 << curr->pcKey << "\n";
                }
                curr = curr->next;
            }
        }        
    }

    wf2 << "Symbol Table: \n";

    for(int i = 0; i < buckets; i++){
        struct binding *curr = oSymTable->table[i];
        while(curr != NULL){
            wf2 << curr->pcKey << " " << curr->scope << " " << 
            curr->isActive << " " << curr->scope_space << " " << 
            curr->offset << " " << curr->type << " " << 
            curr->lineno << "\n"; 
            curr = curr->next;
        }
    } 
    
    int i_size = instructions.size();

    wf2 << "Instructions: \n";

    wf2 << i_size << "\n";
    for(int i = 0; i < instructions.size(); i++){
        wf2 << instructions[i].opcode << "\n";
        if(instructions[i].result != NULL){
            instructions[i].result->sym_table_binding = SymTable_getBinding((char*)instructions[i].result->sym.c_str(), instructions[i].result->type);
            wf2 << "result "<<"struct " << instructions[i].result->type << " " << instructions[i].result->sym << " " << instructions[i].result->numVal << " " 
            << instructions[i].result->strVal << " " << instructions[i].result->booleanVal << " " << instructions[i].result->label
            << " " << instructions[i].result->index << "\n";
        }
        else
            wf2 << "result = NULL" << "\n";

        if(instructions[i].arg1 != NULL){
            instructions[i].arg1->sym_table_binding = SymTable_getBinding((char*)instructions[i].arg1->sym.c_str(), instructions[i].arg1->type);
            wf2 << "arg1 "<<"struct "  << instructions[i].arg1->type << " " << instructions[i].arg1->sym << " " << instructions[i].arg1->numVal << " " 
            << instructions[i].arg1->strVal << " " << instructions[i].arg1->booleanVal << " " << instructions[i].arg1->label
            << " " << instructions[i].arg1->index << "\n";
        }
        else wf2 << "arg1 = NULL" << "\n";

        if(instructions[i].arg2 != NULL){
            instructions[i].arg2->sym_table_binding = SymTable_getBinding((char*)instructions[i].arg2->sym.c_str(), instructions[i].arg2->type);          
            wf2 << "arg2 "<<"struct "  << instructions[i].arg2->type << " " << instructions[i].arg2->sym << " " << instructions[i].arg2->numVal << " " 
            << instructions[i].arg2->strVal << " " << instructions[i].arg2->booleanVal << " " << instructions[i].arg2->label
            << " " << instructions[i].arg2->index << "\n";  
        }  
        else  wf2 << "arg2 = NULL" << "\n";           
    } 

    wf2.close(); 

    if(!wf2.good()) {
        cout << "Error occurred at writing time!" << endl;
        return 1;
    }   
}

vmarg *make_operand(struct expr *e){
    vmarg *arg = new vmarg();
    switch(e->type){
        case var_e:
        {
            arg->numVal = SymTable_getOffset((char*)e->sym.c_str());
            arg->sym = e->sym;
            arg->strVal = e->strConst;
            arg->booleanVal = e->boolConst;
            int x = SymTable_getScopeSpace((char*)e->sym.c_str());
            switch(x){
                case 0: arg->type = global_a; break;
                case 1: arg->type = local_a; break;
                case 2: arg->type = formal_a; break;
                default: break;
            }
            arg->index = var_counter;
            var_counter++;
            break;
        }
        case tableitem_e:
        {
            arg->numVal = SymTable_getOffset((char*)e->sym.c_str());
            arg->sym = e->sym;
            arg->strVal = e->strConst;
            arg->booleanVal = e->boolConst;
            for(int i=0; i<e->sym.size(); i++)
            {
                if(e->sym[i]=='\"')
                {
                    arg->type=string_a;
                    arg->index = var_counter;
                    var_counter++;
                    return arg;
                }
            }
            switch(SymTable_getScopeSpace((char*)e->sym.c_str())){
                case 0: arg->type = global_a; break;
                case 1: arg->type = local_a; break;
                case 2: arg->type = formal_a; break;
                default: break;
            }
            arg->index = var_counter;
            var_counter++;
            break;
        }
        case arithexpr_e: 
        {
            arg->sym = e->sym;
            arg->numVal = e->numConst;
            arg->strVal = e->strConst;
            arg->booleanVal = e->boolConst;
            int x = SymTable_getScopeSpace((char*)e->sym.c_str());
            switch(x){
                case 0: arg->type = global_a; break;
                case 1: arg->type = local_a; break;
                case 2: arg->type = formal_a; break;
                default:  break;
            }
            arg->index = arg->sym[2] - '0';
            //t_counter++;
            break;            
        }
        case assignexpr_e:{
            //cout << "ass_e" << endl;
            arg->sym = e->sym;
            arg->numVal = e->numConst;
            arg->strVal = e->strConst;
            arg->booleanVal = e->boolConst;
            int x = SymTable_getScopeSpace((char*)e->sym.c_str());
            switch(x){
                case 0: arg->type = global_a; break;
                case 1: arg->type = local_a; break;
                case 2: arg->type = formal_a; break;
                default: arg->type = retval_a; break;
            }
            arg->index = arg->sym[2] - '0';
            //t_counter++;
            break;
        }
        case newtable_e:{
            arg->sym = e->sym;
            arg->numVal = SymTable_getOffset((char*)e->sym.c_str());
            arg->booleanVal = e->boolConst;
            arg->strVal = e->strConst;
            switch(SymTable_getScopeSpace((char*)e->sym.c_str())){
                case 0: arg->type = global_a; break;
                case 1: arg->type = local_a; break;
                case 2: arg->type = formal_a; break;
                default: break;
            }
            arg->index = user_func_counter;
            user_func_counter++;
            break;
        }
        case constbool_e:{
            arg->type = bool_a;
            arg->booleanVal = e->boolConst;
            arg->index = bool_counter;
            bool_counter++;
            break;
        }
        case conststring_e:{
            arg->type = string_a;
            arg->strVal = e->strConst;
            arg->index = str_counter;
            cout<<":::"<<arg->strVal<<endl;
            str_counter++;            
            break;
        }
        case constnum_e:{
            arg->type = number_a;
            arg->numVal = e->numConst;
            arg->index = num_counter;
            num_counter++;
            break;
        }
        case nil_e:{
            arg->type = nil_a;
            break;
        }
        case programfunc_e:{
            arg->numVal = SymTable_getAdress((char*)e->sym.c_str());
            arg->type = userfunc_a;
            arg->sym = e->sym;
            arg->index = user_func_counter;
            user_func_counter++;
            break;
        }
        case libraryfunc_e:{
            arg->sym = e->sym;
            arg->type = libfunc_a;
            arg->index = lib_func_counter;
            lib_func_counter++; 
            break;
        }
        default:{ cout << "***DEFAULT***" <<endl; break;}
    }
    return arg;
}
void insert_instruction(struct instruction *i)
{
    currInstr++;
	instructions.push_back(*i);
}
void insert_vmarg(vmarg *v){
    for(int i=0; i<vmargs.size(); i++)
    {
        if(v->sym.compare(vmargs[i].sym)==0)
        {
            if(v->type == vmargs[i].type){
                return;
            }
        }
    }
    vmargs.push_back(*v);
}
void backpatch_funcstart(int srcLine, int label)
{
    for(int i=0; i<instructions.size(); i++)
    {
        if(instructions[i].srcLine==srcLine)
        {
            if(instructions[i].result->label==-1 || instructions[i].result->label==0)
            {
                instructions[i].result->label=currInstr;
            }
        }
    } 
}
void generate(struct quad *q)
{
    switch(q->op)
    {
        case jump:
            {vmarg *temp=new vmarg(label_a, "", -1, "",false, q->label);
            insert_vmarg(temp);
            insert_instruction(new instruction(jump_v, temp, NULL, NULL, currInstr));
            break;}
        case if_eq:
            {vmarg *temp=new vmarg(label_a, "", -1,  "",false, q->label);
            insert_vmarg(temp);
            vmarg *temp2=make_operand(q->result);
            vmarg *temp3=make_operand(q->arg1);
            insert_vmarg(temp2);
            insert_vmarg(temp3);
            insert_instruction(new instruction(jeq_v, temp, temp2, temp3, currInstr));
            break;}
        case if_noteq:
            {vmarg *temp = new vmarg(label_a, "", -1, "", false, q->label);
            vmarg *temp2=make_operand(q->result);
            vmarg *temp3=make_operand(q->arg1);
            insert_vmarg(temp);
            insert_vmarg(temp2);
            insert_vmarg(temp3);
            insert_instruction(new instruction(jne_v, temp, temp2, temp3, currInstr));
            break;}
        case if_greatereq:
            {vmarg *temp = new vmarg(label_a, "", -1, "", false, q->label);
            vmarg *temp2=make_operand(q->result);
            vmarg *temp3=make_operand(q->arg1);
            insert_vmarg(temp);
            insert_vmarg(temp2);
            insert_vmarg(temp3);
            insert_instruction(new instruction(jge_v, temp, temp2, temp3, currInstr));
            break;}
        case if_lesseq:
            {vmarg *temp = new vmarg(label_a, "", -1, "", false, q->label);
            vmarg *temp2=make_operand(q->result);
            vmarg *temp3=make_operand(q->arg1);
            insert_vmarg(temp);
            insert_vmarg(temp2);
            insert_vmarg(temp3);
            insert_instruction(new instruction(jle_v, temp, temp2, temp3, currInstr));
            break;}
        case if_less:
            {vmarg *temp = new vmarg(label_a, "", -1, "", false, q->label);
            vmarg *temp2=make_operand(q->result);
            vmarg *temp3=make_operand(q->arg1);
            insert_vmarg(temp);
            insert_vmarg(temp2);
            insert_vmarg(temp3);
            insert_instruction(new instruction(jlt_v, temp, temp2, temp3, currInstr));
            break;}
        case call:
            {
            vmarg *temp = make_operand(q->result);
            insert_vmarg(temp);
            insert_instruction(new instruction(call_v, temp,NULL,NULL, currInstr));
            break;}
        case param:
            {
            vmarg *temp = make_operand(q->result);
            insert_vmarg(temp);
            insert_instruction(new instruction(pusharg_v, temp,NULL,NULL, currInstr));
            break;}
        case funcstart:{
            vmarg *temp=new vmarg(label_a, "", -1, "", false, -1);
            funcstart_labels.push_back(currInstr);
            funcstart_labels_counter++;
            insert_vmarg(temp); 
            insert_instruction(new instruction(jump_v, temp, NULL, NULL, currInstr));
            vmarg *__temp = make_operand(q->result);
            insert_vmarg(__temp);
            insert_instruction(new instruction(funcenter_v, __temp,NULL,NULL, currInstr));
            break;
        }
        case funcend:{
            vmarg *temp = make_operand(q->result);
            insert_vmarg(temp);
            insert_instruction(new instruction(funcexit_v, temp,NULL,NULL, currInstr));
            funcstart_labels_counter--;
            backpatch_funcstart(funcstart_labels[funcstart_labels_counter], currInstr+2);
            if(funcstart_labels_counter==0)
                funcstart_labels.clear();
            bool flag=false;
            for(int i=funcstart_labels[funcstart_labels_counter]+1; i<instructions.size(); i++)
            {
                instructions[i].result->label++;
            }  
            break;
        }
        case getretval:{
            vmarg *temp = make_operand(q->result);
            insert_vmarg(temp);
            vmarg *temp2 = make_operand(q->arg1);
            if(getretval_vector.size()>0)
                temp->sym=getretval_vector[0]->strConst;
            insert_vmarg(temp2);
            insert_instruction(new instruction(assign_v, temp2,temp,NULL, currInstr));            
            break;
        }
        case ret:
        {
            vmarg *temp = make_operand(q->result);
            insert_vmarg(temp);
            vmarg *temp2;
            if(getretval_vector.size()>0)
                temp2=new vmarg(retval_a, getretval_vector[0]->strConst, -1, "", false, currInstr);
            else
                temp2=new vmarg(retval_a, "", -1, "", false, currInstr);
            insert_vmarg(temp2);
            insert_instruction(new instruction(assign_v, temp2, temp, NULL, currInstr));
            break;
        }
        case _assign:{
            vmarg *temp = make_operand(q->result);    
            insert_vmarg(temp);
            vmarg *temp2=make_operand(q->arg1);
            insert_vmarg(temp2);
            insert_instruction(new instruction(assign_v, temp, temp2, NULL, currInstr));
            break;}
        case add:{
            //cout<<":::"<<q->result->strConst<<endl;
            vmarg *temp=make_operand(q->result);
            insert_vmarg(temp);
            vmarg *temp2=make_operand(q->arg1);
            insert_vmarg(temp2);
            vmarg *temp3=make_operand(q->arg2);
            insert_vmarg(temp3);
            insert_instruction(new instruction(add_v, temp, temp2, temp3, currInstr));
            break;}
        case sub:{
            vmarg *temp=make_operand(q->result);
            insert_vmarg(temp);
            vmarg *temp2=make_operand(q->arg1);
            insert_vmarg(temp2);
            vmarg *temp3=make_operand(q->arg2);
            insert_vmarg(temp3);
            insert_instruction(new instruction(sub_v, temp, temp2, temp3, currInstr));
            break;}
        case mul:{
            vmarg *temp=make_operand(q->result);
            insert_vmarg(temp);
            vmarg *temp2=make_operand(q->arg1);
            insert_vmarg(temp2);
            vmarg *temp3=make_operand(q->arg2);
            insert_vmarg(temp3);
            insert_instruction(new instruction(mul_v, temp, temp2, temp3, currInstr));
            break;}
        case _div:{
            vmarg *temp=make_operand(q->result);
            insert_vmarg(temp);
            vmarg *temp2=make_operand(q->arg1);
            insert_vmarg(temp2);
            vmarg *temp3=make_operand(q->arg2);
            insert_vmarg(temp3);
            insert_instruction(new instruction(div_v, temp, temp2, temp3, currInstr));
            break;}
        case mod:{
            vmarg *temp=make_operand(q->result);
            insert_vmarg(temp);
            vmarg *temp2=make_operand(q->arg1);
            insert_vmarg(temp2);
            vmarg *temp3=make_operand(q->arg2);
            insert_vmarg(temp3);
            insert_instruction(new instruction(mod_v, temp, temp2, temp3, currInstr));
            break;}
        case tablecreate:{
            vmarg *temp=make_operand(q->result);
            insert_vmarg(temp);
            insert_instruction(new instruction(newtable_v, temp, NULL, NULL, currInstr));
            break;}
        case tablegetelem:{
            vmarg *temp=make_operand(q->result);
            insert_vmarg(temp);
            vmarg *temp2=make_operand(q->arg1);
            insert_vmarg(temp2);
            vmarg *temp3=make_operand(q->arg2);
            insert_vmarg(temp3);
            insert_instruction(new instruction(tablegetelem_v, temp, temp2, temp3, currInstr));
            break;}
        case tablesetelem:{
            vmarg *temp=make_operand(q->result);
            insert_vmarg(temp);
            vmarg *temp2=make_operand(q->arg1);
            insert_vmarg(temp2);
            vmarg *temp3=make_operand(q->arg2);
            insert_vmarg(temp3);
            insert_instruction(new instruction(tablesetelem_v, temp, temp2, temp3, currInstr));
            break;}
        case uminus:{
            vmarg *temp=make_operand(q->result);
            insert_vmarg(temp);
            vmarg *temp2= new vmarg(number_a, "", -1, "", false, -2);
            temp2->index = num_counter;
            num_counter++; 
            insert_instruction(new instruction(mul_v, temp, temp, temp2, currInstr));        
        }
    }
}
void generate_ADD(struct quad* q){generate(q);}
void generate_SUB(struct quad* q){generate(q);}
void generate_MUL(struct quad* q){generate(q);}
void generate_DIV(struct quad* q){generate(q);}
void generate_MOD(struct quad* q){generate(q);}
void generate_NEWTABLE(struct quad* q){generate(q);}
void generate_TABLEGETELEM(struct quad* q){generate(q);}
void generate_TABLESETELEM(struct quad* q){generate(q);}
void generate_ASSIGN(struct quad* q){generate(q);}
void generate_NOP(struct quad* q){generate(q);}
void generate_JUMP(struct quad* q){generate(q);}
void generate_UMINUS(struct quad *q){generate(q);}
void generate_IF_EQ(struct quad* q){generate(q);}
void generate_IF_NOTEQ(struct quad* q){generate(q);}
void generate_IF_GREATER(struct quad* q){generate(q);}
void generate_IF_GREATEREQ(struct quad* q){generate(q);}
void generate_IF_LESS(struct quad* q){generate(q);}
void generate_IF_LESSEQ(struct quad* q){generate(q);}
void generate_AND(struct quad* q){generate(q);}
void generate_NOT(struct quad* q){generate(q);}
void generate_OR(struct quad* q){generate(q);}
void generate_PARAM(struct quad* q){generate(q);}
void generate_CALL(struct quad* q){generate(q);}
void generate_GETRETVAL(struct quad* q){generate(q);}
void generate_FUNCSTART(struct quad* q){generate(q);}
void generate_RETURN(struct quad* q){generate(q);}
void generate_FUNCEND(struct quad* q){generate(q);}  
generator_func_t generators_t[] = {
	generate_ASSIGN,
	generate_ADD,
	generate_SUB,
	generate_MUL,
	generate_DIV,
	generate_MOD,
	generate_UMINUS,
	generate_AND,
	generate_OR,
	generate_NOT,
	generate_IF_EQ,
	generate_IF_NOTEQ,
	generate_IF_LESSEQ,
	generate_IF_GREATEREQ,
	generate_IF_LESS,
	generate_IF_GREATER,
	generate_JUMP,
	generate_CALL,
	generate_PARAM,
	generate_RETURN, 
	generate_GETRETVAL,
	generate_FUNCSTART,
	generate_FUNCEND,
	generate_NEWTABLE,
	generate_TABLEGETELEM,
	generate_TABLESETELEM,
	generate_NOP
};
void enable_generates()
{
    for(int i=0; i<currQuad; i++)
    {
        (*generators_t[quads[i].op])(&quads[i]);
    }
}
void print_Args(vmarg *arg)
{
    switch(arg->type)
    { 
        case label_a:
            cout<<"0"<<arg->type<<"(label)"<<arg->label<<"\t";
            break;
        case global_a:
            cout<<"0"<<arg->type<<"(global)"<<arg->index<<":"<<arg->sym<<"\t ";
            break;
        case formal_a:
            cout<<"0"<<arg->type<<"(formal)"<<arg->numVal<<":"<<arg->sym<<"\t";
            break;
        case local_a:
            cout<<"0"<<arg->type<<"(local)"<<arg->index<<":"<<arg->sym<<"\t ";
            break;
        case number_a:
            cout<<"0"<<arg->type<<"(number)"<<arg->index<<":"<<arg->numVal<<"\t";
            break;
        case string_a:
            if(arg->sym=="")
                cout<<"0"<<arg->type<<"(string)"<<arg->index<<":"<<"\""<<arg->strVal<<"\""<<"\t";   
            else     
                cout<<"0"<<arg->type<<"(string)"<<arg->index<<":"<<arg->sym<<"\t";
            break;
        case bool_a:
            if(arg->booleanVal==1)
                cout<<"0"<<arg->type<<"(bool)"<<arg->index<<":TRUE"<<"\t";
            else    
                cout<<"0"<<arg->type<<"(bool)"<<arg->index<<":FALSE"<<"\t";
            break;
        case nil_a:
            cout<<"0"<<arg->type<<"(nil)"<<":NIL"<<"\t";
            break;
        case userfunc_a:
            cout<<"0"<<arg->type<<"(userfunc)"<<":"<<arg->sym<<"\t";
            break;
        case libfunc_a:
            cout<<"0"<<arg->type<<"(libfunc)"<<":"<<arg->sym<<"\t";
            break;
        case retval_a:
            cout<<"0"<<arg->type<<"(retval)"<<":"<<arg->sym<<"\t ";            
            break;
        default:
            cout<<"\t*****\t";
            break;
    }

}
void print_instruction()
{
	int i=0;  
    cout<<"\033[1;32m";
	cout<<"\n\nLine \tOpCode \t\tResult \t\tArg1 \t\tArg2\n\n";
    cout<<"\033[0m";
	while(i < currInstr-1){
		cout<<instructions[i].srcLine<<"\t";
        if(instructions[i].opcode==jeq_v){
            cout<<"JEQ\t\t";
        }
        else if(instructions[i].opcode == uminus_v){
				cout<<"UMINUS\t\t";
        }
        else if(instructions[i].opcode == assign_v){
				cout<<"ASSIGN\t\t";
        }
        else if(instructions[i].opcode == add_v){
				cout<<"ADD\t\t";
        }
        else if(instructions[i].opcode == sub_v){
				cout<<"SUB\t\t";
        }
        else if(instructions[i].opcode == mul_v){
				cout<<"MUL\t\t";
        }
        else if(instructions[i].opcode == div_v){
				cout<<"DIV\t\t";
        }
        else if(instructions[i].opcode == mod_v){
				cout<<"MOD\t\t";
        }
        else if(instructions[i].opcode == and_v){
				cout<<"AND\t\t";
        }
        else if(instructions[i].opcode == or_v){
				cout<<"OR\t\t";
        }
        else if(instructions[i].opcode == not_v){
				cout<<"NOT\t\t";
        }
        else if(instructions[i].opcode == jne_v){
				cout<<"JNE\t\t";
        }
        else if(instructions[i].opcode == jgt_v){
				cout<<"JGT\t\t";
        }
        else if(instructions[i].opcode == jlt_v){
				cout<<"JLT\t\t";
        }
        else if(instructions[i].opcode == jge_v){
				cout<<"JGE\t\t";
        }
        else if(instructions[i].opcode == jle_v){
				cout<<"JLE\t\t";
        }
        else if(instructions[i].opcode == call_v){
				cout<<"CALL\t\t";
        }
        else if(instructions[i].opcode == funcenter_v){
				cout<<"FNCNTR\t\t";
        }
        else if(instructions[i].opcode == funcexit_v){
				cout<<"FNCXIT\t\t";
        }
        else if(instructions[i].opcode == newtable_v){
				cout<<"NEWTABLE\t\t";
        }
        else if(instructions[i].opcode == tablegetelem_v){
				cout<<"TBLGTLMENT\t\t";
        }
        else if(instructions[i].opcode == tablesetelem_v){
				cout<<"TBLSTLMNT\t\t";
        }
        else if(instructions[i].opcode == pusharg_v){
				cout<<"PUSHARG\t\t";
        }
        else if(instructions[i].opcode == nop_v){
				cout<<"NOP\t\t";
        }
        else if(instructions[i].opcode == jump_v){
				cout<<"JUMP\t\t";
        }
        else{
				cout<<"\t*******\n";
        }
        
		if(instructions[i].result!=NULL)
		      print_Args(instructions[i].result);
		else	
            cout<<"\t\t";
		if(instructions[i].arg1!=NULL)
		    print_Args(instructions[i].arg1);
		else	
            cout<<"\t\t";
		if(instructions[i].arg2!=NULL)
		    print_Args(instructions[i].arg2);
		else	
            cout<<"\t\t";
		cout<<"\n";
        i++;
	}
	cout<<"\n";
}