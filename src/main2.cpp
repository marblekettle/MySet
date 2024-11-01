#include <iostream>
#include "yourHeader.h"

int	main(void) {
	YourSet	set;
	set.add("c");
	set.add("d");
	std::cout << "Add e: " << set.add("e") << std::endl;
	std::cout << "Add e again: " << set.add("e") << std::endl;
	std::cout << "Contains c: " << set.contains("c") << std::endl;
	std::cout << "Contains d: " << set.contains("d") << std::endl;
	std::cout << "Contains a: " << set.contains("a") << std::endl;
	set.add("a");
	set.debug();
	std::cout << "Delete c: " << set.remove("c") << std::endl;
	std::cout << "Delete c again: " << set.remove("c") << std::endl;
	set.debug();
	return (0);
}
