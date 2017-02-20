%{
	#include <stdio.h>
	#define YYDEBUG 101
	int yywrap();
	int yylex();
%}

%union {

}

%token BRACE_OPEN      
%token BRACE_CLOSE     
%token ASSIGN          
%token COLON           

%token TYPE_FUNCTION   
%token TYPE_INTEGER    
%token TYPE_STRING     
%token TYPE_FLOAT      
%token TYPE_COMPOUND   
%token OPTION_STMT     
%token CASE_STMT       
%token IF_STMT         
%token ELIF_STMT       
%token ELSE_STMT       
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

%token IDENTIFIER      
%token NUMERIC_LITERAL 
%token STRING_LITERAL  

%%


%%

int yywrap() {
	return 1;
}

void yyerror(const char* str) {
	fprintf(stderr, "COMPILER ERROR: '%s'.\n", str);
}

int main(int argc, char **argv) {
	int token;
	do {
    token = yylex( );
    
    printf(token);

  } while(token != 0);
	
	return 0;
}