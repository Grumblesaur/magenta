#ifndef MG_INT_H
#define MG_INT_H

class mg_int : public mg_obj {
	public:
		mg_int(void * value);
		~mg_int();
		int value;
};
#endif
