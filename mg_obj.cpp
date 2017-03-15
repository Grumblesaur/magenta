#ifndef MG_OBJ_CPP
#define MG_OBJ_CPP

#include <string>
#include <map>
#include <iostream>
#include "mg_obj.h"
#include "tree.h"
#define DEBUG 0

using std::string;

class mg_obj {
	public:
		mg_obj(int type);
		mg_obj(int type, T value);
		~mg_obj();
		
		int type;
		bool set;
		virtual value( ) = 0;
}

#endif
