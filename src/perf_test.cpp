#include "yourHeader.h"

void	measure_time(struct timeval *tv) {
	struct timeval newtv;
	gettimeofday(&newtv, NULL);
	time_t secs = (newtv.tv_sec - tv->tv_sec);
	if (newtv.tv_usec < tv->tv_usec)
		secs--;
	time_t usecs = (newtv.tv_usec - tv->tv_usec);
	std::cout << "Time elapsed: " << secs << ".";
	std::cout << std::setfill('0') << std::setw(6) << usecs << std::endl;
}

void	insertion_test(std::vector<std::string> *split) {
	struct timeval tv;
	std::cout << "- Insertion -" << std::endl;
	std::cout << std::endl;
	
	std::cout << "Testing YourSet" << std::endl;
	std::vector<std::string>::iterator	i = split->begin();
	YourSet	*set = new YourSet;
	std::cout << "Ready... GO!" << std::endl;
	gettimeofday(&tv, NULL);

	while (i != split->end()) {
		set->add(*i);
		i++;
	}

	measure_time(&tv);
	delete set;
	std::cout << std::endl;

	std::cout << "Testing std::set" << std::endl;
	i = split->begin();
	std::set<std::string>	*set2 = new std::set<std::string>;
	std::cout << "Ready... GO!" << std::endl;
	gettimeofday(&tv, NULL);

	while (i != split->end()) {
		set2->insert(*i);
		i++;
	}

	measure_time(&tv);
	delete set2;
}

void	lookup_test(std::vector<std::string> *split) {
	struct timeval tv;
	std::cout << "- Lookup -" << std::endl;
	std::cout << std::endl;

	std::cout << "Testing YourSet" << std::endl;
	YourSet *set = new YourSet;
	std::vector<std::string>::iterator i = split->begin();
	while (i != split->end()) {
		set->add(*i);
		i++;
	}

	std::cout << "Ready... GO!" << std::endl;
	gettimeofday(&tv, NULL);

	while (i != split->begin()) {
		i--;
		set->contains(*i);
	}

	measure_time(&tv);
	delete set;

	std::cout << std::endl;
	std::cout << "Testing std::set" << std::endl;
	std::set<std::string> *set2 = new std::set<std::string>;
	i = split->begin();
	while (i != split->end()) {
		set2->insert(*i);
		i++;
	}

	std::cout << "Ready... GO!" << std::endl;
	gettimeofday(&tv, NULL);

	while (i != split->begin()) {
		i--;
		set2->count(*i);
	}

	measure_time(&tv);
	delete set2;

	return ;
}

void	iterator_test(std::vector<std::string> *split) {
	struct timeval tv;
	std::cout << "- Iterator -" << std::endl;
	std::cout << std::endl;

	std::cout << "Testing YourSet" << std::endl;
	YourSet *set = new YourSet;
	std::vector<std::string>::iterator i = split->begin();
	while (i != split->end()) {
		set->add(*i);
		i++;
	}

	YourSet::iterator	it = set->begin();
	std::cout << "Ready... GO!" << std::endl;
	gettimeofday(&tv, NULL);

	while (it != set->end()) {
		*it;
		it++;
	}

	measure_time(&tv);
	delete set;

	std::cout << std::endl;
	std::cout << "Testing std::set" << std::endl;
	std::set<std::string> *set2 = new std::set<std::string>;
	i = split->begin();
	while (i != split->end()) {
		set2->insert(*i);
		i++;
	}

	std::set<std::string>::iterator	it2 = set2->begin();
	std::cout << "Ready... GO!" << std::endl;
	gettimeofday(&tv, NULL);

	while (it2 != set2->end()) {
		*it2;
		it2++;
	}

	measure_time(&tv);
	delete set2;

	return ;
}

void	remove_test(std::vector<std::string> *split) {
	struct timeval tv;
	std::cout << "- Removal -" << std::endl;
	std::cout << std::endl;

	std::cout << "Testing YourSet" << std::endl;
	YourSet *set = new YourSet;
	std::vector<std::string>::iterator i = split->begin();
	while (i != split->end()) {
		set->add(*i);
		i++;
	}

	i = split->begin();
	std::cout << "Ready... GO!" << std::endl;
	gettimeofday(&tv, NULL);

	while (i != split->end()) {
		set->remove(*i);
		i++;
	}

	measure_time(&tv);
	delete set;

	std::cout << std::endl;
	std::cout << "Testing std::set" << std::endl;
	std::set<std::string> *set2 = new std::set<std::string>;
	i = split->begin();
	while (i != split->end()) {
		set2->insert(*i);
		i++;
	}

	i = split->begin();
	std::cout << "Ready... GO!" << std::endl;
	gettimeofday(&tv, NULL);

	while (i != split->end()) {
		set2->erase(*i);
		i++;
	}

	measure_time(&tv);
	delete set2;

	return ;
}

void	performance_test() {
	std::fstream	f("lorem.txt");
	if (!f.is_open()) {
		std::cout << "Please place lorem.txt in the root directory.";
		std::cout << std::endl;
		return ;
	}

	std::stringstream	ss;
	ss << f.rdbuf();
	std::vector<std::string> split(std::istream_iterator<std::string> {ss},
		std::istream_iterator<std::string>());

	insertion_test(&split);
	std::cout << std::endl;
	lookup_test(&split);
	std::cout << std::endl;
	iterator_test(&split);
	std::cout << std::endl;
	remove_test(&split);
	std::cout << std::endl;
}