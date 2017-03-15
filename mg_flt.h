#ifndef MG_INT_H
#define MG_INT_H

class mg_flt : public mg_obj {
	public:
		mg_flt(void * value);
		~mg_flt();
		double value;
};
#endif
