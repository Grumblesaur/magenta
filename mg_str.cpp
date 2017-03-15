#include <string>
#include "mg_str.h"
#include "mg_obj.h"

mg_str::mg_str(int type, void * value) {
	this->type = type;
	this->value = std::string((char *)value);
	this->set = true;
}
