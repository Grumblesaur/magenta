%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "tree.h"
	#include "interpreter.h"
	extern int linecount;
	int yydebug = 1;
	int yywrap();
	int yylex();

	void yyerror(const char* str);
	struct node * result;
%}

%union {
	struct node * n;
	char* str;
	int ival;
	double fval;
}

%token BRACE_OPEN      
%token BRACE_CLOSE     
%token ASSIGN          
%token COLON 
%token SEMICOLON          
%token COMMA

%token TYPE_FUNCTION
%token TYPE_METHOD   
%token TYPE_INTEGER    
%token TYPE_STRING     
%token TYPE_FLOAT      
%token TYPE_TYPE
%token TYPE_VOID
%token OPTION    
%token CASE       
%precedence IF         
%precedence ELSE       
%token FOR_LOOP
%token FROM
%token TO
%token BY        
%token WHILE_LOOP
%token IN
%token BREAK
%token NEXT
%token RETURN

%token ACCESS          
%token BRACKET_OPEN    
%token BRACKET_CLOSE   
%token PAREN_OPEN      
%token PAREN_CLOSE     
%token POWER           
%token LOG
%token INT_DIVIDE
%token TIMES           
%token DIVIDE          
%token MODULO          
%token PLUS            
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

%token<str> IDENTIFIER      
%token<str> INTEGER_LITERAL
%token<str> FLOAT_LITERAL 
%token<str> STRING_LITERAL 

%token STATEMENT
%token PARAM 
%token ARGUMENT

%token PRINT
%token INPUT
%token LEN
%token PASS

%token F_CALL
%token M_CALL

%type<n> program statements statement expression disjunction
%type<n> conjunction relation addend factor exponent term id
%type<n> return_type type function_call function_definition
%type<n> method_definition argument implication parameter
%type<n> case or_bit xor_bit and_bit imp_bit shift from to by
%type<n> l_val

%error-verbose

%%

program: statements {
		result = make_node(STATEMENT, NULL);
		attach(result, $1);
	}


statements: statement statements {
		$$ = make_node(STATEMENT, NULL);
		attach($$, $1);
		attach($$, $2);
	} | statement {
		$$ = make_node(STATEMENT, NULL);
		attach($$, $1);
	}
	
function_definition: TYPE_FUNCTION id PAREN_OPEN parameter PAREN_CLOSE COLON type statement {
		$$ = make_node(TYPE_FUNCTION, NULL);
		attach($$, $2); //identifier
		attach($$, $4); // paramters
		attach($$, $7); // return type
		attach($$, $8); // statements
	} | TYPE_FUNCTION id PAREN_OPEN PAREN_CLOSE COLON type statement {
		$$ = make_node(TYPE_FUNCTION, NULL);
		attach($$, $2); //identifier
		attach($$, $6); // return type
		attach($$, $7); // statements
	}

method_definition: TYPE_METHOD id PAREN_OPEN parameter PAREN_CLOSE COLON return_type statement {
		$$ = make_node(TYPE_METHOD, NULL);
		attach($$, $2);
		attach($$, $4);
		attach($$, $7);
		attach($$, $8);
	}

parameter: type id COMMA parameter {
		$$ = make_node(PARAM, NULL);
		attach($$, $1);
		attach($$, $2);
		attach($$, $4);
	} | type id { 
		$$ = make_node(PARAM, NULL);
		attach($$, $1);
		attach($$, $2);
	}

function_call: id PAREN_OPEN argument PAREN_CLOSE {
		$$ = make_node(F_CALL, NULL);
		attach($$, $1);
		attach($$, $3);
	} | id PAREN_OPEN PAREN_CLOSE {
		$$ = make_node(F_CALL, NULL);
		attach($$, $1);
	} | LEN PAREN_OPEN expression PAREN_CLOSE {
		$$ = make_node(LEN, NULL);
		attach($$, $3);
	}

argument: expression COMMA argument {
		$$ = make_node(ARGUMENT, NULL);
		attach($$, $1);
		attach($$, $3);
	} | expression {
		$$ = make_node(ARGUMENT, NULL);
		attach($$, $1);
	}
	
statement: type id ASSIGN expression SEMICOLON { // declare a var w/value
		$$ = make_node(ASSIGN, NULL);
		attach($$, $1);
		attach($$, $2);
		attach($$, $4);
	} | l_val ASSIGN expression SEMICOLON { // re-assign a var w/value
		$$ = make_node(ASSIGN, NULL);
		attach($$, $1);
		attach($$, $3);
	} | WHILE_LOOP expression statement {
		$$ = make_node(WHILE_LOOP, NULL);
		attach($$, $2);
		attach($$, $3);
	} | IF expression statement {
		$$ = make_node(IF, NULL);
		attach($$, $2);
		attach($$, $3);
	} | IF expression statement ELSE statement {
		$$ = make_node(IF, NULL);
		attach($$, $2);
		attach($$, $3);
		attach($$, $5);
	} | OPTION expression BRACE_OPEN case BRACE_CLOSE {
		$$ = make_node(OPTION, NULL);
		attach($$, $2);
		attach($$, $4);
	} | BRACE_OPEN statements BRACE_CLOSE {
		$$ = make_node(STATEMENT, NULL);
		attach($$, $2);
	} | expression SEMICOLON {
		$$ = make_node(STATEMENT, NULL);
		attach($$, $1);
	} | PRINT expression SEMICOLON {
		$$ = make_node(PRINT, NULL);
		attach($$, $2);
	} | BREAK SEMICOLON{ 
		$$ = make_node(BREAK, NULL);
	} | NEXT SEMICOLON {
		$$ = make_node(NEXT, NULL);
	} | FOR_LOOP id from to by statement {
		$$ = make_node(FOR_LOOP, NULL);
		attach($$, $2);
		attach($$, $3);
		attach($$, $4);
		attach($$, $5);
		attach($$, $6);
	} | FOR_LOOP id from to statement {
		$$ = make_node(FOR_LOOP, NULL);
		attach($$, $2);
		attach($$, $3);
		attach($$, $4);
		attach($$, $5);
	} | FOR_LOOP id to by statement {
		$$ = make_node(FOR_LOOP, NULL);
		attach($$, $2);
		attach($$, $3);
		attach($$, $4);
		attach($$, $5);
	} | FOR_LOOP id from by statement {
		$$ = make_node(FOR_LOOP, NULL);
		attach($$, $2);
		attach($$, $3);
		attach($$, $4);
		attach($$, $5);
	} | FOR_LOOP id to statement {
		$$ = make_node(FOR_LOOP, NULL);
		attach($$, $2);
		attach($$, $3);
		attach($$, $4);
	} | FOR_LOOP id from statement {
		$$ = make_node(FOR_LOOP, NULL);
		attach($$, $2);
		attach($$, $3);
		attach($$, $4);
	} | FOR_LOOP id by statement {
		$$ = make_node(FOR_LOOP, NULL);
		attach($$, $2);
		attach($$, $3);
		attach($$, $4);
	} | FOR_LOOP id statement {
		$$ = make_node(FOR_LOOP, NULL);
		attach($$, $2);
		attach($$, $3);
	} | SEMICOLON {
		// empty statement
		$$ = make_node(PASS, NULL);
	} | PASS SEMICOLON {
		$$ = make_node(PASS, NULL);
	} | RETURN expression {
		$$ = make_node(RETURN, NULL);
		attach($$, $2);
	} | function_definition { }

from: FROM expression {
	$$ = make_node(FROM, NULL);
	attach($$, $2);
	}

to: TO expression {
	$$ = make_node(TO, NULL);
	attach($$, $2);
	}

by:	BY expression {
	$$ = make_node(BY, NULL);
	attach($$, $2);	
	}

case: CASE expression COLON statements case {
		$$ = make_node(CASE, NULL);
		attach($$, $2);
		attach($$, $4);
		attach($$, $5);
	} | CASE expression COLON statements {
		$$ = make_node(CASE, NULL);
		attach($$, $2);
		attach($$, $4);
	} 


expression: expression LOG_OR disjunction {
		$$ = make_node(LOG_OR, NULL);
		attach($$, $1);
		attach($$, $3);
	} | expression LOG_XOR disjunction {
		$$ = make_node(LOG_XOR, NULL);
		attach($$, $1);
		attach($$, $3);
	} | disjunction { }


disjunction: disjunction LOG_AND conjunction {
		$$ = make_node(LOG_AND, NULL);
		attach($$, $1);
		attach($$, $3);
	} | conjunction { }

conjunction: conjunction LOG_IMPLIES implication {
		$$ = make_node(LOG_IMPLIES, NULL);
		attach($$, $1);
		attach($$, $3);
	} | implication { }

implication: implication BIT_OR or_bit {
		$$ = make_node(BIT_OR, NULL);
		attach($$, $1);
		attach($$, $3);
	} | or_bit { }

or_bit: or_bit BIT_XOR xor_bit {
		$$ = make_node(BIT_XOR, NULL);
		attach($$, $1);
		attach($$, $3);
	} | xor_bit { }

xor_bit: xor_bit BIT_AND and_bit {
		$$ = make_node(BIT_AND, NULL);
		attach($$, $1);
		attach($$, $3);
	} | and_bit { }

and_bit: and_bit BIT_IMPLIES imp_bit {
		$$ = make_node(BIT_IMPLIES, NULL);
		attach($$, $1);
		attach($$, $3);
	} | imp_bit { }

imp_bit: imp_bit LESS_THAN relation {
		$$ = make_node(LESS_THAN, NULL);
		attach($$, $1);
		attach($$, $3);
	} | imp_bit LESS_EQUAL relation {
		$$ = make_node(LESS_EQUAL, NULL);
		attach($$, $1);
		attach($$, $3);
	} | imp_bit EQUAL relation {
		$$ = make_node(EQUAL, NULL);
		attach($$, $1);
		attach($$, $3);
	} | imp_bit GREATER_THAN relation {
		$$ = make_node(GREATER_THAN, NULL);
		attach($$, $1);
		attach($$, $3);
	} | imp_bit GREATER_EQUAL relation {
		$$ = make_node(GREATER_EQUAL, NULL);
		attach($$, $1);
		attach($$, $3);
	} | imp_bit NOT_EQUAL relation {
		$$ = make_node(NOT_EQUAL, NULL);
		attach($$, $1);
		attach($$, $3);
	} | relation { }

relation: relation PLUS shift {
		$$ = make_node(PLUS, NULL);
		attach($$, $1);
		attach($$, $3);
	} | relation MINUS shift {
		$$ = make_node(MINUS, NULL);
		attach($$, $1);
		attach($$, $3);
	} | shift { }

shift: shift RIGHT_SHIFT addend {
		$$ = make_node(RIGHT_SHIFT, NULL);
		attach($$, $1);
		attach($$, $3);
	} | shift LEFT_SHIFT addend {
		$$ = make_node(LEFT_SHIFT, NULL);
		attach($$, $1);
		attach($$, $3);
	} | addend { }

addend: addend TIMES factor {
		$$ = make_node(TIMES, NULL);
		attach($$, $1);
		attach($$, $3);
	} | addend DIVIDE factor {
		$$ = make_node(DIVIDE, NULL);
		attach($$, $1);
		attach($$, $3);
	} | addend INT_DIVIDE factor {
		$$ = make_node(INT_DIVIDE, NULL);
		attach($$, $1);
		attach($$, $3);
	} | addend MODULO factor {
		$$ = make_node(MODULO, NULL);
		attach($$, $1);
		attach($$, $3);
	} | factor { }


factor: factor POWER exponent {
		$$ = make_node(POWER, NULL);
		attach($$, $1);
		attach($$, $3);
	} | factor LOG exponent {
		$$ = make_node(LOG, NULL);
		attach($$, $1);
		attach($$, $3);
	} | exponent { }


exponent: LOG_NOT exponent {
		$$ = make_node(LOG_NOT, NULL);
		attach($$, $2);
	} | BIT_NOT exponent {
		$$ = make_node(BIT_NOT, NULL);
		attach($$, $2);
	} | term { }

term: PAREN_OPEN expression PAREN_CLOSE {
		$$ = make_node(PAREN_OPEN, NULL);
		attach($$, $2);
	} | STRING_LITERAL {
		$$ = make_node(STRING_LITERAL, $1);
	} | INTEGER_LITERAL {
		$$ = make_node(INTEGER_LITERAL, &$1);
	} | FLOAT_LITERAL {
		$$ = make_node(FLOAT_LITERAL, &$1); 
	} | term BRACKET_OPEN expression BRACKET_CLOSE {
		$$ = make_node(BRACKET_OPEN, NULL);
		attach($$, $1);
		attach($$, $3);
	} | MINUS term { 
		$$ = make_node(MINUS, NULL);
		attach($$, $2);
	} | INPUT {
		$$ = make_node(INPUT, NULL);
	} | id { } | function_call { }
		

id: IDENTIFIER {
		$$ = make_node(IDENTIFIER, $1);
	}
	
	
l_val: id BRACKET_OPEN expression BRACKET_CLOSE {
		$$ = make_node(BRACKET_OPEN, NULL);
		attach($$, $1);
		attach($$, $3);
	} | id { }


return_type: TYPE_VOID {
		$$ = make_node(TYPE_VOID, NULL);
	} | type { }


type: TYPE_INTEGER {
		$$ = make_node(TYPE_INTEGER, NULL);
	} | TYPE_FLOAT {
		$$ = make_node(TYPE_FLOAT, NULL);
	} | TYPE_STRING {
		$$ = make_node(TYPE_STRING, NULL);
	} | TYPE_FUNCTION {
		$$ = make_node(TYPE_FUNCTION, NULL);
	} | TYPE_METHOD {
		$$ = make_node(TYPE_METHOD, NULL);
	} | TYPE_TYPE {
		$$ = make_node(TYPE_TYPE, NULL);
	}

%%

int yywrap() {
	return 1;
}

void yyerror(const char* str) {
	fprintf(stderr, "at line %d: `%s'.\n", linecount, str);
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
	FILE* orig_stdin; 
	if (argc-1) {
		orig_stdin = stdin;
		stdin = fopen(argv[1], "r");
	} else {
		printf("stdin mode. press ctrl-d to execute and exit.\n");
	}
	yyparse();
	
	
	//print(result, 0);
	eval_stmt(result);
	
	if (argc-1) {
		fclose(stdin);
		stdin = orig_stdin;
	}
	return 0;
}
