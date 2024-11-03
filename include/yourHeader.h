#ifndef YOURHEADER_H
# define YOURHEADER_H
# include <iostream>
# include <iomanip>
# include <fstream>
# include <sstream>
# include <vector>
# include <set>
# include <iterator>
# include <sys/time.h>
# include "Set.h"

/**	"YourSet" is just a specific case of the set class I wrote that
*	specifically works with the std::string datatype.
*	To see how it works, refer to Set.h, Set.tpp, and SetIterator.tpp
*/
class	YourSet : public My::Set<std::string> {};

//	Only used for a test
class	SomeSet : public My::Set<std::string> {};

void	functional_test();
void	performance_test();

#endif