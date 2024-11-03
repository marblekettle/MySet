#ifndef YOURHEADER_H
# define YOURHEADER_H
# include <cstddef>
# include <string>
# include <iostream>

/**
*	The set class stores string data in an AVL binary search tree. This
*	provides an optimally balanced BST, with slightly more insertion/deletion
*	This version is hardcoded to only accept std::string data, but can be
*	modified into a template, so other storage types (e.g. dict/map) can
*	inherit from it. I have not done so, because templates would require
*	almost the entire implementation to be in the template header, which
*	hinders readability.
*/

//	This enum is used to indicate direction
typedef enum		e_Dir : bool {
	LEFT,
	RIGHT
}					t_Dir;

class YourSet {

private:
	// Struct for BST nodes (branches)
	typedef struct		s_Node {
		// String data
		std::string		data;
		// Pointers to left and right sub-nodes
		struct s_Node	*left;
		struct s_Node	*right;
		// Pointer to parent node
		int				height;
		// Function to initialize new nodes
		s_Node(const std::string &d) {
			data = std::string(d);
			left = NULL;
			right = NULL;
			height = 1;
		}
	}					t_Node;

	// BST Root
	t_Node	*_root;

	// Internal functions for handling nodes

	// Insert node into root BST
	// Returns a pointer to the inserted node
	t_Node	*__insert_node(t_Node **node, const std::string &data);

	// Delete node and any sub-nodes
	void	__clear_node(t_Node *node);

	// Remove only the node that matches the data
	// Returns a pointer to the node to be removed
	t_Node	*__delete_node(t_Node **node, const std::string &data);

	// Find a node's successor
	// Returns a pointer to the successor node
	t_Node	*__successor(t_Node *node);

	// Replaces a node with its successor and deletes the original
	// (called when a node with two children has to be deleted)
	void	__successor_switch(t_Node *node);

	// Returns the node that is sub-node to the given node that has matching data
	t_Node	*__search(t_Node *node, const std::string &data) const;

	// Copy node and any sub-nodes
	// Returns the copied node	
	t_Node	*__copy_node(t_Node *node);


	// The following functions are used only for rebalancing
	// Returns the height of a node (0 for leaves)
	int		__height(t_Node *node);

	// Rotate nodes to rebalance an unbalanced node
	void	__fix_balance(t_Node **node);

	// Rotate this node left or right
	void	__rotate(t_Node **node, t_Dir l_or_r);

	// Print some info about a node to STDOUT
	void	__debug(t_Node *node);

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
	// Removes the node containing data, will return false if not found
	bool	remove(const std::string &data);
	// Prints some useful info about the BST
	void	debug();

	// Iterator sub-class (technically a const_iterator)

	class iterator : public std::iterator<
		std::forward_iterator_tag, std::string> {
	private:
		// Stores a pointer to the root of its designated BST for reference
		YourSet	*_set;
		// And a pointer to the target node it is pointing at
		t_Node	*_node;

	public:
		// Constructor
		iterator();
		// Constructor binding it to an existing set's leftmost node of a BST
		iterator(YourSet &x);
		// Destructor
		~iterator();
		// Copy constructor
		iterator(const iterator &x);
		// Assignment overload
		// ( ex: it1 = it2 )
		iterator	&operator=(const iterator &x);
		// Comparison
		// ( ex: it1 == it2 )
		bool		operator==(const iterator &x) const;
		// ( ex: it1 != it2 )
		bool		operator!=(const iterator &x) const;
		// Increment
		// ( ex: ++it )
		iterator	&operator++();
		// ( ex: it++ )
		iterator	operator++(int x);
		// Dereference (only dereferences as rvalue)
		// ( ex: str = *it )
		const std::string	&operator*() const;
		// ( ex: it->length() )
		const std::string	*operator->() const;

		// Needs access to the root node of the set BST
		friend class YourSet;
	};

	// Return an iterator pointing at the first (left-most) node
	iterator	begin();
	// Return an iterator pointing at a null node
	iterator	end();
};

#endif