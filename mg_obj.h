#ifndef MG_OBJECT
#define MG_OBJECT

enum obj_type {
	FUNC, // 0
	METH, // 1
	INT,  // 2
	STR,  // 3
	FLT,  // 4
	TYPE  // 5
};

struct mg_obj {
	void * value;
	obj_type type;
};

#endif
