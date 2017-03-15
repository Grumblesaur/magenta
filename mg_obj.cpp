#ifndef MG_OBJ_CPP
#define MG_OBJ_CPP

#include <string>
#include <map>
#include <iostream>
#include "mg_obj.h"
#include "tree.h"
#define DEBUG 0

using std::string;


template<typename T>
mg_obj::mg_obj(int type, T value) {
	this->type = type;
	this->set = true;
	this->value = value;
}

mg_obj::~mg_obj(void) {
	// if (DEBUG) std::cout << "destructed: " << value << std::endl;
}

#endif