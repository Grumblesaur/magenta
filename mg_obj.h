#ifndef MG_OBJECT_H
#define MG_OBJECT_H

#include <map>
#include <string>
#include "tree.h"
#include "parser.tab.h"
#include "v_wrapper.h"


class mg_obj {
	public:
	
		mg_obj(int type);

		template <typename T>
		mg_obj(int type, T value);

		~mg_obj();
		
		int type;
		bool set;

		template <typename T>
		virtual T value( ) = 0;
};

#include "mg_obj.cpp"
#endif
