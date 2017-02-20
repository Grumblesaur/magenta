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

%precedence BRACE_OPEN      
%token BRACE_CLOSE     
%token ASSIGN          
%token COLON 
%token SEMICOLON          

%token TYPE_FUNCTION
%token TYPE_METHOD   
%token TYPE_INTEGER    
%token TYPE_STRING     
%token TYPE_FLOAT      
%token TYPE_TYPE
%token OPTION    
%token CASE       
%token IF         
%precedence ELIF      
%precedence ELSE       
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

%type <node> prog stmts stmt elif_stmt expr or_term and_term comp_term addend factor exponent term num id type

%error-verbose

%%

prog: stmts { result = make_node(STMT, "", NULL);
			attach(result, $1);
			}


stmts: stmt stmts { $$ = make_node(STMT, "", NULL);
					attach($$, $1);
					attach($$, $2);
					}
	| stmt { $$ = make_node(STMT, "", NULL);
			attach($$, $1);
			}


stmt: type id ASSIGN expr SEMICOLON { $$ = make_node(ASSIGN, "", NULL);
										attach($$, $1);
										attach($$, $2);
										attach($$, $4);
										}
	| WHILE_LOOP expr stmt { $$ = make_node(WHILE_LOOP, "", NULL)
							attach($$, $2);
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

//TODO
expr: expr LOG_OR or_term { $$ = make_node(LOG_OR, "", NULL);
							attach($$, $1);
							attach($$, $3);
							}
	| expr LOG_XOR or_term { $$ = make_node(LOG_XOR, "", NULL);
							attach($$, $1);
							attach($$, $3);
							}
	| or_term { }


or_term: or_term LOG_AND and_term { $$ = make_node(LOG_AND, "", NULL);
									attach($$, $1);
									attach($$, $3);
									}
		| and_term { }


and_term: and_term LESS_THAN comp_term { $$ = make_node(LESS_THAN, "", NULL);
										attach($$, $1);
										attach($$, $3);
										}
		| and_term LESS_EQUAL comp_term { $$ = make_node(LESS_EQUAL, "", NULL);
										attach($$, $1);
										attach($$, $3);
										}
		| and_term EQUAL comp_term { $$ = make_node(EQUAL, "", NULL);
										attach($$, $1);
										attach($$, $3);
										}
		| and_term GREATER_THAN comp_term { $$ = make_node(GREATER_THAN, "", NULL);
											attach($$, $1);
											attach($$, $3);
											}
		| and_term GREATER_EQUAL comp_term { $$ = make_node(GREATER_EQUAL, "", NULL);
										attach($$, $1);
										attach($$, $3);
										}
		| and_term NOT_EQUAL comp_term { $$ = make_node(NOT_EQUAL, "", NULL);
										attach($$, $1);
										attach($$, $3);
										}
		| and_term { }


comp_term: comp_term PLUS addend { $$ = make_node(PLUS, "", NULL);
									attach($$, $1);
									attach($$, $3);
									}
		| comp_term MINUS addend { $$ = make_node(MINUS, "", NULL);
									attach($$, $1);
									attach($$, $3);
									}


addend: addend TIMES factor { $$ = make_node(TIMES, "", NULL);
								attach($$, $1);
								attach($$, $3);
								}
		| addend DIVIDE factor { $$ = make_node(DIVIDE, "", NULL);
								attach($$, $1);
								attach($$, $3);
								}
		| addend MODULO factor { $$ = make_node(MODULO, "", NULL);
								attach($$, $1);
								attach($$, $3);
								}
		| factor { }


factor: factor POWER exponent { $$ = make_node(POWER, "", NULL);
								attach($$, $1);
								attach($$, $3);
								}
		| factor LOG exponent { $$ = make_node(LOG, "", NULL);
								attach($$, $1);
								attach($$, $3);
								}
		| factor { }


exponent: LOG_NOT exponent { $$ = make_node(LOG_NOT, "", NULL);
							attach($$, $2);
							}
		| MINUS exponent { $$ = make_node(MINUS, "", NULL);
							attach($$, $2);
							}
		| term { }


term: PAREN_OPEN expr PAREN_CLOSE { $$ = make_node(PAREN_OPEN, "", NULL);
									attach($$, $2);
									}
	| STRING_LITERAL { $$ = make_node(STRING_LITERAL, "", $1); }
	| id { }
	| num { }
		

num: INT_LITERAL { $$ = make_node(INT_LITERAL, "", $1); }
	| FLOAT_LITERAL { $$ = make_node(FLOAT_LITERAL, "", $1); }

id: IDENTIFIER { $$ = make_node(IDENTIFIER, $1, NULL); }

type: TYPE_INTEGER { $$ = make_node(TYPE_INTEGER, "", NULL); }
	| TYPE_FLOAT { $$ = make_node(TYPE_FLOAT, "", NULL); }
	| TYPE_STRING { $$ = make_node(TYPE_STRING, "", NULL); }
	| TYPE_FUNCTION { $$ = make_node(TYPE_FUNCTION, "", NULL); }
	| TYPE_METHOD { $$ = make_node(TYPE_METHOD, "", NULL); }
	| TYPE_TYPE { $$ make_node(TYPE_TYPE, "", NULL); }

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

	yyparse();

	// int token;
	// do {	
	// 	token = yylex( );
		
	// 	printf("%d\n", token);

  	// } while(token != 0);
	

	fclose(stdin);
	stdin = orig_stdin;
	return 0;
}