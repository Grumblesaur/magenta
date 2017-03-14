// Write code for creating and destroying mg_objects
#include <string>
#include <map>
#include <iostream>
#include "mg_obj.h"
#include "tree.h"

using std::string;

struct mg_obj * mg_alloc(int type, void * value) {
	struct mg_obj * m = new struct mg_obj;
	switch (type) {
		case TYPE_FUNCTION:
			break;
		
		case TYPE_METHOD:
			break;
		
		case TYPE_INTEGER:
			m->type = TYPE_INTEGER;
			m->value = new int(*(int*)value);
			break;
		
		case TYPE_FLOAT:
			m->type = TYPE_FLOAT;
			m->value = new double(*(double*)value);
			break;
		
		case TYPE_STRING:
			m->type = TYPE_STRING;
			m->value = new std::string((char*)value);
			break;
	}
	return m;
}

// Allocate memory for a user-defined type instance using the name of the
// type, the names of each member of an instance of this type, and the
// values corresponding to each member.
// member_count must be passed in because detecting length of arrays of
// user-defined structs is impossible.
struct mg_format * mg_alloc_type(
	std::string name_of_type,
	std::string members[],
	int member_count,
	struct mg_obj values[]
) {
	struct mg_format * m = new struct mg_format;
	m->name_of_type = name_of_type;
	
	mg_obj * x;
	for (int i = 0; i < member_count; i++) {
		x = new mg_obj;
		*x = values[i];
		m->data[members[i]] = x;
	}
	return m;
}
