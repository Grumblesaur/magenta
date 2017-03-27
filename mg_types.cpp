#include <iostream>
#include <string>
#include "mg_types.h"
#include "parser.tab.h"

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

void mg_delete(mg_obj * ptr) {
	if (!ptr) return; // bail out if nullptr
	switch (ptr->type) {
		case TYPE_INTEGER:
			delete (mg_int *) ptr;
			break;
		case TYPE_FLOAT:
			delete (mg_flt *) ptr;
			break;
		case TYPE_STRING:
			delete (mg_str *) ptr;
			break;
		default:
			std::cerr << "deleting unknown object type at " << ptr << std::endl;
			delete ptr;
	}
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
		default:
			os << &obj;
			break;
	}
	return os;
}

