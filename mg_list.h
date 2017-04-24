#ifndef MG_LIST_H
#define MG_LIST_H

mg_list * combine(const mg_list * left, const mg_list * right);
mg_list * repeat(const mg_list * left, const mg_int * right);
mg_list * remove(const mg_list * left, const mg_obj * right);

#endif
