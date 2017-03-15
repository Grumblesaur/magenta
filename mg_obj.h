#ifndef MG_OBJECT_H
#define MG_OBJECT_H

#include <map>
#include <string>
#include "tree.h"
#include "parser.tab.h"


template<typename T> 
class mg_obj {
	public:
		mg_obj<T>(int type);
		mg_obj<T>(int type, T value);
		~mg_obj();
		
		int type;
		bool set;
		T value;
};
#include "mg_obj.cpp"
#endif
