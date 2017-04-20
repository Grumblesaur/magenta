#include <iostream>
#include <vector>
#include "parser.tab.h"
#include "mg_types.h"
#include "mg_list.h"

using std::vector;
using std::cout;
using std::endl;

mg_list * combine(const mg_list * left, const mg_list * right) {
	vector<mg_obj *> combination = vector<mg_obj *>();
	mg_obj * temp;
	cout << endl << "left hand list (" << left << "): " << endl;
	for (auto it = left->value.begin(); it != left->value.end(); it++) {
		switch ((*it)->type) {
			case TYPE_INTEGER:
				temp = new mg_int(*(mg_int*)*it);
				break;
			case TYPE_STRING:
				temp = new mg_str(*(mg_str*)*it);
				break;
			case TYPE_FLOAT:
				temp = new mg_flt(*(mg_flt*)*it);
				break;
			case TYPE_LIST:
				temp = new mg_list(*(mg_list*)*it);
				break;
			case TYPE_FUNCTION:
				temp = *it;
				break;
		}
		cout << "\t" << temp << " from " << *it << endl;
		combination.push_back(temp);
	}
	cout << endl << "right hand list (" << right << "): " << endl;
	for (auto it = right->value.begin(); it != right->value.end(); it++) {
		switch ((*it)->type) {
			case TYPE_INTEGER:
				temp = new mg_int(*(mg_int*)*it);
				break;
			case TYPE_STRING:
				temp = new mg_str(*(mg_str*)*it);
				break;
			case TYPE_FLOAT:
				temp = new mg_flt(*(mg_flt*)*it);
				break;
			case TYPE_LIST:
				temp = new mg_list(*(mg_list *)*it);
				break;
			case TYPE_FUNCTION:
				temp = *it;
				break;
		}
		cout << "\t" << temp << " from " << *it << endl;
		combination.push_back(temp);
	}
	
	mg_list * out = new mg_list(combination);
	cout << endl << "combination (" << out << "): " << endl;
	
	unsigned c = 0;
	for (auto it = combination.begin(); it != combination.end(); it++) {
		cout << "\t" << *it;
		c++;
		if (!(c % 4)) cout << endl;
	} cout << endl;
	
	return new mg_list(combination);
}

