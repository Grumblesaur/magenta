#ifndef INTERP_H
#define INTERP_H

#include "tree.h"

#ifdef __cplusplus
extern "C" {
	double eval_expr(struct node* node);
	void eval_stmt(struct node* node);
	void printVars();
};
#endif

#endif