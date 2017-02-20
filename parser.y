%{
	#include <stdio.h>
	#include "tree.h"
	#define YYDEBUG 1
	int yywrap();
	int yylex();
	void yyerror(const char* str);
	node* result;
%}

%union {
	node* node;
	int i_val;
	float f_val;
	char* str, id;
}

%token BRACE_OPEN      
%token BRACE_CLOSE     
%token ASSIGN          
%token COLON 
%token SEMICOLON          

%token TYPE_FUNCTION
%token TYPE_METHOD   
%token TYPE_INTEGER    
%token TYPE_STRING     
%token TYPE_FLOAT      
%token TYPE_COMPOUND   
%token OPTION    
%token CASE       
%token IF         
%token ELIF      
%token ELSE       
%token FOR_LOOP        
%token WHILE_LOOP      

%token ACCESS          
%token BRACKET_OPEN    
%token BRACKET_CLOSE   
%token PAREN_OPEN      
%token PAREN_CLOSE     
%token POWER           
%token LOG             
%token TIMES           
%token DIVIDE          
%token MODULO          
%token PLUS            
%token CONCAT          
%token MINUS
%token LEFT_SHIFT
%token RIGHT_SHIFT

%token LESS_THAN       
%token GREATER_THAN    
%token EQUAL           
%token NOT_EQUAL       
%token GREATER_EQUAL   
%token LESS_EQUAL      

%token LOG_AND         
%token LOG_OR          
%token LOG_NOT         
%token LOG_XOR         
%token LOG_IMPLIES     

%token BIT_AND         
%token BIT_OR          
%token BIT_NOT         
%token BIT_XOR         
%token BIT_IMPLIES     

%token<id> IDENTIFIER      
%token<i_val> INT_LITERAL
%token<f_val> FLOAT_LITERAL 
%token<str> STRING_LITERAL 

%token STMT 

%type <node> prog, stmts, stmt, expr, num

%error-verbose

%%

prog: stms { result = make_node(STMT, "", NULL);
			attach(result, $1);
			}


stmts: stmt stmts { $$ = make_node(STMT, "", NULL);
					attach($$, $1);
					attach($$, $2);
					}
	| stmt { $$ = make_node(STMT, "", NULL);
			attach($$, $1);
			}


stmt: IDENTIFIER ASSIGN expr SEMICOLON { $$ = make_node(ASSIGN, "", NULL);
										attach($$, $1);
										attach($$, $3);
										}
	| WHILE_LOOP expr stmt { $$ = make_node(WHILE_LOOP, "", NULL) {
							attach($$, $1);
							attach($$, $3);
							}
	| IF expr stmt { $$ = make_node(IF_STMT, "", NULL);
						attach($$, $2);
						attach($$, $3);
						}
	| IF expr stmt ELIF elif_stmt { $$ = make_node(IF, "", NULL);
								attach($$, $2);
								attact($$, $3)
								attach($$, $5);
								}
	| IF expr stmt ELSE stmt { $$ = make_node(IF, "", NULL);
								attach($$, $2);
								attach($$, $3);
								attach($$, $5);
								}
	| BRACE_OPEN stmts BRACE_CLOSE { $$ = make_node(STMT, "", NULL);
									attach($$, $2);
									}


elif_stmt: expr stmt ELIF elif_stmt { $$ = make_node(ELIF, "", NULL);
										attach($$, $1);
										attach($$, $2);
										attach($$, $4);
										}
		| expr stmt ELSE stmt { $$ = make_node(ELIF, "", NULL);
								attach($$, $1);
								attach($$, $2);
								attach($$, $4);
								}
		| expr stmt { $$ = make_node(ELIF, "", NULL);
						attach($$, $1);
						attach($$, $2);
						}



not_term: PAREN_OPEN expr PAREN_CLOSE {}
		| num {}
		| STRING_LITERAL {} 
		| //what goes here?

num: INT_LITERAL { $$ = make_node()}
	| FLOAT_LITERAL {}

%%

int yywrap() {
	return 1;
}

void yyerror(const char* str) {
	fprintf(stderr, "COMPILER ERROR: '%s'.\n", str);
}

int main(int argc, char **argv) {

	FILE* orig_stdin = stdin;
	stdin = fopen(argv[1], "r");

	int token;
	do {	
		token = yylex( );
		
		printf("%d\n", token);

  	} while(token != 0);
	

	fclose(stdin);
	stdin = orig_stdin;
	return 0;
}