#include <iostream>
#include "tree.h"
#include "parser.tab.h"

struct node* make_node(int token, char* value) {

	struct node* n = new node;
	n->token = token;
	n->value = value;
	n->num_children = 0;
	for (int i = 0; i <= MAX_CHILDREN; i++) {
		n->children[i] = NULL;
	}
	return n;
}

void attach(struct node* parent, struct node* child) {

	parent->children[parent->num_children] = child;
	parent->num_children++;
}

void print(struct node* node, int tabs) {
	if(!node) return;

	/* print leading tabs */
	for(int i = 0; i < tabs; i++) {
		std::cout << "    ";
 	}
	
	switch (node->token) {
		// unholy
		using std::cout; using std::endl;
		case BRACE_OPEN: cout << "BRACE_OPEN" << endl; break;
		case BRACE_CLOSE: cout << "BRACE_CLOSE" << endl; break;
		case ASSIGN: cout << "ASSIGN" << endl; break;
		case COLON: cout << "COLON" << endl; break;
		case SEMICOLON: cout << "SEMICOLON" << endl; break;
		
		case TYPE_FUNCTION: cout << "FUNCTION" << endl; break;
		case TYPE_METHOD: cout << "METHOD" << endl; break;
		case TYPE_INTEGER: cout << "INTEGER" << endl; break;
		case TYPE_STRING: cout << "STRING" << endl; break;
		case TYPE_FLOAT: cout << "FLOAT" << endl; break;
		case TYPE_TYPE: cout << "USER TYPE" << endl; break;
		case TYPE_VOID: cout << "VOID" << endl; break;
		case OPTION: cout << "OPTION" << endl; break;
		case CASE: cout << "CASE" << endl; break;
		case IF: cout << "IF" << endl; break;
		case ELIF: cout << "ELIF" << endl; break;
		case ELSE: cout << "ELSE" << endl; break;
		case FOR_LOOP: cout << "FOR" << endl; break;
		case WHILE_LOOP: cout << "WHILE" << endl; break;
		
		case ACCESS: cout << "ACCESS" << endl; break;
		case BRACKET_OPEN: cout << "BRACKET_OPEN" << endl; break;
		case BRACKET_CLOSE: cout << "BRACKET_CLOSE" << endl; break;
		case PAREN_OPEN: cout << "PAREN_OPEN" << endl; break;
		case PAREN_CLOSE: cout << "PAREN_CLOSE" << endl; break;
		case POWER: cout << "POWER" << endl; break;
		case LOG: cout << "LOG" << endl; break;
		case TIMES: cout << "TIMES" << endl; break;
		case DIVIDE: cout << "DIVIDE" << endl; break;
		case MODULO: cout << "MODULO" << endl; break;
		case PLUS: cout << "PLUS" << endl; break;
		case CONCAT: cout << "CONCAT" << endl; break;
		case MINUS: cout << "MINUS" << endl; break;
		case LEFT_SHIFT: cout << "LEFT_SHIFT" << endl; break;
		case RIGHT_SHIFT: cout << "RIGHT_SHIFT" << endl; break;
		
		case LESS_THAN: cout << "LESS_THAN" << endl; break;
		case GREATER_THAN: cout << "GREATER_THAN" << endl; break;
		case EQUAL: cout << "EQUAL" << endl; break;
		case NOT_EQUAL: cout << "NOT_EQUAL" << endl; break;
		case GREATER_EQUAL: cout << "GREATER_EQUAL" << endl; break;
		case LESS_EQUAL: cout << "LESS_EQUAL" << endl; break;
		
		case LOG_AND: cout << "LOG_AND" << endl; break;
		case LOG_OR: cout << "LOG_OR" << endl; break;
		case LOG_NOT: cout << "LOG_NOT" << endl; break;
		case LOG_XOR: cout << "LOG_XOR" << endl; break;
		case LOG_IMPLIES: cout << "LOG_IMPLIES" << endl; break;
		
		case BIT_AND: cout << "BIT_AND" << endl; break;
		case BIT_OR: cout << "BIT_OR" << endl; break;
		case BIT_NOT: cout << "BIT_NOT" << endl; break;
		case BIT_XOR: cout << "BIT_XOR" << endl; break;
		case BIT_IMPLIES: cout << "BIT_IMPLIES" << endl; break;
		
		case IDENTIFIER: cout << "IDENTIFIER: " << node->value << endl; break;
		case INTEGER_LITERAL:
		case FLOAT_LITERAL:
		case STRING_LITERAL:
			cout << node->value << endl;
			break;
		
		case STATEMENT: cout << "STATEMENT: " << endl; break;
		default:
			cout << "Invalid token: " << node->token << endl; break;
	}

	for(int i = 0; i < node->num_children; i++) {
    	print(node->children[i], tabs + 1);
  	}
	
}
