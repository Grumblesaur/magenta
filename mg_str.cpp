#include <string>
#include "mg_str.h"
#include "mg_obj.h"
#include "parser.tab.h"

<<<<<<< HEAD
mg_str::mg_str(int type, void * value) {
	this->type = type;
	this->value = std::string((char *)value);
=======
mg_str::mg_str(void * value) {
	this->type = TYPE_STRING;
	this->value = *(std::string *)value;
>>>>>>> f5b1cd6c759c699bd1525374b8b9579757df1032
	this->set = true;
}
