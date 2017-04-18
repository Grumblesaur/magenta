#include <iostream>
#include <vector>
#include "parser.tab.h"
#include "mg_types.h"
#include "mg_list.h"

using std::vector;


mg_list * combine(const mg_list * left, const mg_list * right) {
	vector<mg_obj *> combination;
	std::cout << "enter combine()" << std::endl;
	std::cout << "start with left list" << std::endl;
	for (auto it = left->value.begin(); it != left->value.end(); it++) {
		std::cout << "type of current value: " << (*it)->type << std::endl;
		std::cout << "\tpush back " << **it << std::endl;
		switch ((*it)->type) {
			case TYPE_INTEGER:
				combination.push_back(new mg_int((*(mg_int *) *it).value));
				break;
			case TYPE_FLOAT:
				combination.push_back(new mg_flt((*(mg_flt *) *it).value));
				break;
			case TYPE_STRING:
				combination.push_back(new mg_str((*(mg_str *) *it).value));
				break;
			case TYPE_LIST:
				combination.push_back(
					new mg_list((*(mg_list *) *it).value)
				);
				break;
			case TYPE_FUNCTION:
				combination.push_back(*it);
				break;
		}
	}
	std::cout << "now add right list " << std::endl;
	for (auto it = right->value.begin(); it != right->value.end(); it++) {
		std::cout << "type of current value: " << (*it)->type << std::endl;
		std::cout << "\t push back " << **it << std::endl;
		switch ((*it)->type) {
			case TYPE_INTEGER:
				combination.push_back(new mg_int((*(mg_int *) *it).value));
				break;
			case TYPE_FLOAT:
				combination.push_back(new mg_flt((*(mg_flt *) *it).value));
				break;
			case TYPE_STRING:
				combination.push_back(new mg_str((*(mg_str *) *it).value));
				break;
			case TYPE_LIST:
				combination.push_back(
					new mg_list((*(mg_list *) *it).value)
				);
				break;
			case TYPE_FUNCTION:
				combination.push_back(*it);
				break;
		}
	}
	
	std::cout << "check right for integrity" << std::endl;
	for (auto it = right->value.begin(); it != right->value.end(); it++) {
		std::cout << **it << std::endl;
	}
	return new mg_list(combination);
}

