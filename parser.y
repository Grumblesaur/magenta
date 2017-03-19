%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "tree.h"
	#include "interpreter.h"
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
%token WHILE_LOOP
%token IN
%token BREAK
%token NEXT

%token ACCESS          
%token BRACKET_OPEN    
%token BRACKET_CLOSE   
%token PAREN_OPEN      
%token PAREN_CLOSE     
%token POWER           
%token LOG
%token INT_DIV            
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
%token ARGUMENT
%token ARG_LIST

%token PRINT

%type<n> program statements statement expression disjunction
%type<n> conjunction relation addend factor exponent term id
%type<n> return_type type function_call function_definition
%type<n> method_definition arguments argument arg_list implication
%type<n> case or_bit xor_bit and_bit imp_bit

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
	
function_definition: TYPE_FUNCTION id arg_list COLON type statements {
		$$ = make_node(TYPE_FUNCTION, NULL);
		attach($$, $2); //identifier
		attach($$, $3); // arguments
		attach($$, $5); // return type
		attach($$, $6); // statements
	}

method_definition: TYPE_METHOD id arg_list COLON return_type statements {
		$$ = make_node(TYPE_METHOD, NULL);
		attach($$, $2);
		attach($$, $3);
		attach($$, $5);
		attach($$, $6);
	}

arg_list: PAREN_OPEN arguments PAREN_CLOSE {
		$$ = make_node(ARG_LIST, NULL);
		attach($$, $2);
	}

arguments: argument COMMA arguments {
		$$ = make_node(ARGUMENT, NULL);
		attach($$, $1);
		attach($$, $3);
	} | argument { }

argument: type id { }
	
statement: type id ASSIGN expression SEMICOLON { // declare a var w/value
		$$ = make_node(ASSIGN, NULL);
		attach($$, $1);
		attach($$, $2);
		attach($$, $4);
	} | id ASSIGN expression SEMICOLON { // re-assign a var w/value
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
	} | OPTION BRACE_OPEN case BRACE_CLOSE {
		$$ = make_node(OPTION, NULL);
		attach($$, $3);
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

relation: relation PLUS addend {
		$$ = make_node(PLUS, NULL);
		attach($$, $1);
		attach($$, $3);
	} | relation MINUS addend {
		$$ = make_node(MINUS, NULL);
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
	} | id {
	}
		

id: IDENTIFIER {
		$$ = make_node(IDENTIFIER, $1);
	}


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
	fprintf(stderr, "COMPILER ERROR: '%s'.\n", str);
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {

	FILE* orig_stdin = stdin;
	stdin = fopen(argv[1], "r");
	yyparse();
	

	// print(result, 0);
	eval_stmt(result);
	

	fclose(stdin);
	stdin = orig_stdin;
	return 0;
}
