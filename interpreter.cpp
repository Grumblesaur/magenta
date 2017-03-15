#include <unordered_map>
#include <iostream>
#include <string>
#include <cstring>
#include "interpreter.h"
#include "parser.tab.h"
#include "tree.h"
#include "mg_obj.h"
#include "v_wrapper.h"

using std::string; using std::cout; using std::endl;

std::unordered_map<string, mg_obj<v_wrapper>> vars;

template <typename T>
bool declared(string id) {
	std::unordered_map<string, mg_obj<v_wrapper>>::const_iterator iter =
		vars.find(id);
	return iter != vars.end();
}

using std::string;
using std::cout;
using std::endl;

template <typename T>
mg_obj<T> assign(struct node * n) {
	
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

template <typename T>
mg_obj<T> eval_expr(struct node * node) {
	bool t_val;
	mg_obj<T> left, right;

	switch (node->token) {
		case IDENTIFIER:
			return vars[string((char *)node->value)];
		case INTEGER_LITERAL:
			return mg_obj<int>(TYPE_INTEGER, *(int *)node->value);
		case FLOAT_LITERAL:
			return mg_obj<double>(TYPE_FLOAT, *(double *)node->value);
		case STRING_LITERAL:
			return mg_obj<string>(TYPE_STRING, string((char *)node->value);
		case PAREN_OPEN:
			return eval_expr(node->children[0]);
		case LOG_NOT:
			right = eval_expr(node->children[0]);
			t_val = !eval_bool(right);
			return mg_obj<int>(TYPE_INTEGER, new int(t_val));
		default:
			cout << "STILL WORKING ON IT" << endl;
	}
	return mg_obj<int>(TYPE_INTEGER);
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
