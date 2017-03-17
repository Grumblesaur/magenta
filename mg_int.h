#ifndef MG_INT_H
#define MG_INT_H

#include "mg_obj.h"

class mg_int : public mg_obj{
	public:
		mg_int(int value);
		~mg_int();
		int value;
};
#endif
