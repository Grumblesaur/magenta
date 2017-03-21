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
