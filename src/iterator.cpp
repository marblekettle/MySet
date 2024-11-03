#include "yourHeader.h"

YourSet::iterator::iterator(): _root(NULL), _path(NULL), _path_size(0) {};

YourSet::iterator::~iterator() {
	if (_path != NULL)
		delete[] _path;
}

// Important to initialize a copy with a path of NULL
YourSet::iterator::iterator(const YourSet::iterator &x): _path(NULL) {
	*this = x;
}

YourSet::iterator	&YourSet::iterator::operator=(const YourSet::iterator &x) {
	// Switch to the other set's BST
	this->_root = x._root;
	// Remove the original path if it exists
	if (this->_path != NULL)
		delete[] this->_path;
	// And replace with the other iterator's path
	this->_path_size = x._path_size;
	this->_path = new t_Dir[x._path_size];
	for (size_t i = 0; i < x._path_size; i++)
		this->_path[i] = x._path[i];
	return (*this);
}

bool	YourSet::iterator::operator==(const YourSet::iterator &x) const {
	// Their BST must be the same and have the same path size
	if (this->_root != x._root || this->_path_size != x._path_size)
		return (false);
	// ...As well as the same path (or it won't point to the same node)
	for (size_t i = 0; i < x._path_size; i++) {
		if (this->_path[i] != x._path[i])
			return (false);
	}
	return (true);
}

bool	YourSet::iterator::operator!=(const YourSet::iterator &x) const {
	return (!(*this == x));
}

YourSet::iterator	&YourSet::iterator::operator++() {
	__next();
	return (*this);
}

YourSet::iterator	YourSet::iterator::operator++(int x) {
	// This MUST have an int as its argument but it isn't used
	(void)x;
	YourSet::iterator	copy(*this);
	__next();
	return (copy);
}

std::string	YourSet::iterator::operator*() const {
	return (__find_node()->data);
}

YourSet::t_Node	*YourSet::iterator::__find_node() const {
	YourSet::t_Node	*node = _root;
	// Just follow the path 
	for (size_t i = 0; i < _path_size; i++) {
		if (_path[i] == LEFT)
			node = node->left;
		else if (_path[i] == RIGHT)
			node = node->right;
		// Until we either find NULL
		if (node == NULL)
			return (NULL);
	}
	// ...Or we arrive at the correct node
	return (node);
}


//	CLEAN UP THIS FUNCTION
void	YourSet::iterator::__next() {
	YourSet::t_Node	*node = __find_node();
	if (node == NULL)
		return ;
	size_t	newsize = 0;
	// If there is more to the right
	if (node->right != NULL) {
		// Go right
		node = node->right;
		newsize++;
		// Go all the way left
		while (node->left) {
			node = node->left;
			newsize++;
		}
		// Update direction path
		t_Dir *newdir = new t_Dir[_path_size + newsize];
		for (size_t i = 0; i < _path_size; i++)
			newdir[i] = _path[i];
		for (size_t i = 0; i < newsize; i++)
			newdir[i + _path_size] = LEFT;
		newdir[_path_size] = RIGHT;
		delete[] _path;
		_path = newdir;
		_path_size += newsize;
	} else {
		// Go back to the first node up-right
		newsize = _path_size - 1;
		while (_path[newsize] != LEFT) {
			if (newsize == 0) {
				// We're off the deep end
				__beyond_end();
				return ;
			}
			newsize--;
		}
		// Update direction path
		t_Dir *newdir = new t_Dir[newsize];
		for (size_t i = 0; i < newsize; i++)
			newdir[i] = _path[i];
		delete[] _path;
		_path = newdir;
		_path_size = newsize;
	}
}

void	YourSet::iterator::__beyond_end() {
	_path_size++;
	t_Dir *newdir = new t_Dir[_path_size];
	// Sets the path to string of RIGHT that goes off the right-end of BST
	for (size_t i = 0; i < _path_size; i++)
		newdir[i] = RIGHT;
	delete[] _path;
	_path = newdir;
}
