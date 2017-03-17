#include "mg_int.h"
#include "mg_obj.h"
#include "parser.tab.h"

mg_int::mg_int(int value) {
	this->type = TYPE_INTEGER;
	this->value = value;
}

mg_int::~mg_int() {
	
}