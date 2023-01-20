%{
#include "parser.hpp" 
#include <iostream>
#include <assert.h>
int count = 1;
int string_counter = 0; 
struct alpha_token_t{
	int TOKEN_ID; 
	int LINE_NUMBER;
	char *data;
	char *type; 
	char *ctype; 
	struct alpha_token_t *next;	
	};
struct alpha_token_t *head = NULL;

struct invalid_list{ 
	int line;
	char * c;
	struct invalid_list *next;
	};

struct invalid_string_list{
	int line;
	char * c;
	struct invalid_string_list *next;
	};

struct str_list{ 
	char * c;
	struct str_list *next;
};
struct str_list * str_list_head = NULL;

struct str_list * str_list_insert(char * c){
	struct str_list * newnode;
	struct str_list * temp;
	newnode = (struct str_list *)malloc(128*sizeof(struct str_list));
	newnode->c = strdup(c);
	temp = str_list_head;

	if(str_list_head == NULL){
		str_list_head = newnode;
	}else{
		while(temp->next != NULL){ 
			temp = temp->next;
		}
		temp->next = newnode;
	}
	return str_list_head;
}

struct invalid_list * invalid_list_head = NULL;

struct invalid_list * invalid_insert(int line, char * c){
	struct invalid_list * newnode;
	newnode = (struct invalid_list *)malloc(128 * sizeof(struct invalid_list));
	newnode->line = line;
	newnode->c = strdup(c);
	struct invalid_list * temp;
	temp = invalid_list_head;
	if(invalid_list_head == NULL){
		invalid_list_head = newnode;
		newnode->next = NULL;
	}else{
		while(temp->next != NULL){
			temp = temp->next;
		}
		temp->next = newnode;
		newnode->next = NULL;
	}
	return invalid_list_head;
}

void print_invalid_list(){
		struct invalid_list * temp;
		temp = invalid_list_head;
		while(temp != NULL){
			printf("At line: %d there is a not valid input \"%s\"\n", temp->line, temp->c);
			temp = temp->next;
		}
}

struct invalid_string_list * invalid_string_list_head = NULL;

struct invalid_string_list * invalid_string_insert(int line, char * c){
	struct invalid_string_list * newnode;
	newnode = (struct invalid_string_list *)malloc(sizeof(struct invalid_string_list));
	newnode->line = line;
	newnode->c = strdup(c);
	struct invalid_string_list * temp;
	temp = invalid_string_list_head;

	if(invalid_string_list_head == NULL){
		invalid_string_list_head = newnode;
	}else{
		while(temp->next != NULL){
			temp = temp->next;
		}
		temp->next = newnode;
	}
	return invalid_string_list_head;
}

void print_invalid_string_list(){
		struct invalid_string_list * temp;
		temp = invalid_string_list_head;
		while(temp != NULL){
			printf("At line: %d there is a not valid String input \"%s\"\n", temp->line, temp->c);
			temp = temp->next;
		}
}


struct comment_list{
	int x;
	int y;
	struct comment_list *next;
	struct comment_list *prev;
	};

struct comment_list * multi_comm_list_head = NULL;
struct comment_list * multi_comm_list_tail = NULL;

struct comment_list * dll_comment_insert(int flag, int val){
	//flag = 0 left comment
	//flag = 1 right comment
	struct comment_list * newnode;	
	struct comment_list * temp;	

	if(flag == 0){
		newnode = (struct comment_list *)malloc(sizeof(struct comment_list));
		newnode->x = -1;
		newnode->y = -1;
		newnode->x = val;
		if(multi_comm_list_head == NULL){
			multi_comm_list_head = newnode;
			newnode->next = NULL;
			newnode->prev = NULL;
			multi_comm_list_tail = newnode;
		}else{
			temp = multi_comm_list_head;
			while(temp->next != NULL){
				temp = temp->next;
			}
			temp->next = newnode;
			newnode->prev = temp;
			newnode->next = NULL;
			multi_comm_list_tail = newnode;
		}
	}
	if((flag == 1) && (multi_comm_list_tail->y == -1)){
		multi_comm_list_tail->y = val;
	}else if((flag == 1) && (multi_comm_list_tail->y != -1)){
		temp = multi_comm_list_tail;
		while(temp != NULL){
			if(temp->y == -1){
				temp->y = val;
				break;
			}
			temp = temp->prev;
		}
	}
	return multi_comm_list_head;
}


struct alpha_token_t *insert_token(int LINE_NUMBER, int TOKEN_ID , char * data , char * type, char * ctype){
	assert(data);
	assert(type);
	assert(ctype);
	struct alpha_token_t * newnode;
	struct alpha_token_t * temp;
	newnode = (struct alpha_token_t *)malloc(128* sizeof(struct alpha_token_t));
	newnode->LINE_NUMBER = LINE_NUMBER;
	newnode->TOKEN_ID = TOKEN_ID;
	newnode->data = strdup(data);
	newnode->type = type;
	newnode->ctype = ctype;
	temp = head;
	if(head == NULL){
		head = newnode; 
		newnode->next = NULL;
	}else{
		while(temp->next != NULL){
			temp = temp->next;
		}
		temp->next = newnode;
		newnode->next = NULL;
	}
	return head;	
}

struct alpha_token_t * print_list(){
		struct alpha_token_t * temp;
		temp = head;
		printf("\033[1;32m");
		printf("--------------Lexical Analysis--------------\n");
		printf("\033[0m");
		while(temp != NULL){
			if((temp->type == "STRING")||(temp->type == "ID")){
				printf("%d:\t #%d\t \"%s\"\t %s\t \"%s\"\t <-%s\n", temp->LINE_NUMBER, temp->TOKEN_ID, strdup(temp->data), temp->type, temp->data, temp->ctype);
			}else{
				if((temp->type == "LINE_COMMENT")||(temp->type == "BLOCK_COMMENT")||(temp->type == "NESTED_COMMENT")){
					printf("%d:\t #%d\t \"%s\"\t %s\t %s\t <-%s\n", temp->LINE_NUMBER, temp->TOKEN_ID, temp->data,"COMMENT" , temp->type,  temp->ctype);
				}
				else if((temp->type=="EQUAL")||(temp->type=="PLUS")||(temp->type=="MINUS")||(temp->type=="MULTIPLY")||(temp->type=="DIV")||(temp->type=="PERCENT")||(temp->type=="EQUAL_EQUAL")||(temp->type=="NOT_EQUAL")||(temp->type=="PLUS_PLUS")||(temp->type=="MINUS_MINUS")||(temp->type=="GREATER")||(temp->type=="LESS")||(temp->type=="GREATER_EQUAL")||(temp->type=="LESS_EQUAL")){
					printf("%d:\t #%d\t \"%s\"\t %s\t %s\t <-%s\n", temp->LINE_NUMBER, temp->TOKEN_ID, temp->data, "OPERATOR",temp->type, temp->ctype);
				}
				else if((temp->type=="LEFT_BRACE")||(temp->type=="RIGHT_BRACE")||(temp->type=="LEFT_BRACKET")||(temp->type=="RIGHT_BRACKET")||(temp->type=="LEFT_PARENTHESIS")||(temp->type=="RIGHT_PARENTHESIS")||(temp->type=="SEMICOLON")||(temp->type=="COMMA")||(temp->type=="COLON")||(temp->type=="COLON_COLON")||(temp->type=="DOT")||(temp->type=="DOT_DOT")){
					printf("%d:\t #%d\t \"%s\"\t %s\t %s\t <-%s\n", temp->LINE_NUMBER, temp->TOKEN_ID, temp->data, "PUNCTUATION",temp->type, temp->ctype);
				}

				else{
					printf("%d:\t #%d\t \"%s\"\t %s\t %s\t <-%s\n", temp->LINE_NUMBER, temp->TOKEN_ID, temp->data, temp->type, temp->data, temp->ctype);

				}

			}
			temp = temp->next;
		}
		return head;
	}

%} 
%option outfile="lala.cpp"
%option noyywrap
%option yylineno

IF "if"
ELSE "else"
WHILE "while"
FOR "for"
FUNCTION "function"
RETURN "return"
BREAK "break"
CONTINUE "continue"
AND "and"
NOT "not"
OR "or"
LOCAL "local"
TRUE "true"
FALSE "false"
NIL "nil"
ISON "="
PLUS "+"
MINUS "-"
STAR "*"
SLASH "/"
PERCENT "%"
EQUAL "=="
NOT_EQUAL "!="
PLUS_PLUS "++"
MINUS_MINUS "--"
GREATER ">"
LESS "<"
GREATER_EQUAL ">="
LESS_EQUAL "<="
INTCONST      [0-9]+
REALCONST     [0-9]+[.][0-9]+
STRING \"
LEFT_BRACE "{"
RIGHT_BRACE "}"
LEFT_BRACKET "["
RIGHT_BRACKET "]"
ARISTERI_PARENTHESI "("
DEXIA_PARENTHESI ")"
SEMICOLON ";"
COMMA ","
COLON ":"
COLON_COLON "::"
DOT "."
DOT_DOT ".."
ID	[a-zA-Z][a-zA-Z_0-9]*
SINGLECOMMENT	[/][/].*
MULTICOMMENT	"/\*"

%% 
{IF}               {insert_token(yylineno, count, yytext, "KEYWORD", "enumerated"); count++; 
					 return IF;}
{ELSE}             {insert_token(yylineno, count, yytext, "KEYWORD", "enumerated"); count++;
					 return ELSE;}
{WHILE}            {insert_token(yylineno, count, yytext, "KEYWORD", "enumerated"); count++;
					 return WHILE;}
{FOR}              {insert_token(yylineno, count, yytext, "KEYWORD", "enumerated"); count++;
					 return FOR;}
{FUNCTION}         {insert_token(yylineno, count, yytext, "KEYWORD", "enumerated"); count++;
					 return FUNCTION;}
{RETURN}           {insert_token(yylineno, count, yytext, "KEYWORD", "enumerated"); count++;
					 return RETURN;}
{BREAK}            {insert_token(yylineno, count, yytext, "KEYWORD", "enumerated"); count++;
					 return BREAK;}  
{CONTINUE}         {insert_token(yylineno, count, yytext, "KEYWORD", "enumerated"); count++;
					 return CONTINUE;}
{AND}              {insert_token(yylineno, count, yytext, "KEYWORD", "enumerated"); count++;
					 return AND;}
{NOT}              {insert_token(yylineno, count, yytext, "KEYWORD", "enumerated"); count++;
					 return NOT;}
{OR}               {insert_token(yylineno, count, yytext, "KEYWORD", "enumerated"); count++;
					 return OR;}
{LOCAL}            {insert_token(yylineno, count, yytext, "KEYWORD", "enumerated"); count++;
					 return LOCAL;}
{TRUE}             {insert_token(yylineno, count, yytext, "KEYWORD", "enumerated"); count++;
					 return TRUE;} 
{FALSE}            {insert_token(yylineno, count, yytext, "KEYWORD", "enumerated"); count++;
					 return FALSE;}
{NIL}              {insert_token(yylineno, count, yytext, "KEYWORD", "enumerated"); count++;
					 return NIL;} 
{ISON}              {insert_token(yylineno, count, yytext, "EQUAL", "enumerated"); count++;
					 return ISON;} 
{PLUS}               {insert_token(yylineno, count, yytext, "PLUS", "enumerated"); count++;
					 return PLUS;}
{MINUS}              {insert_token(yylineno, count, yytext, "MINUS", "enumerated"); count++;
					 return MINUS;}
{STAR}              {insert_token(yylineno, count, yytext, "MULTIPLY", "enumerated"); count++;
					 return STAR;}
{SLASH}             {insert_token(yylineno, count, yytext, "DIV", "enumerated"); count++; 
					return SLASH;}
{PERCENT}           {insert_token(yylineno, count, yytext, "PERCENT", "enumerated"); count++;
					 return PERCENT;}
{EQUAL}             {insert_token(yylineno, count, yytext, "EQUAL_EQUAL", "enumerated"); count++; 
					return EQUAL;}
{NOT_EQUAL}         {insert_token(yylineno, count, yytext, "NOT_EQUAL", "enumerated"); count++;
					 return NOT_EQUAL;}
{PLUS_PLUS}          {insert_token(yylineno, count, yytext, "PLUS_PLUS", "enumerated"); count++; 
					return PLUS_PLUS;}
{MINUS_MINUS}       {insert_token(yylineno, count, yytext, "MINUS_MINUS", "enumerated"); count++; 
					return MINUS_MINUS;}
{GREATER}           {insert_token(yylineno, count, yytext, "GREATER", "enumerated"); count++; 
					return GREATER;}
{LESS}              {insert_token(yylineno, count, yytext, "LESS", "enumerated"); count++; 
					return LESS;}
{GREATER_EQUAL}     {insert_token(yylineno, count, yytext, "GREATER_EQUAL", "enumerated"); count++; 
					return GREATER_EQUAL;}
{LESS_EQUAL}        {insert_token(yylineno, count, yytext, "LESS_EQUAL", "enumerated"); count++; 
					return LESS_EQUAL;}
{INTCONST}       {insert_token(yylineno, count, yytext, "CONST_INT", "integer"); count++; 
					yylval.intValue = atof(yytext); return INTCONST;}
{REALCONST}      {insert_token(yylineno, count, yytext, "REAL_INT", "double"); count++; 
					yylval.realValue = atof(yytext); return REALCONST;}
{LEFT_BRACE}        {insert_token(yylineno, count, yytext, "LEFT_BRACE", "punctuation"); count++; 
					return LEFT_BRACE;}
{RIGHT_BRACE}       {insert_token(yylineno, count, yytext, "RIGHT_BRACE", "punctuation"); count++; 
					return RIGHT_BRACE;}
{LEFT_BRACKET}      {insert_token(yylineno, count, yytext, "LEFT_BRACKET", "punctuation"); count++; 
					return LEFT_BRACKET;}
{RIGHT_BRACKET}     {insert_token(yylineno, count, yytext, "RIGHT_BRACKET", "punctuation"); count++; 
					return RIGHT_BRACKET;}
{ARISTERI_PARENTHESI} {insert_token(yylineno, count, yytext, "LEFT_PARENTHESIS", "punctuation"); count++;
					return ARISTERI_PARENTHESI;}
{DEXIA_PARENTHESI}    {insert_token(yylineno, count, yytext, "RIGHT_PARENTHESIS", "punctuation"); count++; 
					return  DEXIA_PARENTHESI;}
{SEMICOLON}         {insert_token(yylineno, count, yytext, "SEMICOLON", "punctuation"); count++; 
					return SEMICOLON;}
{COMMA}             {insert_token(yylineno, count, yytext, "COMMA", "punctuation"); count++;
					return COMMA;}
{COLON}             {insert_token(yylineno, count, yytext, "COLON", "punctuation"); count++; 
					return COLON;}
{COLON_COLON}       {insert_token(yylineno, count, yytext, "COLON_COLON", "punctuation"); count++;
					return COLON_COLON;}
{DOT}               {insert_token(yylineno, count, yytext, "DOT", "punctuation"); count++; 
					return DOT;}
{DOT_DOT}           {insert_token(yylineno, count, yytext, "DOT_DOT", "punctuation"); count++;
					return DOT_DOT;}
{STRING} {
		int c;
		int string_first_line = yylineno;
		int autakia_sto_telos=0;
		char *c_str =(char*)malloc(sizeof(char));
		str_list_head = NULL;
		while((c=yyinput())!=EOF)
		{

			if( c == '\n')
			{
				char *c_str =(char*)malloc(sizeof(char));
				sprintf(c_str, "%c", '\n');
				str_list_head = str_list_insert(c_str);
				string_counter++;
				continue;
			}
			if(c=='\\')
			{
				c=yyinput();
				if(c=='n')
				{
					sprintf(c_str, "%c", '\n');
					str_list_head = str_list_insert(c_str);
					string_counter++;
					continue;
				}
				else if(c=='t')
				{
					sprintf(c_str, "%c", '\t');
					str_list_head = str_list_insert(c_str);
					string_counter++;
					continue;
				}
				else if(c=='\"')
				{
					sprintf(c_str, "%c", '"');
					str_list_head = str_list_insert(c_str);
					string_counter++;
					continue;
				}else
				{
					char *str_c =(char*)malloc(sizeof(char));
					char *temp_str=(char*)malloc(2*sizeof(char));
					sprintf(temp_str, "%s", "\\");
					sprintf(str_c, "%c", c);
					strcat(temp_str, str_c);
					invalid_string_insert(yylineno, temp_str);
					continue;
				}
			}
			if(c=='\"')
			{
				autakia_sto_telos++;
				break;	
			}
			if(!((c>=32) && (c<=126)))
			{
				char *lala=(char*)malloc(sizeof(char));
				lala[0]=c+'\0';
				head = insert_token(string_first_line, count++, lala, "INVALID CHARACTER" , "\033[1;31mERROR\033[0m");
				free(lala);
				continue;
			}
			sprintf(c_str, "%c", c);
			str_list_head = str_list_insert(c_str);
			string_counter++;
			//str=(char*)realloc(str, i*sizeof(char));
		}
		if(!autakia_sto_telos)
		{
			head=insert_token(string_first_line, count++, "string not closed", "\033[1;31mERROR\033[0m", "error");
		}
		else
		{
			char *str=(char*)malloc(sizeof(string_counter));
			struct str_list * temp = str_list_head;
			while(temp != NULL){
				strcat(str, temp->c);
				temp = temp->next;
			}
			head=insert_token(string_first_line, count++, strdup(str), "STRING", "char*");
			yylval.strValue = strdup(str); return STRING;
		}
	}
{ID} {	
		head = insert_token(yylineno, count, yytext, "ID", "char*");
		count++; yylval.strValue = strdup(yytext); return ID;
	}
{SINGLECOMMENT}	{	
					char * s1 = (char*)malloc(sizeof(yyleng-2));
					char * temp = (char*)malloc(sizeof(char));
					sprintf(s1, "%s", "");
					int i;
					for(i=2; i<yyleng; i++)
					{
						sprintf(temp, "%c", yytext[i]);
						strcat(s1, temp);
					}		
					head=insert_token(yylineno, count++, strdup(s1), "LINE_COMMENT", "enumerated");	
				}
{MULTICOMMENT}		{
					multi_comm_list_head = NULL;
					int comment_first_line=yylineno;
					int c;
					int l_sum=1;
					int r_sum=0;
					multi_comm_list_head=dll_comment_insert(0, comment_first_line);
					while((c=yyinput())!=EOF)
					{
						if(c=='*') /* kleinei to comment*/
						{
							c=yyinput();
							if(c=='/')
							{
								r_sum++;
								multi_comm_list_head=dll_comment_insert(1, yylineno);
								if(l_sum==r_sum)
								{
									break;
								}
							}else{
								unput(c);
							}
							continue;
						}
						if(c=='/') /* anoigei to comment*/
						{
							c=yyinput();
							if(c=='*')
							{
								l_sum++;
								multi_comm_list_head=dll_comment_insert(0, yylineno);
							}else{
								unput(c);
							}
						}
						
					}
					if(l_sum>r_sum)
					{
						struct comment_list *temp;
						temp=multi_comm_list_head;
						while(temp->next!=NULL)
						{
							temp=temp->next;
						}
						head=insert_token(temp->x, count++, "Comment not closed", "\033[1;31mERROR\033[0m", "error");
					}
					if(l_sum==r_sum)
					{
						struct comment_list *temp;
						temp=multi_comm_list_head;
						while(temp!=NULL)
						{
							char *temp_str=(char*)malloc(sizeof(temp));
							char *yyline=(char*)malloc(sizeof(yyline));
							sprintf(temp_str, "%d", temp->x);
							strcat(temp_str, "-");
							sprintf(yyline, "%d", temp->y);
							strcat(temp_str, yyline);
							if(temp == multi_comm_list_head)
							{
								head=insert_token(temp->x, count++, temp_str, "BLOCK_COMMENT", "enumerated");
							}
							else
							{
								head=insert_token(temp->x, count++, temp_str, "NESTED_COMMENT", "enumerated");
							}
							temp=temp->next;
						}						 		
					}
				}
	 
" "	{}
.     {invalid_insert(yylineno, yytext);} 
\n	{}
