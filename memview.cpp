#include <iostream>
#include "mg_types.h"

using std::cout;
using std::endl;

int main(void) {
	cout << "size of int = " << sizeof(int) << endl;
	cout << "size of double = " << sizeof(double) << endl;
	cout << "size of std::string = " << sizeof(std::string) << endl;
	
	cout << "size of mg_int = " << sizeof(mg_int) << endl;
	cout << "size of mg_flt = " << sizeof(mg_flt) << endl;
	cout << "size of mg_str = " << sizeof(mg_str) << endl;
	
	return 0;
}
