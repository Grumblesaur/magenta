#include <iostream>
#include <cstdlib>
#include <cmath>
#include "mg_error.h"
#include "mg_ops.h"
#include "mg_string.h"
#include "mg_list.h"
#include "mg_types.h"
#include "parser.tab.h"

extern unsigned linecount;

using std::cerr;
using std::endl;
using std::string;

mg_obj * element_of(mg_obj * left, mg_obj * right) {
	bool found = false;
	if (right->type != TYPE_LIST) {
		error("right operand is not a list", linecount);
	}
	auto it = ((mg_list *)right)->value.begin();
	while (!found && it != ((mg_list *)right)->value.end()) {
		found = *left == **it;
		++it;
	}
	return new mg_int(found);
}

// list bracket operations
mg_obj * list_index(mg_list * list, mg_int * index) {
	mg_obj * val = list->value[index->value];
	mg_obj * out;
	switch (val->type) {
		// functions pass by reference, since you can't mutate them
		case TYPE_FUNCTION: out = val;                           break;
		case TYPE_INTEGER:  out = new mg_int(*(mg_int *) val);   break;
		case TYPE_STRING:   out = new mg_str(*(mg_str *) val);   break;
		case TYPE_FLOAT:    out = new mg_flt(*(mg_flt *) val);   break;
		case TYPE_LIST:     out = new mg_list(*(mg_list *) val); break;
		}
	return out;
}

// string bracket operations
mg_obj * str_index(mg_str * str, mg_int * index) {
	string text = str->value;
	unsigned length = text.length();
	int position = index->value;
	string out;
	if (abs(position) >= length) {
		error("index out of bounds", linecount);
	}
	out = position < 0 ? text[length + position] : text[position];
	return new mg_str(out);
}


// Handle computation of expressions of the form x ** y where x and y are
// numeric types.
mg_obj * power(mg_obj * left, mg_obj * right) {
	if (left->type == TYPE_STRING || right->type == TYPE_STRING) {
		error("unsupported exponentiation operation", linecount);
	}
	bool left_is_float, right_is_float;
	left_is_float = left->type == TYPE_FLOAT;
	right_is_float = right->type == TYPE_FLOAT;
	
	double lval, rval, result;
	lval = left_is_float ?
		((mg_flt *)left)->value : ((mg_int *)left)->value;
	rval = right_is_float ?
		((mg_flt *)right)->value : ((mg_int *)right)->value;
	
	if (!left_is_float && !right_is_float) {
		return new mg_int(pow(lval, rval));
	}
	return new mg_flt(pow(lval, rval));
}

mg_obj * logarithm(mg_obj * left, mg_obj * right) {
	if (left->type == TYPE_STRING || right->type == TYPE_STRING) {
		error("unsupported logarithmic operation", linecount);
	}
	bool left_is_float = left->type == TYPE_FLOAT;
	bool right_is_float = right->type == TYPE_FLOAT;
	double lval, rval, result;
	lval = left_is_float ?
		((mg_flt *)left)->value : ((mg_int *)left)->value;
	rval = right_is_float ?
		((mg_flt *)right)->value : ((mg_int *)right)->value;
	
	return new mg_flt(log(lval) / log(rval));
}

mg_obj * multiply(mg_obj * left, mg_obj * right) {
	int i_product;
	double d_product;
	int repeats;
	string text;
	mg_obj * out;
	if (left->type == TYPE_INTEGER && right->type == TYPE_INTEGER) {
		i_product = ((mg_int *)left)->value * ((mg_int *)right)->value;
		out = new mg_int(i_product);
	} else if (left->type == TYPE_INTEGER && right->type == TYPE_FLOAT) {
		d_product = ((mg_int *)left)->value * ((mg_flt *)right)->value;
		out = new mg_flt(d_product);
	} else if (left->type == TYPE_FLOAT && right->type == TYPE_INTEGER) {
		d_product = ((mg_flt *)left)->value * ((mg_int *)right)->value;
		out = new mg_flt(d_product);
	} else if (left->type == TYPE_FLOAT && right->type == TYPE_FLOAT) {
		d_product = ((mg_flt *)left)->value * ((mg_flt *)right)->value;
		out = new mg_flt(d_product);
	} else if (left->type == TYPE_INTEGER && right->type == TYPE_STRING) {
		repeats = ((mg_int *)left)->value;
		text = ((mg_str *)right)->value;
		string str_product = str_multiply(text, repeats);
		out = new mg_str(str_product);
	} else if (left->type == TYPE_STRING && right->type == TYPE_INTEGER) {
		repeats = ((mg_int *)right)->value;
		text = ((mg_str *)left)->value;
		string str_product = str_multiply(text, repeats);
		out = new mg_str(str_product);
	} else if (left->type = TYPE_LIST && right->type == TYPE_INTEGER) {
		out = repeat((mg_list *) left, (mg_int *) right);
	} else if (left->type = TYPE_INTEGER && right->type == TYPE_LIST) {
		out = repeat((mg_list *) right, (mg_int *) left);
	} else {
		error("unsupported multiplication operation", linecount);
	}
	return out;
}

mg_obj * divide(mg_obj * left, mg_obj * right) {
	bool is_numeric =
		left->type == TYPE_INTEGER
		|| left->type == TYPE_FLOAT
		&& right->type == TYPE_INTEGER
		|| right->type == TYPE_FLOAT;
	
	if (!is_numeric) {
		if (left->type == TYPE_LIST) {
			return remove((mg_list *) left, right);
		} else {
			error("invalid division operation", linecount);
		}
	}
	double dividend, divisor;
	dividend = left->type == TYPE_INTEGER
		? ((mg_int *)left)->value
		: ((mg_flt *)left)->value;
	divisor = right->type == TYPE_INTEGER
		? ((mg_int *)right)->value
		: ((mg_flt *)right)->value;
	return new mg_flt(dividend / divisor);
}

// divide two numbers after coercing them to integers
mg_obj * int_divide(mg_obj * left, mg_obj * right) {
	bool is_numeric =
		left->type == TYPE_INTEGER
		|| left->type == TYPE_FLOAT
		&& right->type == TYPE_INTEGER
		|| right->type == TYPE_FLOAT;
	if (!is_numeric) {
		error("invalid integer division operation", linecount);
	}
	
	
	bool left_is_float = left->type == TYPE_FLOAT;
	bool right_is_float = right->type == TYPE_FLOAT;
	double lval, rval, result;
	lval = left_is_float ?
		((mg_flt *)left)->value : ((mg_int *)left)->value;
	rval = right_is_float ?
		((mg_flt *)right)->value : ((mg_int *)right)->value;
	return new mg_int((int) lval / (int) rval);
}

// remainder output of remainder division for integers only
mg_obj * mod(mg_obj * left, mg_obj * right) {
	if (left->type == TYPE_INTEGER && right->type == TYPE_INTEGER) {
		int i_mod = ((mg_int *)left)->value % ((mg_int *)right)->value;
		return new mg_int(i_mod);
	}
	error("unsupported modulus operation", linecount);
}

mg_obj * add(mg_obj * left, mg_obj * right) {
	if (left->type == TYPE_STRING && right->type == TYPE_STRING) {
		string concat = ((mg_str *)left)->value + ((mg_str *)right)->value;
		return new mg_str(concat);
	} else if (left->type == TYPE_LIST && right->type == TYPE_LIST) {
		return combine((mg_list *) left, (mg_list *)right);
	} else if (left->type == TYPE_STRING && right->type != TYPE_STRING
		|| left->type != TYPE_STRING && right->type == TYPE_STRING) {
		error("unsupported addition operation", linecount);
	}
		
	bool left_is_float, right_is_float;
	left_is_float = left->type == TYPE_FLOAT;
	right_is_float = right->type == TYPE_FLOAT;
	
	double lval, rval, result;
	lval = left_is_float ?
		((mg_flt *)left)->value : ((mg_int *)left)->value;
	rval = right_is_float ?
		((mg_flt *)right)->value : ((mg_int *)right)->value;
	
	result = lval + rval;
	return ((!left_is_float && !right_is_float)
		? (mg_obj *) new mg_int(result)
		: (mg_obj *) new mg_flt(result)
	);
}

mg_obj * subtract(mg_obj * left, mg_obj * right) {
	bool left_is_float, right_is_float;
	double lval, rval, result;
	right_is_float = right->type == TYPE_FLOAT;
	rval = right_is_float ?
		((mg_flt *)right)->value : ((mg_int *)right)->value;
	
	// handle unary minus first
	if (!left && right->type != TYPE_STRING) {
		if (right_is_float) { 
			return new mg_flt(-rval);
		} else {
			return new mg_int(-rval);
		}
	}
	
	if (left->type == TYPE_STRING || right->type == TYPE_STRING) {
		error("unsupported subtraction operation", linecount);
	}
	
	left_is_float = left->type == TYPE_FLOAT;
	lval = left_is_float ?
		((mg_flt *)left)->value : ((mg_int *)left)->value;
	
	if (!left_is_float && !right_is_float) {
		result = lval - rval;
		return new mg_int(result);
	}
	result = lval - rval;
	return new mg_flt(result);
}

mg_obj * eval_logical(mg_obj * left, int token, mg_obj * right) {
	mg_int * out = NULL;
	bool bleft = eval_bool(left);
	bool bright = eval_bool(right);
	switch (token) {
		case LOG_OR:      out = new mg_int(bleft || bright);  break;
		case LOG_AND:     out = new mg_int(bleft && bright);  break;
		case LOG_IMPLIES: out = new mg_int(!bleft || bright); break;
		case LOG_XOR:     out = new mg_int(
			(bleft || bright) && !(bleft && bright)
		); break;

	}
	return out;
}

// returns the boolean evaluation of a comparison between the values of
// two mg_objs
mg_obj * eval_comp(mg_obj * left, int op, mg_obj * right) {
	bool out = 0;
	switch (op) {
		case EQUAL:         out = *left == *right; break;
		case NOT_EQUAL:     out = *left == *right; break;
		case GREATER_THAN:  out = *left > *right;  break;
		case GREATER_EQUAL: out = *left >= *right; break;
		case LESS_THAN:     out = *left < *right;  break;
		case LESS_EQUAL:    out = *left <= *right; break;
	}
	return new mg_int(out);
}

mg_obj * eval_bitwise(mg_obj * left, int token, mg_obj * right) {
	// case for bitwise not (unary operator, left passed as null)
	if (left == NULL && right->type == TYPE_INTEGER) {
		return new mg_int(~((mg_int *)right)->value);
	}
	
	// bitwise operations are only valid for integers
	if (left->type != TYPE_INTEGER || right->type != TYPE_INTEGER) {
		error("unsupported bit twiddle", linecount);
	}
	
	int lval, rval, out;
	lval = ((mg_int *)left)->value;
	rval = ((mg_int *)right)->value;
	
	switch (token) {
		case BIT_XOR:     out = lval ^  rval; break;
		case BIT_OR:      out = lval |  rval; break;
		case BIT_AND:     out = lval &  rval; break;
		case LEFT_SHIFT:  out = lval << rval; break;
		case RIGHT_SHIFT: out = lval >> rval; break;
	}
	return new mg_int(out);
}


// given mg_obj pointer o this function will
// cast the pointer to a pointer of the appropriate subclass and
// return the boolean value of that pointer's actual value
bool eval_bool(mg_obj * o) {
	switch(o->type) {
		case TYPE_STRING:   return ((mg_str *) o)->value != "";
		case TYPE_INTEGER:  return ((mg_int *) o)->value != 0;
		case TYPE_FLOAT:    return ((mg_flt *) o)->value != 0.0;
		case TYPE_FUNCTION: return !((mg_func *) o)->param_types.empty();
		case TYPE_LIST:     return !((mg_list *) o)->value.empty();
		default:
			return false;
	}
}
