// Write code for creating and destroying mg_objects
#include <string>
#include <map>
#include <iostream>
#include "mg_obj.h"
#include "tree.h"

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
			m->value = new std::string(*(std::string*)value);
			break;
	}
	return m;
}

// Allocate memory for a user-defined type instance using the name of the
// type, the names of each member of an instance of this type, and the
// values corresponding to each member.
struct mg_format * mg_alloc_type(
	std::string name_of_type,
	std::string members[],
	struct mg_obj values[]
) {
	struct mg_format * m = new struct mg_format;
	m->name_of_type = name_of_type;

	size_t members_size = sizeof(members) / sizeof(members[0]);
	size_t values_size = sizeof(values) / sizeof(values[0]);
	
	// If we pass in more values than we have members (by some error in
	// writing the interpreter), this will give us an error to check for.
	if (values_size > members_size) {
		std::cerr << "Bad alloc of type `" << name_of_type << "`:\n";
		std::cerr << "\t more values supplied than member fields to fill!";
		std::cerr << std::endl;
		delete m;
		return NULL;
	}
	struct mg_obj * x;
	for (int i = 0; i < members_size; i++) {
		// fields can be left uninitialized
		// TODO: ensure that each unclarified member gets its default value
		if (i >= values_size) {
			m->data[members[i]] = NULL;
		} else {
			x = new mg_obj;
			*x = values[i];
			m->data[members[i]] = x;
		}
	}
	return m;
}
