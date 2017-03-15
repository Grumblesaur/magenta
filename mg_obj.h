#ifndef MG_OBJECT
#define MG_OBJECT

#include <map>
#include <string>
#include "tree.h"
#include "parser.tab.h"


template<typename T> 
class mg_obj {
	public:
		mg_obj(int type);
		mg_obj(int type, T value);
		~mg_obj();
		
		int type;
		bool set;
		T value;
};

#endif
