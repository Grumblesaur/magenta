#include <unordered_map>
#include <iterator>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <climits>
#include "interpreter.h"
#include "parser.tab.h"
#include "tree.h"
#include "mg_types.h"
#include "mg_ops.h"
#include "except.h"

using std::string;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;

mg_obj * eval_expr(struct node * node);

// mg_objs need to be cast to their appropriate subclasses to access value
// we need to use pointers for this.
// e.g. map<string, mg_obj *> 
// 		mg_obj * o;
// 		if (mg_obj->type == TYPE_INTEGER) {
// 			int value = ((mg_int *)o)->value;
// 		}
// you can't access value from mg_obj because it doesn't have that field
// you can't directly cast mg_obj to any of its subclasses,
// but you can cast pointers

/* This contains a mapping of <identifier name : value> for variables */
std::unordered_map<string, mg_obj *> vars;

// returns whether id is an initialized variable name
bool declared(string id) {
	std::unordered_map<string, mg_obj *>
		::const_iterator iter = vars.find(id);
	return iter != vars.end();
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
		string id;
		bool has_index = false;
		int index = 0;
		if (n->children[0]->token == BRACKET_OPEN) {
			id = string((char *)(n->children[0]->children[0]->value));
			mg_obj * temp = eval_expr(n->children[0]->children[1]);
			index = ((mg_int *)temp)->value;
			delete temp;
		} else {
			id = string((char *)n->children[0]->value);
		}
		if (!declared(id)) {
			cerr << "ERROR: assignment to uninitialized identifier" << endl;
			exit(EXIT_FAILURE);
		}
		mg_obj * value = eval_expr(n->children[1]);
		int type = vars[id]->type;
		if (type != TYPE_STRING && has_index) {
			cerr << "ERROR: assignment to index of non-indexed data type";
			cerr << endl;
			exit(EXIT_FAILURE);
		} else if (has_index) {
			string replacement = ((mg_str *)value)->value;
			string original = ((mg_str*)vars[id])->value;
			original.replace(index, index + 1, replacement);
			delete value;
			cout << original << endl;
			value = (mg_obj *) new mg_str(original);
		} else if (type == TYPE_FLOAT && value->type == TYPE_INTEGER) {
				mg_flt * temp = new mg_flt(
					(double)((mg_int *)value)->value
				);
				delete value;
				value = (mg_obj *) temp;
		} else if (type != value->type) {
			cerr << "ERROR: TYPE MISMATCH" << endl;
			exit(EXIT_FAILURE);
		}
		delete vars[id];
		vars[id] = value;
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
		case LOG_XOR:
		case LOG_AND:
		case LOG_IMPLIES:
			return eval_logical(
				eval_expr(node->children[0]),
				node->token,
				eval_expr(node->children[1])
			);
			
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
		
		case INT_DIVIDE:
			return int_divide(
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
	int children = node->num_children;
	bool next = false;
	switch (node->token) {
		case ASSIGN:
			assign(node);
			break;
		case WHILE_LOOP: {
			while (eval_bool(eval_expr(node->children[0]))) {
				try {
					if (next) {
						next = false;
						continue;
					}
					eval_stmt(node->children[1]);
				} catch (break_except &e) {
					break;
				} catch (next_except &e) {
					next = true;
				}
			}
		} break;
		
		case FOR_LOOP: {
			int from = 0, to = INT_MAX, by = 1, ch_token = 0;
			mg_int * ptr;
			string iter_name;
			struct node * child;
			// handle variable arrangements of by/from/to clauses
			for (int x = 0; x < children; x++) {
				child = node->children[x];
				ch_token = child->token;
				if (ch_token == IDENTIFIER) {
					iter_name = string((char *) child->value);
					vars[iter_name] = new mg_int(0);
				} else {
					ptr = ((mg_int *)eval_expr(child->children[0]));
					int error = 0;
					(ch_token == FROM ? from
						: ch_token == TO ? to
						: ch_token == BY ? by
						: error
					) = ptr->value;
				}
			}
			// if there was a from clause, start the loop var from there
			vars[iter_name] = (mg_obj *) new mg_int(from ? from : 0);
			
			// loop from `from` to `to` - 1 by `by`
			if (from < to) {
				for(int i = from; i < to; i += by) {
					((mg_int *)vars[iter_name])->value = i;
					try {
						if (next) {
							next = false;
							continue;
						}
						eval_stmt(node->children[children - 1]);
					} catch (break_except &e) {
						break;
					} catch (next_except &e) {
						next = true;
					}
				}
			} else if (from > to) {
				for (int i = from; i > to; i -= by) {
					((mg_int *)vars[iter_name])->value = i;
					try {
						if (next) {
							next = false;
							continue;
						}
						eval_stmt(node->children[children - 1]);
					} catch (break_except &e) {
						break;
					} catch (next_except &e) {
						break;
					}
				}
			}
			// remove temporary loop variable from scope
			delete vars[iter_name];
			vars.erase(iter_name);
		} break;
		
		case IF:
			if (eval_bool(eval_expr(node->children[0]))) {
				eval_stmt(node->children[1]);
			} else if (children == 3) {
				eval_stmt(node->children[2]);
			}
			break;
		case OPTION:
			eval_option(node);
			break;
		case STATEMENT:
			for (int i = 0; i < children; i++) {
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
