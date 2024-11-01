#include <iostream>
#include "yourHeader.h"

/**
*	The main function
*/

int		main(void) {
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
