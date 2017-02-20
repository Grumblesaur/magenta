#include <iostream>
#include "tree.h"

node* make_node(int token, mg_obj* value) {

	node* n = new node;
	n->token = token;
	n->value = value;
	n->num_children = 0;
	for (int i = 0; i <= MAX_CHILDREN; i++) {
		n->children[i] = NULL;
	}
	return n;
}

void attach(node* parent, node* child) {

	parent->children[parent->num_children] = child;
	parent->num_children++;
}

void print(node* node, int tabs) {
	if(!node) return;

	/* print leading tabs */
	for(int i = 0; i < tabs; i++) {
		std::cout << "\t";
 	}
}