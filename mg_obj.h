#ifndef MG_OBJECT
#define MG_OBJECT

#ifdef __cplusplus
extern "C" {

	enum obj_type {
		FUNC, // 0
		METH, // 1
		INT,  // 2
		STR,  // 3
		FLT,  // 4
		TYPE  // 5
	};

	typedef enum obj_type obj_type;

	struct mg_obj {
		void * value;
		obj_type type;
	};

	typedef struct mg_obj mg_obj;

	mg_obj* make_mg_obj(obj_type o, void* value);
};

#endif

#endif
