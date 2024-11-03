#include "Set.h"

namespace My {

	// An empty set only contains one leaf with no data in it
	template<typename T>
	Set<T>::Set(): _root(NULL) {};

	// Clear the entire BST after the set is deleted
	template<typename T>
	Set<T>::~Set() {
		__clear_node(_root);
	}

	template<typename T>
	Set<T>::Set(const Set<T> &x) {
		*this = x;
	}

	// Create a deep copy of the BST
	template<typename T>
	Set<T>	&Set<T>::operator=(const Set<T> &x) {
		this->_root = __copy_node(x._root);
		return (*this);
	}

	// These functions form the interface of the class for adding, checking,
	// and removing. They call the other internal functions which have a
	// slightly different form so that they can be used recursively.
	template<typename T>
	bool	Set<T>::add(const T &data) {
		return (__insert_node(&_root, data) != NULL);
	}

	template<typename T>
	bool	Set<T>::contains(const T &data) {
		return (__search(data) != NULL);
	}

	template<typename T>
	bool	Set<T>::remove(const T &data) {
		// We retrieve the node that is to be removed, modifying the BST
		// in the process
		Set<T>::t_Node *toremove = __remove_node(&_root, data);
		// If it isn't found
		if (toremove == NULL)
			return (false);
		// If it was found, deallocate it
		delete toremove;
		return (true);
	}

	// Here we check each node and decides whether to go left or right, as well as
	// applying rotations if imbalances occur at any node
	template<typename T>
	typename Set<T>::t_Node	*Set<T>::__insert_node(Set<T>::t_Node **node,
		const T &data) {
		// If we've reached a leaf without finding a match, this is where
		// the node belongs
		if (*node == NULL) {
			*node = new Set<T>::t_Node(data);
			return (*node);
		}
		Set<T>::t_Node	*out;
		// Run same function on left if new data is sorted before the stored data
		if ((*node)->data > data)
			out = __insert_node(&((*node)->left), data);
		// Run same function on right if new data is sorted after the stored data
		else if ((*node)->data < data)
			out = __insert_node(&((*node)->right), data);
		// This means the data is already in the BST
		else 
			return (NULL);
		if (out != NULL) {
			// Before we retrace, update height of the current node
			(*node)->height = 1 + std::max(__height((*node)->left),
				__height((*node)->right));
			// ...And check if this node needs rebalancing (i.e. abs(BF) > 1)
			__fix_balance(node);
		}
		return (out);
	}

	template<typename T>
	void	Set<T>::__clear_node(Set<T>::t_Node *node) {
		// Don't do anything if you've reached a leaf or BST is empty
		if (node == NULL)
			return ;
		if (node->left)
			__clear_node(node->left);
		if (node->right)
			__clear_node(node->right);
		delete node;
	}

	template<typename T>
	typename Set<T>::t_Node	*Set<T>::__remove_node(Set<T>::t_Node **node,
		const T &data) {
		// Edge case: If there is no BST, nothing is there to delete
		if (*node == NULL)
			return (NULL);
		// First, find the node that matches the given data, going left or right
		// depending on data comparison
		Set<T>::t_Node *out;
		if ((*node)->data > data)
			out = __remove_node(&((*node)->left), data);
		else if ((*node)->data < data)
			out = __remove_node(&((*node)->right), data);
		else {
			// We found it! How many children does it have?
			if ((*node)->left != NULL && (*node)->right != NULL) {
				// Two children, successor replaces the node
				// First switch the node with its successor
				__successor_switch(*node);
				// The original data is now in the tree right of the node
				// Find it and delete it
				return (__remove_node(&((*node)->right), data));
			} else {
				// Only one child or no children
				Set<T>::t_Node	*temp = *node;
				// Left child replaces the node
				if ((*node)->right == NULL)
					*node = (*node)->left;
				// Right child replaces the node (may be NULL if no children)
				else
					*node = (*node)->right;
				return (temp);
			}
		}
		if (out != NULL) {
			// Before we retrace, update height of the current node
			(*node)->height = 1 + std::max(__height((*node)->left),
				__height((*node)->right));
			// ...And check if this node needs rebalancing (i.e. abs(BF) > 1)
			__fix_balance(node);
		}
		return (out);
	}

	template<typename T>
	typename Set<T>::t_Node	*Set<T>::__successor(Set<T>::t_Node *node) {
		Set<T>::t_Node	*succ = node->right;
		if (succ == NULL) {
			// If we can't go right, it's trickier to find the successor
			// We have to go through the tree
			Set<T>::t_Node	*temp = _root;
			while (temp != node && temp != NULL) {
				// Going left every time the current node is higher, making it a
				// potential successor
				if (temp->data > node->data) {
					succ = temp;
					temp = temp->left;
				// And going right every time the current node is lower
				} else
					temp = temp->right;
			}
			// Go with the latest (lowest) potential successor we found
			return (succ);
		} else {
			// Go one to the right, and then keep going left: that's the successor
			while (succ->left)
				succ = succ->left;
		}
		return (succ);
	}

	template<typename T>
	void	Set<T>::__successor_switch(Set<T>::t_Node *node) {
		Set<T>::t_Node *succ = __successor(node);
		// Switch the data of the node with its successor's 
		T temp = succ->data;
		succ->data = node->data;
		node->data = temp;		
	}

	template<typename T>
	typename Set<T>::t_Node	*Set<T>::__search(const T &data) const {
		// This one doesn't use recursive tricks, just iterative use of the
		// properties of a BST
		Set<T>::t_Node	*node = _root;
		// If the node doesn't exist or there is no BST, just return NULL
		while (node != NULL) {
			// When the data matches, we have the right node
			if (data == node->data)
				break ;
			// If the data is lower than the stored data, go left
			else if (data < node->data)
				node = node->left;
			else
			// If the data is higher than the stored data, go right
				node = node->right;
		}
		return (node);
	}

	template<typename T>
	typename Set<T>::t_Node	*Set<T>::__copy_node(Set<T>::t_Node *node) {
		// Start by copying the info of the root node
		Set<T>::t_Node	*newnode = new Set<T>::t_Node(node->data);
		newnode->height = node->height;
		// Then create new nodes to be its children
		if (node->left)
			newnode->left = __copy_node(node->left);
		if (node->right)
			newnode->right = __copy_node(node->right);
		return (newnode);
	};

	template<typename T>
	int		Set<T>::__height(t_Node *node) {
		// Leaves have 0 height
		if (node == NULL)
			return (0);
		// Return whatever height the node has
		return (node->height);
	}

	template<typename T>
	void	Set<T>::__fix_balance(t_Node **node) {
		int balance = __height((*node)->left) - __height((*node)->right);
		if (balance > 1) {
			// Needs to be rotated to the right
			if ((*node)->left->left == NULL)
				// "Un-angle" the child node by rotating it opposite
				__rotate(&((*node)->left), LEFT);
			__rotate(node, RIGHT);
		} else if (balance < -1){
			// Needs to be rotated to the left
			if ((*node)->right->right == NULL)
				// "Un-angle" the child node by rotating it opposite
				__rotate(&((*node)->right), RIGHT);
			__rotate(node, LEFT);
		}
	}

	template<typename T>
	void	Set<T>::__rotate(Set<T>::t_Node **node, t_Dir l_or_r) {
		Set<T>::t_Node	*temp = *node;
		if (l_or_r == LEFT) {
			// If node is leaf or has no right child, it cannot be rotated left
			if (*node == NULL || (*node)->right == NULL)
				return ;
			// Original node becomes the left child of its right child
			*node = temp->right;
			// Replacing node's left child becomes original's right child
			temp->right = (*node)->left;
			(*node)->left = temp;
		} else {
			// Basically the symmetric version of the "LEFT" case
			if (*node == NULL || (*node)->left == NULL)
				return ;
			*node = temp->left;
			temp->left = (*node)->right;
			(*node)->right = temp;
		}
		// Recalculate heights
		temp->height = 1 + std::max(__height(temp->left),
			__height(temp->right));
		(*node)->height = 1 + std::max(__height((*node)->left), 
			__height((*node)->right));
	}

	template<typename T>
	typename Set<T>::iterator	Set<T>::begin() {
		Set<T>::iterator	it(*this);
		return (it);
	}

	template<typename T>
	typename Set<T>::iterator	Set<T>::end() {
		Set<T>::iterator	it(*this);
		it._node = NULL;
		return (it);
	}

};
