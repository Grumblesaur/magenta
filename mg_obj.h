#ifndef MG_OBJECT_H
#define MG_OBJECT_H

#include <map>
#include <string>
#include "tree.h"
#include "parser.tab.h"


class mg_obj {
	public:
		
		int type;
		bool set;
};

#include "mg_obj.cpp"
#endif
