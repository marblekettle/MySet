#include <iostream>
#include "yourHeader.h"

/**
*	The main function
*/

int		your_main(void) {
	//create your set
	YourSet	set;

	//add some data
	set.add(std::string("Some data"));

	//check some data
	std::cout << (set.contains(std::string("Some data")) ? "yes" : "no")
		<< std::endl;
	std::cout << (set.contains(std::string("some data")) ? "yes" : "no")
		<< std::endl;

	//remove some data
	std::cout << (set.remove(std::string("Some data")) ? "contained"
		: "did not contain") << std::endl;
	std::cout << (set.remove(std::string("some data")) ? "contained"
		: "did not contain") << std::endl;

	//done
	return (0);
}

int		main(void) {
	// This is the code that has to compile
	std::cout << "________Main Test________\n" << std::endl;
	your_main();

	// ...But we can do much better
	std::cout << "________Functional Test________\n" << std::endl;
	functional_test();
	std::cout << "________Performance Test________\n" << std::endl;
	performance_test();

	return (0);
}
