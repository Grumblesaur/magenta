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
		mg_flt(void);
		mg_flt(double);
		mg_flt(const mg_flt &);
		~mg_flt();
		double value;
};

class mg_int : public mg_obj {
	public:
		mg_int(void);
		mg_int(int value);
		mg_int(const mg_int &);
		~mg_int();
		int value;
};

class mg_str : public mg_obj {
	public:
		mg_str(void);
		mg_str(char *);
		mg_str(const mg_str &);
		mg_str(std::string);
		~mg_str();
		string value;
};

class mg_list : public mg_obj {
	public:
		mg_list(std::vector<mg_obj *>);
		mg_list(const mg_list &);
		mg_list();
		~mg_list();
		std::vector<mg_obj *> value;
};

class mg_func : public mg_obj {
	public:
		mg_func(struct node *, std::unordered_map<string, int> &);
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
		mg_type(struct node *, int, std::unordered_map<string, int> &);
		~mg_type();
		std::vector<string> field_names;
		std::vector<int> field_types;
		int magenta_type;
};

class mg_instance : public mg_obj {
	public:
		mg_instance(mg_type * type_def, std::vector<mg_obj *> * args);
		mg_instance(int type, std::unordered_map<string, mg_obj *> u);
		~mg_instance();
		int magenta_type;
		std::unordered_map< string, mg_obj *> fields;
};

class mg_nil : public mg_obj { 
	public:
		mg_nil();
		~mg_nil();
};

std::ostream & operator<<(std::ostream &, const mg_obj &);
std::ostream & operator<<(std::ostream &, const mg_list &);
#endif
