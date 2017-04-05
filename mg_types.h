#ifndef MG_TYPES
#define MG_TYPES

#include <vector>
#include <unordered_map>
#include <ostream>
#include <string>
#include "tree.h"

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
		mg_str(std::string value);
		~mg_str();
		std::string value;
};

class mg_func : public mg_obj {
	public:
		mg_func(struct node * start);
		~mg_func();
		// a pointer to a subtree of the syntax tree where the code for the
		// function is stored
		node * value;
		
		// a map of identifiers to objects holding the arguments and local
		// variables for the function, to be populated when called and
		// emptied on function return
		// flag that indicates the return type of a function for determining
		// what subclass of mg_obj * to construct as the return value
		int return_type;
		std::vector<std::string> param_names;
		std::vector<int> param_types;


};

std::ostream & operator<<(std::ostream &, const mg_obj &);

#endif
