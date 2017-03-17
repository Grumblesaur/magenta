#include "mg_flt.h"
#include "mg_obj.h"
#include "parser.tab.h"

mg_flt::mg_flt(double value) {
	this->type = TYPE_FLOAT;
	this->value = value;
}

mg_flt::~mg_flt() {
	
}