#ifndef YOURHEADER_H
# define YOURHEADER_H
# include <iostream>
# include <fstream>
# include <sys/time.h>
# include "Set.h"

class YourSet : public My::Set<std::string> {};

void	functional_test();
void	performance_test();

#endif