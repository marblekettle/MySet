#include <iostream>
#include "yourHeader.h"

int	main(void) {
	YourSet	set;
	set.add("a");
	set.add("b");
	set.add("c");
	set.add("d");
	set.add("f");
	set.add("e");
	YourSet::iterator it = set.begin();
	std::cout << it->length() << std::endl;
//	while (it != set.end()) {
//		std::cout << *it++ << std::endl;
//	}
//	YourSet set2 = set;
//	set.add("g");
//	set.debug();
//	set.add("e");
//	set.add("f");
/*	set.add("g");
	set.add("f");
	set.add("b");
	set.add("a"); */
//	set2.debug();
//	set.debug();
//	std::cout << "Contains c: " << set.contains("c") << std::endl;
//	std::cout << "Contains g: " << set.contains("g") << std::endl;
//	set.remove("d");
//	set.debug();
/*	std::cout << "Add e: " << set.add("e") << std::endl;
	std::cout << "Add e again: " << set.add("e") << std::endl;
	std::cout << "Contains c: " << set.contains("c") << std::endl;
	std::cout << "Contains d: " << set.contains("d") << std::endl;
	std::cout << "Contains a: " << set.contains("a") << std::endl;
	set.add("a");
	set.debug();
	std::cout << "Delete c: " << set.remove("c") << std::endl;
	std::cout << "Delete c again: " << set.remove("c") << std::endl;
	set.debug();
*/
	return (0);
}
