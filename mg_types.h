#ifndef MG_TYPES
#define MG_TYPES

#include <string>

class mg_obj {
	public:
		int type;
};

class mg_flt : public mg_obj {
	public:
		mg_flt(double value);
		~mg_flt();
		double value;
};

class mg_int : public mg_obj{
	public:
		mg_int(int value);
		~mg_int();
		int value;
};

class mg_str : public mg_obj{
	public:
		mg_str(char * value);
		mg_str(std::string value);
		~mg_str();
		std::string value;
};

#endif
