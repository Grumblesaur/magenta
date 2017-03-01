#include <unordered_map>
#include <iostream>
#include <string>
#include <cstring>
#include "interpreter.h"
#include "parser.tab.h"
#include "tree.h"
#include "mg_obj.h"


std::unordered_map<std::string, struct mg_obj*> vars;


void print_vars() {
	std::unordered_map<std::string, struct mg_obj*> :: const_iterator iter;
	for(iter = vars.begin(); iter != vars.end(); iter++) {
	
		switch(iter->second->type) {
			case TYPE_INTEGER:
				std::cout << iter->first << "  " << *(int*)iter->second->value << std::endl;
				break;
			case TYPE_FLOAT:
				std::cout << iter->first << "  " << *(double*)iter->second->value << std::endl;
				break;
			case TYPE_STRING:
				std::cout << iter->first << "  " << *(std::string*)iter->second->value << std::endl;
				break;
		}
	}
}

//returns true if id is a key in the variable map
bool declared(std::string id) {
	std::unordered_map<std::string, struct mg_obj*> :: const_iterator iter = vars.find(id);
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
			std::cout << "assign" << std::endl;

		std::string id = std::string((char*)n->children[1]->value);
		// reduce expression node to mg_obj
		struct mg_obj * value = eval_expr(n->children[2]); 
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
	std::cout << "eval_bool" << std::endl;
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

//returns an int that represents a boolean value indicating
//wether the comparison between nodes left and right evaluates to true or false
//comparison type is passes in as its token
//could probably be more elegantly done. should be revisited.
int eval_comp(struct mg_obj * left, int token, struct mg_obj * right) {
	std::cout << "eval_comp" << std::endl;
	if (left->type != right->type) {
		// TODO: raise type comparison error
	}

	if (left->type == TYPE_INTEGER) {
		switch(token) {
			case LESS_THAN:
				return *(int*)left->value < *(int*)right->value;
				break;
			case LESS_EQUAL:
				return *(int*)left->value <= *(int*)right->value;
				break;
			case EQUAL:
				return *(int*)left->value == *(int*)right->value;
				break;
			case NOT_EQUAL:
				return *(int*)left->value != *(int*)right->value;
				break;
			case GREATER_EQUAL:
				return *(int*)left->value >= *(int*)right->value;
				break;
			case GREATER_THAN:
				return *(int*)left->value > *(int*)right->value;
				break;
		}
	}
	else if (left->type == TYPE_FLOAT) {
		switch(token) {
			case LESS_THAN:
				return *(double*)left->value < *(double*)right->value;
				break;
			case LESS_EQUAL:
				return *(double*)left->value <= *(double*)right->value;
				break;
			case EQUAL:
				return *(double*)left->value == *(double*)right->value;
				break;
			case NOT_EQUAL:
				return *(double*)left->value != *(double*)right->value;
				break;
			case GREATER_EQUAL:
				return *(double*)left->value >= *(double*)right->value;
				break;
			case GREATER_THAN:
				return *(double*)left->value > *(double*)right->value;
				break;
		}
	}
	else if (left->type == TYPE_STRING) {
		switch(token) {
			case LESS_THAN:
				return *(std::string*)left->value < *(std::string*)right->value;
				break;
			case LESS_EQUAL:
				return *(std::string*)left->value <= *(std::string*)right->value;
				break;
			case EQUAL:
				return *(std::string*)left->value == *(std::string*)right->value;
				break;
			case NOT_EQUAL:
				return *(std::string*)left->value != *(std::string*)right->value;
				break;
			case GREATER_EQUAL:
				return *(std::string*)left->value >= *(std::string*)right->value;
				break;
			case GREATER_THAN:
				return *(std::string*)left->value > *(std::string*)right->value;
				break;
		}
	}
}

//returns mg_obj * with product of x and y
// int*int->int
// int*flt->flt
// flt*int->flt
// flt*flt->flt
// int*str->str
// str*int->str
// else error
struct mg_obj * multiply(struct mg_obj * x, struct mg_obj * y) {
	std::cout << "multiply" << std::endl;
	if (x->type == TYPE_INTEGER && y->type == TYPE_INTEGER) {
		int product = *(int*)x->value * *(int*)y->value;
		return mg_alloc(TYPE_INTEGER, new int(product));
	}
	else if (x->type == TYPE_INTEGER && y->type == TYPE_FLOAT) {
		double product = *(int*)x->value * *(double*)y->value;
		return mg_alloc(TYPE_FLOAT, new double(product));
	}
	else if (x->type == TYPE_FLOAT && y->type == TYPE_INTEGER) {
		double product = *(double*)x->value * *(int*)y->value;
		return mg_alloc(TYPE_FLOAT, new double(product));
	}
	else if (x->type == TYPE_FLOAT && y->type == TYPE_FLOAT) {
		double product = *(double*)x->value * *(double*)y->value;
		return mg_alloc(TYPE_FLOAT, new double(product));
	}
	else if (x->type == TYPE_INTEGER && y->type == TYPE_STRING) {
		//TODO
	}
	else if (x->type == TYPE_STRING && y->type == TYPE_INTEGER) {
		//TODO
	}
	//TODO raise invalid operand types error
}


//returns mg_obj / with quotient of x and y
// int/int->int
// int/flt->flt
// flt/int->flt
// flt/flt->flt
// int/str->str
// str/int->str
// else error
struct mg_obj * divide(struct mg_obj * x, struct mg_obj * y) {
	std::cout << "divide" << std::endl;
	if (x->type == TYPE_INTEGER && y->type == TYPE_INTEGER) {
		int quotient = *(int*)x->value / *(int*)y->value;
		return mg_alloc(TYPE_INTEGER, new int(quotient));
	}
	else if (x->type == TYPE_INTEGER && y->type == TYPE_FLOAT) {
		double quotient = *(int*)x->value / *(double*)y->value;
		return mg_alloc(TYPE_FLOAT, new double(quotient));
	}
	else if (x->type == TYPE_FLOAT && y->type == TYPE_INTEGER) {
		double quotient = *(double*)x->value / *(int*)y->value;
		return mg_alloc(TYPE_FLOAT, new double(quotient));
	}
	else if (x->type == TYPE_FLOAT && y->type == TYPE_FLOAT) {
		double quotient = *(double*)x->value / *(double*)y->value;
		return mg_alloc(TYPE_FLOAT, new double(quotient));
	}
	else if (x->type == TYPE_INTEGER && y->type == TYPE_STRING) {
		//TODO
	}
	else if (x->type == TYPE_STRING && y->type == TYPE_INTEGER) {
		//TODO
	}
	//TODO raise invalid operand types error
}


struct mg_obj * add(struct mg_obj * x, struct mg_obj * y) {
	std::cout << "add" << std::endl;
	if (x->type == TYPE_INTEGER && y->type == TYPE_INTEGER) {
		int sum = *(int*)x->value + *(int*)y->value;
		return mg_alloc(TYPE_INTEGER, new int(sum));
	}
	else if (x->type == TYPE_INTEGER && y->type == TYPE_FLOAT) {
		double sum = *(int*)x->value + *(double*)y->value;
		return mg_alloc(TYPE_FLOAT, new double(sum));
	}
	else if (x->type == TYPE_FLOAT && y->type == TYPE_INTEGER) {
		double sum = *(double*)x->value + *(int*)y->value;
		return mg_alloc(TYPE_FLOAT, new double(sum));
	}
	else if (x->type == TYPE_FLOAT && y->type == TYPE_FLOAT) {
		double sum = *(double*)x->value + *(double*)y->value;
		return mg_alloc(TYPE_FLOAT, new double(sum));
	}
	else if (x->type == TYPE_INTEGER && y->type == TYPE_STRING) {
		//TODO
	}
	else if (x->type == TYPE_STRING && y->type == TYPE_INTEGER) {
		//TODO
	}
	//TODO raise invalid operand types error
}

struct mg_obj * subtract(struct mg_obj * x, struct mg_obj * y) {
	std::cout << "subtract" << std::endl;
	if (x->type == TYPE_INTEGER && y->type == TYPE_INTEGER) {
		int diff = *(int*)x->value - *(int*)y->value;
		return mg_alloc(TYPE_INTEGER, new int(diff));
	}
	else if (x->type == TYPE_INTEGER && y->type == TYPE_FLOAT) {
		double diff = *(int*)x->value - *(double*)y->value;
		return mg_alloc(TYPE_FLOAT, new double(diff));
	}
	else if (x->type == TYPE_FLOAT && y->type == TYPE_INTEGER) {
		double diff = *(double*)x->value - *(int*)y->value;
		return mg_alloc(TYPE_FLOAT, new double(diff));
	}
	else if (x->type == TYPE_FLOAT && y->type == TYPE_FLOAT) {
		double diff = *(double*)x->value - *(double*)y->value;
		return mg_alloc(TYPE_FLOAT, new double(diff));
	}
	else if (x->type == TYPE_INTEGER && y->type == TYPE_STRING) {
		//TODO
	}
	else if (x->type == TYPE_STRING && y->type == TYPE_INTEGER) {
		//TODO
	}
	//TODO raise invalid operand types error
}


void eval_stmt(struct node* node) {
	std::cout << "eval_stmt" << std::endl;
	print_vars();
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
		case PRINT:
			mg_obj * out = eval_expr(node->children[0]);
			switch(out->type){
				case TYPE_INTEGER:
					std::cout << *(int*)out->value << std::endl;
					break;
				case TYPE_FLOAT:
					std::cout << *(double*)out->value << std::endl;
					break;
				case TYPE_STRING:
					std::cout << *(std::string*)out->value << std::endl;
					break;
			}
	}
}


struct mg_obj * eval_expr(struct node* node) {

std::cout << "eval_expr" << std::endl;
	bool t_val;
	struct mg_obj * left;
	struct mg_obj * right;

	switch (node->token) {
		case IDENTIFIER:
			return vars[std::string((char*)node->value)];
			break;
		case INTEGER_LITERAL:
			return mg_alloc(TYPE_INTEGER, (int*)node->value);
			break;
		case FLOAT_LITERAL:
			return mg_alloc(TYPE_FLOAT, (double*)node->value);
			break;
		case STRING_LITERAL:
			return mg_alloc(TYPE_STRING, (char*)node->value);
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
			eval_comp( eval_expr(node->children[0]), LESS_THAN, eval_expr(node->children[1]) );
			break;
		case LESS_EQUAL:
			eval_comp( eval_expr(node->children[0]), LESS_EQUAL, eval_expr(node->children[1]) );
			break;
		case EQUAL:
			eval_comp( eval_expr(node->children[0]), EQUAL, eval_expr(node->children[1]) );
			break;
		case NOT_EQUAL:
			eval_comp( eval_expr(node->children[0]), NOT_EQUAL, eval_expr(node->children[1]) );
			break;
		case GREATER_THAN:
			eval_comp( eval_expr(node->children[0]), GREATER_THAN, eval_expr(node->children[1]) );
			break;
		case GREATER_EQUAL:
			eval_comp( eval_expr(node->children[0]), GREATER_EQUAL, eval_expr(node->children[1]) );
			break;
		case TIMES:
			return multiply( eval_expr(node->children[0]), eval_expr(node->children[1]) );
			break;
		case DIVIDE:
			return divide( eval_expr(node->children[0]), eval_expr(node->children[1]) );
			break;
		case MODULO:
			break;
		case PLUS:
			return add( eval_expr(node->children[0]), eval_expr(node->children[1]) );
			break;
		case MINUS:
			return subtract( eval_expr(node->children[0]), eval_expr(node->children[1]) );
			break;
		case POWER:
			break;
		case LOG:
			break;
	}
}
