#include "Set.h"

namespace My {

	template<typename T>
	Set<T>::iterator::iterator(): _set(NULL), _node(NULL) {};

	template<typename T>
	Set<T>::iterator::iterator(Set &x): _set(&x), _node(x._root) {
		// Go left until you no longer can
		while (_node->left)
			_node = _node->left;
	}

	template<typename T>
	Set<T>::iterator::~iterator() {}

	template<typename T>
	Set<T>::iterator::iterator(const Set<T>::iterator &x) {
		*this = x;
	}

	template<typename T>
	typename Set<T>::iterator	&Set<T>::iterator::operator=(const Set<T>::iterator &x) {
		// Switch to the other set and target node
		this->_set = x._set;
		this->_node = x._node;
		return (*this);
	}

	template<typename T>
	bool	Set<T>::iterator::operator==(const Set<T>::iterator &x) const {
		// Their BST and target node must be the same
		return (this->_set == x._set && this->_node == x._node);
	}

	template<typename T>
	bool	Set<T>::iterator::operator!=(const Set<T>::iterator &x) const {
		return (!(*this == x));
	}

	template<typename T>
	typename Set<T>::iterator	&Set<T>::iterator::operator++() {
		// Set the node to its successor
		_node = _set->__successor(_node);
		return (*this);
	}

	template<typename T>
	typename Set<T>::iterator	Set<T>::iterator::operator++(int x) {
		// This MUST have an int as its argument but it isn't used
		(void)x;
		Set<T>::iterator	copy(*this);
		++(*this);
		return (copy);
	}

	template<typename T>
	typename Set<T>::iterator	&Set<T>::iterator::operator--() {
		// Set the node to its predecessor
		_node = _set->__predecessor(_node);
		return (*this);
	}

	template<typename T>
	typename Set<T>::iterator	Set<T>::iterator::operator--(int x) {
		(void)x;
		Set<T>::iterator	copy(*this);
		--(*this);
		return (copy);
	}
	template<typename T>
	const T	&Set<T>::iterator::operator*() const {
		return (_node->data);
	}

	template<typename T>
	const T	*Set<T>::iterator::operator->() const {
		return (&(_node->data));
	}

};
