#include "mg_int.h"
#include "mg_obj.h"

mg_flt::mg_flt(int type, void * value) {
	this->type = type;
	this->value = *(double *)value;
	this->set = true;
}
