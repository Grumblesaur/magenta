#ifndef TREE_H
#define TREE_H

#ifdef __cplusplus
extern "C" {

	#define MAX_CHILDREN 3
	
	struct node {
		int token;
		char* value;
		int num_children;
		struct node* children[MAX_CHILDREN];
	};


	struct node* make_node(int token, char* value);

	void attach(struct node* parent, struct node* child);

	void print(struct node* node, int tabs);
};

#endif
#endif
