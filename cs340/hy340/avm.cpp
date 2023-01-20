#include "avm.hpp" 
vector<int> erase_formals;
void print_cells(avm_table_bucket* temp)
{
    avm_table_bucket* current=temp; 
    while(current!=NULL) 
    {
        if(current->key!=NULL)
        {
            if(current->key->type==table_m)
            {  
                cout<<"table:\t"<<endl;
                for(int i=0; i<AVM_TABLE_HASHSIZE; i++)
                {
                    if(current->key->data.tableVal->strIndexed[i]!=NULL)
                        print_cells(current->key->data.tableVal->strIndexed[i]);
                    if(current->key->data.tableVal->numIndexed[i]!=NULL)
                        print_cells(current->key->data.tableVal->numIndexed[i]);
                }
            }
            else if(current->key->type==number_m)
                cout<<"key numVal "<<current->key->data.numVal<<endl;
            else if(current->key->type==string_m)
                cout<<"key string "<<current->key->data.strVal<<endl;
            else if(current->key->type==bool_m)
                cout<<"key bool "<<current->key->data.boolVal<<endl;
            else if(current->key->type==userfunc_m)
                cout<<"key userfunc "<<current->key->data.funcVal<<endl;
            else if(current->key->type==libfunc_m)
                cout<<"key libfunc "<<current->key->data.libfuncVal<<endl;    
        }
        if(current->value!=NULL)
        {        
            if(current->value->type==table_m)
            {
                cout<<"table:\t"<<endl;
                for(int i=0; i<AVM_TABLE_HASHSIZE; i++)
                {
                    if(current->value->data.tableVal->strIndexed[i]!=NULL)
                        print_cells(current->value->data.tableVal->strIndexed[i]);
                    if(current->value->data.tableVal->numIndexed[i]!=NULL)
                        print_cells(current->value->data.tableVal->numIndexed[i]);
                }
            }
            else if(current->value->type==number_m)
                cout<<"value numVal "<<current->value->data.numVal<<endl;
            else if(current->value->type==string_m)
                cout<<"value string "<<current->value->data.strVal<<endl;
            else if(current->value->type==bool_m)
                cout<<"value bool "<<current->value->data.boolVal<<endl;
            else if(current->value->type==userfunc_m)
                cout<<"value userfunc "<<current->value->data.funcVal<<endl;
            else if(current->value->type==libfunc_m)
                cout<<"value libfunc "<<current->value->data.libfuncVal<<endl;            
            current=current->next;
        }
    }
} 
void print_stack()
{
    cout<<"\033[1;32m";
    cout<<"\tSTACK"<<endl;
    cout<<"\033[0m";
    cout<<"Cell\tType\tValue"<<endl;
    for(int i=0; i<avm_stack.size(); i++)
    {
        if(avm_stack[i].type!=undef_m)
        {
            cout<<i<<"|\t";
            if(avm_stack[i].type==table_m)
            {
                cout<<"table:\n";
                for(int j=0; j<AVM_TABLE_HASHSIZE; j++)
                {
                    if(avm_stack[i].data.tableVal!=NULL)
                    {
                        if(avm_stack[i].data.tableVal->strIndexed[j]!=NULL){
                            cout<<"\033[1;32m";
                            cout<<"\nstrIndexed\n\n";
                            cout<<"\033[0m";
                            print_cells(avm_stack[i].data.tableVal->strIndexed[j]);
                        }
                        if(avm_stack[i].data.tableVal->numIndexed[j]!=NULL)
                        {
                            cout<<"\033[1;32m";
                            cout<<"\nnumIndexed\n\n";
                            cout<<"\033[0m";
                            print_cells(avm_stack[i].data.tableVal->numIndexed[j]);
                        }
                    }
                }
            }
            else if(avm_stack[i].type==number_m)
                cout<<"numVal\t"<<avm_stack[i].data.numVal;                
            else if(avm_stack[i].type==string_m)
                cout<<"string\t"<<avm_stack[i].data.strVal;
            else if(avm_stack[i].type==bool_m)
                cout<<"bool\t"<<avm_stack[i].data.boolVal<<endl;
            else if(avm_stack[i].type==userfunc_m)
                cout<<"userfunc\t"<<avm_stack[i].data.funcVal<<endl;
            else if(avm_stack[i].type==libfunc_m)
                cout<<"libfunc\t"<<avm_stack[i].data.libfuncVal<<endl;
        }
        cout<<endl;
    }
}
void avm_read_file(char *lala)
{
    string line="";
    string file_string;
    string magic_number_string;
    int magic_number;
    bool flag=false, flag2 = false, flag3 = false, seen = false, flag4 = false, flag5 = false, flag6 = false, flag7 = false, flag8 = false,flag9 = false, flag10 = false, flag11 = false;
    bool seen4 = false, seen5 = false, seen6 = false, seen7 = false, seen8 = false, seen9 = false, seen10 = false, seen11 = false;
    ifstream infile(lala);
    SymTable_new();
    while(getline(infile, line))
    {
        if(flag==true)
        { 
            codeSize=atoi((char*)line.c_str());
            flag=false;
        }
        if(!line.compare("Instructions: "))
        {
            flag=true;
        }

        std::string str2 ("Instructions");

        std::size_t found = line.find(str2);
        if (found!=std::string::npos){
            flag2 = true;
            flag3 = false;
            continue;
        }

        std::string str3 ("Number table");

        found = line.find(str3);
        if (found!=std::string::npos){
            flag4 = true;
            continue;
        }

        std::string str4 ("String table");

        found = line.find(str4);
        if (found!=std::string::npos){
            flag5 = true;
            flag4 = false;
            continue;
        }

        std::string str5 ("Boolean table");

        found = line.find(str5);
        if (found!=std::string::npos){
            flag6 = true;
            flag5 = false;
            continue;
        }

        std::string str6 ("User function table");

        found = line.find(str6);
        if (found!=std::string::npos){
            flag7 = true;
            flag6 = false;
            continue;
        }

        std::string str7 ("Library function table");

        found = line.find(str7);
        if (found!=std::string::npos){
            flag8 = true;
            flag7 = false;
            continue;
        }

        std::string str8 ("Global table");

        found = line.find(str8);
        if (found!=std::string::npos){
            flag9 = true;
            flag8 = false;
            continue;
        }

        std::string str10 ("Local table");

        found = line.find(str10);
        if (found!=std::string::npos){
            flag10 = true;
            flag9 = false;
            continue;
        }

        std::string str11 ("Formal table");

        found = line.find(str11);
        if (found!=std::string::npos){
            flag11 = true;
            flag10 = false;
            continue;
        }

        std::string str9 ("Symbol Table");

        found = line.find(str9);
        if (found!=std::string::npos){
            flag3 = true;
            flag11 = false;
            continue;
        }

        if(flag4 && !seen4){
            if(line.length() == 2){
                seen4 = true;
                continue;
            }
        }

        if(flag4 && seen4){
            stringstream s_stream(line);
            double x = 0;
            s_stream >> x;
            vmarg *v = new vmarg();
            v->numVal = x;
            number_table.push_back(*v);          
        }

        if(flag5 && !seen5){
            flag4 = false;
            if(line.length() == 2){
                seen5 = true;
                continue;
            }
        }

        if(flag5 && seen5){
            vmarg *v = new vmarg();
            v->sym = line;
            string_table.push_back(*v);            
        }

        if(flag6 && !seen6){
            flag5 = false;
            if(line.length() == 2){
                seen6 = true;
                continue;
            }
        }

        if(flag6 && seen6){
            stringstream s_stream(line);
            double x = 0;
            s_stream >> x;
            vmarg *v = new vmarg();
            if(x) v->booleanVal = true;
            else v->booleanVal = false;
            boolean_table.push_back(*v);            
        }

        if(flag7 && !seen7){
            flag6 = false;
            if(line.length() == 2){
                seen7 = true;
                continue;
            }
        }

        if(flag7 && seen7){
            stringstream s_stream(line);
            double x = 0;
            s_stream >> x;
            vmarg *v = new vmarg();
            v->numVal = x;
            userfunc_table.push_back(*v);            
        }
        
        if(flag8 && !seen8){
            flag7 = false;
            if(line.length() == 2){
                seen8 = true;
                continue;
            }
        }

        if(flag8 && seen8){
            vmarg *v = new vmarg();
            v->sym = line;
            libfunc_table.push_back(*v);            
        }
        
        if(flag9 && !seen9){
            flag8 = false;
            if(line.length() >= 2){
                seen9 = true;
                continue;
            }
        }

        if(flag9 && seen9){
            vmarg *v = new vmarg();
            v->sym = line;
            global_table.push_back(*v);           
        }

        if(flag10 && !seen10){
            if(line.length() == 2){
                seen10 = true;
                continue;
            }
        }

        if(flag10 && seen10){
            vmarg *v = new vmarg();
            v->sym = line;
            local_table.push_back(*v);           
        }

        if(flag11 && !seen11){
            if(line.length() == 2){
                seen11 = true;
                continue;
            }
        }

        if(flag11 && seen11){
            vmarg *v = new vmarg();
            v->sym = line;
            formal_table.push_back(*v);           
        }
        
        if(flag3){
            flag9 = false;
            std::vector<std::string> result;	
            boost::split(result, line, boost::is_any_of(" ")); 
            if(result.size() == 7){
                stringstream s_stream(result[1]);
                
                int scope = 0;

                s_stream >> scope;    

                stringstream s_stream2(result[6]);
                
                int lineno = 0;

                s_stream2 >> lineno;   

                stringstream s_stream3(result[5]);
                 
                int type = 0;

                s_stream3 >> type;   

                stringstream s_stream4(result[3]);
                
                int scope_space = 0;

                s_stream4 >> scope_space;

                stringstream s_stream5(result[4]);
                
                int offset = 0;

                s_stream5 >> offset;                
                
                if(type == 0)
                    SymTable_put(scope, lineno, GLOBAL, (char*)result[0].c_str(), scope_space, offset);
                else if(type == 1) SymTable_put(scope, lineno, __LOCAL, (char*)result[0].c_str(), scope_space, offset);
                else if(type == 2) SymTable_put(scope, lineno, FORMAL, (char*)result[0].c_str(), scope_space, offset);
                else if(type == 3) SymTable_put(scope, lineno, USERFUNCT, (char*)result[0].c_str(), scope_space, offset);
                else if(type == 4) SymTable_put(scope, lineno, LIBFUNC, (char*)result[0].c_str(), scope_space, offset);
                else if(type == 5) SymTable_put(scope, lineno, USERMETHOD, (char*)result[0].c_str(), scope_space, offset);
            } 
        }

        if(flag2){
            flag3 = false;
            std::vector<std::string> result;	
            boost::split(result, line, boost::is_any_of(" "));    

            
            if(result.size() > 0){
                if(result.size() == 1 && !seen){
                    seen = true;
                    continue;
                }
                if(result.size() == 1 && seen){
                    std::vector<std::string> result2;	
                    boost::split(result2, result[0], boost::is_any_of("\n")); 
                    stringstream s_stream(result2[0]);
                    
                    int x = 0;

                    s_stream >> x;
                    instr->opcode = (vmopcode)x;
                }
                else if(result.size() == 9){
                    if(!result[0].compare("result")){
                        if(!result[1].compare("struct")){
                            stringstream s_stream(result[2]);
                            
                            int type = 0;

                            s_stream >> type;           

                            instr->result = new vmarg();
                            instr->result->type = (enum vmarg_t)type;          

                            instr->result->sym = result[3];     

                            stringstream s_stream2(result[4]);
                            
                            double numVal = 0;

                            s_stream2 >> numVal;           

                            instr->result->numVal = numVal; 

                            instr->result->strVal = result[5];   

                            stringstream s_stream3(result[6]);
                            
                            int boolVal = 0;

                            s_stream3 >> boolVal;           
                            
                            if(boolVal == 1)
                                instr->result->booleanVal = true; 
                            else 
                                instr->result->booleanVal = false;

                            stringstream s_stream4(result[7]);
                            
                            int label = 0;

                            s_stream4 >> label;

                            instr->result->label = label;   

                            stringstream s_stream5(result[8]);
                            
                            int index = 0;

                            s_stream5 >> index;

                            instr->result->index = index; 
                        }
                        count_instr++;                                                             
                    }
                    else if(!result[0].compare("arg1")){
                        if(!result[1].compare("struct")){
                            stringstream s_stream(result[2]);
                            
                            int type = 0;

                            s_stream >> type;           
                            instr->arg1 = new vmarg();
                            instr->arg1->type = (enum vmarg_t)type;          

                            instr->arg1->sym = result[3];     

                            stringstream s_stream2(result[4]);
                            
                            double numVal = 0;

                            s_stream2 >> numVal;           

                            instr->arg1->numVal = numVal;   

                            instr->arg1->strVal = result[5]; 

                            stringstream s_stream3(result[6]);
                            
                            int boolVal = 0;

                            s_stream3 >> boolVal;           
                            
                            if(boolVal == 1)
                                instr->arg1->booleanVal = true; 
                            else 
                                instr->arg1->booleanVal = false;

                            stringstream s_stream4(result[7]);
                            
                            int label = 0;

                            s_stream4 >> label;

                            instr->arg1->label = label;   

                            stringstream s_stream5(result[8]);
                            
                            int index = 0;

                            s_stream5 >> index;

                            instr->arg1->index = index; 
                        } 
                        count_instr++;   
                    }
                    else if(!result[0].compare("arg2")){
                        if(!result[1].compare("struct")){
                            stringstream s_stream(result[2]);
                            
                            int type = 0;

                            s_stream >> type;           
                            instr->arg2 = new vmarg();
                            instr->arg2->type = (enum vmarg_t)type;          

                            instr->arg2->sym = result[3];     

                            stringstream s_stream2(result[4]);
                            
                            double numVal = 0;

                            s_stream2 >> numVal;           

                            instr->arg2->numVal = numVal; 

                            instr->arg2->strVal = result[5];  

                            stringstream s_stream3(result[6]);
                            
                            int boolVal = 0;

                            s_stream3 >> boolVal;           
                            
                            if(boolVal == 1)
                                instr->arg2->booleanVal = true; 
                            else 
                                instr->arg2->booleanVal = false;

                            stringstream s_stream4(result[7]);
                            
                            int label = 0;

                            s_stream4 >> label;

                            instr->arg2->label = label;   

                            stringstream s_stream5(result[8]);
                            
                            int index = 0;

                            s_stream5 >> index;

                            instr->arg2->index = index; 
                        } 
                        count_instr++;                        
                    }                                
                }
                else if(result.size() == 3){
                    if(!result[0].compare("result") || !result[0].compare("arg1") || !result[0].compare("arg2")) count_instr++;
                }
                
            } 
        }

        if(count_instr == 3){
             instructions.push_back(*instr); 
             count_instr = 0;
             instr = new instruction();
        }

        file_string+=line+"\n";
    }
    int i=0;
    while(file_string[i++]!='\n')
    {
        magic_number_string+=file_string;
    }
    magic_number=atoi((char*)magic_number_string.c_str());
    if(magic_number<=0)
    {
        cerr<<"Wrong magic number"<<endl;
        exit(1);
    }
    if(codeSize<=0)
    {
        cerr<<"Invalid code size"<<endl; 
        exit(1);
    }
    cout<<"magic number:: "<<magic_number<<endl;
    cout<<"code size::"<<codeSize<<endl;
}
void avm_store_globals_to_stack(){
    for(int i=0; i<global_table.size(); i++)
    {
        avm_memcell *tmp=new avm_memcell();
        tmp->type=string_m;
        tmp->data.strVal=strdup((char*)global_table[i].sym.c_str());
        avm_stack.push_back(*tmp);
        avm_dec_top();
    } 

    topsp = top;

    for(int i=0; i<local_table.size(); i++)
    {
        avm_memcell *tmp=new avm_memcell();
        tmp->type=string_m;
        tmp->data.strVal=strdup((char*)local_table[i].sym.c_str());
        avm_stack.push_back(*tmp);
        avm_dec_top();
    }

    for(int i=0; i<formal_table.size(); i++)
    {
        avm_memcell *tmp=new avm_memcell();
        tmp->type=string_m;
        tmp->data.strVal=strdup((char*)formal_table[i].sym.c_str());
        avm_stack.push_back(*tmp);
        avm_dec_top();
    }
}

void clear_stack(){
    for(int i = 0; i < AVM_STACKSIZE; i++){
        avm_stack[i].type = undef_m;
        avm_stack[i].data.numVal = -1;
        memclear_string(&avm_stack[i]);
        avm_stack[i].data.boolVal = false;
        avm_stack[i].data.funcVal = -1;
        avm_stack[i].data.libfuncVal = NULL;
    }
}

void clear_stack_from_tables(){
    for(int i = 0; i < AVM_STACKSIZE; i++){
        if(avm_stack[i].data.tableVal){
            for(int j = 0; j < AVM_TABLE_HASHSIZE; j++){
                struct avm_table_bucket *curr = avm_stack[i].data.tableVal->strIndexed[j];
                while(curr){
                    free(curr->key);
                    free(curr->value);
                    curr = curr->next;
                }

                curr = avm_stack[i].data.tableVal->numIndexed[j];
                while(curr){
                    free(curr->key);
                    free(curr->value);
                    curr = curr->next;
                }                
            }
        }
    }
}

void execute_cycle(void) {
  unsigned int oldPc;
  if (executionFinished)
    return;
  else {
    if (pc == AVM_ENDING_PC) {
      cout<<"\nExecution of Virtual Machine completed.\n";
      executionFinished = 1;
      return;
    } else {
      if(pc >= AVM_ENDING_PC){
        cout<<"\nExecution of Virtual Machine completed.\n";
        executionFinished = 1;
        return;
      }
      assert(instructions[pc].opcode >= 0 && instructions[pc].opcode <= AVM_MAX_INSTRUCTIONS);
      if (instructions[pc].srcLine) 
          currLine = instructions[pc].srcLine;

      oldPc = pc; 
      (*executeFuncs[instructions[pc].opcode])(&instructions[pc]); 
      if (pc == oldPc) pc++;
    } 
  }
}

int main(int argc, char** argv){
    if(argc==1)
    {
        cerr<<"No input files"<<endl;
        exit(1);
    }
    avm_read_file(argv[1]);
    avm_initialize();
    avm_store_globals_to_stack();
    SymTable_PRINT();
    while(executionFinished==0)
        execute_cycle();
    print_stack();

    if(active_table){
        clear_stack_from_tables();
        cout << endl;
        cout<<"\033[1;32m";
        cout << "***CLEARED STACK FROM TABLES***" << endl;
        cout<<"\033[0m";
        print_stack();
        active_table = false;
    }
    cout << endl;
    clear_stack();
    cout<<"\033[1;32m";
    cout << "***STACK HAS BEEN CLEARED***" << endl;
    cout<<"\033[0m";
    print_stack();
    return 0;
}