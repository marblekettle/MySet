#include "yourHeader.h"

// An empty set only contains one leaf with no dats in it
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
bool	YourSet::__insertnode(YourSet::t_Node **bst, const std::string &data) {
	// If we've reached a leaf without finding a match, this is where
	// the node belongs
	if (*bst == NULL) {
		*bst = new YourSet::t_Node(data);
		return (true);
	}
	// Go left if the new data is sorted before the stored data
	if ((*bst)->data > data)
		return (__insertnode(&((*bst)->left), data));
	// Go right if the new data is sorted before the stored data
	if ((*bst)->data < data)
		return (__insertnode(&((*bst)->right), data));
	// This means the data is already in the BST
	return (false);
};


void	YourSet::__clearnode(YourSet::t_Node *bst) {
	if (bst == NULL)
		return ;
	if (bst->left)
		__clearnode(bst->left);
	if (bst->right)
		__clearnode(bst->right);
	delete bst;
}

bool	YourSet::__deletenode(YourSet::t_Node **bst, const std::string &data) {
	// Edge case: If there is no BST, nothing is there to delete
	if ((*bst) == NULL)
		return (false);
	// First, find the node that matches the given data, going left or right
	// depending on data comparison
	if ((*bst)->data > data)
		return (__deletenode(&((*bst)->left), data));
	else if ((*bst)->data < data)
		return (__deletenode(&((*bst)->right), data));
	else {
		// We found it! How many children does it have?
		if ((*bst)->left == NULL) {
			if ((*bst)->right == NULL) {
				// No children, just delete it
				delete (*bst);
				(*bst) = NULL;
			} else {
				// Only right child, it replaces the node
				YourSet::t_Node	*temp;
				temp = (*bst);
				(*bst) = (*bst)->right;
				delete temp;
			}
		} else {
			if ((*bst)->right == NULL) {
				// Only left child, it replaces the node
				YourSet::t_Node	*temp;
				temp = (*bst);
				(*bst) = (*bst)->left;
				delete temp;
			} else {
				//Two children, successor replaces the node
				YourSet::t_Node *succ = (*bst)->right;
				YourSet::t_Node *succparent = NULL;
				while (succ->left) {
					succparent = succ;
					succ = succ->left;
				}
				if (succparent != NULL) {
					succparent->left = succ->right;
					succ->right = (*bst)->right;
				}
				succ->left = (*bst)->left;
				delete (*bst);
				(*bst) = succ;
			}
		}
		return (true);
	}
}

/*
YourSet::t_Node	*YourSet::__successor(YourSet::t_Node *bst) {
	YourSet::t_Node	*succ = bst->right;
	while (succ->left)
		succ = succ->left;
	return (succ);
} */

YourSet::t_Node	*YourSet::__search(YourSet::t_Node *bst,
	const std::string &data) const {
	if (bst == NULL)
		return (NULL);
	if (data == bst->data)
		return (bst);
	YourSet::t_Node *left = __search(bst->left, data);
	if (left != NULL)
		return (left);
	return __search(bst->right, data);
}
	
YourSet::t_Node	*YourSet::__copynode(YourSet::t_Node *bst) {
	YourSet::t_Node	*newnode = new YourSet::t_Node(bst->data);
	newnode->red = bst->red;
	if (bst->left)
		newnode->left = __copynode(bst->left);
	if (bst->right)
		newnode->right = __copynode(bst->right);
	return (newnode);
};

void	YourSet::__rebalance(YourSet::t_Node **bst) {
	// To be implemented...
	(void)bst;	
}

void	YourSet::__debug(YourSet::t_Node *bst) {
	if (bst) {
		std::cout << "___" << std::endl;
		std::cout << bst->data << std::endl;
		std::cout << bst->left << " " << bst->right << std::endl;
		__debug(bst->left);
		__debug(bst->right);
	}
}
	