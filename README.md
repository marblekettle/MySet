# MySet
***By Brendan Mans (MarbleKettle)***

MySet is a simplified replica of the std::set data structure used in C++. I wrote it as a template so that it can be used for any data type, as long as that data type supports the comparison operators ==, <, and >. To store data, it uses an AVL Binary Search Tree (or BST), which has some advantages over a regular BST that maximize lookup speed, with slightly slower insertion and removal speed as a trade-off. MySet may be, in the future, used to implement map/dictionary objects. My specific intention with MySet is to write code that is readable, well-documented, and re-usable. This README document contains supplementary information about the design choices and implementation of MySet.

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
- Two iterators can be compared (`==` and `!=` operators)
- An iterator can be dereferenced as an rvalue: information about what the iterator points to can be extracted (`*` and `->` operators)
- An iterator can **NOT** be dereferenced as an lvalue: the information an iterator points to can not be modified
- An iterator can be incremented to point to the next element of a set (`++` operator)

To work with these iterators, MySet has two more member functions:
- `begin()`: Returns an iterator that points at the first (or lowest) element in the set
- `end()`: Returns an iterator that points at a nonexistent node that would be placed *beyond* the last (highest) element in the set. If an iterator pointing to the last element of the set is incremented, this is what it will be equal to.

## III. Binary Search Tree

MySet, similarly to many other set data structures, makes use of a Binary Search Tree under the hood. A BST works similarly to a chained list, but rather than forming a single connected chain, the elements can each have two elements connected to it. A full BST consists of the following parts:
- A root: This is a pointer that points to the topmost element of the tree
- Nodes (or branches): Each node represents an element, and contains pointers that can either be NULL (leaves) or point to other nodes.
- Leaves: The pointers of nodes that are NULL. These mean the end of the tree is reached, but new nodes may be placed here.

The convenience of a BST is that when inserting data, it can be placed in such a way that the whole tree remains ordered (sorted). For each node, all nodes attached to the left are lower, all nodes to the right are higher. By traversing the tree inorder, this will reach every single element in the order from lowest to highest. Note that "lower" and "higher" here depend on how comparison works for a particular data type (e.g. the "higher" of two integers is the one with the greatest value, the "higher" of two strings of characters is the one lexicologically further in the dictionary). This is also the reason that the iterator has to be constant: Dereferencing a pointer as an lvalue may allow the user to modify its data, which means that the whole set will no longer be inorder-sorted, unless the element is removed and placed somewhere else. Inserting data into a BST works recursively according to the following algorithm:
1. Start at the root: It will be the `current node`
2. Compare the `new data` with the data stored in the `current node`
3. If the `current node` is a leaf, this is where the `new data` will be inserted: We are **done**
4. If the `data` of the `current node` is *higher* than the `new data`, go back to step 2 with the `current node`'s **left** node as the new `current node`
5. If the `data` of the `current node` is *lower* than the `new data`, go back to step 2 with the `current node`'s **right** node as the new `current node`

Lookup in a BST goes in a similar manner, moving to the left child if the data is lower, the right child if the data is higher, until a node is found that matches the data, verifying that it was already inserted before. MySet does this in an iterative manner, overwriting the same node pointer with the next node. This is because in the case of lookup, there is no need for backtracking as with insertion or removal, for a reason we will get into later.

Removing a node is slightly more complicated, because the node may not always be at the very end of the tree as is the case with insertion. Here we distinguish three different scenarios that may occur, after we've recursively moved through the BST and found the node to be removed:
- The node has no children: This means it is at the end of the tree and can be removed with no changes to the rest of the tree.
- The node has exactly one child: In this case, it suffices to simply replace the node with its one child. We can justify this: Suppose the node we want to remove is called `N`. We call its child `C` and its parent `P`. If `C` is on the **left** of `N`, then we know that the entire sub-tree with `C` at the top is lower than `N`, otherwise it would be part of `N`'s **right** child. If `N` < `P`, then `C` < `P`, and `C` fits as `P` **left** child. If `N` > `P`, note that any nodes lower than `P` would be in `P`'s **left** child, meaning that all sub-notes of `N`, and by extension `C`, will be in between `P` and `N`. This means that `C` > `P`, and `C` can become the **right** child of `P`. The symmetrical case applies when `C` is on the **right** of `N`.
- The node has two children: In this case we have to find the inorder successor. Fortunately, this will just be the lowest node that is still part of the sub-tree to the right of the node to be removed. Since the lowest value in a BST is always to its far left, all we need to do is go into this right tree and then keep going left to find the inorder successor. Next, we switch the node with the inorder successor, the latter now in its proper place. Since the inorder successor was guaranteed not to have a left child, the node that replaces it now has at most one child and can be removed in one of the above two methods: We simply have to find it in the right sub-tree. Recursion is useful here, as we can just apply the same routine again on the successor's right child.

## IV. AVL BST

The type of BST used with MySet is called an AVL Tree (short for Adelson-Velsky-Landis). This is, besides the Red-Black Tree, the most well-known and used type of a self-balancing BST. The height of a self-balancing BST, which means the greatest number of notes one needs to go through to find a leaf, is `O(log(n))` where `n` is the total number of nodes, while a regular BST will have `O(n)` as worst case (where all nodes are on the same side and the tree is essentially a chained list). Red-Black Trees are most commonly used, and work by coloring each node red or black and having a number of rules regarding these colors in place that require tree rebalancing when violated. In comparison to AVL, they perform on average fewer operations whenever a new node is inserted or another one removed, though this may result in a slightly less balanced tree for large data sets. AVL, however, tries to maintain an optimal balance at all times which often requires more operations during inserting and deleting, but save time during lookups. This is why they are often specifically used for set datastructures in databases, where there may be a large number of lookups in between modifications.

Both AVL and Red-Black trees rebalance by means of so-called rotations, which may be left or right. If a node is rotated left, it is replaced by its right child. It will become the former child's left child, and its new right child is the original left-child of the former child (even if it is a leaf). This will result in a tree with a different base node that still follows the rules of a BST.

Here is an example of a left rotation in node `b`. It's right child, `d`, takes it's place at the top.

```
  b                    d
 / \                  / \
a   d        ->      b   e
   / \              / \
  c   e            a   c
```
If we were to rotate this tree left in `d` however, the result would be this:

```
  b                    b
 / \                  / \
a   d        ->      a   e
   / \                  /
  c   e                d
                      /
                     c
```

In order to determine when a node has to be rotated, every node also has a 'height' property, which represents its distance to the furthest leaf down. Nodes at the end of the tree have a height of 1, since they are considered to be the only nodes between it and its leaves. Every node up from that has a height of 1 plus the greater of its child nodes' height. If we look at the tree in the above example, before its rotation, `a` has a height of 1, `d` has a height of 2, so `b` has a height of 3.

Keeping track of these heights helps us calculate a "Balance Factor" for each node, which is defined as the height of its left child minus the height of its right child. As long as this balance factor is greater than -2 and smaller than 2, the node is considered balanced and does not need to be rotated.
