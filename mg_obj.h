#ifndef MG_OBJECT
#define MG_OBJECT

#include <map>
#include <string>
#include "tree.h"

#define FUNC 1000
#define METH 1001
#define INT  1002
#define STR  1003
#define FLT  1004
#define TYPE 1005

typedef int obj_type;

struct mg_obj {
	void * value;
	obj_type type;
};

struct mg_format {
	std::string name_of_type;
	std::map<std::string, struct mg_obj *> data;
};

struct mg_obj * mg_alloc(obj_type, void *, std::string);
struct mg_format * mg_alloc_type(std::string, struct mg_format);

#endif
