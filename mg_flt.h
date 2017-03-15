#ifndef MG_FLT_H
#define MG_FLT_H

#include "mg_obj.h"

class mg_flt : public mg_obj {
	public:
		mg_flt(void * value);
		~mg_flt();
		double value;
};
#endif
