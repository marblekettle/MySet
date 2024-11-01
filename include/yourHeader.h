#ifndef YOURHEADER_H
# define YOURHEADER_H
# define NODE YourSet::t_Node
# include <cstddef>
# include <string>
# include <iostream>

/**
*	The set class stores string data in a red-black binary search tree.
*	This creates a balance between search time and insert/delete time.
*	This version is hardcoded to only accept std::string data, but can be
*	modified into a template, so other storage types (e.g. dict/map) can
*	inherit from it. I have not done so, because templates would require
*	the entire implementation to be in the template header, which hinders
*	readability.
*/

class YourSet {
public:
	// All the canonical form stuff goes here
	// Default Constructor
	YourSet();
	// Destructor
	~YourSet();
	// Copy constructor
	YourSet(const YourSet &x);
	// Assignment overload
	YourSet	&operator=(const YourSet &x);

	// Insert data into BST, will return false if data is already present
	bool	add(const std::string &data);
	// Returns true if the BST already contains this data
	bool	contains(const std::string &data);
	//
	bool	remove(const std::string &data);

	void	debug();

private:

	// Struct for BST nodes (branches)
	typedef struct		s_Node {
		// String data
		std::string		data;
		// Pointers to left and right sub-nodes
		struct s_Node	*left;
		struct s_Node	*right;
		// Boolean to indicate node color (0 = black, 1 = red)
		bool			red;
		// Function to initialize new nodes
		s_Node(const std::string &d) {
			data = std::string(d);
			left = NULL;
			right = NULL;
			// Upon creation, a red-black BST node is always red
			red = true;
		}
	}					t_Node;

	// Internal functions for handling nodes

	// Insert node into root BST
	bool	__insertnode(t_Node **bst, const std::string &data);

	// Delete node and any sub-nodes
	void	__clearnode(t_Node *bst);

	// Delete only the node that matches the data
	bool	__deletenode(t_Node **bst, const std::string &data);

	// Returns the node that is sub-node to the given node that has matching data
	t_Node	*__search(t_Node *bst, const std::string &data) const;

	// Copy node and any sub-nodes
	t_Node	*__copynode(t_Node *bst);

	// Modify the BST such that it is still a valid red-black BST
	void	__rebalance(t_Node **bst);

	void	__debug(t_Node *bst);

	// BST Root
	t_Node	*_root;
};

#endif