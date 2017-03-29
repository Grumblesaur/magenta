#ifndef MG_TYPES
#define MG_TYPES

#include <ostream>
#include <string>
#include "tree.h"

class mg_obj {
	public:
		int type;
		virtual ~mg_obj();
};

class mg_flt : public mg_obj {
	public:
		mg_flt(double value);
		~mg_flt();
		double value;
};

class mg_int : public mg_obj {
	public:
		mg_int(int value);
		~mg_int();
		int value;
};

class mg_str : public mg_obj {
	public:
		mg_str(char * value);
		mg_str(std::string value);
		~mg_str();
		std::string value;
};

class mg_func : public mg_obj {
	public:
		mg_func(struct node * start);
		~mg_func();
		node * value;
};

std::ostream & operator<<(std::ostream &, const mg_obj &);

#endif
