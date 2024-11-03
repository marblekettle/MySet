#include "yourHeader.h"

YourSet::iterator::iterator(): _set(NULL), _node(NULL) {};

YourSet::iterator::iterator(YourSet &x): _set(&x), _node(x._root) {
	// Go left until you no longer can
	while (_node->left)
		_node = _node->left;
}

YourSet::iterator::~iterator() {}

// Important to initialize a copy with a path of NULL
YourSet::iterator::iterator(const YourSet::iterator &x) {
	*this = x;
}

YourSet::iterator	&YourSet::iterator::operator=(const YourSet::iterator &x) {
	// Switch to the other set and target node
	this->_set = x._set;
	this->_node = x._node;
	return (*this);
}

bool	YourSet::iterator::operator==(const YourSet::iterator &x) const {
	// Their BST and target node must be the same
	return (this->_set == x._set && this->_node == x._node);
}

bool	YourSet::iterator::operator!=(const YourSet::iterator &x) const {
	return (!(*this == x));
}

YourSet::iterator	&YourSet::iterator::operator++() {
	if (_node == NULL)
		return (*this);
	_node = _set->__successor(_node);
	return (*this);
}

YourSet::iterator	YourSet::iterator::operator++(int x) {
	// This MUST have an int as its argument but it isn't used
	(void)x;
	YourSet::iterator	copy(*this);
	++(*this);
	return (copy);
}

const std::string	&YourSet::iterator::operator*() const {
	return (_node->data);
}

const std::string	*YourSet::iterator::operator->() const {
	return (&(_node->data));
}
