#include "mg_int.h"
#include "mg_obj.h"

mg_str::mg_str(int type, void * value) {
	this->type = type;
	this->value = *(std::string *)value;
	this->set = true;
}
