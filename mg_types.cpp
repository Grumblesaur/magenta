#include <unordered_map>
#include <ostream>
#include <string>
#include "mg_types.h"
#include "tree.h"
#include "parser.tab.h"

mg_obj::~mg_obj() {

}

mg_flt::mg_flt(double value) {
	this->type = TYPE_FLOAT;
	this->value = value;
}

mg_flt::~mg_flt() {
	
}

mg_int::mg_int(int value) {
	this->type = TYPE_INTEGER;
	this->value = value;
}

mg_int::~mg_int() {
	
}

mg_str::mg_str(char * value) {
	this->type = TYPE_STRING;
	this->value = std::string(value);
}

mg_str::mg_str(std::string value) {
	this->type = TYPE_STRING;
	this->value = value;
}

mg_str::~mg_str() {
	
}

mg_func::mg_func(struct node * start) {
	bool has_args = false;
	this->type = TYPE_FUNCTION;
	this->value = start->children[start->num_children-1];
	this->return_type = (
		start->num_children == 4 
			? has_args = true, start->children[2]->token
			: start->children[1]->token
		);
	this->locals = std::unordered_map<std::string, mg_obj *>();

	struct node * n = start->children[1];
	while (n->token == PARAM) {
		arg_count++;
		n = n->children[n->num_children-1];
	}
}

mg_func::~mg_func() {
	
}

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
			os << "function object at " << &obj;
			break;
		default:
			os << obj.type << " : " << &obj;
			break;
	}
	return os;
}

