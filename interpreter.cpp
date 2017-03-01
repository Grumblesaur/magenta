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
		if(iter->second != NULL){
			switch(iter->second->type) {
				case TYPE_INTEGER:
					std::cerr << iter->first << "  ";
					std::cerr << *(int*)iter->second->value << std::endl;
					break;
				case TYPE_FLOAT:
					std::cerr << iter->first << "  ";
					std::cerr << *(double*)iter->second->value << std::endl;
					break;
				case TYPE_STRING:
					std::cerr << iter->first;
					std::cerr << "  " << *(std::string*)iter->second->value;
					std::cerr << std::endl;
					break;
			}
		}
	}
}

//returns true if id is a key in the variable map
bool declared(std::string id) {
	std::unordered_map<std::string, struct mg_obj*>::const_iterator iter =
		vars.find(id);
	return iter != vars.end();
}

// determines whether to do assignment, reassignment, or initialization

// assignment -> reduces expression node to mg_obj and compares its type to
// the declared type. if the types match it inserts the <id,mg_obj> pair
// into vars map.

// reassignment -> if the identifier has already been
// declared/initialized reduces expression node to mg_obj and compares its
// type to the existing mg_obj associated with the id if the types match
// the value is overwritten.

// initialization-> stores the identifier in the vars map and associates
// it with a mg_obj of the declared type with NULL value
void assignment(struct node * n) {

	//assignment
	if (n->num_children == 3) {
		std::cout << "assign" << std::endl;
		std::string id = std::string((char*)n->children[1]->value);
		
		// reduce expression node to mg_obj
		struct mg_obj * value = eval_expr(n->children[2]); 
		int type = (n->children[0])->token;

		if (type == value->type) {
			vars[id] = value;
		} else if (type == TYPE_FLOAT && value->type == TYPE_INTEGER) {
			value->type = TYPE_FLOAT;
			*(double *) value->value = (double) *(int*)value->value;
			vars[id] = value;
		}
	} else {
		//reassignment 
		if(n->children[0]->token == IDENTIFIER) {
			std::string id = std::string((char*)n->children[0]->value);
			
			if (declared(id)) {
				struct mg_obj * current_val = vars[id];
				//reduce expression node to mg_obj
				struct mg_obj * value = eval_expr(n->children[1]); 
				if (current_val->type == value->type) {
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
		return std::string((char *)o->value) != "";
	}
	if (type == TYPE_INTEGER) {
		return *(int*)o->value != 0;
	}
	if (type == TYPE_FLOAT) {
		return *(double*)o->value != 0.0;
	}
	
	// default for other types: determine whether the object has a value
	return o->value != NULL;
}

// returns an int that represents a boolean value indicating
// whether the comparison between nodes left and right evaluates to true
// or false comparison type is passes in as its token
// could probably be more elegantly done. should be revisited.
int eval_comp(struct mg_obj * left, int token, struct mg_obj * right) {
	std::cout << "eval_comp" << std::endl;
	static int counter = 1;
	std::cerr << "we have passed through eval_comp() " << counter++;
	std::cerr << " times" << std::endl;
	print_vars();
	if (left == NULL) {
		std::cerr << "left arg of eval_comp() is null" << std::endl;
	}
	if (right == NULL) {
		std::cerr << "right arg of eval_comp() is null" << std::endl;
	}
	
	print_vars();
	if ( left == NULL || right == NULL 
	||(left->type == TYPE_STRING && left->type != right->type)
	|| (right->type == TYPE_STRING && left->type != right->type)) {
		// TODO: raise type comparison error
		std::cerr << "Invalid comparison between incompatible types.";
		std::cerr << std::endl;
		exit(EXIT_FAILURE);
	}

	bool numeric = left->type != TYPE_STRING && right->type != TYPE_STRING;
	double lfloat, rfloat;
	std::string lstr, rstr;
	
	// numerics are treated as floating-point values for comparison to
	// allow comparison between floating-point values and integer values
	if (left->type == TYPE_INTEGER) {
		lfloat = *(int *) left->value;
	} else if (left->type = TYPE_FLOAT) {
		lfloat = *(double *) left->value;
	}
	
	if (right->type == TYPE_FLOAT) {
			rfloat = *(double *) right->value;
	} else if (right->type == TYPE_INTEGER) {
			rfloat = *(int *) right-> value;
	}
	
	if (numeric) {
		switch (token) {
			case LESS_THAN: return lfloat < rfloat;
			case LESS_EQUAL: return lfloat <= rfloat;
			case EQUAL: return lfloat == rfloat;
			case NOT_EQUAL: return lfloat != rfloat;
			case GREATER_EQUAL: return lfloat >= rfloat;
			case GREATER_THAN: return lfloat > rfloat;
		}
	} else {
		lstr = *(std::string*) left->value;
		rstr = *(std::string*) right->value;
		switch(token) {
			case LESS_THAN: return lstr < rstr;
			case LESS_EQUAL: return lstr <= rstr;
			case EQUAL: return lstr == rstr;
			case NOT_EQUAL: return lstr != rstr;
			case GREATER_EQUAL: return lstr >= rstr;
			case GREATER_THAN: return lstr > rstr;
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
		// int * int -> int
		int product = *(int*)x->value * *(int*)y->value;
		return mg_alloc(TYPE_INTEGER, &product);
	} else if (x->type == TYPE_INTEGER && y->type == TYPE_FLOAT) {
		// int * float -> float
		double product = *(int*)x->value * *(double*)y->value;
		return mg_alloc(TYPE_FLOAT, &product);
	} else if (x->type == TYPE_FLOAT && y->type == TYPE_INTEGER) {
		// float * int -> float
		double product = *(double*)x->value * *(int*)y->value;
		return mg_alloc(TYPE_FLOAT, &product);
	} else if (x->type == TYPE_FLOAT && y->type == TYPE_FLOAT) {
		// float * float -> float
		double product = *(double*)x->value * *(double*)y->value;
		return mg_alloc(TYPE_FLOAT, &product);
	} else if (x->type == TYPE_INTEGER && y->type == TYPE_STRING) {
		// int n * string s -> s repeated n times
		int repeats = *(int *) x->value;
		std::string text = *(std::string *) y->value;
		std::string repetition = "";
		while (repeats) {
			repetition += text;
			repeats--;
		}
		return mg_alloc(TYPE_STRING, &repetition);
	} else if (x->type == TYPE_STRING && y->type == TYPE_INTEGER) {
		// string s * int n -> s repeated n times
		int repeats = *(int *) y->value;
		std::string text = *(std::string *) x->value;
		std::string repetition = "";
		while (repeats) {
			repetition += text;
			repeats--;
		}
		return mg_alloc(TYPE_STRING, &repetition);
	}
	//TODO raise invalid operand types error
}


// returns mg_obj / with quotient of x and y
// int/int->int
// int/flt->flt
// flt/int->flt
// flt/flt->flt
// else error
// handles operations with the `/` operator
struct mg_obj * divide(struct mg_obj * x, struct mg_obj * y) {
	std::cout << "divide" << std::endl;
	if (x->type == TYPE_INTEGER && y->type == TYPE_INTEGER) {
		int quotient = *(int*)x->value / *(int*)y->value;
		return mg_alloc(TYPE_INTEGER, &quotient);
	}
	else if (x->type == TYPE_INTEGER && y->type == TYPE_FLOAT) {
		double quotient = *(int*)x->value / *(double*)y->value;
		return mg_alloc(TYPE_FLOAT, &quotient);
	}
	else if (x->type == TYPE_FLOAT && y->type == TYPE_INTEGER) {
		double quotient = *(double*)x->value / *(int*)y->value;
		return mg_alloc(TYPE_FLOAT, &quotient);
	}
	else if (x->type == TYPE_FLOAT && y->type == TYPE_FLOAT) {
		double quotient = *(double*)x->value / *(double*)y->value;
		return mg_alloc(TYPE_FLOAT, &quotient);
	}
	//TODO raise invalid operand types error
}


// modulo is only defined for integers
struct mg_obj * modulo(struct mg_obj * x, struct mg_obj * y) {
	std::cout << "modulo" << std::endl;
	if (x->type == TYPE_INTEGER && y->type == TYPE_INTEGER) {
		int z = *(int *)x->value % *(int *)y->value;
		return mg_alloc(TYPE_INTEGER, &z);
	}
	// TODO raise invalid operand types error
}

// handles operations with the `+` operator
struct mg_obj * add(struct mg_obj * x, struct mg_obj * y) {
	std::cout << "add" << std::endl;
	print_vars();
	static int counter = 1;
	std::cerr << "We have entered add() " << counter++ << " times";
	std::cerr << std::endl;
	
	if (x == NULL) {
		std::cerr << "x is null in add" << std::endl;
	}
	if (y == NULL) {
		std::cerr << "y is null in add" << std::endl;
	}
	if (x == NULL || y == NULL) {
		std::cerr << "uninitialized argument: add" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	if (x->type == TYPE_INTEGER && y->type == TYPE_INTEGER) {
		// int + int -> int
		int sum = *(int*)x->value + *(int*)y->value;
		return mg_alloc(TYPE_INTEGER, &sum);
	} else if (x->type == TYPE_INTEGER && y->type == TYPE_FLOAT) {
		// int + float -> float
		double sum = *(int*)x->value + *(double*)y->value;
		return mg_alloc(TYPE_FLOAT, &sum);
	} else if (x->type == TYPE_FLOAT && y->type == TYPE_INTEGER) {
		// float + int -> float
		double sum = *(double*)x->value + *(int*)y->value;
		return mg_alloc(TYPE_FLOAT, &sum);
	} else if (x->type == TYPE_FLOAT && y->type == TYPE_FLOAT) {
		// float + float -> float
		double sum = *(double*)x->value + *(double*)y->value;
		return mg_alloc(TYPE_FLOAT, &sum);
	} else if (x->type == TYPE_STRING && y->type == TYPE_STRING) {
		// str + str -> str (concatenation)
		std::string s = (*(std::string *) x->value)
			+ (*(std::string *) y->value);
		return mg_alloc(TYPE_STRING, &s);
	}
	//TODO raise invalid operand types error
}


// handles operations with the `-` operator
struct mg_obj * subtract(struct mg_obj * x, struct mg_obj * y) {
	std::cout << "subtract" << std::endl;
	if (!x) {
		std::cerr << "x is null in subtract" << std::endl;
	}
	if (!y) {
		std::cerr << "y is null in subtract" << std::endl;
	}
	if (!x || !y) exit(EXIT_FAILURE);
	
	if (x->type == TYPE_INTEGER && y->type == TYPE_INTEGER) {
		// int - int -> int
		std::cerr << "\tint - int" << std::endl;
		int diff = *(int*)x->value - *(int*)y->value;
		return mg_alloc(TYPE_INTEGER, &diff);
		
	} else if (x->type == TYPE_INTEGER && y->type == TYPE_FLOAT) {
		// int - float -> float
		std::cerr << "\tint - float" << std::endl;
		double diff = *(int*)x->value - *(double*)y->value;
		return mg_alloc(TYPE_FLOAT, &diff);
		
	} else if (x->type == TYPE_FLOAT && y->type == TYPE_INTEGER) {
		// float - int -> float
		std::cerr << "\tfloat - int" << std::endl;
		double diff = *(double*)x->value - *(int*)y->value;
		return mg_alloc(TYPE_FLOAT, &diff);
		
	} else if (x->type == TYPE_FLOAT && y->type == TYPE_FLOAT) {
		// float - float -> float
		std::cerr << "\tfloat - float" << std::endl;
		double diff = *(double*)x->value - *(double*)y->value;
		return mg_alloc(TYPE_FLOAT, &diff);
	}
	//TODO raise invalid operand types error
	std::cerr << "SUBTRACTION FALLTHROUGH ERROR" << std::endl;
	return NULL;
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
			while (eval_bool(eval_expr(node->children[0]))) {
				eval_stmt(node->children[1]);
			}
			break;
		case IF:
			conditional = eval_expr(node->children[0]);
			if (eval_bool(conditional)) {
				eval_stmt(node->children[1]);
			} else if (node->num_children == 3) {
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
			switch (out->type) {
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
			t_val = (eval_bool(left) || eval_bool(right))
				&& !(eval_bool(left) && eval_bool(right));
			return mg_alloc(TYPE_INTEGER, new int(t_val));
			break;
		case LOG_AND:
			left = eval_expr(node->children[0]);
			right = eval_expr(node->children[1]);
			t_val = eval_bool(left) && eval_bool(right);
			return mg_alloc(TYPE_INTEGER, new int(t_val));
			break;
		
		case LESS_THAN:
		case LESS_EQUAL:
		case EQUAL:
		case NOT_EQUAL:
		case GREATER_THAN:
		case GREATER_EQUAL:
			// use token passed in to process the value instead of having
			// a separate case for each
			t_val = eval_comp(
				eval_expr(node->children[0]), // left hand side
				node->token,                  // comparison operator
				eval_expr(node->children[1])  // right hand side
			);
			return mg_alloc(TYPE_INTEGER, new int(t_val));
			break;
		
		case TIMES:
			return multiply(
				eval_expr(node->children[0]), // left hand factor
				eval_expr(node->children[1])  // right hand factor
			);
			break;
		case DIVIDE:
			return divide(
				eval_expr(node->children[0]), // dividend
				eval_expr(node->children[1])  // divisor
			);
			break;
		case MODULO:
			break;
		case PLUS:
			return add(
				eval_expr(node->children[0]), // left hand addend
				eval_expr(node->children[1])  // right hand addend
			);
			break;
		case MINUS:
			std::cerr << "case MINUS in EVAL_EXPR" << std::endl;
			return subtract(
				eval_expr(node->children[0]), // minuend
				eval_expr(node->children[1])  // subtrahend
			);
			break;
		case POWER:
			break;
		case LOG:
			break;
	}
}
