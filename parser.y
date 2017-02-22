%{
	#include <stdio.h>
	#include "tree.h"
	#include "mg_obj.h"
	#define YYDEBUG 1

	int yywrap();
	int yylex();
	struct node* make_node(int token, char* value);
	void attach(struct node* parent, struct node* child);
	void print(struct node* node, int tabs);
	void yyerror(const char* str);
	struct node * result;
%}

%union {
	struct node * n;
	char * val;
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
%precedence ELIF      
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

%token<val> IDENTIFIER      
%token<val> INTEGER_LITERAL
%token<val> FLOAT_LITERAL 
%token<val> STRING_LITERAL 

%token STATEMENT 

%type<n> program statements statement elif_statement expression disjunction
%type<n> conjunction relation addend factor exponent term num id
%type<n> return_type type function_call

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

statement: type id ASSIGN expression SEMICOLON { // declare a var w/value
		$$ = make_node(ASSIGN, NULL);
		attach($$, $1);
		attach($$, $2);
		attach($$, $4);
	} | id ASSIGN expression SEMICOLON { // re-assign a var w/value
		$$ = make_node(ASSIGN, NULL);
		attach($$, $1);
		attach($$, $3);
	} | type id SEMICOLON { // variable declared but not assigned a value
		$$ = make_node(ASSIGN, NULL);
		attach($$, $1);
		attach($$, $2);
		// attach a default value here?
		
	} | WHILE_LOOP expression statement {
		$$ = make_node(WHILE_LOOP, NULL);
		attach($$, $2);
		attach($$, $3);
	} | IF expression statement {
		$$ = make_node(IF, NULL);
		attach($$, $2);
		attach($$, $3);
	} | IF expression statement ELIF elif_statement {
		$$ = make_node(IF, NULL);
		attach($$, $2);
		attach($$, $3);
		attach($$, $5);
	} | IF expression statement ELSE statement {
		$$ = make_node(IF, NULL);
		attach($$, $2);
		attach($$, $3);
		attach($$, $5);
	} | BRACE_OPEN statements BRACE_CLOSE {
		$$ = make_node(STATEMENT, NULL);
		attach($$, $2);
	} | expression SEMICOLON {
		$$ = make_node(STATEMENT, NULL);
		attach($$, $1);
	}


elif_statement: expression statement ELIF elif_statement {
		$$ = make_node(ELIF, NULL);
		attach($$, $1);
		attach($$, $2);
		attach($$, $4);
	} | expression statement ELSE statement {
		$$ = make_node(ELIF, NULL);
		attach($$, $1);
		attach($$, $2);
		attach($$, $4);
	} | expression statement {
		$$ = make_node(ELIF, NULL);
		attach($$, $1);
		attach($$, $2);
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


conjunction: conjunction LESS_THAN relation {
		$$ = make_node(LESS_THAN, NULL);
		attach($$, $1);
		attach($$, $3);
	} | conjunction LESS_EQUAL relation {
		$$ = make_node(LESS_EQUAL, NULL);
		attach($$, $1);
		attach($$, $3);
	} | conjunction EQUAL relation {
		$$ = make_node(EQUAL, NULL);
		attach($$, $1);
		attach($$, $3);
	} | conjunction GREATER_THAN relation {
		$$ = make_node(GREATER_THAN, NULL);
		attach($$, $1);
		attach($$, $3);
	} | conjunction GREATER_EQUAL relation {
		$$ = make_node(GREATER_EQUAL, NULL);
		attach($$, $1);
		attach($$, $3);
	} | conjunction NOT_EQUAL relation {
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
	} | MINUS exponent {
		$$ = make_node(MINUS, NULL);
		attach($$, $2);
	} | term { }


term: PAREN_OPEN expression PAREN_CLOSE {
		$$ = make_node(PAREN_OPEN, NULL);
		attach($$, $2);
	} | STRING_LITERAL {
		$$ = make_node(STRING_LITERAL, $1);
	} | id {
	} | num { }
		

num: INTEGER_LITERAL {
		$$ = make_node(INTEGER_LITERAL, $1);
	} | FLOAT_LITERAL {
		$$ = make_node(FLOAT_LITERAL, $1); 
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
}

int main(int argc, char **argv) {

	FILE* orig_stdin = stdin;
	stdin = fopen(argv[1], "r");


	yyparse();

	print(result, 0);
	// int token;
	// do {	
	// 	token = yylex( );
		
	// 	printf("%d\n", token);

  	// } while(token != 0);
	

	fclose(stdin);
	stdin = orig_stdin;
	return 0;
}
