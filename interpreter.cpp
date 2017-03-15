#include <unordered_map>
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

std::unordered_map<string, mg_obj> vars;

// returns whether id is an initialized variable name
bool declared(string id) {
	std::unordered_map<string, mg_obj>::const_iterator iter =
		vars.find(id);
	return iter != vars.end();
}


mg_obj eval_expr(struct node * node) {
	
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
			cerr << "ERROR: IDENTIFIER CANNOT BE INITIALIZED MORE THAN ONCE." << endl;
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
