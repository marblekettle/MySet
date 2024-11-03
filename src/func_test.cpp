#include "yourHeader.h"

void	functional_test() {

	std::cout << "- Copying -" << std::endl;
	// Testing the copy constructor and assign operator overload
	while (true) {
		YourSet	set;
		std::cout << (set.add("a") ? "added" : "not added") << std::endl;
		std::cout << (set.add("b") ? "added" : "not added") << std::endl;
		std::cout << (set.add("c") ? "added" : "not added") << std::endl;
		std::cout << (set.add("c") ? "added" : "not added") << std::endl;
		std::cout << std::endl;

		// Copy Constructor
		YourSet	otherset(set);
		std::cout << (otherset.contains("a") ? "yes" : "no") << std::endl;
		std::cout << (otherset.contains("b") ? "yes" : "no") << std::endl;
		std::cout << (otherset.contains("c") ? "yes" : "no") << std::endl;
		std::cout << (otherset.contains("d") ? "yes" : "no") << std::endl;
		std::cout << std::endl;
		
		// Copy by assign operator
		otherset.remove("a");
		YourSet anotherset = otherset;
		anotherset.remove("b");
		std::cout << (set.contains("a") ? "yes" : "no") << std::endl;
		std::cout << (otherset.contains("a") ? "yes" : "no") << std::endl;
		std::cout << (otherset.contains("b") ? "yes" : "no") << std::endl;
		std::cout << (anotherset.contains("b") ? "yes" : "no") << std::endl;
		std::cout << (anotherset.contains("d") ? "yes" : "no") << std::endl;
		std::cout << std::endl;

		break ;
	}

	std::cout << "- Heap Allocation -" << std::endl;
	// Testing how the set is allocated on the heap
	while (true) {
		//	Constructor, adding, and checking
		YourSet *set = new YourSet;
		set->add("a");
		set->add("b");
		set->add("c");
		std::cout << set << std::endl;
		std::cout << (set->contains("a") ? "yes" : "no") << std::endl;
		std::cout << (set->contains("b") ? "yes" : "no") << std::endl;
		std::cout << (set->contains("c") ? "yes" : "no") << std::endl;
		std::cout << (set->contains("d") ? "yes" : "no") << std::endl;
		std::cout << std::endl;

		//	Copying and deallicating the original
		YourSet *otherset = new YourSet(*set);
		std::cout << set << std::endl;
		std::cout << otherset << std::endl;
		delete set;
		std::cout << (otherset->contains("a") ? "yes" : "no") << std::endl;
		std::cout << (otherset->contains("b") ? "yes" : "no") << std::endl;
		std::cout << (otherset->contains("c") ? "yes" : "no") << std::endl;
		std::cout << (otherset->contains("d") ? "yes" : "no") << std::endl;
		delete otherset;
		std::cout << std::endl;

		break ;
	}

	std::cout << "- Iterator -" << std::endl;
	// Testing the functionality of the iterator
	while (true) {
		YourSet set;
		set.add("apple");
		set.add("banana");
		set.add("coconut");
		
		// YourSet::begin()
		YourSet::iterator	i = set.begin();
		// YourSet::end() and not-equals comparison
		while (i != set.end()) {
			// Dereferencing
			std::cout << *i << " (";
			// Arrow dereferencing
			std::cout << i->length() << ") ";
			// Increment (post) and equals comparison
			std::cout << (i++ == set.begin() ? "yes" : "no") << std::endl;
		}
		std::cout << std::endl;

		YourSet::iterator	i2(set.begin());
		while (i2 != set.end()) {
			std::cout << *i2 << " (";
			std::cout << i2->length() << ") ";
			// Increment (pre)
			std::cout << (++i2 == set.end() ? "yes" : "no") << std::endl;
		}
		std::cout << std::endl;

		break ;
	}

	std::cout << "- Other Datatypes -" << std::endl;
	// Testing that the set also works with other datatypes, like integers
	while (true) {
		My::Set<int>	set;
		// Add some numbers
		set.add(1);
		set.add(2);
		set.add(3);
		std::cout << (set.contains(1) ? "yes" : "no") << std::endl;
		std::cout << (set.contains(2) ? "yes" : "no") << std::endl;
		std::cout << (set.contains(3) ? "yes" : "no") << std::endl;
		std::cout << (set.contains(4) ? "yes" : "no") << std::endl;
		std::cout << std::endl;

		// Remove a number
		set.remove(2);
		std::cout << (set.contains(1) ? "yes" : "no") << std::endl;
		std::cout << (set.contains(2) ? "yes" : "no") << std::endl;
		std::cout << (set.contains(3) ? "yes" : "no") << std::endl;
		std::cout << (set.contains(4) ? "yes" : "no") << std::endl;
		std::cout << std::endl;

		break ;
	}

	std::cout << "- Polymorphism -" << std::endl;
	// Testing the functionality of YourSet assigned to a My::Set pointer
	while (true) {
		// Here we introduce SomeSet, a doppelganger of YourSet that is a
		// My::Set but not a YourSet
		My::Set<std::string>	*set = new YourSet;
		My::Set<std::string>	*otherset = new SomeSet;

		set->add("a");
		std::cout << (set->contains("a") ? "yes" : "no") << std::endl;
		std::cout << (set->remove("a") ? "removed" : "notremoved") << std::endl;
		std::cout << (set->remove("a") ? "removed" : "notremoved") << std::endl;
		std::cout << std::endl;

		YourSet	*set_checker;
		SomeSet	*otherset_checker;

		// Trying to cast a SomeSet to a YourSet will return an error or, in
		// the case of a pointer, NULL
		std::cout << set << std::endl;
		set_checker = dynamic_cast<YourSet *>(set);
		std::cout << set_checker << std::endl;
		set_checker = dynamic_cast<YourSet *>(otherset);
		std::cout << set_checker << std::endl;
		otherset_checker = dynamic_cast<SomeSet *>(set);
		std::cout << otherset_checker << std::endl;
		otherset_checker = dynamic_cast<SomeSet *>(otherset);
		std::cout << otherset_checker << std::endl;
		std::cout << std::endl;
		delete set;
		delete otherset;
		
		break ;
	}

	return ;
}
