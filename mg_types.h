#ifndef MG_TYPES
#define MG_TYPES

#include <vector>
#include <unordered_map>
#include <ostream>
#include <string>
#include "tree.h"

using std::string;

class mg_obj {
	public:
		int type;
		virtual ~mg_obj();
};

class mg_flt : public mg_obj {
	public:
		mg_flt(double value);
		~mg_flt();
		double value;
};

class mg_int : public mg_obj {
	public:
		mg_int(int value);
		~mg_int();
		int value;
};

class mg_str : public mg_obj {
	public:
		mg_str(char * value);
		mg_str(string value);
		~mg_str();
		string value;
};

class mg_func : public mg_obj {
	public:
		mg_func(struct node * start);
		~mg_func();

		// a pointer to a subtree of the syntax tree where the code for the
		// function is stored
		node * value;

		// flag that indicates the return type of a function for determining
		// what subclass of mg_obj * to construct as the return value
		int return_type;
		std::vector<string> param_names;
		std::vector<int> param_types;
};

class mg_type : public mg_obj {
	public:
		mg_type(struct node * node, int type);
		~mg_type();
		std::vector<string> field_names;
		std::vector<int> field_types;
		int magenta_type;
};

class mg_instance : public mg_obj {
	public:
		mg_instance(mg_type * type_def, std::vector<mg_obj *> * args);
		mg_instance(std::unordered_map<string, mg_obj *> u);
		~mg_instance();
		int magenta_type;
		std::unordered_map< string, mg_obj *> fields;
};

std::ostream & operator<<(std::ostream &, const mg_obj &);

#endif
