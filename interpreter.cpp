#include <unordered_map>
#include <iterator>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include "interpreter.h"
#include "parser.tab.h"
#include "tree.h"
#include "mg_obj.h"
#include "mg_int.h"
#include "mg_flt.h"
#include "mg_str.h"

using std::string;
using std::cout;
using std::cerr;
using std::endl;

std::unordered_map<string, mg_obj *> vars;

// returns whether id is an initialized variable name
bool declared(string id) {
	std::unordered_map<string, mg_obj>::const_iterator iter =
		vars.find(id);
	return iter != vars.end();
}


bool eval_bool(struct node * node) {
	switch(node->token) {
		case TYPE_STRING:
			return string((char *) node->value) != "";
		case TYPE_INTEGER:
			return *(int *) node->value != 0;
		case TYPE_FLOAT:
			return *(double *) node->value != 0.0;
		default: // for non-primitive types XXX this may change later
			return node->value != NULL;
	}
}

//mg_objs need to be cast to their appropriate subclasses to access value
//we will need to use pointers for this.
// e.g. map<string, mg_obj *> 
// 		mg_obj * o;
// 		if (mg_obj->type == TYPE_INTEGER) {
// 			int value = (mg_int *)o->value;
// 		}
bool eval_comp(mg_obj * left, int op, mg_obj * right) {
	if (left.type == TYPE_STRING && left.type != right.type
		|| right.type == TYPE_STRING && left.type != right.type) {
		
		cerr << "Bad comparison: str val against non-str val" << endl;
		exit(EXIT_FAILURE);
	}
	
	bool numeric = left.type != TYPE_STRING && right.type != TYPE_STRING;
	double lfloat, rfloat;
	string lstr, rstr;
	
	if (numeric) {
		lfloat = (double) ((mg_flt*)left)->value;
		rfloat = (double) right.value;
		switch (op) {
			case LESS_THAN: return lfloat < rfloat;
			case LESS_EQUAL: return lfloat <= rfloat;
			case EQUAL: return lfloat == rfloat;
			case NOT_EQUAL: return lfloat != rfloat;
			case GREATER_EQUAL: return lfloat >= rfloat;
			case GREATER_THAN: return lfloat > rfloat;
		}
	} else {
		lstr = left.value;
		rstr = right.value;
		switch (op) {
			case LESS_THAN: return lstr < rstr;
			case LESS_EQUAL: return lstr <= rstr;
			case EQUAL: return lstr == rstr;
			case NOT_EQUAL: return lstr != rstr;
			case GREATER_EQUAL: return lstr >= rstr;
			case GREATER_THAN: return lstr > rstr;
		}
	}
	
}


//want to know pls explain to me (string part)
mg_obj multiply(mg_obj left, mg_obj right) {
	int i_product;
	double d_product;
	int repeats;
	string text;
	char temp;
	std::ostringstream oss;
	std::vector<string> repetition;
	
	if (x.type == TYPE_INTEGER && right.type == TYPE_INTEGER) {
		i_product = left.value * right.value;
		return mg_int(&i_product);
	} else if (left.type == TYPE_INTEGER && right.type TYPE_FLOAT) {
		d_product = left.value * right.value;
		return mg_flt(&d_product);
	} else if (left.type == TYPE_FLOAT && right.type == TYPE_INTEGER) {
		d_product = left.value * right.value;
		return mg_flt(&d_product);
	} else if (left.type == TYPE_FLOAT && right.type == TYPE_FLOAT) {
		d_product = left.value * right.value;
		return mg_flt(&d_product);
	} else if (left.type == TYPE_INTEGER && right.type == TYPE_STRING) {
		repeats = left.value;
		text = right.value;
		if (repeats < 0) {
			// reverse the string on negative repeats
			repeats *= 1;
			for (int i = 0; i < text.length() / 2; i++) {
				temp = text[i];
				text[i] = text[text.length() - i - 1];
				text[text.length() - i - 1] = temp;
			}
		repetition = std::vector<string>(repeats, text);
		std::copy(
			repetition.begin(),
			repetition.end(),
			std::ostream_iterator<>(oss)
		);
		return oss.str()
	} else if (left.type == TYPE_STRING && right.type == TYPE_INTEGER) {
		repeats = right.value;
		text = left.value;
		if (repeats < 0) {
			// reverse the string on negative repeats
			repeats *= 1;
			for (int i = 0; i < text.length() / 2; i++) {
				temp = text[i];
				text[i] = text[text.length() - i - 1];
				text[text.length() - i - 1] = temp;
			}
		repetition = std::vector<string>(repeats, text);
		std::copy(
			repetition.begin(),
			repetition.end(),
			std::ostream_iterator<>(oss)
		);
		return oss.str();
	}
}

mg_obj eval_expr(struct node * node) {
	bool t_val;
	mg_obj left, right;
	switch(node->token) {
		case IDENTIFIER:
			return vars[std::string((char *) node->value)];
		case INTEGER_LITERAL:
			return mg_int(node->value);
		case FLOAT_LITERAL:
			return mg_flt(node->value);
		case STRING_LITERAL:
			return mg_str(node->value);
		
		case PAREN_OPEN:
			return eval_expr(node->children[0]);
		
		case LOG_NOT:
			right = eval_expr(node->children[0]);
			t_val = !eval_bool(right);
			return mg_int(&t_val); 
		case LOG_OR:
			left = eval_expr(node->children[0]);
			right = eval_expr(node->children[1]);
			t_val = eval_bool(left) || eval_bool(right);
			return mg_int(&t_val);
		case LOG_XOR:
			left = eval_expr(node->children[0]);
			right = eval_expr(node->children[1]);
			t_val = eval_bool(left) || eval_bool(right)
				&& !(eval_bool(left) && eval_bool(right));
			return mg_int(&t_val);
		case LOG_AND:
			left = eval_expr(node->children[0]);
			right = eval_expr(node->children[1]);
			t_val = eval_bool(left) && eval_bool(right);
			return mg_int(&t_val);
		
		case LESS_THAN:
		case LESS_EQUAL:
		case EQUAL:
		case NOT_EQUAL:
		case GREATER_THAN:
		case GREATER_EQUAL:
			// use token passed in to determine the operation in eval_comp()
			t_val = eval_comp(
				eval_expr(node->children[0]),
				node->token,
				eval_expr(node->children[1])
			);
			return mg_int(&tval);
		
		case TIMES:
			return multiply(
				eval_expr(node->children[0]),
				eval_expr(node->children[1])
			);
		
		case DIVIDE:
			return divide(
				eval_expr(node->children[0]),
				eval_expr(node->children[1])
			);
		
	}
	
}

// given a node n this function will do one of the following:
// 1 initialize a new variable and assign it a value
// 2 reassign a initialized variable
// 3 throw a type mismatch error
// 4 throw a multiple initialization error
void assign(struct node * n) {
	//assignment 
	if (n->num_children == 3) {
		string id = string((char *)n->children[1]->value);
		int type = n->children[0]->token;
		mg_obj value = eval_expr(n->children[2]);
		if (!declared(id)) {
			if (type != value.type) {
				cerr << "ERROR: TYPE MISMATCH" << endl;
				exit(EXIT_FAILURE);
			}
			vars[id] = value;	
		} else {
			cerr << "ERROR: IDENTIFIER CANNOT BE INITIALIZED ";
			cerr << "MORE THAN ONCE." << endl;
			exit(EXIT_FAILURE);
		}
	} else {
		// reassignment
		string id = string((char *)n->children[0]->value);
		mg_obj value = eval_expr(n->children[1]);
		int type = vars[id].type;
		if (type != value.type) {
			cerr << "ERROR: TYPE MISMATCH" << endl;
			exit(EXIT_FAILURE);
		}
		vars[id] = value;
	}
}

void eval_stmt(struct node * node) {

	switch (node->token) {
		case ASSIGN:
			assign(node);
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
		case PRINT:
			break;

	}
}
