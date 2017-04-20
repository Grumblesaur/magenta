#ifndef MG_OPS
#define MG_OPS

#include "mg_types.h"

using std::string;

mg_obj * element_of(mg_obj *, mg_obj *);
mg_obj * list_index(mg_list *, mg_int *);
mg_obj * str_index(mg_str *, mg_int *);
mg_obj * power(mg_obj * , mg_obj * );
mg_obj * logarithm(mg_obj * , mg_obj * );
mg_obj * multiply(mg_obj * , mg_obj * );
mg_obj * divide(mg_obj * , mg_obj * );
mg_obj * int_divide(mg_obj * , mg_obj * );
mg_obj * mod(mg_obj * , mg_obj * );
mg_obj * add(mg_obj * , mg_obj * );
mg_obj * subtract(mg_obj * , mg_obj * );
mg_obj * eval_logical(mg_obj * , int , mg_obj * );
mg_obj * eval_comp(mg_obj * , int , mg_obj * );
mg_obj * eval_bitwise(mg_obj * , int , mg_obj * );
bool eval_bool(mg_obj * o);


#endif
