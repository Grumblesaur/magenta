#include <unordered_map>
#include <iostream>
#include <string>
#include <cstring>
#include "interpreter.h"
#include "parser.tab.h"
#include "tree.h"
#include "mg_obj.h"
#include "mg_int.h"
#include "mg_flt.h"
#include "mg_str.h"

using std::string; using std::cout; using std::endl;

std::unordered_map<string, mg_obj> vars;

bool declared(string id) {
	std::unordered_map<string, mg_obj>::const_iterator iter =
		vars.find(id);
	return iter != vars.end();
}

using std::string;
using std::cout;
using std::endl;

mg_obj assign(struct node * n) {
	
	//assignment 
	if (n->num_children == 3) {
		string id = string((char *)n->children[0]->value);

	} else {

		// reassignment
		if (n->children[0]->token == IDENTIFIER) {


		// initialization
		} else {

		}
	}
}

mg_obj eval_expr(struct node * node) {
	
}


void eval_stmt(struct node * node) {

	switch (node->token) {
		case ASSIGN:
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
