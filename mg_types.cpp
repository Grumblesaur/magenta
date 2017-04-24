#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <cassert>
#include <cstdlib>
#include "mg_types.h"
#include "tree.h"
#include "parser.tab.h"

extern unsigned linecount;

using std::cout;
using std::endl;

bool mg_obj::operator<=(const mg_obj & that) const {
	return *this < that || *this == that;
}

bool mg_obj::operator!=(const mg_obj & that) const {
	return !(*this == that);
}

bool mg_obj::operator>=(const mg_obj & that) const {
	return !(*this < that);
}

bool mg_obj::operator>(const mg_obj & that) const {
	return !(*this < that && *this == that);
}

bool mg_obj::operator<(const mg_obj & that) const {
	double fleft, fright;
	bool is_numeric =
		this->type == TYPE_INTEGER
		|| this->type == TYPE_FLOAT
		&& that.type == TYPE_INTEGER
		|| that.type == TYPE_FLOAT;
	
	if (!is_numeric && this->type < that.type) {
		return true;
	} else if (!is_numeric && this->type > that.type) {
		return false;
	} else switch (this->type) {
		case TYPE_FUNCTION:
			return ((mg_func *)this)->param_names.size()
				< ((mg_func *)&that)->param_names.size();
		case TYPE_STRING:
			return ((mg_str *)this)->value < ((mg_str *)&that)->value;
		case TYPE_INTEGER:
		case TYPE_FLOAT:
			fleft = this->type == TYPE_INTEGER
				? ((mg_int *)this)->value
				: ((mg_flt *)this)->value;
			fright = that.type == TYPE_INTEGER
				? ((mg_int *)&that)->value
				: ((mg_flt *)&that)->value;
			return fleft < fright;
		case TYPE_LIST: {
			unsigned llen = ((mg_list *)this)->value.size();
			unsigned rlen = ((mg_list *)&that)->value.size();
			if (llen < rlen)
				return true;
			else if (llen > rlen)
				return false;
			bool less = true;
			mg_obj * left, * right;
			for (int i = 0; i < rlen; i++) {
				left = ((mg_list *)this)->value[i];
				right = ((mg_list *)&that)->value[i];
				less = *left < *right;
				if (!less) return false;
			}
			
		} break;
	}
	return true;
}
	

bool mg_obj::operator==(const mg_obj & that) const {
	bool is_numeric =
		this->type == TYPE_INTEGER
		|| this->type == TYPE_FLOAT
		&& that.type == TYPE_INTEGER
		|| that.type == TYPE_FLOAT;
	
	if (!is_numeric && this->type != that.type) {
		return false;
	}
	double fleft, fright;
	switch (this->type) {
		case TYPE_FUNCTION:
			return this == &that;
		case TYPE_STRING:
			return ((mg_str *)this)->value == ((mg_str *)&that)->value;
		case TYPE_INTEGER:
		case TYPE_FLOAT: 
			fleft = this->type == TYPE_INTEGER
				? ((mg_int *)this)->value
				: ((mg_flt *)this)->value;
			fright = that.type == TYPE_INTEGER
				? ((mg_int *)&that)->value
				: ((mg_flt *)&that)->value;
			return fleft == fright;
		case TYPE_LIST: {
			unsigned llen = ((mg_list *)this)->value.size();
			unsigned rlen = ((mg_list *)&that)->value.size();
			if (llen != rlen) return false;
			bool matching = true;
			for (int i = 0; i < llen; i++) {
				matching = *(((mg_list *)this)->value[i])
					== *(((mg_list *)&that)->value[i]);
				if (!matching) return false;
			}
		} break;
	}
	return true;
}

mg_obj::~mg_obj() {

}

/* floating point objects */

// primary constructor
mg_flt::mg_flt(double value) {
	this->type = TYPE_FLOAT;
	this->value = value;
}

// default constructor
mg_flt::mg_flt(void) {
	this->type = TYPE_FLOAT;
	this->value = 0.0;
}

// copy constructor
mg_flt::mg_flt(const mg_flt & rhs) {
	this->type = rhs.type;
	this->value = rhs.value;
}

// destructor
mg_flt::~mg_flt() {
	
}

/* integer objects */

// default constructor
mg_int::mg_int(void) {
	this->type = TYPE_INTEGER;
	this->value = 0;
}

// copy constructor
mg_int::mg_int(const mg_int & rhs) {
	this->type = rhs.type;
	this->value = rhs.value;
}

// primary constructor
mg_int::mg_int(int value) {
	this->type = TYPE_INTEGER;
	this->value = value;
}

// destructor
mg_int::~mg_int() {
	
}

/* string objects */

// default constructor
mg_str::mg_str(void) {
	this->type = TYPE_STRING;
	this->value = "";
}

// char constructor
mg_str::mg_str(char * value) {
	this->type = TYPE_STRING;
	this->value = std::string(value);
}

// string constructor
mg_str::mg_str(std::string value) {
	this->type = TYPE_STRING;
	this->value = value;
}

// copy constructor
mg_str::mg_str(const mg_str & rhs) {
	this->type = rhs.type;
	this->value = rhs.value;
}

// destructor
mg_str::~mg_str() {
	
}

/* function objects */

// primary constructor
mg_func::mg_func(struct node * start) {
	this->type = TYPE_FUNCTION;
	this->value = start->children[start->num_children-1];
	this->return_type = (
		start->num_children == 4 
			? start->children[2]->token : start->children[1]->token
	);
	
	node * n = start->children[1];
	while (n->token == PARAM) {
		this->param_types.push_back(n->children[0]->token);
		this->param_names.push_back(
			std::string((char*)n->children[1]->value)
		);
		n = n->children[n->num_children-1];
	}
}

// destructor
mg_func::~mg_func() {
}

/* list objects */

// primary constructor
mg_list::mg_list(std::vector<mg_obj *> objs) {
	this->type = TYPE_LIST;
	this->value = std::vector<mg_obj *>(objs);
}

// copy constructor
mg_list::mg_list(const mg_list & rhs) {
	this->type = rhs.type;
	this->value = std::vector<mg_obj *>(rhs.value.size());
	int itemtype;
	for (int i = 0; i < this->value.size(); i++) {
		itemtype = rhs.value[i]->type;
		switch (itemtype) {
			case TYPE_FUNCTION:
				this->value[i] = rhs.value[i];
				break;
			case TYPE_INTEGER:
				this->value[i] = new mg_int(*(mg_int *) rhs.value[i]);
				break;
			case TYPE_STRING:
				this->value[i] = new mg_str(*(mg_str *) rhs.value[i]);
				break;
			case TYPE_FLOAT:
				this->value[i] = new mg_flt(*(mg_flt *) rhs.value[i]);
				break;
			case TYPE_LIST:
				this->value[i] = new mg_list(*(mg_list *) rhs.value[i]);
				break;
		}
	}
}

// default constructor
mg_list::mg_list(void) {
	this->type = TYPE_LIST;
	this->value = std::vector<mg_obj *>();	
}

// destructor
mg_list::~mg_list(void) {
	for (auto it = value.begin(); it != value.end(); it++) {
		delete *it;
	}
}

/* mg_list `<<` overload for boxing string elements neatly in '' */
std::ostream & operator<<(std::ostream & os, const mg_list & obj) {
	os << "[";
	auto it = obj.value.begin();
	while (it != obj.value.end()) {
		if ((**it).type == TYPE_STRING) {
			os << "'" << **it << "'";
		} else {
			os << **it;
		}
		if (it+1 != obj.value.end()) {
			os << ", ";
		}
		it++;
	}
	os << "]";
	return os;
}

/* Generic mg_obj `<<` overload */
std::ostream & operator<<(std::ostream & os, const mg_obj & obj) {
	switch (obj.type) {
		case TYPE_INTEGER:
			os << ((mg_int &)obj).value;
			break;
		case TYPE_STRING:
			os << ((mg_str &)obj).value;
			break;
		case TYPE_FLOAT:
			os << ((mg_flt &)obj).value;
			break;
		case TYPE_FUNCTION:
			os << "(function object at " << &obj << ")";
			break;
		case TYPE_LIST:
			os << * (mg_list *) &obj;
			break;
		default:
			os << "type = " << obj.type << "; value = " << &obj;
			break;
	}
	return os;
}

