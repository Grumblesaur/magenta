#ifndef MG_INT_H
#define MG_INT_H

class mg_flt : public mg_obj{
	public:
		mg_int(int type, void * value);
		~mg_int();
		double value;
};
#endif
