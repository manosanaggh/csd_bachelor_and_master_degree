 	/*--------HY-340----P-R-0-J-E-C-T----2-0-2-0-------*
	*---------A-N-A-G-N-W-S-T-A-K-I-S----M-A-N-0-S-----*
	*---------M-E-T-A-X-A-K-I-S----D-I-M-I-T-R-I-S-----*
	*---------S-A-M-P-S-A-K-I----A-G-G-E-L-I-K-I-------* 
	****************************************************   
	*/  
#include "avm_and_target.hpp" 
#define YY_DECL int alpha_yylex(void* ylval)
extern int yylineno; 
int yylex(void);
int yyerror(char* yaccProvidedMessage){
	std::cout << yylineno << "\033[1;31mERROR IN GRAMMAR, NOT REDUCING TO PROGRAM\033[0m"<<" \n";
	exit(1);
}
std::vector<std::pair<int, std::string> > map_temp;
std::vector <struct quad> quads;
vector<int> while_startlist; 
vector<struct expr*> getretval_vector;
bool ison = false;
bool member_flag_set = false;
bool member_flag_get = false;
bool t_create = false;
bool call_func_flag = false;
int loop_index=0;
string string_member="";
bool expression_semicolon=false;
bool ifstmt_flag=false;
bool assign_flag=false;
int array_index = 0;
int last_jump=0;
int for_index=0;
int number_of_functions=0;
vector<string>func_list;
vector<string>func_list_2;
int func_c = -1;
int func_c_2 = -1;
vector<int> iflist;
vector<int> end_iflist;
vector<int> assign_quads;
vector<int> breaklist;
vector<int> continuelist;
int number_of_elses;
int else_quad;
bool temp_metavlhth=false;
bool loop_start=false;
bool logic_flag=false;
bool while_flag=false;
bool if_flag = false;
bool for_flag= false;
bool b_par = false;
bool member_flag = false; //to identify if in rule member: lvalue dot id 
int temp_counter=0;
int total=0;
bool mul_div= false;
bool add_sub = false;
int currQuad=0;
int accessed_lib = 0;
int table_index=0;
int global_for = 0;
int is_function = 0;
string method_string;
bool logic_flag2=false;
char *global_for_val = "";
char c_temp_function[64];
extern char* yytext;
extern FILE* yyin;
string temp_tablecreate="";
int flag = 0; //to identify a string in rule objectdef 
bool method_flag = false;
int anonymous_count = 0;
int program_offset = 0;
int function_offset = 0;
int formal_offset = 0;
char prev_func_id[2];
char prev_func_id2[32];
int prev_scope;
int prev_lineno;
bool func_flag = false;
bool ret_flag = false;
vector<int>ret_list;
int count_temps = -1;
int count_overall_temps = -1;
vector<string>temp_vector;
bool left_bracket = false;
vector<struct expr*>indexes;
string table_str_index;

enum iopcode{
    _assign, add, sub, mul,
    _div, mod, uminus, _and,
    _or, _not, if_eq, if_noteq,
    if_lesseq, if_greatereq, if_less, if_greater,
    call, param, ret, getretval, jump, 
    funcstart, funcend, tablecreate, tablegetelem,
    tablesetelem
}; 
enum expr_t{
    var_e, tableitem_e, programfunc_e, libraryfunc_e, 
    arithexpr_e, boolexpr_e, assignexpr_e, newtable_e,
    constnum_e, constbool_e, conststring_e, nil_e
};
struct expr{
    expr_t type;
    std::string sym; 
    struct expr* index;
    double numConst;
    std::string strConst;
	string strConst2;
    bool boolConst;
	std::vector<int> falselist; 
	std::vector<int> truelist;
	vector<int> list;
	std::vector<int> whilelist;
	std::vector<int> forlist; 
    struct expr* next;

    expr(expr_t type, std::string sym, double numConst, std::string strConst, bool boolConst, struct expr *next){
        this->type=type;
        this->sym.assign(sym);
        this->numConst=numConst;
        this->strConst.assign(strConst);
        this->boolConst=boolConst;
        this->next=next;
    }
}; 
struct expr* expression=NULL;
struct quad{
    enum iopcode op;
    struct expr* result;
    struct expr* arg1;
    struct expr* arg2;
    int label;
	int line;

	quad(enum iopcode op, struct expr* result, struct expr* arg1, struct expr* arg2, int label, int line){
		this->op = op;
		this->result = result;
		this->arg1 = arg1;
		this->arg2 = arg2;
		this->label = label;
		this->line = line;
	}
};

void insert_quads(struct quad *q)
{
	quads.push_back(*q);
}
std::string new_temp_name()
{
	std::ostringstream out;
	out<< "_t"<< temp_counter++;
	return out.str();
}
void backpatch(int line, int label)
{
	for(int i=0; i<quads.size(); i++)
	{
		if(quads[i].line==line)
		{
			if(quads[i].label==-1 ||quads[i].label==0)
				quads[i].label=label;
		}
	}
}
void print_expr(struct expr *ex)
{
	switch(ex->type)
	{
		case var_e:
			std::cout<<"\t\t"<<ex->sym;
			break;
		case tableitem_e:
			std::cout<<"\t\t"<<ex->sym;
			break;
		case programfunc_e:
			std::cout<<"\t\t"<<ex->sym;
			break;
		case libraryfunc_e:
			std::cout<<"\t\t"<<ex->sym;
			break;
		case arithexpr_e:
			std::cout<<"\t\t"<<ex->sym;
			break;
		case boolexpr_e:
			std::cout<<"\t\t"<<ex->sym;
			break;
		case assignexpr_e:
			if(ex->sym=="")
			{
				std::cout<<"\t\t"<<ex->numConst;
			} 
			else
			{
				std::cout<<"\t\t"<<ex->sym;
			}
			break;
		case newtable_e:
			std::cout<<"\t\t"<<ex->sym;
			break;
		case constnum_e:
			std::cout<<"\t\t"<<ex->numConst;
			break;
		case constbool_e:
			if(ex->boolConst)
			{
				std::cout<<"\t\tTRUE";	
			}
			else
			{
				std::cout<<"\t\tFALSE";
			}
			break;
		case conststring_e:
			if(ex->strConst=="")
				cout<<"\t\t"<<ex->sym;
			else	
				std::cout<<"\t\t\""<<ex->strConst<<"\"";
			break;
		case nil_e:
			std::cout<<"\t\t"<<ex->strConst;
			break;
		case jump:
			std::cout<<"test";
			std:: cout<<"\t\t\t\t\t";	
		default:
			std::cout<<"\t\t";	
	}
}
void print_quads()
{
	int i=0;
	std::cout<<"\033[1;32m";
	std::cout<<"quad#"<<"\t\t"<<"opcode"<<"\t\t"<<"result"<<"\t\t"<<"arg1"<<"\t\t"<<"arg2"<<"\t\t"<<"label"<<std::endl;
	std::cout<<"\033[0m";
	while(i<currQuad)
	{
		std::cout<<quads[i].line<<":\t\t";
		if(quads[i].op==_assign)
		{
			std::cout<<"ASSIGN "<<quads[i].result->numConst;
		}
		else if(quads[i].op==add)
		{
			std::cout<<"ADD";
		}
		else if(quads[i].op==sub)
		{
			std::cout<<"SUB";
		}
		else if(quads[i].op==mul)
		{
			std::cout<<"MUL";
		}
		else if(quads[i].op==_div)
		{
			std::cout<<"DIV";
		}
		else if(quads[i].op==mod)
		{
			std::cout<<"MOD";
		}
		else if(quads[i].op==_and)
		{
			std::cout<<"AND";
		}
		else if(quads[i].op==_or)
		{
			std::cout<<"OR";
		}
		else if(quads[i].op==_not)
		{
			std::cout<<"NOT";
		}
		else if(quads[i].op==jump)
		{
			std::cout<<"JUMP\t\t\t\t";
		}
		else if(quads[i].op==if_eq)
		{
			std::cout<<"IF_EQ";
		}
		else if(quads[i].op==if_noteq)
		{
			std::cout<<"IF_NEQ"; 
		}
		else if(quads[i].op==if_greater)
		{
			std::cout<<"IF_GREATER";
		}
		else if(quads[i].op==if_lesseq)
		{
			std::cout<<"IF_LEQ";
		}
		else if(quads[i].op==if_greatereq)
		{
			std::cout<<"IF_GREQ";
		}
		else if(quads[i].op==if_less)
		{
			std::cout<<"IF_LESS";
		}
		else if(quads[i].op==if_eq)
		{
			std::cout<<"IF_EQ";
		}
		else if(quads[i].op==call)
		{
			std::cout<<"CALL";
		}
		else if(quads[i].op==getretval)
		{
			std::cout<<"GETRTVL  "<<quads[i].result->numConst;
		}
		else if(quads[i].op==funcstart)
		{
			std::cout<<"FUNSTRT";
		}
		else if(quads[i].op==funcend)
		{
			std::cout<<"FUNCEND";
		}
		else if(quads[i].op==tablecreate)
		{
			std::cout<<"TBLCRTE";
		}
		else if(quads[i].op==tablegetelem)
		{
			std::cout<<"TBLGTLM";
		}
		else if(quads[i].op==tablesetelem)
		{
			std::cout<<"TBLSTLM";
		}
		else if(quads[i].op==ret)
		{
			std::cout<<"RETURN";
		}
		else if(quads[i].op==uminus)
		{
			std::cout<<"UMINUS";
		} 
		else if(quads[i].op==param)
		{
			std::cout<<"PARAM";
		}
		if(quads[i].result != NULL)
		{
			print_expr(quads[i].result);
		}
		if(quads[i].arg1 != NULL)
		{
			print_expr(quads[i].arg1);
		}
		if(quads[i].arg2!=NULL)
		{	
			print_expr(quads[i].arg2);
		}
		if((quads[i].label!=-1 &&quads[i].label!=-2) && quads[i].op!=_assign)
		{
			std::cout<<"\t\t\t\t"<<quads[i].label; 
		}
		std::cout<<std::endl;
		i++;
	}
}