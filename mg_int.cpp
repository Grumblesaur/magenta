#include "mg_int.h"
#include "mg_obj.h"

mg_int::mg_int(int type, void * value) {
	this->type = type;
	this->value = *(int *)value;
	this->set = true;
}
