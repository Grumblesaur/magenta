#ifndef MG_OPS
#define MG_OPS

#include "mg_types.h"

using std::string;

mg_obj * list_index(mg_list *, mg_int *);
mg_obj * str_index(mg_str *, mg_int *);
mg_obj * power(mg_obj * left, mg_obj * right);
mg_obj * logarithm(mg_obj * left, mg_obj * right);
mg_obj * multiply(mg_obj * left, mg_obj * right);
mg_obj * divide(mg_obj * left, mg_obj * right);
mg_obj * int_divide(mg_obj * left, mg_obj * right);
mg_obj * mod(mg_obj * left, mg_obj * right);
mg_obj * add(mg_obj * left, mg_obj * right);
mg_obj * subtract(mg_obj * left, mg_obj * right);
mg_obj * eval_logical(mg_obj * left, int token, mg_obj * right);
mg_obj * eval_comp(mg_obj * left, int op, mg_obj * right);
mg_obj * eval_bitwise(mg_obj * left, int token, mg_obj * right);
bool eval_bool(mg_obj * o);


#endif
