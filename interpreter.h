#ifndef INTERP_H
#define INTERP_H

#include "tree.h"
#include "mg_types.h"

#ifdef __cplusplus
extern "C" {
	void eval_stmt(struct node* node);
};
#endif

#endif
