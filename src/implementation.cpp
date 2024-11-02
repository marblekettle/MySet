#include "yourHeader.h"

// An empty set only contains one leaf with no data in it
YourSet::YourSet(): _root(NULL) {}

// Clear the entire BST after the set is deleted
YourSet::~YourSet() {
	__clear_node(_root);
}

YourSet::YourSet(const YourSet &x) {
	*this = x;
}

// Create a deep copy of the BST
YourSet	&YourSet::operator=(const YourSet &x) {
	this->_root = __copy_node(x._root);
	return (*this);
}

// These functions form the interface of the class for adding, checking, and
// removing. They call the other internal functions which have a slightly
// different form so that they can be used recursively.
bool	YourSet::add(const std::string &data) {
	return (__insert_node(&_root, data));
}

bool	YourSet::contains(const std::string &data) {
	return (__search(_root, data));
}

bool	YourSet::remove(const std::string &data) {
	return (__delete_node(&_root, data));
}

void	YourSet::debug() {
	__debug(_root);
}

// Here we check each node and decides whether to go left or right, as well as
// applying rotations if imbalances occur at any node
bool	YourSet::__insert_node(YourSet::t_Node **node,
	const std::string &data) {
	// If we've reached a leaf without finding a match, this is where
	// the node belongs
	if (*node == NULL) {
		*node = new YourSet::t_Node(data);
		return (true);
	}
	bool out;
	// Run same function on left if new data is sorted before the stored data
	if ((*node)->data > data)
		out = __insert_node(&((*node)->left), data);
	// Run same function on right if new data is sorted after the stored data
	else if ((*node)->data < data)
		out = __insert_node(&((*node)->right), data);
	// This means the data is already in the BST
	else 
		return (false);
	if (out) {
		// Before we retrace, update height of the current node
		(*node)->height = 1 + std::max(__height((*node)->left),
			__height((*node)->right));
		// ...And check if this node needs rebalancing (i.e. abs(BF) > 1)
		__fix_balance(node);
	}
	return (out);
};

void	YourSet::__clear_node(YourSet::t_Node *node) {
	// Don't do anything if you've reached a leaf or BST is empty
	if (node == NULL)
		return ;
	if (node->left)
		__clear_node(node->left);
	if (node->right)
		__clear_node(node->right);
	delete node;
}

bool	YourSet::__delete_node(YourSet::t_Node **node,
	const std::string &data) {
	// Edge case: If there is no BST, nothing is there to delete
	if (*node == NULL)
		return (false);
	// First, find the node that matches the given data, going left or right
	// depending on data comparison
	bool out;
	if ((*node)->data > data)
		out = __delete_node(&((*node)->left), data);
	else if ((*node)->data < data)
		out = __delete_node(&((*node)->right), data);
	else {
		// We found it! How many children does it have?
		if ((*node)->left == NULL && (*node)->right == NULL) {
			// No children, just delete it
			delete (*node);
			(*node) = NULL;
		} else if ((*node)->left != NULL && (*node)->right != NULL) {
			// Two children, successor replaces the node
			// First switch the node with its successor
			__successor_switch(*node);
			// The original data is now in the tree right of the node
			// Find it and delete it
			__delete_node(&((*node)->right), data);
		} else {
			// Only one child, it replaces the node
			YourSet::t_Node	*temp = (*node);
			// Left child
			if ((*node)->right == NULL)
				(*node) = (*node)->left;
			// Right child
			else
				(*node) = (*node)->right;
			delete temp;
		}
		return (true);
	}
	if (out) {
		// Before we retrace, update height of the current node
		(*node)->height = 1 + std::max(__height((*node)->left),
			__height((*node)->right));
		// ...And check if this node needs rebalancing (i.e. abs(BF) > 1)
		__fix_balance(node);
	}
	return (out);
}

void	YourSet::__successor_switch(YourSet::t_Node *node) {
	// Successor must be the MOST left node that is still to the right of node
	YourSet::t_Node *succ = node->right;
	while (succ->left)
		succ = succ->left;
	// Everything can stay the same, just the data needs to be switched around
	std::string temp = succ->data;
	succ->data = node->data;
	node->data = temp;
}

bool	YourSet::__search(YourSet::t_Node *node,
	const std::string &data) const {
	// When we reach the end of the tree
	if (node == NULL)
		return (false);
	// When we find the right node
	if (data == node->data)
		return (true);
	// Otherwise, keep searching
	return (__search(node->left, data) || __search(node->right, data));
}

YourSet::t_Node	*YourSet::__copy_node(YourSet::t_Node *node) {
	// Start by copying the info of the root node
	YourSet::t_Node	*newnode = new YourSet::t_Node(node->data);
	newnode->height = node->height;
	// Then create new nodes to be its children
	if (node->left)
		newnode->left = __copy_node(node->left);
	if (node->right)
		newnode->right = __copy_node(node->right);
	return (newnode);
};

int		YourSet::__height(t_Node *node) {
	// Leaves have 0 height
	if (node == NULL)
		return (0);
	// Return whatever height the node has
	return (node->height);
}

void	YourSet::__fix_balance(t_Node **node) {
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

void	YourSet::__rotate(YourSet::t_Node **node, t_Rotate l_or_r) {	
	YourSet::t_Node	*temp = *node;
	if (l_or_r == LEFT) {
		// If node is a leaf or has no right child, it cannot be rotated left
		if (*node == NULL || (*node)->right == NULL)
			return ;
		// The original node becomes the left child of its right child
		*node = temp->right;
		// And the replacing node's left child becomes the original's right child
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
	temp->height = 1 + std::max(__height(temp->left), __height(temp->right));
	(*node)->height = 1 + std::max(__height((*node)->left), 
		__height((*node)->right));
}

void	YourSet::__debug(YourSet::t_Node *node) {
	// If it's a node, print out its content, balance factor, and
	// left and right pointer
	if (node) {
		std::cout << "___" << std::endl;
		int balance = __height(node->left) - __height(node->right);
		std::cout << node->data << "(" << (balance) << ")" << std::endl;
		std::cout << node->left << " " << node->right << std::endl;
		// ...Then continue with its children
		__debug(node->left);
		__debug(node->right);
	}
}
	