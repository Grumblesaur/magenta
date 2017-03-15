#include "mg_flt.h"
#include "mg_obj.h"
#include "parser.tab.h"

mg_flt::mg_flt(void * value) {
	this->type = type;
	this->value = *(double *)value;
}

mg_flt::~mg_flt() {
	
}