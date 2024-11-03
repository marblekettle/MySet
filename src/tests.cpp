#include "yourHeader.h"

void	functional_test() {
	std::cout << "- Constructors & Destructor -" << std::endl;
	while (true) {
		YourSet	s_stack;
		YourSet	*s_heap = new YourSet();
		delete s_heap;
		break ;
	}
	std::cout << "- Other tests -" << std::endl;
	return ;
}

void	performance_test() {
	return ;
}