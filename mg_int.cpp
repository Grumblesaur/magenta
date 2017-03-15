#include "mg_int.h"
#include "mg_obj.h"
#include "parser.tab.h"

mg_int::mg_int(void * value) {
	this->type = TYPE_INTEGER;
	this->value = *(int *)value;
}

mg_int::~mg_int() {
	
}