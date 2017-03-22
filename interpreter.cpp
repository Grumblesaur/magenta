#include <unordered_map>
#include <iterator>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include "interpreter.h"
#include "parser.tab.h"
#include "tree.h"
#include "mg_types.h"
#include "except.h"

using std::string;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;

//mg_objs need to be cast to their appropriate subclasses to access value
//we need to use pointers for this.
// e.g. map<string, mg_obj *> 
// 		mg_obj * o;
// 		if (mg_obj->type == TYPE_INTEGER) {
// 			int value = ((mg_int *)o)->value;
// 		}
// you can't access value from mg_obj because it doesn't have that field
// you can't directly cast mg_obj to any of its subclasses,
// but you can cast pointers



std::unordered_map<string, mg_obj *> vars;

// returns whether id is an initialized variable name
bool declared(string id) {
	std::unordered_map<string, mg_obj *>
		::const_iterator iter = vars.find(id);
	return iter != vars.end();
}


// given mg_obj pointer o this function will
// cast the pointer to a pointer of the appropriate subclass and
// return the boolean value of that pointer's actual value
bool eval_bool(mg_obj * o) {
	switch(o->type) {
		case TYPE_STRING:
			return ((mg_str *) o)->value != "";
		case TYPE_INTEGER:
			return  ((mg_int *) o)->value != 0;
		case TYPE_FLOAT:
			return  ((mg_flt *) o)->value != 0.0;
		default: // for non-primitive types XXX this may change later
			return false;
	}
}

// returns the boolean evaluation of a comparison between the values of
// two mg_objs
// Throws error if str is compared to non-str
bool eval_comp(mg_obj * left, int op, mg_obj * right) {
	if (left->type == TYPE_STRING && left->type != right->type
		|| right->type == TYPE_STRING && left->type != right->type) {
		
		cerr << "ERROR Bad comparison: str val against non-str val" << endl;
		exit(EXIT_FAILURE);
	}
	
	bool numeric = left->type != TYPE_STRING && right->type != TYPE_STRING;
	double lfloat, rfloat;
	string lstr, rstr;
	
	if (numeric) {
		lfloat = (left->type == TYPE_INTEGER) ? 
			(double) ((mg_int *)left)->value : ((mg_flt *)left)->value;
		rfloat = (right->type == TYPE_INTEGER) ? 
			(double) ((mg_int *)right)->value : ((mg_flt *)right)->value;
		switch (op) {
			case LESS_THAN: return lfloat < rfloat;
			case LESS_EQUAL: return lfloat <= rfloat;
			case EQUAL: return lfloat == rfloat;
			case NOT_EQUAL: return lfloat != rfloat;
			case GREATER_EQUAL: return lfloat >= rfloat;
			case GREATER_THAN: return lfloat > rfloat;
		}
	} else {
		lstr = ((mg_str *)left)->value;
		rstr = ((mg_str *)right)->value;
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

mg_obj * power(mg_obj * left, mg_obj * right) {
	if (left->type == TYPE_STRING || right->type == TYPE_STRING) {
		cerr << "ERROR: Unsupported exponentiation operation." << endl;
		exit(EXIT_FAILURE);
	}
	bool left_is_float, right_is_float;
	left_is_float = left->type == TYPE_FLOAT;
	right_is_float = right->type == TYPE_FLOAT;
	
	double lval, rval, result;
	lval = left_is_float ?
		((mg_flt *)left)->value : ((mg_int *)left)->value;
	rval = right_is_float ?
		((mg_flt *)right)->value : ((mg_int *)right)->value;
	
	if (!left_is_float && !right_is_float) {
		return new mg_int(pow(lval, rval));
	}
	return new mg_flt(pow(lval, rval));
}

mg_obj * logarithm(mg_obj * left, mg_obj * right) {
	if (left->type == TYPE_STRING || right->type == TYPE_STRING) {
		cerr << "ERROR: Unsupported logarithmic operation." << endl;
		exit(EXIT_FAILURE);
	}
	bool left_is_float = left->type == TYPE_FLOAT;
	bool right_is_float = right->type == TYPE_FLOAT;
	double lval, rval, result;
	lval = left_is_float ?
		((mg_flt *)left)->value : ((mg_int *)left)->value;
	rval = right_is_float ?
		((mg_flt *)right)->value : ((mg_int *)right)->value;
	
	return new mg_flt(log(lval) / log(rval));
}



// if reps > 0 return value == s repeated reps times
// 	"abc" * 3 == "abcabcabc"
// if reps < 0 return value == reversed s repeated reps times
// 	"abc" * -3 == "cbacbacba""
// if reps == 0 return value == ""
string str_multiply(string s, int reps) {
	int len = s.length();
	int new_len = len * reps;
	if (reps > 0) {
		char temp[new_len];
		for (int i = 0; i < new_len; i++) {
			temp[i] = s[i % len];
		}
		return string(temp, new_len);
	} else if (reps < 0) {
		new_len = new_len * (-1);
		char temp[new_len];
		for (int i = new_len - 1; i > -1; i--) {
			temp[new_len - i - 1] = s[i % len];
		}
		return string(temp, new_len);
	}
	return "";
}


mg_obj * multiply(mg_obj * left, mg_obj * right) {
	int i_product;
	double d_product;
	int repeats;
	string text;
	
	if (left->type == TYPE_INTEGER && right->type == TYPE_INTEGER) {
		i_product = ((mg_int *)left)->value * ((mg_int *)right)->value;
		return new mg_int(i_product);
	} else if (left->type == TYPE_INTEGER && right->type == TYPE_FLOAT) {
		d_product = ((mg_int *)left)->value * ((mg_flt *)right)->value;
		return new mg_int(d_product);
	} else if (left->type == TYPE_FLOAT && right->type == TYPE_INTEGER) {
		d_product = ((mg_flt *)left)->value * ((mg_int *)right)->value;
		return new mg_int(d_product);
	} else if (left->type == TYPE_FLOAT && right->type == TYPE_FLOAT) {
		d_product = ((mg_flt *)left)->value * ((mg_flt *)right)->value;
		return new mg_int(d_product);
	} else if (left->type == TYPE_INTEGER && right->type == TYPE_STRING) {
		repeats = ((mg_int *)left)->value;
		text = ((mg_str *)right)->value;
		string str_product = str_multiply(text, repeats);
		return new mg_str(str_product);
	} else if (left->type == TYPE_STRING && right->type == TYPE_INTEGER) {
		repeats = ((mg_int *)right)->value;
		text = ((mg_str *)left)->value;
		string str_product = str_multiply(text, repeats);
		return new mg_str(str_product);
	} else {
		cerr << "ERROR: unsupported multiplication operation" << endl;
		exit(EXIT_FAILURE);
	}
}

mg_obj * divide(mg_obj * left, mg_obj * right) {
	int i_quotient;
	double d_quotient;
	
	if (left->type == TYPE_INTEGER && right->type == TYPE_INTEGER) {
		d_quotient = (double)((mg_int *)left)->value
			/ (double)((mg_int *)right)->value;
		return new mg_flt(d_quotient);
	} else if (left->type == TYPE_INTEGER && right->type == TYPE_FLOAT) {
		d_quotient = ((mg_int *)left)->value / ((mg_flt *)right)->value;
		return new mg_int(d_quotient);
	} else if (left->type == TYPE_FLOAT && right->type == TYPE_INTEGER) {
		d_quotient = ((mg_flt *)left)->value / ((mg_int *)right)->value;
		return new mg_int(d_quotient);
	} else if (left->type == TYPE_FLOAT && right->type == TYPE_FLOAT) {
		d_quotient = ((mg_flt *)left)->value / ((mg_flt *)right)->value;
		return new mg_int(d_quotient);
	} else {
		cerr << "ERROR: unsupported division operation" << endl;
		exit(EXIT_FAILURE);
	}
}


mg_obj * mod(mg_obj * left, mg_obj * right) {
	if (left->type != TYPE_INTEGER && left->type != TYPE_INTEGER) {
		cerr << "ERROR: unsupported modulus operation" << endl;
		exit(EXIT_FAILURE);
	} else if (left->type == TYPE_INTEGER && right->type == TYPE_INTEGER) {
		int i_mod = ((mg_int *)left)->value % ((mg_int *)right)->value;
		return new mg_int(i_mod);
	}
}

mg_obj * add(mg_obj * left, mg_obj * right) {
	if (left->type == TYPE_STRING && right->type == TYPE_STRING) {
		string concat = ((mg_str *)left)->value + ((mg_str *)right)->value;
		return new mg_str(concat);
	} else if (left->type == TYPE_STRING && right->type != TYPE_STRING
		|| left->type != TYPE_STRING && right->type == TYPE_STRING) {
		
		cerr << "ERROR: unsupported addition operation" << endl;
		exit(EXIT_FAILURE);
	}
		
	bool left_is_float, right_is_float;
	left_is_float = left->type == TYPE_FLOAT;
	right_is_float = right->type == TYPE_FLOAT;
	
	double lval, rval, result;
	lval = left_is_float ?
		((mg_flt *)left)->value : ((mg_int *)left)->value;
	rval = right_is_float ?
		((mg_flt *)right)->value : ((mg_int *)right)->value;
	
	if (!left_is_float && !right_is_float) {
		result = lval + rval;
		return new mg_int(result);
	}
	
	result = lval + rval;
	return new mg_flt(result);
}

mg_obj * subtract(mg_obj * left, mg_obj * right) {
	bool left_is_float, right_is_float;
	double lval, rval, result;
	right_is_float = right->type == TYPE_FLOAT;
	rval = right_is_float ?
		((mg_flt *)right)->value : ((mg_int *)right)->value;
	
	// handle unary minus first
	if (left == NULL && right->type != TYPE_STRING) {
		if (right_is_float) { 
			return new mg_flt(-rval);
		} else {
			return new mg_int(-rval);
		}
	}
	
	if (left->type == TYPE_STRING || right->type == TYPE_STRING) {
		cerr << "ERROR: unsupported subtraction operation" << endl;
		exit(EXIT_FAILURE);
	}
	
	
	left_is_float = left->type == TYPE_FLOAT;
	lval = left_is_float ?
		((mg_flt *)left)->value : ((mg_int *)left)->value;
	
	if (!left_is_float && !right_is_float) {
		result = lval - rval;
		return new mg_int(result);
	}
	result = lval - rval;
	return new mg_flt(result);
}

int eval_bitwise(mg_obj * left, int token, mg_obj * right) {
	// case for bitwise not (unary operator, left passed as null)
	if (left == NULL && right->type == TYPE_INTEGER) {
		return ~((mg_int *)right)->value;
	}
	
	// bitwise operations are only valid for integers
	if (left->type != TYPE_INTEGER || right->type != TYPE_INTEGER) {
		cerr << "Unsupported bitwise operation." << endl;
		exit(EXIT_FAILURE);
	}
	
	int lval, rval;
	lval = ((mg_int *)left)->value;
	rval = ((mg_int *)right)->value;
	
	switch (token) {
		case BIT_XOR:
			return lval ^ rval;
		case BIT_OR:
			return lval | rval;
		case BIT_AND:
			return lval & rval;
		case LEFT_SHIFT:
			return lval << rval;
		case RIGHT_SHIFT:
			return lval >> rval;
	}
}

mg_obj * eval_index(mg_obj * left, mg_obj * right) {
	// TODO: amend this later when we support vector types
	if (!(left->type == TYPE_STRING && right->type == TYPE_INTEGER)) {
		cout << "Unsupported index operation." << endl;
		exit(EXIT_FAILURE);
	}
	
	string text = ((mg_str *)left)->value;
	int length = text.length();
	string out;
	int position = ((mg_int *)right)->value;
	
	if (abs(position) >= length) {
		cout << "Index out of bounds." << endl;
		exit(EXIT_FAILURE);
	}
	
	if (position < 0) {
		out = text[length + position];
	} else {
		out = text[position];
	}
	return new mg_str(out);
}

mg_obj * eval_expr(struct node * node) {
	bool t_val;
	mg_obj * left;
	mg_obj * right;
	string id;
	switch(node->token) {
		case IDENTIFIER:
			id = std::string((char *) node->value);
			return vars[id];
		case INTEGER_LITERAL:
			return new mg_int(*(int *)node->value);
		case FLOAT_LITERAL:
			return new mg_flt(*(double *)node->value);
		case STRING_LITERAL:
			return new mg_str((char *)node->value);
		
		case INPUT:
			getline(cin, id); // use already-allocated `id` var for holder
			return new mg_str(id);
		
		case PAREN_OPEN:
			return eval_expr(node->children[0]);
		
		case BRACKET_OPEN:
			left = eval_expr(node->children[0]);
			right = eval_expr(node->children[1]);
			return eval_index(left, right);
		
		case LOG_NOT:
			right = eval_expr(node->children[0]);
			t_val = !eval_bool(right);
			return new mg_int(t_val); 
		case LOG_OR:
			left = eval_expr(node->children[0]);
			right = eval_expr(node->children[1]);
			t_val = eval_bool(left) || eval_bool(right);
			return new mg_int(t_val);
		case LOG_XOR:
			left = eval_expr(node->children[0]);
			right = eval_expr(node->children[1]);
			t_val = (eval_bool(left) || eval_bool(right))
				&& !(eval_bool(left) && eval_bool(right));
			return new mg_int(t_val);
		case LOG_AND:
			left = eval_expr(node->children[0]);
			right = eval_expr(node->children[1]);
			t_val = eval_bool(left) && eval_bool(right);
			return new mg_int(t_val);
		case LOG_IMPLIES:
			left = eval_expr(node->children[0]);
			right = eval_expr(node->children[1]);
			t_val = !eval_bool(left) && eval_bool(right);
			return new mg_int(t_val);
		
		case BIT_NOT:
		case BIT_AND:
		case BIT_OR:
		case BIT_XOR:
		case LEFT_SHIFT:
		case RIGHT_SHIFT:
			if (node->token == BIT_NOT) {
				left = NULL;
				right = eval_expr(node->children[0]);
			} else {
				left = eval_expr(node->children[0]);
				right = eval_expr(node->children[1]);
			}
			return new mg_int(eval_bitwise(left, node->token, right));
		
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
			return new mg_int(t_val);
		
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

		case MODULO:
			return mod(
				eval_expr(node->children[0]),
				eval_expr(node->children[1])
			);

		case PLUS:
			return add(
				eval_expr(node->children[0]),
				eval_expr(node->children[1])
			);
		
		case MINUS:
			// unary minus
			if (node->num_children == 1) {
				return subtract(
					NULL,
					eval_expr(node->children[0])
				);
			}
			return subtract(
				eval_expr(node->children[0]),
				eval_expr(node->children[1])
			);
		
		case POWER:
			return power(
				eval_expr(node->children[0]),
				eval_expr(node->children[1])
			);
		case LOG:
			return logarithm(
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
		mg_obj * value = eval_expr(n->children[2]);
		if (!declared(id)) {
			if (type == TYPE_FLOAT && value->type == TYPE_INTEGER) {
				mg_flt * temp = new mg_flt(
					(double)((mg_int *)value)->value
				);
				delete value;
				value = (mg_obj *) temp;
			} else if (type != value->type) {
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
		if (!declared(id)) {
			cerr << "ERROR: assignment to uninitialized identifier" << endl;
			exit(EXIT_FAILURE);
		}
		mg_obj * value = eval_expr(n->children[1]);
		int type = vars[id]->type;
		if (type == TYPE_FLOAT && value->type == TYPE_INTEGER) {
				mg_flt * temp = new mg_flt(
					(double)((mg_int *)value)->value
				);
				delete value;
				value = (mg_obj *) temp;
		} else if (type != value->type) {
			cerr << "ERROR: TYPE MISMATCH" << endl;
			exit(EXIT_FAILURE);
		}
		vars[id] = value;
	}
}

// given a CASE node, it's option mg_obj and option type this function will
// evaluate whether option == case and if so will execute the statements
// within the scope of that case
// returns false if a break statement is reached
// returns true otherwise
// raises a type mismatch error if option and case don't match
bool eval_case(struct node * n, mg_obj * option, int option_type) {
	mg_obj * c = eval_expr(n->children[0]);
	if (c->type != option_type) {
		cerr << "ERROR: case type and option type do not match" << endl;
		exit(EXIT_FAILURE);
	}
	
	mg_int * i_option, * i_c;
	mg_flt * d_option, * d_c;
	mg_str * s_option, * s_c;
	bool match = false;
	
	switch (option_type) {
		
		case TYPE_INTEGER:
			i_option = (mg_int *) option;
			i_c = (mg_int *) c;
			if (i_c->value == i_option->value) {
				match = true;
			}
			break;
		case TYPE_FLOAT:
			d_option = (mg_flt *) option;
			d_c = (mg_flt *) c;
			if (d_c->value == d_option->value) {
				match = true;
			}
			break;
		case TYPE_STRING:
			s_option = (mg_str *) option;
			s_c = (mg_str *) c;
			if (s_c->value == s_option->value) {
				match = true;
			}
			break;
	}
	if (match) {
		struct node * stmts = n->children[1];
			try {
				eval_stmt(stmts);
			} catch (break_except &e) {
				return false;
			}
	}
	return true;
}

// given an OPTION node this function will
// evaluate all case statements within it's scope
// until a break statement is reached
// or until the cases are exhausted
void eval_option(struct node * n) {
	mg_obj * option = eval_expr(n->children[0]);
	struct node * current = n->children[1];
	struct node * previous = NULL;
	bool unbroken;
	do {
		unbroken = eval_case(current, option, option->type);
		previous = current;
		if (current->num_children == 3) {
			current = current->children[2];
		}
	} while (unbroken && current != previous);
}

void eval_stmt(struct node * node) {
	mg_obj * to_print;

	switch (node->token) {
		case ASSIGN:
			assign(node);
			break;
		case WHILE_LOOP:
			while (eval_bool(eval_expr(node->children[0]))) {
				try {
					eval_stmt(node->children[1]);
				} catch (break_except &e) {
					break;
				}
			}
			break;
		case IF:
			if (eval_bool(eval_expr(node->children[0]))) {
				eval_stmt(node->children[1]);
			} else if (node->num_children == 3) {
				eval_stmt(node->children[2]);
			}
			break;
		case OPTION:
			eval_option(node);
			break;
		case STATEMENT:
			for (int i = 0; i < node->num_children; i++) {
				eval_stmt(node->children[i]);
			}
			break;
		
		case PRINT:
			to_print = eval_expr(node->children[0]);
			switch (to_print->type) {
				case TYPE_INTEGER:
					cout << ((mg_int *)to_print)->value << endl;
					break;
				case TYPE_FLOAT:
					cout << ((mg_flt *)to_print)->value << endl;
					break;
				case TYPE_STRING:
					cout << ((mg_str *)to_print)->value << endl;
					break;
			}
			break;
		case BREAK:
			throw break_except();
			break;
		case NEXT:
			throw next_except();
			break;
	}
}
