#ifndef MG_INT_H
#define MG_INT_H

class mg_str : public mg_obj{
	public:
		mg_str(void * value);
		~mg_str();
		std::string value;
};
#endif
