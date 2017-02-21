#ifndef TREE_H
#define TREE_H

#ifdef __cplusplus
extern "C" {

	#include "mg_obj.h"

	#define MAX_CHILDREN 3

	struct node {
		int token;
		mg_obj* value;
		int num_children;
		struct node* children[MAX_CHILDREN];
	};

	typedef struct node node;

	node* make_node(int token, mg_obj* value);

	void attach(node* parent, node* child);

	void print(node* node, int tabs);
};

#endif
#endif
