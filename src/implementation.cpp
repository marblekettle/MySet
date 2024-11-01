#include "yourHeader.h"

// An empty set only contains one leaf with no data in it
YourSet::YourSet(): _root(NULL) {}

// Clear the entire BST after the set is deleted
YourSet::~YourSet() {
	__clearnode(_root);
}

YourSet::YourSet(const YourSet &x) {
	*this = x;
}

// Create a deep copy of the BST
YourSet	&YourSet::operator=(const YourSet &x) {
	this->_root = __copynode(x._root);
	return (*this);
}

bool	YourSet::add(const std::string &data) {
	bool ret = __insertnode(&_root, data);
	return (ret);
}

bool	YourSet::contains(const std::string &data) {
	return (__search(_root, data) != NULL);
}

bool	YourSet::remove(const std::string &data) {
	bool ret = __deletenode(&_root, data);
	return (ret);
}

void	YourSet::debug() {
	__debug(_root);
}

// This recursively checks each node and decides whether to go left or right
bool	YourSet::__insertnode(YourSet::t_Node **node, const std::string &data) {
	// If we've reached a leaf without finding a match, this is where
	// the node belongs
	if (*node == NULL) {
		*node = new YourSet::t_Node(data);
		return (true);
	}
	// Go left if the new data is sorted before the stored data
	if ((*node)->data > data)
		return (__insertnode(&((*node)->left), data));
	// Go right if the new data is sorted after the stored data
	if ((*node)->data < data)
		return (__insertnode(&((*node)->right), data));
	// This means the data is already in the BST
	return (false);
};

void	YourSet::__clearnode(YourSet::t_Node *node) {
	// Don't do anything if you've reached a leaf or BST is empty
	if (node == NULL)
		return ;
	if (node->left)
		__clearnode(node->left);
	if (node->right)
		__clearnode(node->right);
	delete node;
}

bool	YourSet::__deletenode(YourSet::t_Node **node, const std::string &data) {
	// Edge case: If there is no BST, nothing is there to delete
	if ((*node) == NULL)
		return (false);
	YourSet::t_Node	*temp;
	// First, find the node that matches the given data, going left or right
	// depending on data comparison
	if ((*node)->data > data)
		return (__deletenode(&((*node)->left), data));
	else if ((*node)->data < data)
		return (__deletenode(&((*node)->right), data));
	else {
		// We found it! How many children does it have?
		if ((*node)->left == NULL && (*node)->right == NULL) {
			// No children, just delete it
			delete (*node);
			(*node) = NULL;
		} else if ((*node)->left != NULL && (*node)->right != NULL) {
			//Two children, successor replaces the node
			__successor_switch(node);
		} else {
			// Only one child, it replaces the node
			temp = (*node);
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
}

void	YourSet::__successor_switch(YourSet::t_Node **node) {
	YourSet::t_Node *succ = (*node)->right;
	YourSet::t_Node *succparent = NULL;
	while (succ->left) {
		succparent = succ;
		succ = succ->left;
	}
	if (succparent != NULL) {
		succparent->left = succ->right;
		succ->right = (*node)->right;
	}
	succ->left = (*node)->left;
	delete (*node);
	(*node) = succ;
}

YourSet::t_Node	*YourSet::__search(YourSet::t_Node *node,
	const std::string &data) const {
	if (node == NULL)
		return (NULL);
	if (data == node->data)
		return (node);
	YourSet::t_Node *left = __search(node->left, data);
	if (left != NULL)
		return (left);
	return __search(node->right, data);
}
	
YourSet::t_Node	*YourSet::__copynode(YourSet::t_Node *node) {
	YourSet::t_Node	*newnode = new YourSet::t_Node(node->data);
	newnode->black = node->black;
	if (node->left)
		newnode->left = __copynode(node->left);
	if (node->right)
		newnode->right = __copynode(node->right);
	return (newnode);
};

void	YourSet::__rotate_left(YourSet::t_Node **node) {
	// If node is a leaf or has no right child, it cannot be rotated left
	if (*node == NULL || (*node)->right == NULL)
		return ;
	YourSet::t_Node	*temp = *node;
	*node = temp->right;
	temp->right = (*node)->left;
	(*node)->left = temp;	
}

void	YourSet::__rotate_right(YourSet::t_Node **node) {
	// If node is a leaf or has no left child, it cannot be rotated right
	if (*node == NULL || (*node)->left == NULL)
		return ;
	YourSet::t_Node	*temp = *node;
	*node = temp->left;
	temp->left = (*node)->right;
	(*node)->right = temp;
}

void	YourSet::__debug(YourSet::t_Node *node) {
	if (node) {
		std::cout << "___" << std::endl;
		std::cout << node->data << "(" << (node->black ? "B" : "R")  << ")" << std::endl;
		std::cout << node->left << " " << node->right << std::endl;
		__debug(node->left);
		__debug(node->right);
	}
}
	