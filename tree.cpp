#include "tree.h"

node* make_node(int token, mg_obj* value, std::string id) {

	node* n = new node;
	n->token = token;
	n->value = value;
	n->id = id;
	n->num_children = 0;
	for (int i = 0; i <= MAX_CHILDREN; i++) {
		n->children[i] = NULL;
	}
	return n;
}

void attach_node(node* parent, node* child) {

	parent->children[parent->num_children] = child;
	parent->num_children++;
}