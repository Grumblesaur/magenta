#include <iostream>
#include <cstdlib>
#include <cmath>
#include "mg_ops.h"
#include "mg_string.h"
#include "mg_types.h"
#include "parser.tab.h"
using std::cerr;
using std::endl;
using std::string;


// Handle computation of expressions of the form x ** y where x and y are
// numeric types.
mg_obj * power(mg_obj * left, mg_obj * right) {
	if (left->type == TYPE_STRING || right->type == TYPE_STRING) {
		cerr << "error: unsupported exponentiation operation." << endl;
		exit(EXIT_FAILURE);
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
		cerr << "ERROR: Unsupported logarithmic operation." << endl;
		exit(EXIT_FAILURE);
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
	
	if (left->type == TYPE_INTEGER && right->type == TYPE_INTEGER) {
		i_product = ((mg_int *)left)->value * ((mg_int *)right)->value;
		return new mg_int(i_product);

	} else if (left->type == TYPE_INTEGER && right->type == TYPE_FLOAT) {
		d_product = ((mg_int *)left)->value * ((mg_flt *)right)->value;
		return new mg_flt(d_product);

	} else if (left->type == TYPE_FLOAT && right->type == TYPE_INTEGER) {
		d_product = ((mg_flt *)left)->value * ((mg_int *)right)->value;
		return new mg_flt(d_product);

	} else if (left->type == TYPE_FLOAT && right->type == TYPE_FLOAT) {
		d_product = ((mg_flt *)left)->value * ((mg_flt *)right)->value;
		return new mg_flt(d_product);

	} else if (left->type == TYPE_INTEGER && right->type == TYPE_STRING) {
		repeats = ((mg_int *)left)->value;
		text = ((mg_str *)right)->value;
		string str_product = str_multiply(text, repeats);
		return new mg_str(str_product);

	} else if (left->type == TYPE_STRING && right->type == TYPE_INTEGER) {
		repeats = ((mg_int *)right)->value;
		text = ((mg_str *)left)->value;
		string str_product = str_multiply(text, repeats);
		return new mg_str(str_product);

	} else {
		cerr << left->type << " ; " << right->type << endl;
		cerr << "error: unsupported multiplication operation" << endl;
		exit(EXIT_FAILURE);
	}
}

mg_obj * divide(mg_obj * left, mg_obj * right) {
	int i_quotient;
	double d_quotient;
	
	if (left->type == TYPE_INTEGER && right->type == TYPE_INTEGER) {
		d_quotient = (double)((mg_int *)left)->value
			/ (double)((mg_int *)right)->value;
		return new mg_flt(d_quotient);
	} else if (left->type == TYPE_INTEGER && right->type == TYPE_FLOAT) {
		d_quotient = ((mg_int *)left)->value / ((mg_flt *)right)->value;
		return new mg_int(d_quotient);
	} else if (left->type == TYPE_FLOAT && right->type == TYPE_INTEGER) {
		d_quotient = ((mg_flt *)left)->value / ((mg_int *)right)->value;
		return new mg_int(d_quotient);
	} else if (left->type == TYPE_FLOAT && right->type == TYPE_FLOAT) {
		d_quotient = ((mg_flt *)left)->value / ((mg_flt *)right)->value;
		return new mg_int(d_quotient);
	} else {
		cerr << "error: unsupported division operation" << endl;
		exit(EXIT_FAILURE);
	}
}

// divide two numbers after coercing them to integers
mg_obj * int_divide(mg_obj * left, mg_obj * right) {
	if (left->type == TYPE_STRING || right->type == TYPE_STRING) {
		cerr << "error: unsupported division operation" << endl;
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

mg_obj * mod(mg_obj * left, mg_obj * right) {
	if (left->type != TYPE_INTEGER && left->type != TYPE_INTEGER) {
		cerr << "error: unsupported modulus operation" << endl;
		exit(EXIT_FAILURE);
	} else if (left->type == TYPE_INTEGER && right->type == TYPE_INTEGER) {
		int i_mod = ((mg_int *)left)->value % ((mg_int *)right)->value;
		return new mg_int(i_mod);
	}
}

mg_obj * add(mg_obj * left, mg_obj * right) {
	if (left->type == TYPE_STRING && right->type == TYPE_STRING) {
		string concat = ((mg_str *)left)->value + ((mg_str *)right)->value;
		return new mg_str(concat);
	} else if (left->type == TYPE_STRING && right->type != TYPE_STRING
		|| left->type != TYPE_STRING && right->type == TYPE_STRING) {
		
		cerr << "error: unsupported addition operation" << endl;
		exit(EXIT_FAILURE);
	}
		
	bool left_is_float, right_is_float;
	left_is_float = left->type == TYPE_FLOAT;
	right_is_float = right->type == TYPE_FLOAT;
	
	double lval, rval, result;
	lval = left_is_float ?
		((mg_flt *)left)->value : ((mg_int *)left)->value;
	rval = right_is_float ?
		((mg_flt *)right)->value : ((mg_int *)right)->value;
	
	mg_obj * out;
	result = lval + rval;
	if (!left_is_float && !right_is_float) {
		out = (mg_obj *) new mg_int(result);
	} else {
		out = (mg_obj *) new mg_flt(result);
	}
	return out;
}

mg_obj * subtract(mg_obj * left, mg_obj * right) {
	bool left_is_float, right_is_float;
	double lval, rval, result;
	right_is_float = right->type == TYPE_FLOAT;
	rval = right_is_float ?
		((mg_flt *)right)->value : ((mg_int *)right)->value;
	
	// handle unary minus first
	if (left == NULL && right->type != TYPE_STRING) {
		if (right_is_float) { 
			return new mg_flt(-rval);
		} else {
			return new mg_int(-rval);
		}
	}
	
	if (left->type == TYPE_STRING || right->type == TYPE_STRING) {
		cerr << "ERROR: unsupported subtraction operation" << endl;
		exit(EXIT_FAILURE);
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
		case LOG_OR:
			out = new mg_int(bleft || bright);
			break;
		case LOG_XOR:
			out = new mg_int((bleft || bright) && !(bleft && bright));
			break;
		case LOG_AND:
			out = new mg_int(bleft && bright);
			break;
		case LOG_IMPLIES:
			out = new mg_int(!bleft && bright);
			break;
		}
	return out;
}

// returns the boolean evaluation of a comparison between the values of
// two mg_objs
// Throws error if str is compared to non-str
mg_obj * eval_comp(mg_obj * left, int op, mg_obj * right) {
	if (left->type == TYPE_STRING && left->type != right->type
		|| right->type == TYPE_STRING && left->type != right->type) {
		
		cerr << "error: compares numeric type with string" << endl;
		exit(EXIT_FAILURE);
	}
	
	bool numeric = left->type != TYPE_STRING && right->type != TYPE_STRING;
	double lfloat, rfloat;
	string lstr, rstr;
	
	bool out;
	if (numeric) {
		lfloat = (left->type == TYPE_INTEGER) ? 
			(double) ((mg_int *)left)->value : ((mg_flt *)left)->value;
		rfloat = (right->type == TYPE_INTEGER) ? 
			(double) ((mg_int *)right)->value : ((mg_flt *)right)->value;
		switch (op) {
			case LESS_THAN:     out = lfloat <  rfloat; break;
			case LESS_EQUAL:    out = lfloat <= rfloat; break;
			case EQUAL:         out = lfloat == rfloat; break;
			case NOT_EQUAL:     out = lfloat != rfloat; break;
			case GREATER_EQUAL: out = lfloat >= rfloat; break;
			case GREATER_THAN:  out = lfloat >  rfloat; break;
		}
	} else {
		lstr = ((mg_str *)left)->value;
		rstr = ((mg_str *)right)->value;
		switch (op) {
			case LESS_THAN:     out = lstr <  rstr; break;
			case LESS_EQUAL:    out = lstr <= rstr; break;
			case EQUAL:         out = lstr == rstr; break;
			case NOT_EQUAL:     out = lstr != rstr; break;
			case GREATER_EQUAL: out = lstr >= rstr; break;
			case GREATER_THAN:  out = lstr >  rstr; break;
		}
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
		cerr << "Unsupported bitwise operation." << endl;
		exit(EXIT_FAILURE);
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
		case TYPE_STRING:
			return ((mg_str *) o)->value != "";
		case TYPE_INTEGER:
			return  ((mg_int *) o)->value != 0;
		case TYPE_FLOAT:
			return  ((mg_flt *) o)->value != 0.0;
		default: // for non-primitive types XXX this may change later
			return false;
	}
}
