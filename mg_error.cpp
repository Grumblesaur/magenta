#include <iostream>
#include <cstdlib>
void error(std::string msg, unsigned line) {
	std::cerr << msg << " at " << line << std::endl;
	exit(EXIT_FAILURE);
}
