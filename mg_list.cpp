#include <iostream>
#include <vector>
#include <algorithm>
#include "parser.tab.h"
#include "mg_types.h"
#include "mg_list.h"

using std::vector;
using std::cout;
using std::endl;

// removes the first instance of right->value from left->value
mg_list * remove(const mg_list * left, const mg_obj * right) {
	vector<mg_obj *> pruned = vector<mg_obj *>();
	auto it = left->value.begin();
	bool found_first = false;
	mg_obj * temp;
	while (it != left->value.end()) {
		if (!found_first && **it == *right) {
			found_first = true;
		} else {
			switch ((*it)->type) {
				case TYPE_FUNCTION:
					temp = *it; break;
				case TYPE_INTEGER:
					temp = new mg_int(*(mg_int *)*it); break;
				case TYPE_STRING:
					temp = new mg_str(*(mg_str *)*it); break;
				case TYPE_FLOAT:
					temp = new mg_flt(*(mg_flt *)*it); break;
				case TYPE_LIST:
					temp = new mg_list(*(mg_list *)*it); break;
			}
			pruned.push_back(temp);
		}
		it++;
	}
	return new mg_list(pruned);
}

mg_list * repeat(const mg_list * left, const mg_int * right) {
	vector<mg_obj *> repetition = vector<mg_obj *>();
	int reps = right->value;
	bool reverse = reps < 0;
	reps = abs(reps);
	mg_obj * temp;
	for (int i = 0; i < reps; i++) {
		for (auto it = left->value.begin(); it != left->value.end(); it++) {
			switch ((*it)->type) {
				case TYPE_FUNCTION:
					temp = *it; break;
				case TYPE_INTEGER:
					temp = new mg_int(*(mg_int *)*it); break;
				case TYPE_STRING:
					temp = new mg_str(*(mg_str *)*it); break;
				case TYPE_FLOAT:
					temp = new mg_flt(*(mg_flt *)*it); break;
				case TYPE_LIST:
					temp = new mg_list(*(mg_list *)*it); break;
			}
			repetition.push_back(temp);
		}
	}
	if (reverse) std::reverse(repetition.begin(), repetition.end());
	return new mg_list(repetition);
}

mg_list * combine(const mg_list * left, const mg_list * right) {
	vector<mg_obj *> combination = vector<mg_obj *>();
	mg_obj * temp;
	for (auto it = left->value.begin(); it != left->value.end(); it++) {
		switch ((*it)->type) {
			case TYPE_FUNCTION: temp = *it;                         break;
			case TYPE_INTEGER:  temp = new mg_int(*(mg_int *)*it);  break;
			case TYPE_STRING:   temp = new mg_str(*(mg_str *)*it);  break;
			case TYPE_FLOAT:    temp = new mg_flt(*(mg_flt *)*it);  break;
			case TYPE_LIST:     temp = new mg_list(*(mg_list*)*it); break;
		}
		combination.push_back(temp);
	}
	for (auto it = right->value.begin(); it != right->value.end(); it++) {
		switch ((*it)->type) {
			case TYPE_FUNCTION: temp = *it;                         break;
			case TYPE_INTEGER:  temp = new mg_int(*(mg_int *)*it);  break;
			case TYPE_STRING:   temp = new mg_str(*(mg_str *)*it);  break;
			case TYPE_FLOAT:    temp = new mg_flt(*(mg_flt *)*it);  break;
			case TYPE_LIST:     temp = new mg_list(*(mg_list*)*it); break;
		}
		combination.push_back(temp);
	}
	
	return new mg_list(combination);
}

