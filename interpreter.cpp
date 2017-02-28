#include <unordered_map>
#include <iostream>
#include <string>
#include <cstring>
#include "interpreter.h"
#include "parser.tab.h"
#include "tree.h"
#include "mg_obj.h"


std::unordered_map<std::string, struct mg_obj*> vars;


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

// determines whether to do assignment, reassignment, or initialization

// assignment -> reduces expression node to mg_obj and compares its type to
// the declared type. if the types match it inserts the <id,mg_obj> pair into
// vars map.

// reassignment -> if the identifier has already been
// declared/initialized reduces expression node to mg_obj and compares its type
// to the existing mg_obj associated with the id if the types match the value is
// overwritten.

// initialization-> stores the identifier in the vars map and associates it with
// a mg_obj of the declared type with NULL value
void assignment(struct node * n) {
	//assignment
	if (n->num_children == 3) {
		std::string id = std::string((char*)n->children[1]->value);
		// reduce expression node to mg_obj
		struct mg_obj* value = eval_expr(n->children[2]); 
		int type = (n->children[0])->token;

		if (typesMatch(type, value->type)) {
			vars[id] = value;
		} else {
			//TODO: raise error for non matching types
		}
	} else {
		//reassignment 
		if(n->children[0]->token == IDENTIFIER) {
			std::string id = std::string((char*)n->children[0]->value);
			
			if (declared(id)) {
				struct mg_obj * current_val = vars[id];
				//reduce expression node to mg_obj
				struct mg_obj * value = eval_expr(n->children[1]); 
				if (typesMatch(current_val->type, value->type)) {
					delete current_val;
					vars[id] = value;
				} else {
					//raise types don't match
				}
			} else {
				//raise assignment to undeclared identifier
			}
		} else { //initialization
			std::string id = std::string((char*)n->children[1]->value);
			int type = n->children[0]->token;
			vars[id] = mg_alloc(type, NULL);
		}
	}
}

int eval_bool(struct mg_obj * o) {
	int type = (o->type);
	if (type == TYPE_STRING) {
		std::string v = std::string((char *)o->value);
		return v != "";
	}
	if (type == TYPE_INTEGER) {
		return *(int*)o->value != 0;
	}
	if (type == TYPE_FLOAT) {
		return *(double*)o->value != 0;
	}
	
	// default for other types: determine whether the object has a value
	return o->value != NULL;
}

int eval_comp(struct mg_obj * left, struct mg_obj * right) {
	if (left->type != right->type) {
		// TODO: raise type comparison error
	}

	if (left->type == TYPE_INTEGER) {

	}
	else if (left->type == TYPE_FLOAT) {

	}
	else if (left->type == TYPE_STRING) {

	}
}


void eval_stmt(struct node* node) {
	struct mg_obj * conditional;
	switch (node->token) {
		case ASSIGN:
			assignment(node);
			break;
		case WHILE_LOOP:
			conditional = eval_expr(node->children[0]);
			while (eval_bool(conditional)) {
				eval_stmt(node->children[1]);
			}
			break;
		case IF:
			conditional = eval_expr(node->children[0]);
			if (eval_bool(conditional)) {
				eval_stmt(node->children[1]);
			}
			else if (node->num_children == 3) {
				eval_stmt(node->children[2]);
			}
			break;
		case STATEMENT:
			for (int i = 0; i < node->num_children; i++) {
				eval_stmt(node->children[i]);
			}
			break;
	}
}


mg_obj* eval_expr(struct node* node) {

	bool t_val;
	struct mg_obj * left;
	struct mg_obj * right;

	switch (node->token) {
		case IDENTIFIER:
			return vars[*(std::string*)(node->value)];
			break;
		case INTEGER_LITERAL:
			return mg_alloc(TYPE_INTEGER, (int*)node->value);
			break;
		case FLOAT_LITERAL:
			return mg_alloc(TYPE_FLOAT, (double*)node->value);
			break;
		case STRING_LITERAL:
			return mg_alloc(TYPE_STRING, (std::string*)node->value);
			break;
		case PAREN_OPEN:
			return eval_expr(node->children[0]);
			break;
		case LOG_NOT:
			right = eval_expr(node->children[0]);
			t_val = !eval_bool(right);
			return mg_alloc(TYPE_INTEGER, new int(t_val));
			break;
		case LOG_OR:
			left = eval_expr(node->children[0]);
			right = eval_expr(node->children[1]);
			t_val = eval_bool(left) || eval_bool(right);
			return mg_alloc(TYPE_INTEGER, new int(t_val));
			break;
		case LOG_XOR:
			left = eval_expr(node->children[0]);
			right = eval_expr(node->children[1]);
			t_val = (eval_bool(left) || eval_bool(right)) && !((eval_bool(left) && eval_bool(right)));
			return mg_alloc(TYPE_INTEGER, new int(t_val));
			break;
		case LOG_AND:
			left = eval_expr(node->children[0]);
			right = eval_expr(node->children[1]);
			t_val = eval_bool(left) && eval_bool(right);
			return mg_alloc(TYPE_INTEGER, new int(t_val));
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
