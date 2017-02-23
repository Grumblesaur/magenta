#ifndef MG_OBJECT
#define MG_OBJECT

#include <map>
#include <string>
#include "tree.h"
#include "parser.tab.h"


struct mg_obj {
	void * value;
	int type;
};

struct mg_format {
	std::string name_of_type;
	std::map<std::string, struct mg_obj *> data;
};

struct mg_obj * mg_alloc(int, void *, std::string);
struct mg_format * mg_alloc_type(std::string, struct mg_format);

#endif
