#ifndef MG_OBJECT
#define MG_OBJECT
#include <map>
#include <string>
#include "tree.h"

enum obj_type {
	FUNC, // 0
	METH, // 1
	INT,  // 2
	STR,  // 3
	FLT,  // 4
	TYPE  // 5
};

struct mg_obj {
	void * value;
	obj_type type;
};

struct mg_format {
	std::string name_of_type;
	std::map<std::string, mg_obj *> data;
};

typedef struct mg_obj mg_obj;
typedef struct mg_format mg_format;

mg_obj * mg_alloc_int(int);
mg_obj * mg_alloc_flt(double);
mg_obj * mg_alloc_str(std::string);
mg_obj * mg_alloc_func(node *);
mg_obj * mg_alloc_meth(node *);
mg_obj * mg_alloc_type(std::string, mg_format);

#endif
