#ifndef TREE_H
#define TREE_H

#include <string>

#ifdef __cplusplus
extern "C" {

	#define MAX_CHILDREN 3
	#define MAX_ID_LEN 64
	
	struct node {
		int token;
		// char value[MAX_ID_LEN];
		void * value;
		int num_children;
		struct node* children[MAX_CHILDREN];
	};

	struct node* make_node(int token, void* value);
	void attach(struct node* parent, struct node* child);
	void print(struct node* node, int tabs);
};

#endif
#endif
