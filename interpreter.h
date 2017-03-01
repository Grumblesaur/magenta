#ifndef INTERP_H
#define INTERP_H

#include "tree.h"
#include "mg_obj.h"

#ifdef __cplusplus
extern "C" {
	mg_obj* eval_expr(struct node* node);
	void eval_stmt(struct node* node);
	void print_vars();
};
#endif

#endif