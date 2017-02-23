#include <unordered_map>
#include <iostream>
#include <string>
#include "interpreter.h"
#include "parser.tab.h"
#include "tree.h"
#include "mg_obj.h"


std::unordered_map<std::string, struct mg_obj*> vars;


// bool declared(struct node*);
// bool typesMatch(int, int);

void printVars() {
	// std::cout << "VARIABLES" << std::endl;
	// std::unordered_map<std::string, double>::iterator it;
	// for(it = vars.begin(); it != vars.end(); it++) {
	// 	std::cout << it->first << "  " << it->second << std::endl;
	// }
}

//returns true if id is a key in the variable map
bool declared(std::string id) {
	std::unordered_map<std::string, struct mg_obj*>::const_iterator iter = vars.find(id);
	return iter != vars.end();
}

//returns whether a given token type and literal type correspond
bool typesMatch(int token, int literal) {

	return (token == TYPE_INTEGER && literal == INTEGER_LITERAL)
	|| (token == TYPE_FLOAT && literal == FLOAT_LITERAL)
	|| (token == TYPE_STRING && literal == STRING_LITERAL);
}

//determines whether to do assignment, reassignment, or initialization
// assignment -> reduces expression node to mg_obj and compares its type to the declared type
// 					if the types match it inserts the <id,mg_obj> pair into vars map
// reassignment -> if the identifier has already been declared/initialized
// 					reduces expression node to mg_obj and compares its type to the existing 
// 					mg_obj associated with the id if the types match the value is overwritten
//initialization-> stores the identifier in the vars map and associates it with a mg_obj
// 					of the declared type with NULL value
void assignment(struct node * n) {
	//assignment
	if (n->num_children == 3) {

		std::string id = (char*)(n->children[1])->value;
		struct mg_obj* value = eval_expr(n->children[2]); // reduce expression node to mg_obj
		int type = (n->children[0])->token;

		if (typesMatch(type, value->type)) {
			vars[id] = value;
		}
		else {
			//raise error for non matching types
		}
	}
	else {
		//reassignment 
		if(n->children[0]->token == IDENTIFIER) {
			std::string id = (char*)(n->children[0])->value;
			
			if (declared(id)) {
				struct mg_obj * current_val = vars[id];
				struct mg_obj * value = eval_expr(n->children[1]); //reduce expression node to mg_obj

				if (typesMatch(current_val->type, value->type)) {
					delete current_val;
					vars[id] = value;
				}else {
					//raise types don't match
				}
			} else {
				//raise assignment to undeclared identifier
			}
		}
		//initialization
		else {
			std::string id = (char*)(n->children[1])->value;
			int type = (n->children[0])->token;
			vars[id] = mg_alloc(type, NULL);
		}
	}
}

void eval_stmt(struct node* node) {

	switch (node->token) {
		case ASSIGN:
			assignment(node);
			break;
		case WHILE_LOOP:
			break;
		case IF:
			break;
		case STATEMENT:
			for (int i = 0; i < node->num_children; i++) {
				eval_stmt(node->children[i]);
			}
			break;
	}
}


mg_obj* eval_expr(struct node* node) {

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