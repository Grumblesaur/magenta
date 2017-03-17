#include <string>
#include "mg_str.h"
#include "mg_obj.h"
#include "parser.tab.h"

mg_str::mg_str(char * value) {
	this->type = TYPE_STRING;
	this->value = std::string(value);
}

mg_str::~mg_str() {
	
}