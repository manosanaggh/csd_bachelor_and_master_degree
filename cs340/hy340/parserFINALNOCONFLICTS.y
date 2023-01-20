%{ 
	#include "target_code.hpp"    
	using namespace std;  
%} 
%start program  
%union {   
	struct expr *exprValue; 
	char* strValue;
	bool Boolean;   
	long double intValue; 
	long double realValue;
}
%token IF 
%token ELSE 
%token WHILE
%token FOR  
%token FUNCTION
%token RETURN
%token BREAK
%token CONTINUE
%token AND
%token NOT 
%token OR 
%token LOCAL
%token TRUE
%token FALSE
%token NIL
%token ISON
%token PLUS
%token MINUS
%token STAR
%token SLASH
%token PERCENT
%token EQUAL
%token NOT_EQUAL
%token PLUS_PLUS
%token MINUS_MINUS
%token GREATER
%token LESS
%token GREATER_EQUAL
%token LESS_EQUAL
%token INTCONST
%token REALCONST
%token STRING
%token LEFT_BRACE
%token RIGHT_BRACE
%token LEFT_BRACKET
%token RIGHT_BRACKET
%token ARISTERI_PARENTHESI
%token DEXIA_PARENTHESI
%token SEMICOLON
%token COMMA
%token COLON
%token COLON_COLON
%token DOT
%token DOT_DOT
%token ID
%token SINGLECOMMENT
%token MULTICOMMENT

%right ISON
%nonassoc AND OR
%nonassoc EQUAL NOT_EQUAL
%nonassoc GREATER GREATER_EQUAL LESS LESS_EQUAL
%left PLUS MINUS
%left STAR SLASH PERCENT
%right NOT PLUS_PLUS MINUS_MINUS UMINUS
%left DOT DOT_DOT
%left LEFT_BRACKET RIGHT_BRACKET
%left ARISTERI_PARENTHESI DEXIA_PARENTHESI
%left LEFT_BRACE RIGHT_BRACE
%nonassoc IF ELSE
 
%type <exprValue> const
%type <exprValue> ID
%type <exprValue> expr
%type <exprValue> assignexpr
%type <exprValue> term
%type <exprValue> primary
%type <exprValue> lvalue
%type <exprValue> member
%type <exprValue> call
%type <exprValue> objectdef 
%type <exprValue> objectdef_2
%type <exprValue> ifstmt
%type <exprValue> ifstmt_temp
%type <exprValue> ifstart
%type <exprValue> stmt
%type <exprValue> stmt_list
%type <exprValue> methodcall
%type <exprValue> callsuffix
%type <exprValue> indexed
%type <exprValue> indexedelem
%type <exprValue> indexedelem_temp
%type <exprValue> elist
%type <exprValue> expr2
%type <exprValue> whilestmt
%type <exprValue> whilestart
%type <exprValue> forstart
%type <exprValue> forstart2
%type <exprValue> forstmt
%type <exprValue> returnstmt
%type <exprValue> funcdef
%type <exprValue> block
%type <exprValue> normcall
 
%%

program:	stmt_list{
				for(int i=0; i<quads.size(); i++)
				{
					if(quads[i].label==-1)
					{
						quads[i].label=last_jump+1;
					}
				}
				std::cout<<"program <-- stmt_list"<<std::endl;}
			;

stmt_list:	stmt stmt_list{std::cout<<"stmt_list <-- stmt stmt_list\n";}
			|{std::cout<<"stmt_list <-- empty"<<std::endl;}
			;
 
stmt:		expr SEMICOLON{
				expression_semicolon=true;
				if(if_flag)  
				{
					insert_quads(new quad(jump, NULL, NULL, NULL, -1, ++currQuad));
					$$ = new expr(constnum_e, "", 0, "", false, NULL);
					end_iflist.push_back(currQuad);
				}
				if(number_of_elses==0)
					if_flag=false;
				std::cout<<"stmt <-- expr;\n"; }
			| ifstmt{
				std::cout<<"stmt <-- ifstmt\n";
			 }
			| whilestmt{  loop_start=false;    std::cout<<"stmt <-- whilestmt\n";}
			| forstmt{  loop_start=false;       std::cout<<"stmt <-- forstmt\n";  }
			| returnstmt{        std::cout<<"stmt <-- returnstmt\n";}
			| BREAK SEMICOLON {
				if(!loop_start)
					std::cout << "\033[1;31mERROR\033[0m" << ": Cannot use break outside a loop!" << std::endl;
				insert_quads(new quad(jump, NULL, NULL, NULL, -1, ++currQuad));
				breaklist.push_back(currQuad);
				std::cout<<"stmt <-- BREAK SEMICOLON\n";
			}
			| CONTINUE SEMICOLON{
				if(!loop_start &&!for_index)
					std::cout << "\033[1;31mERROR\033[0m" << ": Cannot use continue outside a loop!" << std::endl;
				insert_quads(new quad(jump, NULL, NULL, NULL, -1, ++currQuad));
				continuelist.push_back(currQuad);
				std::cout<<"stmt <-- CONTINUE SEMICOLON\n";}
			| block{              std::cout<<"stmt <-- block\n";	}
			| funcdef{        std::cout<<"stmt <-- funcdef\n";}
			| SEMICOLON{        std::cout<<"stmt <-- ;\n";  }
			;
			
expr:		assignexpr{
				$$ = new expr(assignexpr_e, $1->sym, $1->numConst, $1->strConst, $1->boolConst, NULL);	    
				$$->list=$1->list;
				std::cout<<"expr <-- assignexpr\n";  
			}
			| expr AND expr{
				if($1->sym.size()==1 && $3->sym.size()==1)
				{
					insert_quads(new quad(if_eq, $1, new expr(constbool_e, "", 0, "", true, NULL), NULL, currQuad+2, ++currQuad));
					$1->whilelist.push_back(currQuad);
					insert_quads(new quad(jump, NULL, NULL, NULL, -1, ++currQuad));
					insert_quads(new quad(if_eq, $3, new expr(constbool_e, "", 0, "", true, NULL), NULL, currQuad+2, ++currQuad));
					insert_quads(new quad(jump, NULL, NULL, NULL, -1, ++currQuad));
					logic_flag2=true;
				}
				else{
				$$=new expr(boolexpr_e, "", 0, "", $1->boolConst && $3->boolConst, NULL);
				$$->boolConst = $1->boolConst && $3->boolConst;
				for(int i = 0; i < $1->truelist.size(); i++){
					backpatch($1->truelist[i], $1->truelist[i] + 2);
				}
				$$->truelist = $3->truelist;
				for(int i=0; i<$1->falselist.size(); i++)  //merge $1->falselist & $3->falselist
				{
					$$->falselist.push_back($1->falselist[i]);
				}
				for(int i=0; i<$3->falselist.size(); i++)
				{
					$$->falselist.push_back($3->falselist[i]);
				}
				logic_flag=true;
				}
				std::cout<<"expr <-- expr AND expr\n";
			}
			| expr OR expr{	
				if($1->sym.size()==1 && $3->sym.size()==1)
				{
					insert_quads(new quad(if_eq, $1, new expr(constbool_e, "", 0, "", true, NULL), NULL, currQuad+2, ++currQuad));
					insert_quads(new quad(jump, NULL, NULL, NULL, -1, ++currQuad));
					insert_quads(new quad(if_eq, $3, new expr(constbool_e, "", 0, "", true, NULL), NULL, currQuad+2, ++currQuad));
					insert_quads(new quad(jump, NULL, NULL, NULL, -1, ++currQuad));
					logic_flag2=true;	
				}
				else{	    
				$$=new expr(boolexpr_e, "", 0, "", $1->boolConst || $3->boolConst, NULL);
				$$->boolConst = $1->boolConst || $3->boolConst;

				for(int i = 0; i < $1->falselist.size(); i++){
					backpatch($1->falselist[i], $1->falselist[i] + 1);
				}
				for(int i = 0; i < $1->truelist.size(); i++){  //merge $1->falselist & $3->falselist
					$$->truelist.push_back($1->truelist[i]);
				}
				for(int i = 0; i < $3->truelist.size(); i++){
					$$->truelist.push_back($3->truelist[i]);
				}	
				$$->falselist = $3->falselist;	  
				logic_flag=true;
				}
				std::cout<<"expr <-- expr OR expr\n"; 
			}
			| expr PLUS expr{
				std::string temp_str_1=new_temp_name();
				if(scope==0){
					SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
					program_offset++;
				}
				else{
					SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
					function_offset++;
				}
				if($1->type == conststring_e && $3->type == conststring_e){
					cout << "***string(str) + string(str)***" << endl;
					cout<<"::"<<$1->strConst + $3->strConst<<endl;
					$$=new expr(arithexpr_e, temp_str_1, 0, $1->strConst + $3->strConst, false, NULL);
				}
				else if($1->type == constnum_e && $3->type == constnum_e){
					cout << "***num(num) + num(num)***" << endl;
					$$=new expr(arithexpr_e, temp_str_1, $1->numConst + $3->numConst, "", false, NULL);
				}
				else if($1->type == assignexpr_e || $3->type == assignexpr_e || $1->type == var_e || $3->type == var_e){
					if($1->strConst.compare("") && $3->strConst.compare("")){
						cout << "***string(var) + string(var)***" << endl;
						$$=new expr(arithexpr_e, temp_str_1, 0, $1->strConst + $3->strConst, false, NULL);
					} 
					else{
						cout << "***num(var) + num(var)***" << endl;
						$$=new expr(arithexpr_e, temp_str_1, $1->numConst + $3->numConst, "", false, NULL);
					}
				}

				insert_quads(new quad(add, $$, $1, $3, -2, ++currQuad));
				std::cout<<"expr <-- expr + expr\n"; 
			 }
			| expr MINUS expr{  
				std::string temp_str_1=new_temp_name();
				if(scope==0){
					SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
					program_offset++;
				}
				else{
					SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
					function_offset++;
				}
				$$=new expr(arithexpr_e, temp_str_1, $1->numConst - $3->numConst, "", false, NULL);
				$$->numConst = $1->numConst - $3->numConst;
				insert_quads(new quad(sub, $$, $1, $3, -2, ++currQuad));
				std::cout<<"expr <-- expr - expr\n"; 
			 }
			| expr STAR expr{
				std::string temp_str_1=new_temp_name();
				if(scope==0){
					SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
					program_offset++;
				}
				else{
					SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
					function_offset++;
				}
				$$=new expr(arithexpr_e, temp_str_1, $1->numConst * $3->numConst, "", false, NULL);
				$$->numConst = $1->numConst * $3->numConst;
				insert_quads(new quad(mul, $$, $1, $3, -2, ++currQuad));	
			    std::cout<<"expr <-- expr * expr\n";  
			}
			| expr SLASH expr{   
				std::string temp_str_1=new_temp_name();
				if(scope==0){
					SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
					program_offset++;
				}
				else{
					SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
					function_offset++;
				}	
				$$=new expr(arithexpr_e, temp_str_1, $1->numConst / $3->numConst, "", false, NULL);
				$$->numConst = $1->numConst / $3->numConst;
				insert_quads(new quad(_div, $$, $1, $3, -2, ++currQuad));	
				std::cout<<"expr <-- expr / expr\n";  
			}
			| expr PERCENT expr{    
				std::string temp_str_1=new_temp_name();
				if(scope==0){
					SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
					program_offset++;
				}
				else{
					SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
					function_offset++;
				}
				int i = (int)$1->numConst;
				int j = (int)$3->numConst;
				$$=new expr(arithexpr_e, temp_str_1, 0, "", false, NULL);
				insert_quads(new quad(mod, $$, $1, $3, -2, ++currQuad));
				std::cout<<"expr <-- expr % expr\n";  
			}
			| expr GREATER expr{
				temp_metavlhth=true;
				$$=new expr(boolexpr_e, "", 0, "", $1->numConst > $3->numConst, NULL);
				$$->boolConst = $1->numConst > $3->numConst;
				$$->truelist.push_back(++currQuad);
				insert_quads(new quad(if_greatereq, $1, $3, NULL, -1, currQuad));
				$$->falselist.push_back(++currQuad);
				insert_quads(new quad(jump, NULL, NULL, NULL, -1, currQuad));
				if((while_flag || for_flag) && !if_flag){
					while_startlist.push_back(currQuad-1);
				}
				std::cout<<"expr <-- expr > expr\n";  
			}
			| expr GREATER_EQUAL expr{
				temp_metavlhth=true;
				$$=new expr(boolexpr_e, "", 0, "", $1->numConst >= $3->numConst, NULL);
				$$->boolConst = $1->numConst >= $3->numConst;
				$$->truelist.push_back(++currQuad);
				insert_quads(new quad(if_greatereq, $1, $3, NULL, -1, currQuad));
				$$->falselist.push_back(++currQuad);
				insert_quads(new quad(jump, NULL, NULL, NULL, -1, currQuad));
				if((while_flag || for_flag) && !if_flag){
					while_startlist.push_back(currQuad-1);
				}
				std::cout<<"expr <-- expr >= expr\n"; 
			}
			| expr LESS expr{
				temp_metavlhth=true;
				$$=new expr(boolexpr_e, "", 0, "", $1->numConst < $3->numConst, NULL);
				$$->boolConst = $1->numConst < $3->numConst;
				$$->truelist.push_back(++currQuad);
				insert_quads(new quad(if_less, $1, $3, NULL, -1, currQuad));
				$$->falselist.push_back(++currQuad);
				insert_quads(new quad(jump, NULL, NULL, NULL, -1, currQuad));
				if((while_flag || for_flag) && !if_flag){
					while_startlist.push_back(currQuad-1);
				}
				std::cout<<"expr <-- expr < expr\n";
			 }
			| expr LESS_EQUAL expr{ 
				temp_metavlhth=true;	
				$$=new expr(boolexpr_e, "", 0, "", $1->numConst <= $3->numConst, NULL);
				$$->boolConst = $1->numConst <= $3->numConst;
				$$->truelist.push_back(++currQuad);
				insert_quads(new quad(if_lesseq, $1, $3, NULL, -1, currQuad));
				$$->falselist.push_back(++currQuad);
				insert_quads(new quad(jump, NULL, NULL, NULL, -1, currQuad));
				if((while_flag || for_flag) && !if_flag){
					while_startlist.push_back(currQuad-1);
				}
				std::cout<<"expr <-- expr <= expr\n"; 
			} 
			| expr EQUAL expr{  
				temp_metavlhth=true;
				$$=new expr(boolexpr_e, "", 0, "", $1->numConst == $3->numConst, NULL);
				$$->boolConst = $1->numConst == $3->numConst;
				$$->truelist.push_back(++currQuad);
				insert_quads(new quad(if_eq, $1, $3, NULL, -1, currQuad));
				$$->falselist.push_back(++currQuad);
				insert_quads(new quad(jump, NULL, NULL, NULL, -1, currQuad));
				if((while_flag || for_flag) && !if_flag){
					while_startlist.push_back(currQuad-1);
				}
				std::cout<<"expr <-- expr == expr\n"; 
			}
			| expr NOT_EQUAL expr{
				temp_metavlhth=true;
				$$=new expr(boolexpr_e, "", 0, "", $1->numConst != $3->numConst, NULL);
				$$->boolConst = $1->numConst != $3->numConst;
				$$->truelist.push_back(++currQuad);
				insert_quads(new quad(if_noteq, $1, $3, NULL, -1, currQuad));
				$$->falselist.push_back(++currQuad);
				insert_quads(new quad(jump, NULL, NULL, NULL, -1, currQuad));
				if((while_flag || for_flag) && !if_flag){
					while_startlist.push_back(currQuad-1);
				}
				std::cout<<"expr <-- expr != expr\n"; 
			}
			| term{
				$$ = $1;
				std::cout<<"expr <-- term\n";}
			;

assignexpr:	lvalue ISON{if(accessed_lib){
							std::cout << "\033[1;31mERROR\033[0m"<<": Cannot access LIBRARY FUNCTION as a variable"<< std::endl;
							accessed_lib = 0;
						}
						ison = true;
						cout << "***ISON***" <<endl;
					} expr{
						
						std::cout << "assignexpr <-- lvalue = expr" << std::endl;		
				if(!member_flag && !logic_flag && !member_flag_set && !member_flag_get){
					std::string temp_str_1=new_temp_name();
					if(scope==0){
						SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
						program_offset++;
					}
					else{
						SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
						function_offset++;
					}
					$$=new expr(assignexpr_e, temp_str_1, $4->numConst, "", $4->boolConst, NULL);
					insert_quads(new quad(_assign, $$, $4, NULL, -1, ++currQuad));
					currQuad++;
					insert_quads(new quad(_assign, $1, $$, NULL, -1, currQuad));
					ison = false;
				}
				else if(member_flag && !logic_flag && !member_flag_set && !member_flag_get){ 
					std::string temp_str_1=new_temp_name();
					if(scope==0){
						SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
						program_offset++;
					}
					else{
						SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
						function_offset++;
					}		
					std::vector<std::string> result;	
					boost::split(result, string_member, boost::is_any_of("."));
					$$=new expr(tableitem_e, temp_str_1, 0, "", false, NULL);
					struct expr *ex_1 = new expr(tableitem_e, result[0], 0, "", false, NULL);
					std::ostringstream out;
					out << result[1];
					struct expr *ex_2 = new expr(conststring_e, "", 0, out.str(), false, NULL);
					cout<<" ::"<<$4->numConst<<endl;
					currQuad++;
					insert_quads(new quad(tablesetelem, ex_1, ex_2, $4, -2, currQuad));
					currQuad++;
					insert_quads(new quad(tablegetelem, $$, ex_1, ex_2, -2, currQuad));
					member_flag = false; 

				}
				else if(!member_flag && logic_flag && !member_flag_set && !member_flag_get){	
					int trueLabel = ++currQuad;
					int falseLabel = trueLabel + 2;
					for(int i = 0; i < $4->truelist.size(); i++){
						for(int j = 0; j < quads.size(); j++){
							if($4->truelist[i] == quads[j].line){
								if(quads[j].label == -1) quads[j].label = trueLabel;
							}
						}
					}
					for(int i = 0; i < $4->falselist.size(); i++){
						for(int j = 0; j < quads.size(); j++){
							if($4->falselist[i] == quads[j].line){
								if(quads[j].label == -1) quads[j].label = falseLabel;
							}
						}
					}
					std::string temp_str_1=new_temp_name();
					if(scope==0){
						SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
						program_offset++;
					}
					else{
						SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
						function_offset++;
					}	
					$$=new expr(assignexpr_e, temp_str_1, 0, "", false, NULL);
					insert_quads(new quad(_assign, $1, new expr(assignexpr_e, "TRUE", 0, "", false, NULL), NULL, -1, trueLabel));
					currQuad++;
					cout<<"test"<<endl;
					insert_quads(new quad(jump, NULL, NULL, NULL, currQuad + 2, trueLabel + 1));
					currQuad++;
					insert_quads(new quad(_assign, $$, new expr(assignexpr_e, "FALSE", 0, "", false, NULL), NULL, -1, falseLabel));
					currQuad++;
					insert_quads(new quad(_assign, $1, $$, NULL, -1, currQuad));
					logic_flag = false;					
				}
				else if(!member_flag && !logic_flag && member_flag_set && !member_flag_get){
					std::string temp_str_1=new_temp_name();
					if(scope==0){
						SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
						program_offset++;
					}
					else{
						SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
						function_offset++;
					}
					$$ = new expr(tableitem_e, $1->sym, 0, "", false, NULL);
					currQuad++;
						cout << "***SETELEM*** " << $4->type << endl;
					
					if(table_str_index.compare(""))
						insert_quads(new quad(tablesetelem, new expr(tableitem_e, $1->sym, 0, "", false, NULL),
					new expr(conststring_e, table_str_index, table_index, "", false, NULL),$4, -2, currQuad));
					else
						insert_quads(new quad(tablesetelem, new expr(tableitem_e, $1->sym, 0, "", false, NULL),
					new expr(constnum_e, table_str_index, table_index, "", false, NULL),$4, -2, currQuad));						
					
					member_flag_set = false;
				}
				else if(!member_flag && !logic_flag && member_flag_get && !member_flag_set){
					std::string temp_str_1=new_temp_name();
					if(scope==0){
						SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
						program_offset++;
					}
					else{
						SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
						function_offset++;
					}
					$$ = new expr(tableitem_e, temp_str_1, 0, "", false, NULL);
					insert_quads(new quad(tablesetelem, $1, new expr(constnum_e, "", table_index, "", false, NULL), new expr(constnum_e, $4->strConst, $4->numConst, "", false, NULL), -2,++currQuad));
					insert_quads(new quad(tablegetelem, $$, $1, new expr(constnum_e, $4->strConst, table_index, "", false, NULL), -2,++currQuad));
					temp_str_1=new_temp_name();
					if(scope==0){
						SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
						program_offset++;
					}
					else{
						SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
						function_offset++;
					}	
					member_flag_get = false;
					ison = false;
				}
				$$->list.push_back(currQuad);
			}

term:		ARISTERI_PARENTHESI expr DEXIA_PARENTHESI{
				$$ = $2;
				std::cout <<"term <-- (expr)\n"; 
			} 
			| MINUS expr %prec UMINUS{   	
				$$ = $2;
				$$->numConst = -($2->numConst);
				insert_quads(new quad(uminus, $$, new expr(constnum_e, "", -1, "", false, NULL), $2, -2, ++currQuad));
			    std::cout <<"term <-- -expr\n";  
			} 
			| NOT expr{  
				std::string temp_str_1=new_temp_name();
				if(scope==0){
					SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
					program_offset++;
				}
				else{
					SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
					function_offset++;
				}	
				$$=new expr(boolexpr_e, temp_str_1, 0, "", !($2->boolConst), NULL);
				$$->boolConst = !($2->boolConst);
				insert_quads(new quad(if_eq, $2, new expr(constbool_e, "", 0, "", false, NULL), NULL, -1, ++currQuad));
				$$->truelist.push_back(currQuad);
				insert_quads(new quad(jump, NULL, NULL, NULL, -1, ++currQuad));
				$$->falselist.push_back(currQuad);
				logic_flag=true;
				std::cout <<"term <-- !expr\n";  
			}
			| PLUS_PLUS lvalue{ 
				assign_flag=true;
				std::string temp_str_1=new_temp_name();
				if(scope==0){
					SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
					program_offset++;
				}
				else{
					SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
					function_offset++;
				}	
				$$ = $2;
				$$->numConst = ($2->numConst) + 1;				
				insert_quads(new quad(_assign, new expr(assignexpr_e, temp_str_1, 0, "", false, NULL), $$,NULL, -1, ++currQuad));
				assign_quads.push_back(currQuad);
				currQuad++;
				insert_quads(new quad(add, $2, $2, new expr(constnum_e, "", 1, "", false, NULL), -2, currQuad));				
				std::cout <<"term <-- ++lvalue\n";
			} 
			| lvalue PLUS_PLUS{    
				$$=$1;
				assign_flag=true;
				std::string temp_str_1=new_temp_name();	
				if(scope==0){
					SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
					program_offset++;
				}
				else{
					SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
					function_offset++;
				}			
				insert_quads(new quad(_assign, new expr(assignexpr_e, temp_str_1, 0, "", false, NULL), $$, NULL, -1, ++currQuad));
				assign_quads.push_back(currQuad);
				currQuad++;
				insert_quads(new quad(add, $1, $1, new expr(constnum_e, "", 1, "", false, NULL), -2, currQuad));
				std::cout <<"term <-- lvalue++\n"; 
			}
			| MINUS_MINUS lvalue{
				assign_flag=true;
				std::string temp_str_1=new_temp_name();
				if(scope==0){
					SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
					program_offset++;
				}
				else{
					SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
					function_offset++;
				}
				$$ = $2;
				$$->numConst = ($2->numConst) - 1;				
				insert_quads(new quad(_assign, new expr(assignexpr_e, temp_str_1, 0, "", false, NULL), $$,NULL, -1, ++currQuad));
				assign_quads.push_back(currQuad);
				currQuad++;
				insert_quads(new quad(sub, $2, $2, new expr(constnum_e, "", 1, "", false, NULL), -2, currQuad));
				std::cout <<"term <== --lvalue\n"; }
			| lvalue MINUS_MINUS{    
				assign_flag=true;         
				std::string temp_str_1=new_temp_name();
				if(scope==0){
					SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
					program_offset++;
				}
				else{
					SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
					function_offset++;
				}
				$$=$1;						
				insert_quads(new quad(_assign, new expr(assignexpr_e, temp_str_1, 0, "", false, NULL), $$, NULL, -1, ++currQuad));
				assign_quads.push_back(currQuad);
				currQuad++;
				insert_quads(new quad(sub, $1, $1, new expr(constnum_e, "", 1, "", false, NULL), -2, currQuad));
				std::cout <<"term <== lvalue--\n"; }
			| primary{          
							$$ = $1;
							std::cout<<"term <-- primary\n";    }
			; 

primary:	lvalue{	    $$=$1;				std::cout<<"primary <-- lvalue\n";}
			| call{		 $$=$1;   		   std::cout<<"primary <-- call\n";}
			| objectdef{  $$=$1;   		  std::cout<<"primary <-- objectdef\n";}
			| ARISTERI_PARENTHESI funcdef DEXIA_PARENTHESI{
				$$=$2;
				std::cout<<"primary <-- (funcdef)\n";}
			| const{		 $$=$1;	
					      std::cout<<"primary <-- const\n";}
			;

lvalue:		ID{	
					if(SymTable_LIBRARY_contains(yylval.strValue)){
						accessed_lib = 1;
						$$ = new expr(var_e, yylval.strValue, 0, "", false, NULL);
					} 
					else if(SymTable_LOCAL_all_prev_scope_isActive_contains(yylval.strValue)){
						std::cout<<"current scope: "<<scope;
						std::cout << "\033[1;31mERROR\033[0m"<<": Cannot access local variable " << yylval.strValue << std::endl;
					}
					else if(scope == 0 && !SymTable_contains(yylval.strValue) && !SymTable_USERFUNCT_contains(yylval.strValue) &&
					 strcmp(global_for_val,yylval.strValue) != 0){
						SymTable_put(scope, yylineno, GLOBAL, yylval.strValue, 0, program_offset);
						program_offset++;
						$$ = new expr(var_e, yylval.strValue, 0, "", false, NULL);
						SymTable_change_visibility(yylval.strValue, 0);
					}
					else if(scope != 0 && !SymTable_contains(yylval.strValue) && !SymTable_USERFUNCT_contains(yylval.strValue) &&
					 strcmp(global_for_val,yylval.strValue) != 0 && 
					 !SymTable_WHILE_FOR_IF_ELSE_contains(yylval.strValue) && !SymTable_LOCAL_prev_scope_isActive_contains(yylval.strValue)){
					if(is_function){
						SymTable_put(scope, yylineno, __LOCAL, yylval.strValue, 1, function_offset);
						function_offset++;
					}
					else{
						SymTable_put(scope, yylineno, __LOCAL, yylval.strValue, 1, function_offset);
						function_offset++;							
					}
					$$ = new expr(var_e, yylval.strValue, 0, "", false, NULL);
					SymTable_change_visibility(yylval.strValue, 0);						
					}
					else{
						$$ = new expr(var_e, yylval.strValue, 0, "", false, NULL);					
					}
					if(global_for == 1){ 
						global_for_val = (char*)malloc(sizeof(yylval.strValue)); 
						sprintf(global_for_val, "%s",yylval.strValue);
						global_for = 0;
					}
					std::cout<<"lvalue <-- ID\n";
			}
			| LOCAL ID{
					if(SymTable_LIBRARY_contains(yylval.strValue)){
						std::cout <<"\033[1;31mERROR\033[0m"<< ": "<< yylval.strValue <<" is a library function" << std::endl;
					}
					else if(SymTable_LOCAL_isActive_contains(yylval.strValue) && SymTable_contains(yylval.strValue)){
						$$ = new expr(var_e, yylval.strValue, 0, "", false, NULL);
					}
					else if(!SymTable_contains(yylval.strValue) && strcmp(global_for_val,yylval.strValue) != 0){
						if(scope == 0){
							SymTable_put(scope, yylineno, __LOCAL, yylval.strValue, 1, function_offset);
							program_offset++;
						}
						else{
							if(is_function){
								SymTable_put(scope, yylineno, __LOCAL, yylval.strValue, 1, function_offset);
								function_offset++;
							}
							else{
								SymTable_put(scope, yylineno, __LOCAL, yylval.strValue, 1, function_offset);
								function_offset++;							
							}
						}
						$$ = new expr(var_e, yylval.strValue, 0, "", false, NULL);
						SymTable_change_visibility(yylval.strValue, 0);
					}
					if(global_for == 1){
						global_for_val = (char*)malloc(sizeof(yylval.strValue)); 
						sprintf(global_for_val, "%s",yylval.strValue);
						global_for = 0;
					}
				std::cout<<"lvalue <-- LOCAL_ID\n";
			}
			| COLON_COLON ID{
				if(!SymTable_GLOBAL_isActive_contains(yylval.strValue)){
					std::cout <<"\033[1;31mERROR\033[0m"<< ": cannot access " << yylval.strValue << ". Not a global variable." << std::endl;
				} 
				else if(SymTable_GLOBAL_isActive_contains(yylval.strValue)){
					struct expr *e3 = new expr(var_e,yylval.strValue , 0, "", false, NULL);
					$$=e3;
				}
				std::cout<<"lvalue <-- COLON_COLON ID\n";
			}
			| member{   
					$$ = $1;
					
					std::cout<<"lvalue <-- member\n";}
			;

member:		lvalue DOT ID{
				if(SymTable_LIBRARY_contains(yylval.strValue)){
					std::cout <<"\033[1;31mERROR\033[0m"<< ": Cannot access LIBRARY FUNCTION" << yylval.strValue <<" this way."<< std::endl;
				}
				else{
					ostringstream out;
					$$=new expr(assignexpr_e, $1->sym, 0, yylval.strValue, false, NULL);
					cout<< "**pernaei 1" <<endl;					
					out << $1->sym << "." << yylval.strValue;
					cout<< "**pernaei 2" <<endl;
					string_member.assign(out.str());
					cout<< "**pernaei 3" <<endl;					
					ostringstream _OUT;
					_OUT << yylval.strValue; 
					member_flag = true;
				}
				std::cout<<"member <-- lvalue.ID\n";
			}
			| lvalue LEFT_BRACKET expr RIGHT_BRACKET{
					if(ison){
						cout << "***MEMBER FLAG GET***" << endl;
						table_index=$3->numConst;
						$$ = new expr(var_e, $1->sym, $3->numConst, $3->strConst, false, NULL);
						member_flag_get = true;
						ison = false;
					}
					else{
						cout << "***MEMBER FLAG SET***" << endl;
						$$ = new expr(var_e, $1->sym, $3->numConst, $3->strConst, false, NULL);
						//$$ = $3;
						table_index=$3->numConst;
						table_str_index=$3->strConst;
						member_flag_set = true;
					}
					std::cout<<"member <-- lvalue[expr] \n";
				} 
			| call DOT ID{
				if(SymTable_LIBRARY_contains(yylval.strValue)){
					std::cout <<"\033[1;31mERROR\033[0m"<< ": Cannot access LIBRARY FUNCTION" << yylval.strValue <<" this way."<< std::endl;
				}	
				else if(SymTable_GLOBAL_isActive_contains(yylval.strValue)){
					std::cout <<"\033[1;31mERROR\033[0m"<< ": Cannot access GLOBAL " << yylval.strValue <<" this way."<< std::endl;
				}
				else if((!SymTable_contains(yylval.strValue)) && (!SymTable_LIBRARY_contains(yylval.strValue))){
					if(scope == 0){
						SymTable_put(scope, yylineno, GLOBAL, yylval.strValue, 0, program_offset);
						program_offset++;
					}
					else{
						if(is_function){
							SymTable_put(scope, yylineno, __LOCAL, yylval.strValue, 1, function_offset);
							function_offset++;
						}
						else{
							SymTable_put(scope, yylineno, __LOCAL, yylval.strValue, 1, function_offset);
							function_offset++;
						}
					}
					ostringstream out;
					$3=new expr(assignexpr_e, yylval.strValue, 0, "", false, NULL);
					out << $1->sym << "." << $3->sym;
					string temp_str_1=new_temp_name();
					string_member.assign(out.str());
					ostringstream _OUT;
					_OUT <<  "\"" << $3->sym<< "\"";
				if(scope==0){
					SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
					program_offset++;
				}
				else{
					SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
					function_offset++;
				}	
					$$ = new expr(var_e, temp_str_1, 0, "", false, NULL);
					insert_quads(new quad(tablegetelem, $$, new expr(assignexpr_e, $1->sym, 0, "", false, NULL), new expr(assignexpr_e, _OUT.str(), 0, "", false,NULL), -2, ++currQuad));
					member_flag = true;
				}			 
				std::cout<<"member <-- call.ID \n";
			}
			| call LEFT_BRACKET expr RIGHT_BRACKET{
				string temp_str_1=new_temp_name();
				if(scope==0){
					SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
					program_offset++;
				}
				else{
					SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
					function_offset++;
				}
				$$=new expr(var_e, temp_str_1, 0, "", false, NULL);	
				insert_quads(new quad(tablegetelem, $$, $1,$3, -2, ++currQuad));	
				std::cout<<"member <-- [expr] \n";}
			;

call:		call ARISTERI_PARENTHESI elist DEXIA_PARENTHESI{
					insert_quads(new quad(call, $1, NULL, NULL, -2, ++currQuad));
					string temp_str_1=new_temp_name();
					if(scope==0){
						SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
						program_offset++;
					}
					else{
						SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
						function_offset++;
					}	
					insert_quads(new quad(getretval, new expr(assignexpr_e, temp_str_1, 0, "",false, NULL),NULL, NULL, -2, ++currQuad));
					std::cout<<"call <-- call(elist) \n";}
			| lvalue callsuffix{
					string temp_str_1=new_temp_name();
					if(scope==0){
						SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
						program_offset++;
					}
					else{
						SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
						function_offset++;
					}
					if(accessed_lib){
						accessed_lib = 0;
					}
					if(!method_flag && !SymTable_LIBRARY_contains((char*)$1->sym.c_str())){
						for(int i=0; i<getretval_vector.size(); i++)
						{
							if(getretval_vector[i]->sym=="")
							{
								getretval_vector[i]->sym=$1->sym;
							}
						}
						insert_quads(new quad(call, new expr(programfunc_e, $1->sym, 0, "", false, NULL), NULL, NULL, -2, ++currQuad));
						if(getretval_vector.size()>0)
							$$=new expr(assignexpr_e, temp_str_1, getretval_vector[0]->numConst, "", false, NULL);
						else
							$$=new expr(assignexpr_e, temp_str_1, $1->numConst, "", false, NULL);
					}
					else if(SymTable_LIBRARY_contains((char*)$1->sym.c_str())){
						insert_quads(new quad(call, new expr(libraryfunc_e, $1->sym, 0, "", false, NULL), NULL, NULL, -2, ++currQuad));
					}
					else{
						insert_quads(new quad(call, new expr(programfunc_e, $1->sym, 0, "", false, NULL), NULL, NULL, -2, ++currQuad));
						method_flag=false;
					}
					if(getretval_vector.size()>0)
						insert_quads(new quad(getretval, new expr(assignexpr_e, getretval_vector[0]->strConst, getretval_vector[0]->numConst, "", false, NULL), new expr(assignexpr_e, temp_str_1, getretval_vector[0]->numConst, "", false, NULL), NULL, -2, ++currQuad));
					else
						insert_quads(new quad(getretval, new expr(assignexpr_e, $1->strConst, $1->numConst, "", false, NULL), new expr(assignexpr_e, temp_str_1, $1->numConst, "", false, NULL), NULL, -2, ++currQuad));
 
				if(ret_flag){
					/*std::string temp_str_1=new_temp_name();
					if(scope==0){
						SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
						program_offset++;
					}
					else{
						SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
						function_offset++;
					}*/	
					//currQuad++;
					//$$ = new expr(assignexpr_e, temp_str_1, 0, "", false, NULL);
					//insert_quads(new quad(getretval, $$, NULL, NULL, -2, currQuad));					
				}
				std::cout<<"call <-- lvalue callsuffix\n";
			}
			| ARISTERI_PARENTHESI funcdef DEXIA_PARENTHESI ARISTERI_PARENTHESI elist DEXIA_PARENTHESI{
				insert_quads(new quad(call, $2, NULL, NULL, -2, ++currQuad));
					string temp_str_1=new_temp_name();
				if(scope==0){
					SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
					program_offset++;
				}
				else{
					SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
					function_offset++;
				}
					insert_quads(new quad(getretval, new expr(assignexpr_e, temp_str_1, 0, "",false, NULL),NULL, NULL, -2, ++currQuad));
					$$=$2;
				std::cout<<"call <-- (funcdef)(elist)\n";}
			;

callsuffix:	normcall{  std::cout<<"callsuffix <-- normcall\n";}
			| methodcall{ 
				$$=$1;
				std::cout<<"callsuffix <-- methodcall\n";}
			;

normcall:	ARISTERI_PARENTHESI{call_func_flag = true;} elist DEXIA_PARENTHESI{std::cout<<"normcall <-- normcall(elist)\n";}
			;

methodcall:	DOT_DOT ID{
				if(SymTable_LIBRARY_contains(yylval.strValue)){
					std::cout <<"\033[1;31mERROR\033[0m"<< ": Cannot access LIBRARY FUNCTION" << yylval.strValue <<" this way."<< std::endl;
				}	
				else if(!SymTable_contains_no_scope(yylval.strValue) && !SymTable_LIBRARY_contains(yylval.strValue) && scope == 0){
					SymTable_put(scope,yylineno, USERFUNCT, yylval.strValue, 0, program_offset);
					program_offset++;
				}
				else if(!SymTable_contains_no_scope(yylval.strValue) && !SymTable_LIBRARY_contains(yylval.strValue) && scope != 0){
					SymTable_put(scope,yylineno, USERFUNCT, yylval.strValue, 1, function_offset);
					function_offset++;
				}
				
				method_string=yylval.strValue;
				method_flag=true;
			} ARISTERI_PARENTHESI elist DEXIA_PARENTHESI{ // equivalent to lvalue.id(lvalue, elist)
				string temp_str_1=new_temp_name();
				if(scope==0){
					SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
					program_offset++;
				}
				else{
					SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
					function_offset++;
				}	
				ostringstream _OUT;
				_OUT <<  "\"" << method_string<< "\"";
				if(scope==0){
					SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
					program_offset++;
				}
				else{
					SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
					function_offset++;
				}	
				$$ = new expr(var_e, temp_str_1, 0, "", false, NULL);
				insert_quads(new quad(tablegetelem, $$, $5, new expr(assignexpr_e, _OUT.str(), 0, "", false,NULL), -2, ++currQuad));
				insert_quads(new quad(param, new expr(assignexpr_e, $5->sym, 0, "", false, NULL), NULL, NULL, -2, ++currQuad));
				std::cout<<"methodcall <-- ..ID(elist)\n";}
			;  

elist: 		expr{	
				if(t_create){	
					bool found = false;
					int index;
					for(int i = 0; i < indexes.size(); i++){
						if(!temp_vector[count_temps].compare(indexes[i]->sym)){
							found = true;
							index = indexes[i]->numConst;
							indexes[i]->numConst++;
							break;
						}
					}
					
					if(found){ 
						cout << "***INDEX found " << index << endl;
					insert_quads(new quad(tablesetelem, new expr(assignexpr_e, temp_vector[count_temps], 0, "", false,NULL), 
					new expr(constnum_e, "", index,"",false,NULL),
				 $1, -2, ++currQuad));
					}
					else{ 
						cout << "***INDEX not found" << endl;
					insert_quads(new quad(tablesetelem, new expr(assignexpr_e, temp_vector[count_temps], 0, "", false,NULL), 
					new expr(constnum_e, "", array_index,"",false,NULL),
				 $1, -2, ++currQuad));
					}
				}
				array_index++;
				
				if((method_flag || call_func_flag) && $1->strConst == "")
					insert_quads(new quad(param, new expr(constnum_e, "", $1->numConst, "", false, NULL), NULL, NULL, -2, ++currQuad));
				else if((method_flag || call_func_flag) && $1->strConst != "")
					insert_quads(new quad(param, new expr(conststring_e, "", 0, $1->strConst, false, NULL), NULL, NULL, -2, ++currQuad));
			} expr2{
				t_create = false;
				std::cout<<"elist <-- expr expr2\n";
			}
			|{}
			;


expr2:		COMMA expr{
				if(t_create){	
					bool found = false;
					int index;
					for(int i = 0; i < indexes.size(); i++){
						if(!temp_vector[count_temps].compare(indexes[i]->sym)){
							found = true;
							index = indexes[i]->numConst;
							indexes[i]->numConst++;
							break;
						}
					}
					
					if(found){ 
						cout << "***INDEX found " << index << endl;
					insert_quads(new quad(tablesetelem, new expr(assignexpr_e, temp_vector[count_temps], 0, "", false,NULL), 
					new expr(constnum_e, "", index,"",false,NULL),
				 $2, -2, ++currQuad));
					}
					else{ 
						cout << "***INDEX not found" << endl;
					insert_quads(new quad(tablesetelem, new expr(assignexpr_e, temp_vector[count_temps], 0, "", false,NULL), 
					new expr(constnum_e, "", array_index,"",false,NULL),
				 $2, -2, ++currQuad));
					}
				}
				array_index++;	
				if((method_flag || call_func_flag) && $2->strConst == "")
					insert_quads(new quad(param, new expr(constnum_e, "", $2->numConst, "", false, NULL), NULL, NULL, -2, ++currQuad));
				else if((method_flag || call_func_flag) && $2->strConst != "")
					insert_quads(new quad(param, new expr(conststring_e, "", 0, $2->strConst, false, NULL), NULL, NULL, -2, ++currQuad));
			} expr2{

			}
			| {}
	 		;

objectdef:  objectdef_2 elist RIGHT_BRACKET{	
				count_temps--;
				if(left_bracket) count_temps = 0;
				left_bracket = false;
				std::cout<<"objectdef <-- [elist]\n";
			}
			| objectdef_2 indexed RIGHT_BRACKET{
				count_temps--;
				std::cout<<"objectdef <-- [indexed]\n";}
			;

objectdef_2:   LEFT_BRACKET{
				left_bracket = true;
				count_temps = count_overall_temps;
				count_temps++;
				count_overall_temps++;
				array_index = 0;
				string temp_str_1=new_temp_name();
				if(scope==0){
					SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
					program_offset++;
				}
				else{
					SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
					function_offset++;
				}		
				$$=new expr(newtable_e, temp_str_1, 0, "", false, NULL);
				insert_quads(new quad(tablecreate, $$, NULL, NULL, -2, ++currQuad));	
				temp_tablecreate=temp_str_1;
				temp_vector.push_back(temp_str_1);
				indexes.push_back(new expr(constnum_e, temp_str_1, 0, "", false, NULL));
				t_create = true;
				cout << "objectdef_2 <-- [ " << endl;
			   }
indexed:	indexedelem indexedelem_temp{
				$$=$1;
				std::cout<<"indexed <-- indexedelem indexedelem_temp\n";}
			;

indexedelem_temp:COMMA indexedelem indexedelem_temp{
					
					std::cout<<"indexedelem_temp <-- ,indexedelem indexedelem_temp\n";}
				|{std::cout<<"indexedelem_temp<--empty"<<std::endl;}
				;

indexedelem:	LEFT_BRACE{flag = 1;} expr COLON expr RIGHT_BRACE{
				flag=0;
				string temp_str_1=new_temp_name();
				if(scope==0){
					SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
					program_offset++;
				}
				else{
					SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
					function_offset++;
				}	
				if(t_create==true)
				{
					$$=new expr(assignexpr_e, temp_vector[count_temps], 0, "", false,NULL);
					insert_quads(new quad(tablesetelem, $$, $3, $5, -2, ++currQuad));
				}
				else{
					$$=new expr(assignexpr_e, temp_str_1, 0, "", false,NULL);
					insert_quads(new quad(tablesetelem, $$, $3, $5, -2, ++currQuad));
				}
				std::cout<<"indexedelem <-- {expr:expr}\n";
				}
				;

block:		LEFT_BRACE{
				scope++;
			} RIGHT_BRACE{
				SymTable_change_visibility(c_temp_function,1); scope--;
				if(if_flag)
				{
					insert_quads(new quad(jump, NULL, NULL, NULL, -1, ++currQuad));
					$$ = new expr(constnum_e, "", 0, "", false, NULL);
					end_iflist.push_back(currQuad);
				}
				if(number_of_elses==0)
					if_flag=false;
				std::cout<<"block <-- {}\n";
			}
			| LEFT_BRACE{scope++; } stmt stmt_list 
			RIGHT_BRACE {
				SymTable_find_by_type(__LOCAL, scope);
				SymTable_find_by_type(FORMAL, scope);
				SymTable_find_by_type(USERFUNCT, scope);
				scope--;
				while_scope = -1;
				for_scope = -1;
				if_scope = -1;
				is_function = 0;
				$$=$3;
				std::cout<<"block <-- {stmt stmt_list}\n";
			}
			; 

funcdef:	FUNCTION ARISTERI_PARENTHESI{
				is_function = 1; 
				function_offset = 0;
				char temp_str[2];
				char str_anonymous[2];
				strcpy(temp_str,"$");
				str_anonymous[0] = anonymous_count + '0';
				strcat(temp_str,str_anonymous); 
				strcpy(prev_func_id, strdup(temp_str));
				prev_scope = scope;
				prev_lineno = yylineno;
				currQuad++;
				insert_quads(new quad(funcstart, new expr(newtable_e, prev_func_id, 0, "", false, NULL), NULL, NULL, -2, currQuad));
				string s(prev_func_id);
				func_list.push_back(s);
				func_c++;
				func_flag = true;
				number_of_functions++;
				anonymous_count++; 
				scope++;
				cout << "FUNCTION (" << endl;
			} idlist DEXIA_PARENTHESI{scope--;
			} block{
				 if(func_flag){
					SymTable_put(prev_scope, prev_lineno, USERFUNCT, prev_func_id, 1, function_offset);
					function_offset++;
					SymTable_change_visibility(prev_func_id,0);
					currQuad++;
					$$ = new expr(programfunc_e, func_list[func_c], 0, "", false, NULL);
					func_c--;
					insert_quads(new quad(funcend, $$, NULL, NULL, -2, currQuad));
					for(int i = 0; i < ret_list.size(); i++){
						backpatch(ret_list[i], currQuad);
					}
				 }
				 number_of_functions--;
			 			if(number_of_functions==0)
						 	func_flag=false;
				std::cout<<"funcdef <-- function(idlist) block\n";
			}
			|FUNCTION{is_function = 1; function_offset = 0; ret_flag = false;} ID{
				if(SymTable_LIBRARY_contains(yytext)){std::cout <<"\033[1;31mERROR\033[0m"<< ": Redeclaration of Library function." << std::endl;}
				else if(SymTable_prev_USERFUNCT_contains(yytext)){std::cout << "\033[1;31mERROR\033[0m" << ": Redeclaration of function " << yytext << std::endl;}
				else if(SymTable_contains(yytext) && (SymTable_contains_isACTIVE(yytext) || SymTable_LOCAL_GLOBAL_isActive_contains(yytext))){
					std::cout << "\033[1;31mERROR\033[0m"<<": Redeclaration of function with existing id." << std::endl; return 0;}
				else{
					strcpy(prev_func_id2, (char*)yytext);
					prev_scope = scope;
					prev_lineno = yylineno;
					currQuad++;
					insert_quads(new quad(funcstart, new expr(newtable_e, prev_func_id2, 0, "", false, NULL), NULL, NULL, -2, currQuad));
					string s(prev_func_id2);
					func_list_2.push_back(s);
					func_c_2++;
					strcpy(c_temp_function, yylval.strValue);
					func_flag = true;
				}
			}
			 ARISTERI_PARENTHESI{scope++; number_of_functions++;} idlist DEXIA_PARENTHESI{scope--;
			 		} block{
						if(func_flag){
							SymTable_put(prev_scope, prev_lineno, USERFUNCT, prev_func_id2, 1, function_offset);
							function_offset++;
							SymTable_change_visibility(prev_func_id2,0);
							currQuad++;
							$$ = new expr(programfunc_e, func_list_2[func_c_2], 0, "", false, NULL);
							func_c_2--;
							insert_quads(new quad(funcend, $$, NULL, NULL, -2, currQuad));
					for(int i = 0; i < ret_list.size(); i++){
						backpatch(ret_list[i], currQuad);
					}
				 		}
						number_of_functions--;
							if(number_of_functions==0)
								func_flag=false;
				 		std::cout<<"funcdef <-- function ID(idlist) block\n";
			 		}
const:		INTCONST {
				$$=new expr(constnum_e, "", yylval.intValue, "", false, NULL);
				std::cout<<"const <--   INTCONST      \n";}
			| REALCONST {
				$$=new expr(constnum_e, "", yylval.realValue, "", false, NULL);
				std::cout<<"const <--  REALCONST    \n";}
			| STRING     {
				$$ = new expr(conststring_e, "", 0, yylval.strValue, false, NULL);
				std::cout<<"const <-- STRING     \n"; }
			| NIL		  {
				$$=new expr(nil_e, "", 0, "nil", false, NULL);
				std::cout<<"const <-- NIL      \n"; }
			| TRUE         {
				$$=new expr(constbool_e, "", 0, "", true, NULL);
				std::cout<<"const <-- TRUE   \n"; }
			| FALSE         {
				$$=new expr(constbool_e, "", 0, "", false, NULL);
				std::cout<<"const <-- FALSE\n"; }
			;  
idlist:		ID{
				if(SymTable_LIBRARY_contains(yylval.strValue)){
					std::cout <<"\033[1;31mERROR\033[0m"<< ": "<< yylval.strValue <<" is a library function" << std::endl;
				}
				else if(!SymTable_contains(yytext) && !SymTable_FORMAL_sameSCOPE_contains(yytext)) {
					SymTable_put(scope, yylineno, FORMAL, strdup(yytext), 2, formal_offset); 
					formal_offset++;
					SymTable_change_visibility(yytext,0);
					//currQuad++;
					//insert_quads(new quad(param, new expr(assignexpr_e, strdup(yytext), 0, "", false, NULL), NULL, NULL, -2, currQuad));
				}
				else{
					std::cout <<"\033[1;31mERROR\033[0m" <<": Redeclaration of formal " << yylval.strValue << std::endl;
				}
			} idlist_temp{std::cout<<"idlist <-- ID idlist_temp\n";}
			|
			;

idlist_temp: COMMA ID{
				if(SymTable_LIBRARY_contains(yylval.strValue)){
					std::cout <<"\033[1;31mERROR\033[0m"<< ": "<< yylval.strValue <<" is a library function" << std::endl;
				}
				else if(!SymTable_FORMAL_sameSCOPE_contains(yytext)) {
					SymTable_put(scope, yylineno, FORMAL, strdup(yytext), 2, formal_offset); 
					formal_offset++;
					SymTable_change_visibility(yytext,0);
					//currQuad++;
					//insert_quads(new quad(param, new expr(assignexpr_e, strdup(yytext), 0, "", false, NULL), NULL, NULL, -2, currQuad));
				}	
				else{
					std::cout << "\033[1;31mERROR\033[0m"<<": Redeclaration of formal " << yylval.strValue << std::endl;						
				}			
				} idlist_temp{std::cout<<"idlist_temp <-- ,ID idlist_temp\n";}
			|
			; 

ifstmt:		ifstart 
			DEXIA_PARENTHESI stmt ifstmt_temp{
				$$ = $4;
				if(number_of_elses>0) 
					number_of_elses--;
				if(number_of_elses==0) //backpatch gia otan exei ektelestei to if (h to else) kai ueloyme na pame sto telos
				{
					for(int i=0; i<end_iflist.size(); i++)
					{
						backpatch(end_iflist[i], currQuad+1);
						last_jump=end_iflist[i];
					}
				}
				if(ifstmt_flag )
				{
					if(iflist.size()==1)
					{
						backpatch(iflist[0], currQuad+1);
					}
					for(int i = 0; i < iflist.size()-1; i++) //backpatch gia otan den isxuei to if(katw apo to if_eq)
					{
						if(iflist[i]==22)
						{
							for(int i=0; i<quads.size(); i++)
							{
								if(quads[i].line==22)
								{
									quads[i].label=25;
								}
							}
						}
						backpatch(iflist[i], iflist[i+1]-1);
					}
				}
				cout<<"ifstmt <-- ifstart ) stmt ifstmt_temp\n";
			}
			;
			
ifstart:	IF{if_scope = scope; if_flag = true;} ARISTERI_PARENTHESI 
			expr{
					int trueLabel = ++currQuad;
					int falseLabel = trueLabel + 2;
					for(int i = 0; i < $4->truelist.size(); i++){
						for(int j = 0; j < quads.size(); j++){
							if($4->truelist[i] == quads[j].line){
								if(quads[j].label == -1) quads[j].label = trueLabel;
							}
						}
					} 
					for(int i = 0; i < $4->falselist.size(); i++){
						for(int j = 0; j < quads.size(); j++){ 
							if($4->falselist[i] == quads[j].line){
								if(quads[j].label == -1) quads[j].label = falseLabel;
							}
						}
					}
					if(temp_metavlhth)
					{
						std::string temp_str_1=new_temp_name();
						if(scope==0){
							SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
							program_offset++;
						}
						else{
							SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
							function_offset++;
						}	
						$$=new expr(assignexpr_e, temp_str_1, 0, "", false, NULL);					
						insert_quads(new quad(_assign, new expr(assignexpr_e, temp_str_1, 0, "", false, NULL), new expr(assignexpr_e, "TRUE", 0, "", false, NULL), NULL, -1, trueLabel));
						currQuad++;
						insert_quads(new quad(jump, NULL, NULL, NULL, falseLabel+1, trueLabel + 1));
						currQuad++;
						insert_quads(new quad(_assign, new expr(assignexpr_e, temp_str_1, 0, "", false, NULL), new expr(assignexpr_e, "FALSE", 0, "", false, NULL), NULL, -1, falseLabel));
						currQuad++;
						insert_quads(new quad(if_eq, $$, new expr(assignexpr_e, "TRUE", 0, "", false, NULL), NULL, falseLabel+3, falseLabel+1));//allagh edw
						currQuad++;
						insert_quads(new quad(jump, NULL, NULL, NULL, -1, currQuad));
						iflist.push_back(currQuad);
					}
					else
					{
						if($4->sym==""){
							if($4->boolConst==false )
									$$=new expr(constnum_e, $4->sym, -1, "", $4->boolConst, NULL);
							else		
								$$=new expr(constnum_e, $4->sym, $4->numConst, "", $4->boolConst, NULL);
							insert_quads(new quad(if_eq, $$, new expr(constnum_e, "", $4->numConst, "", $4->boolConst, NULL), NULL, currQuad+2, currQuad));
						}
						else{
							if($4->type==assignexpr_e)
							{
								$$=new expr(constnum_e, "", 1, "", $4->boolConst, NULL);
								insert_quads(new quad(if_eq, $$, new expr(constnum_e, "", 1, "", $4->boolConst, NULL), NULL, currQuad+2, currQuad));
							}
							else{
								if($4->boolConst==false)  
									$$=new expr(constnum_e, $4->sym, -1, "", $4->boolConst, NULL);
								else		
									$$=new expr(constnum_e, $4->sym, $4->numConst, "", $4->boolConst, NULL);
								insert_quads(new quad(if_eq, $$, new expr(constnum_e, $4->sym, $4->numConst, "", $4->boolConst, NULL), NULL, currQuad+2, currQuad));
				 			}
						}
						/*if($4->sym=="")
							$$=new expr(constnum_e, "", $4->numConst, "", false, NULL);
						else
							$$=new expr(conststring_e, $4->sym, -4, "", false, NULL);
						insert_quads(new quad(if_eq, $$, new expr(constbool_e, "TRUE", 0, "", true, NULL), NULL, currQuad+2, currQuad));*/
						currQuad++;
						insert_quads(new quad(jump, NULL, NULL, NULL, -1, currQuad));
						iflist.push_back(currQuad);
						if(expression_semicolon)
						{	
							ifstmt_flag = true;
						}							
						else if(!expression_semicolon && !ifstmt_flag){							
							ifstmt_flag = true;
						}
						else
						{
							ifstmt_flag = false;
						}	
					}
					temp_metavlhth=false;
					std::cout << "ifstart <-- IF(expr" << std::endl;
			}
			;
ifstmt_temp:	ELSE stmt{
						$$=$2;
						number_of_elses++;
						std::cout<<"ifstmt_temp <-- ELSE stmt"<<std::endl;
					}
				|{std::cout<<"ifstmt_temp <-- empty"<< std::endl;}
				;	

whilestmt:	whilestart DEXIA_PARENTHESI 
			stmt{ 
				loop_index--;
				currQuad++; 
				if($1->list.size()==1)
				{
					insert_quads(new quad(jump, NULL, NULL, NULL, $1->list[0]-1, currQuad));	
				}
				else
					insert_quads(new quad(jump, NULL, NULL, NULL, while_startlist[loop_index], currQuad)); 
				for(int i = 0; i < $1->whilelist.size(); i++){
					for(int j = 0; j < quads.size(); j++){
						if($1->whilelist[i] == quads[j].line){
							if(quads[j].label == -1) quads[j].label = currQuad+1;
						}
					}
				}	
				for(int i=0; i<breaklist.size(); i++)
				{
					backpatch(breaklist[i], currQuad+1);
				}	
				for(int i=0; i<continuelist.size(); i++)
				{
					if($1->list.size()==1)
					{
						backpatch(continuelist[i], $1->list[0]-1);
					}
					backpatch(continuelist[i], while_startlist[loop_index]); //
				}
				if(loop_index==0)
				{
					while_startlist.clear();
					while_flag=false;
				}
				std::cout<<"whilestmt <-- whilestart ) stmt\n";	
			}
			;

whilestart: WHILE{while_scope = scope; while_flag = true; loop_start=true;} ARISTERI_PARENTHESI expr{
					int trueLabel = ++currQuad;
					int falseLabel = trueLabel + 2;
					for(int i = 0; i < $4->truelist.size(); i++){
						for(int j = 0; j < quads.size(); j++){
							if($4->truelist[i] == quads[j].line){
								if(quads[j].label == -1) quads[j].label = trueLabel;
							}
						}
					}
					for(int i = 0; i < $4->falselist.size(); i++){
						for(int j = 0; j < quads.size(); j++){
							if($4->falselist[i] == quads[j].line){
								if(quads[j].label == -1) quads[j].label = falseLabel;
							}
						}
					}
					if(temp_metavlhth)
					{
						std::string temp_str_1=new_temp_name();
						if(scope==0){
							SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
							program_offset++;
						}
						else{
							SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
							function_offset++;
						}	
						$$=new expr(assignexpr_e, temp_str_1, 0, "", false, NULL);					
						insert_quads(new quad(_assign, new expr(assignexpr_e, temp_str_1, 0, "", false, NULL), new expr(assignexpr_e, "TRUE", 0, "", false, NULL), NULL, -1, trueLabel));
						currQuad++;
						insert_quads(new quad(jump, NULL, NULL, NULL, falseLabel+1, trueLabel + 1));
						currQuad++;
						insert_quads(new quad(_assign, new expr(assignexpr_e, temp_str_1, 0, "", false, NULL), new expr(assignexpr_e, "FALSE", 0, "", false, NULL), NULL, -1, falseLabel));
						currQuad++;
						insert_quads(new quad(if_eq, $$, new expr(assignexpr_e, "TRUE", 0, "", false, NULL), NULL, falseLabel+3, falseLabel+1));
						currQuad++;
						insert_quads(new quad(jump, NULL, NULL, NULL, -1, currQuad));
						$$->whilelist.push_back(currQuad); 
					}
					else
					{ 
						if($4->sym==""){
							$$=new expr(constnum_e, "", $4->numConst, "", true, NULL);
							insert_quads(new quad(if_eq, $$, new expr(constnum_e, "", $4->numConst, "", true, NULL), NULL, currQuad+2, currQuad));
						}
						else{
							if($4->type==assignexpr_e)
							{
								$$=new expr(constnum_e, "", 1, "", true, NULL);
								insert_quads(new quad(if_eq, $$, new expr(constnum_e, "", 1, "", true, NULL), NULL, currQuad+2, currQuad));
							}
							else{
								$$=new expr(constnum_e, $4->sym, $4->numConst, "", true, NULL);
								insert_quads(new quad(if_eq, $$, new expr(constnum_e, $4->sym, $4->numConst, "", true, NULL), NULL, currQuad+2, currQuad));
							}
						}
						//insert_quads(new quad(if_eq, $$, new expr($4->type, "", 1, "", true, NULL), NULL, currQuad+2, currQuad));
						while_startlist.push_back(currQuad); //mono edw
						currQuad++;
						insert_quads(new quad(jump, NULL, NULL, NULL, -1, currQuad));
						$$->whilelist.push_back(currQuad);	
					}
					loop_index++;
					temp_metavlhth=false;
					$$->list=$4->list;
				std::cout<<"whilestart <-- WHILE(expr\n";
			}  
			;

forstmt:	forstart2 DEXIA_PARENTHESI stmt{
				loop_index--; 
				for_index--;
				currQuad++;
				if(!assign_flag)
					assign_quads.push_back(while_startlist[loop_index]+1);
				insert_quads(new quad(jump, NULL, NULL, NULL, assign_quads[for_index], currQuad));
				for(int i = 0; i < $1->forlist.size(); i++){
					for(int j = 0; j < quads.size(); j++){
						if($1->forlist[i] == quads[j].line){
							if(quads[j].label == -1) quads[j].label = currQuad+1;
						}
					} 
				}
				for(int i=0; i<breaklist.size(); i++)
				{
					backpatch(breaklist[i], currQuad+1);
				}
				for(int i=0; i<continuelist.size(); i++)
				{
					backpatch(continuelist[i], while_startlist[loop_index]+1);
				}
				for_flag=false;
				if(for_index==0)
					assign_quads.clear();
			}
			;

forstart2: forstart SEMICOLON elist {
				if(if_flag){
					insert_quads(new quad(jump, NULL, NULL, NULL, while_startlist[loop_index], currQuad));
				}
				if(for_flag){
					currQuad++;	
					insert_quads(new quad(jump, NULL, NULL, NULL, while_startlist[loop_index]-1, currQuad));
				}
				loop_index++;
				for_index++;
			}
			;
			
forstart:	FOR{global_for = 1; for_scope = scope; for_flag = true; loop_start=true;} ARISTERI_PARENTHESI elist SEMICOLON expr {
					int trueLabel = ++currQuad;
					int falseLabel = trueLabel + 2;
					for(int i = 0; i < $6->truelist.size(); i++){
						for(int j = 0; j < quads.size(); j++){
							if($6->truelist[i] == quads[j].line){
								if(quads[j].label == -1) quads[j].label = trueLabel;
							}
						}
					}
					for(int i = 0; i < $6->falselist.size(); i++){
						for(int j = 0; j < quads.size(); j++){
							if($6->falselist[i] == quads[j].line){
								if(quads[j].label == -1) quads[j].label = falseLabel;
							}
						}
					}
					std::string temp_str_1=new_temp_name();
				if(scope==0){
					SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
					program_offset++;
				}
				else{
					SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
					function_offset++;
				}	
					$$=new expr(assignexpr_e, temp_str_1, 0, "", false, NULL);	
					if(temp_metavlhth)
					{				
						insert_quads(new quad(_assign, new expr(assignexpr_e, temp_str_1, 0, "", false, NULL), new expr(assignexpr_e, "TRUE", 0, "", false, NULL), NULL, -1, trueLabel));
						currQuad++;
						insert_quads(new quad(jump, NULL, NULL, NULL, currQuad + 2, trueLabel + 1));
						currQuad++;
						insert_quads(new quad(_assign, new expr(assignexpr_e, temp_str_1, 0, "", false, NULL), new expr(assignexpr_e, "FALSE", 0, "", false, NULL), NULL, -1, falseLabel));
						currQuad++;
						insert_quads(new quad(if_eq, $$, new expr(assignexpr_e, "TRUE", 0, "", false, NULL), NULL, falseLabel+6, falseLabel+1));
						currQuad++;
						insert_quads(new quad(jump, NULL, NULL, NULL, -1, currQuad));
						while_startlist.push_back(currQuad);	
						$$->forlist.push_back(currQuad);
					}
					else
					{
						if($6->sym=="")
							$$=new expr(constnum_e, "", $6->numConst, "", false, NULL);
						else
							$$=new expr(conststring_e, $6->sym, -4, "", false, NULL);
						insert_quads(new quad(if_eq, $$, new expr(assignexpr_e, "TRUE", 0, "", false, NULL), NULL, currQuad+4, currQuad));	
						currQuad++;
						insert_quads(new quad(jump, NULL, NULL, NULL, -1, currQuad));
						$$->forlist.push_back(currQuad);
						while_startlist.push_back(currQuad); 
					}
				std::cout<<"forstart <-- FOR(elist ; expr\n";
			}
			;

returnstmt:	RETURN{
				if (!func_flag)
					std::cout << "\033[1;31mERROR\033[0m" << ": Cannot use return outside a function" << std::endl;
			} SEMICOLON{  
				currQuad++;    
				insert_quads(new quad(ret, NULL, NULL, NULL, -2, currQuad));
				currQuad++;
				insert_quads(new quad(jump, NULL, NULL, NULL, -1, currQuad));
				ret_list.push_back(currQuad);
				ret_flag = true;
				std::cout<<"returnstmt <-- return;\n";}
			| RETURN{
				if(!func_flag)
					std::cout << "\033[1;31mERROR\033[0m" << ": Cannot use return outside a function" << std::endl;
			} expr SEMICOLON{
				currQuad++;
				string temp_str_1=new_temp_name();
				if(scope==0){
					SymTable_put(scope, yylineno, GLOBAL, (char*)temp_str_1.c_str(), 0, program_offset);
					program_offset++;
				}
				else{
					SymTable_put(scope, yylineno, __LOCAL, (char*)temp_str_1.c_str(), 1, function_offset);	
					function_offset++; 
				}
				insert_quads(new quad(ret, $3, new expr(assignexpr_e, temp_str_1, 0, "",false, NULL), NULL, -2, currQuad));
				currQuad++;
				insert_quads(new quad(jump, NULL, NULL, NULL, -1, currQuad));
				ret_list.push_back(currQuad);
				ret_flag = true;
				getretval_vector.push_back(new expr($3->type, $3->sym, $3->numConst, temp_str_1, $3->boolConst, NULL));			
				std::cout<<"returnstmt <-- return expr;\n";}
			;
%%
int main(int argc, char** argv)
{	
	if(argc >1){
		if(!(yyin = fopen(argv[1],"r")))
		{
			std::cout<<"cannot read file: "<< argv[1]<<std::endl;
			return 1;
		}
	}
	else{
		cout<<"\033[1;31mGive input file !!\033[0m"<<endl;
		return 1;
	}
	/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
	SymTable_new(); 
	SymTable_put( 0, 0,LIBFUNC, "print", 0 ,0);
	SymTable_change_visibility("print",0);
	SymTable_put( 0, 0, LIBFUNC, "input", 0 ,0);//
	SymTable_change_visibility("input",0);
	SymTable_put( 0, 0, LIBFUNC, "objectmemberkeys", 0 ,0);//
	SymTable_change_visibility("objectmemberkeys",0);
	SymTable_put( 0, 0, LIBFUNC, "objecttotalmembers", 0 ,0);// 
	SymTable_change_visibility("objecttotalmembers",0);
	SymTable_put( 0, 0, LIBFUNC, "objectcopy", 0 ,0);//
	SymTable_change_visibility("objectcopy",0);
	SymTable_put( 0, 0, LIBFUNC, "totalarguments", 0 ,0);
	SymTable_change_visibility("totalarguments",0);
	SymTable_put( 0, 0, LIBFUNC, "argument", 0 ,0);
	SymTable_change_visibility("argument", 0);
	SymTable_put( 0, 0, LIBFUNC, "typeof", 0 ,0);
	SymTable_change_visibility("typeof", 0);
	SymTable_put( 0, 0, LIBFUNC, "strtonum", 0 ,0);//
	SymTable_change_visibility("strtonum", 0);
	SymTable_put( 0, 0, LIBFUNC, "sqrt", 0 ,0);//
	SymTable_change_visibility("sqrt", 0);
	SymTable_put( 0, 0, LIBFUNC, "cos", 0 ,0);//
	SymTable_change_visibility("cos", 0);
	SymTable_put( 0, 0, LIBFUNC, "sin", 0 ,0);//
	SymTable_change_visibility("sin", 0);
	yyparse();
	SymTable_PRINT();
	print_quads();
	enable_generates();
	print_instruction();
	make_binary_file();
	return 0;
}
