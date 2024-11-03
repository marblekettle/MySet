# MySet
***By Brendan Mans (MarbleKettle)***

MySet is a simplified replica of the std::set data structure used in C++. I wrote it as a template so that it can be used for any data type, as long as that data type supports the comparison operators ==, <, and >. To store data, it uses an AVL Binary Search Tree (or BST). MySet may even be, in the future, used to implement map/dictionary objects. My specific intention with MySet is to write code that is readable, well-documented, and re-usable. This README document contains supplementary information about the design choices and implementation of MySet.

## I. What is a set?

A set is a data structure, a container of data, that has the following properties:

- It contains a collection of objects, called its 'elements', that all have the same data type
    - This sets it apart from data structures like Python's "`list`" object
- The elements have no particular order
    - This sets it apart from structures like vectors or lists
- All elements are unique: There are no duplicates
    - This sets it apart from so-called Multi-sets
- Elements are constant and cannot be changed, only added, or removed
    - This is technically a property specific to a so-called "mutable set": Technically a "static" set doesn't allow for adding or removing either, but for practical purposes by "set" we refer to a mutable set in this document.

There is a technical reason for the last property that we'll get to later. If one wishes to 'change' an element, removing it and inserting another element is the only valid option. In addition, MySet implements an "ordered" set: Despite the 2<sup>nd</sup> property, the elements of the set are still stored in a way that one can iterate through all the elements in an ordered fashion: Each element has a "next" element. In a way, the elements are sorted, and this has everything to do with the way in which the elements are stored as data.

## II. Using MySet

In order to use the MySet class, the files found in the `include` directory, `Set.h`, `Set.tpp`, and `SetIterator.tpp` are needed. The only one you have to include, however, is `Set.h`. It is customary for the entire template class implementation to be placed inside a header file. However, I chose not to do this, as it is also customary to separate header and implementation where possible, and doing so is generally beneficial to readability.

The MySet class is part of the `My` namespace and defined as "`Set`". Since it is a template class, it also requires a data type to be specified to be a complete object. For example, in order to create a MySet object for use with `std::string`, the proper data type is `My::Set<std::string>`.

MySet has 5 member functions. In addition, it is in canonical (Coplien) form, meaning that it has a default and copy constructor, destructor, and assignment operator overload. The other member functions are:
- `add(data)`: Insert an element with `data` into the set - Returns `true` if the data is inserted, `false` if the set already contains the data and it cannot be inserted.
- `contains(data)`: Checks if an element with `data` is already inserted into the set - Returns `true` if it is, `false` if not.
- `remove(data)`: Removes an element with `data` from the set if it does - Returns `true` if the data is successfully removed, `false` if the data was not found.

In order to talk about the other two member functions, we should first mention the iterator object. MySet also has an iterator object that has the properties of a "forward constant iterator". This means the following:
- It is in canonical form
- Two iterators can be compared
- An iterator can be dereferenced as an rvalue: information about what the iterator points to can be extracted
- An iterator can **NOT** be dereferenced as an lvalue: the information an iterator points to can not be modified
- An iterator can be incremented to point to the next element of a set

To work with these iterators, MySet has two more member functions:
- `begin()`: Returns an iterator that points at the first (or lowest) element in the set
- `end()`: Returns an iterator that points at a nonexistent node that would be placed *beyond* the last (highest) element in the set. If an iterator pointing to the last element of the set is incremented, this is what it will be equal to.

## III. Binary Search Tree

MySet, similarly to many other set data structures, makes use of a Binary Search Tree under the hood. A BST works similarly to a chained list, but rather than forming a single connected chain, the elements can each have two elements connected to it. A full BST consists of the following parts:
- A root: This is a pointer that points to the topmost element of the tree
- Nodes (or branches): Each node represents an element, and contains pointers that can either be NULL (leaves) or point to other nodes.
- Leaves: The pointers of nodes that are NULL. These mean the end of the tree is reached, but new nodes may be placed here.

The convenience of a BST is that when inserting data, it can be placed in such a way that the whole tree remains ordered (sorted). For each node, all nodes attached to the left are lower, all nodes to the right are higher. By traversing the tree inorder, this will reach every single element in the order from lowest to highest. Note that "lower" and "higher" here depend on how comparison works for a particular data type (e.g. the "higher" of two integers is the one with the greatest value, the "higher" of two strings of characters is the one lexicologically further in the dictionary). Inserting data into a BST works according to the following algorithm:
1. Start at the root: It will be the `current node`
2. Compare the `new data` with the data stored in the `current node`
3. If the `current node` is a leaf, this is where the `new data` will be inserted: We are **done**
4. If the `data` of the `current node` is *higher* than the `new data`, the `current node`'s *left* node will become the new `current node`
5. If the `data` of the `current node` is *lower* than the `new data`, the `current node`'s *right* node will become the new `current node`
6. Go back to step 2 and repeat until it ends with step 3

