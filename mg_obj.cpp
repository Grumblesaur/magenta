// Write code for creating and destroying mg_objects
#include <string>
#include "mg_obj.h"

mg_obj * make_mg_obj(obj_type o, void * value) {
	mg_obj * m;
	switch (o) {
		case STR:
			m = new mg_obj;
			m->type = STR;
			m->value = new std::string;
			break;

	}
}
