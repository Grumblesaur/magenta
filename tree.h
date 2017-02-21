#ifndef TREE_H
#define TREE_H

#ifdef __cplusplus
extern "C" {

	#define MAX_CHILDREN 3
	
	#include "mg_obj.h"

	struct node {
		int token;
		struct mg_obj* value;
		int num_children;
		struct node* children[MAX_CHILDREN];
	};


	struct node* make_node(int token, struct mg_obj* value);

	void attach(struct node* parent, struct node* child);

	void print(struct node* node, int tabs);
};

#endif
#endif
