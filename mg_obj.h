#ifndef MG_OBJECT
#define MG_OBJECT
#include <map>
#include <string>
#include "tree.h"

#define FUNC 0
#define METH 1
#define INT  2
#define STR  3
#define FLT  4
#define TYPE 5

typedef int obj_type;

#ifdef __cplusplus
extern "C" {

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
};
#endif

#endif
