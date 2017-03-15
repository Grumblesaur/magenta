#ifndef MG_STR_H
#define MG_STR_H

#include <string>
#include "mg_obj.h"

class mg_str : public mg_obj{
	public:
		mg_str(void * value);
		~mg_str();
		std::string value;
};
#endif
