#include <unordered_map>
#include <iostream>
#include <string>
#include "interpreter.h"
#include "parser.tab.h"
#include "tree.h"
#include "mg_obj.h"


std::unordered_map<std::string, mg_obj*> vars;


void printVars() {
	// std::cout << "VARIABLES" << std::endl;
	// std::unordered_map<std::string, double>::iterator it;
	// for(it = vars.begin(); it != vars.end(); it++) {
	// 	std::cout << it->first << "  " << it->second << std::endl;
	// }
}


void eval_stmt(struct node* node) {

	switch (node->token) {
		
	}
}


double eval_expr(struct node* node) {

	switch (node->token) {

	}
}