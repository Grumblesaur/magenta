#include <unordered_map>
#include <iostream>
#include <string>
#include <cstring>
#include "interpreter.h"
#include "parser.tab.h"
#include "tree.h"
#include "mg_obj.h"

template <typename T>
std::unordered_map<std::string, mg_obj<T>> vars;


template <typename T>
mg_obj<T> eval_expr(struct node * node) {

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