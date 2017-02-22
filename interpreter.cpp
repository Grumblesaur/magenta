#include <unordered_map>
#include <iostream>
#include <string>
#include "interpreter.h"
#include "parser.tab.h"
#include "tree.h"
#include "mg_obj.h"


std::unordered_map<std::string, mg_obj*> vars;


void printVars() {
	// std::cout << "VARIABLES" << std::endl;
	// std::unordered_map<std::string, double>::iterator it;
	// for(it = vars.begin(); it != vars.end(); it++) {
	// 	std::cout << it->first << "  " << it->second << std::endl;
	// }
}


void eval_stmt(struct node* node) {

	switch (node->token) {
		
	}
}


mg_obj eval_expr(struct node* node) {

	switch (node->token) {

		case IDENTIFIER:
			break;
		case INTEGER_LITERAL:
			break;
		case FLOAT_LITERAL:
			break;
		case STRING_LITERAL:
			break;
		case PAREN_OPEN:
			break;
		case LOG_NOT:
			break;
		case LOG_OR:
			break;
		case LOG_XOR:
			break;
		case LOG_AND:
			break;
		case LESS_THAN:
			break;
		case LESS_EQUAL:
			break;
		case EQUAL:
			break;
		case NOT_EQUAL:
			break;
		case GREATER_THAN:
			break;
		case GREATER_EQUAL:
			break;
		case TIMES:
			break;
		case DIVIDE:
			break;
		case MODULO:
			break;
		case PLUS:
			break;
		case MINUS:
			break;
		case POWER:
			break;
		case LOG:
			break;
	}
}