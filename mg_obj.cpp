// Write code for creating and destroying mg_objects
#include <string>
#include <map>
#include "mg_obj.h"
#include "tree.h"

mg_obj * make_mg_obj(obj_type o, void * value) {
	mg_obj * m = new mg_obj;
	switch (o) {
		case FUNC:
			// A func is a sub-tree of a program which itself can be treated
			// as a program.
			m->type = FUNC;
			m->value = new node;
			break;
		
		case METH:
			// A meth is the same as a function for these purposes.
			m->type = METH;
			m->value = new node;
			break;
		
		case INT:
			m->type = INT:
			m->value = new int;
			break;
	
		case STR:
			m->type = STR;
			m->value = new std::string;
			break;
		
		case FLT:
			m->type = FLT;
			m->value = new double;
			break;
		
		case TYPE:
			// Objects of user-defined types map their field names to
			// other magenta objects, which allows for nested data types.
			m->type = TYPE;
			m->value = new std::map<std::string, mg_obj>;
			break;
		
		default:
			std::cout << "invalid data type" << std::endl;
	}
	return m;
}
