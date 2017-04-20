#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <cassert>
#include <cstdlib>
#include "mg_types.h"
#include "tree.h"
#include "parser.tab.h"

extern unsigned linecount;

using std::cout;
using std::endl;

mg_obj::~mg_obj() {

}

/* floating point objects */

// primary constructor
mg_flt::mg_flt(double value) {
	this->type = TYPE_FLOAT;
	this->value = value;
}

// default constructor
mg_flt::mg_flt(void) {
	this->type = TYPE_FLOAT;
	this->value = 0.0;
}

// copy constructor
mg_flt::mg_flt(const mg_flt & rhs) {
	this->type = rhs.type;
	this->value = rhs.value;
}

// destructor
mg_flt::~mg_flt() {
	
}

/* integer objects */

// default constructor
mg_int::mg_int(void) {
	this->type = TYPE_INTEGER;
	this->value = 0;
}

// copy constructor
mg_int::mg_int(const mg_int & rhs) {
	this->type = rhs.type;
	this->value = rhs.value;
}

// primary constructor
mg_int::mg_int(int value) {
	this->type = TYPE_INTEGER;
	this->value = value;
}

// destructor
mg_int::~mg_int() {
	
}

/* string objects */

// default constructor
mg_str::mg_str(void) {
	this->type = TYPE_STRING;
	this->value = "";
}

// char constructor
mg_str::mg_str(char * value) {
	this->type = TYPE_STRING;
	this->value = std::string(value);
}

// string constructor
mg_str::mg_str(std::string value) {
	this->type = TYPE_STRING;
	this->value = value;
}

// copy constructor
mg_str::mg_str(const mg_str & rhs) {
	this->type = rhs.type;
	this->value = rhs.value;
}

// destructor
mg_str::~mg_str() {
	
}

/* function objects */

// primary constructor
mg_func::mg_func(
	struct node * start,
	std::unordered_map<string,
	int> &custom_types
) {
	this->type = TYPE_FUNCTION;
	this->value = start->children[start->num_children-1];
	this->return_type = (
		start->num_children == 4 
			? start->children[2]->token
			: start->children[1]->token
		);
	
	node * n = start->children[1];
	while (n->token == PARAM) {
	if (n->children[0]->token == IDENTIFIER) {
		string type_name = string((char*)n->children[0]->value);
		this->param_types.push_back(custom_types[type_name]);
	} else {
		this->param_types.push_back(n->children[0]->token);
	}		
	this->param_names.push_back(
			std::string((char*)n->children[1]->value)
		);
		n = n->children[n->num_children-1];
	}
}

mg_type::mg_type(
	struct node * node,
	int type,
	std::unordered_map<string,
	int> &custom_types
) {
	this->type = TYPE_TYPE;
	this->magenta_type = type;
	struct node * n = node->children[1];
	while (n->token == PARAM) {
		if (n->children[0]->token == IDENTIFIER) {
			string type_name = string((char*)n->children[0]->value);
			this->field_types.push_back(custom_types[type_name]);
		} else {
			this->field_types.push_back(n->children[0]->token);
		}
		this->field_names.push_back(
			std::string((char*)n->children[1]->value)
		);
		n = n->children[n->num_children-1];
	}
}

mg_type::~mg_type() {
	this->field_types.clear();
	this->field_names.clear();
}

mg_instance::mg_instance(mg_type * type_def, std::vector<mg_obj *> * args) {
	this->type = INSTANCE;
	this->magenta_type = type_def->magenta_type;
	for (int i = 0; i < args->size(); i++) {
		this->fields[type_def->field_names[i]] = args->at(i);
	}
	delete args;
}

mg_instance::mg_instance(
	int magenta_type,
	std::unordered_map<string, mg_obj *> u
) {
	this->type = INSTANCE;
	this->magenta_type = magenta_type;
	this->fields = u;
}

mg_instance::~mg_instance() {

}

mg_nil::mg_nil() {
	this->type = NIL;
}

mg_nil::~mg_nil() { }

// destructor
mg_func::~mg_func() {
}

/* list objects */

// primary constructor
mg_list::mg_list(std::vector<mg_obj *> objs) {
	this->type = TYPE_LIST;
	this->value = std::vector<mg_obj *>(objs);
}

// copy constructor
mg_list::mg_list(const mg_list & rhs) {
	this->type = rhs.type;
	this->value = std::vector<mg_obj *>(rhs.value.size());
	int itemtype;
	for (int i = 0; i < this->value.size(); i++) {
		itemtype = rhs.value[i]->type;
		switch (itemtype) {
			case TYPE_FUNCTION:
				this->value[i] = rhs.value[i];
				break;
			case TYPE_INTEGER:
				this->value[i] = new mg_int(*(mg_int *) rhs.value[i]);
				break;
			case TYPE_STRING:
				this->value[i] = new mg_str(*(mg_str *) rhs.value[i]);
				break;
			case TYPE_FLOAT:
				this->value[i] = new mg_flt(*(mg_flt *) rhs.value[i]);
				break;
			case TYPE_LIST:
				this->value[i] = new mg_list(*(mg_list *) rhs.value[i]);
				break;
		}
	}
}

// default constructor
mg_list::mg_list(void) {
	this->type = TYPE_LIST;
	this->value = std::vector<mg_obj *>();	
}

// destructor
mg_list::~mg_list(void) {
	for (auto it = value.begin(); it != value.end(); it++) {
		delete *it;
	}
}


std::ostream & operator<<(std::ostream & os, const mg_list & obj) {
	cout << "[";
	auto it = obj.value.begin();
	while (it != obj.value.end()) {
		cout << **it;
		if (it+1 != obj.value.end()) {
			cout << ", ";
		}
		it++;
	}
	cout << "]";
	return os;
}

// helper print function
std::ostream & operator<<(std::ostream & os, const mg_obj & obj) {

	switch (obj.type) {
		case TYPE_INTEGER:
			os << ((mg_int &)obj).value;
			break;
		case TYPE_STRING:
			os << ((mg_str &)obj).value;
			break;
		case TYPE_FLOAT:
			os << ((mg_flt &)obj).value;
			break;
		case TYPE_FUNCTION:
			os << "(function object at " << &obj << ")";
			break;
		case TYPE_TYPE:
			os << "type definition object at " << &obj;
			break;
		case INSTANCE:
			os << "instance object at " << &obj;
			break;
		case NIL:
			os << "nil";
			break;
		default:
			if (obj.type == TYPE_LIST) {
				os << * (mg_list *) &obj;
			} else {
				os << obj.type << " : " << &obj;
				os << " | HELP ME?";
			}
			break;
	}
	return os;
}

