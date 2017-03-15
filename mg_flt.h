#ifndef MG_INT_H
#define MG_INT_H
#include "mg_obj.h"
class mg_flt : public mg_obj {
	public:
		mg_flt(void * value);
		~mg_flt();
		double value;
};
#endif
