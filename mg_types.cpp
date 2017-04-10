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
	this->type = TYPE_FUNCTION;
	this->value = start->children[start->num_children-1];
	this->return_type = (
		start->num_children == 4 
			? start->children[2]->token
			: start->children[1]->token
		);
	
	node * n = start->children[1];
	while (n->token == PARAM) {
		this->param_types.push_back(n->children[0]->token);
		this->param_names.push_back(
			std::string((char*)n->children[1]->value)
		);
		n = n->children[n->num_children-1];
	}
}

mg_func::~mg_func() {
}

mg_type::mg_type(struct node * node) {
	this->type = TYPE_TYPE;
	struct node * n = node->children[1];
	while (n->token == PARAM) {
		this->field_types.push_back(n->children[0]->token);
		this->field_names.push_back(
			std::string((char*)n->children[1]->value)
		);
		n = n->children[n->num_children-1];
	}
}

mg_type::~mg_type() {

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

