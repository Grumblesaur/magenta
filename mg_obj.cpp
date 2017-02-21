// Write code for creating and destroying mg_objects
#include <iostream>
#include <string>
#include <map>
#include "mg_obj.h"
#include "tree.h"

mg_obj * mg_alloc_int(int value) {
	mg_obj * m = new mg_obj;
	m->type = INT;
	m->value = new int(value);
	return m;
}

mg_obj * mg_alloc_flt(double value) {
	mg_obj * m = new mg_obj;
	m->type = FLT;
	m->value = new double(value);
	return m;
}

mg_obj * mg_alloc_str(std::string s) {
	mg_obj * m = new mg_obj;
	m->type = STR;
	m->value = new std::string(s);
	return m;
}

mg_obj * mg_alloc_func(node * v) {
	mg_obj * m = new mg_obj;
	m->type = FUNC;
	m->value = new node;
	*(m->value) = *v;
	return m;
}

mg_obj * mg_alloc_meth(node * v) {
	mg_obj * m = new mg_obj;
	m->type = METH;
	m->value = new node;
	*(m->value) = *v;
	return m;
}

// Allocate memory for a user-defined type instance using the name of the
// type, the names of each member of an instance of this type, and the
// values corresponding to each member.
mg_obj * mg_alloc_type(
	std::string name_of_type,
	std::string members[],
	mg_obj values[]
) {
	mg_format * m = new mg_format;
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
	
	
	for (int i = 0; i < members_size; i++) {
		// fields can be left uninitialized
		// TODO: ensure that each unclarified member gets its default value
		if (i >= values_size) {
			m->data[members[i]] = NULL;
		} else {
			m->data[members[i]] = values[i];
		}
	}
	return m;
}
