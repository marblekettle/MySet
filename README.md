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

MySet also comes with iterators, more information on them in Section **V**. To work with these iterators, MySet has two more member functions:
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

Keeping track of these heights helps us calculate a "Balance Factor" for each node, which is defined as the height of its right child minus the height of its left child. A negative balance factor means that the BST is "left-heavy", while a positive means it is "right-heavy". As long as this balance factor is greater than -2 and smaller than 2, the node is considered balanced and does not need to be rotated. When a node is out of balance, four scenarios can occur that are balanced as follows:

- The balance factor of the node is positive, and so is that of its child.
  - > Rotate the node to the left.
- The balance factor of the node is negative, and so is that of its child.
  - > Rotate the node to the right.
- The balance factor of the node is positive, but that of its child is negative.
  - > Rotate the child node to the right, then rotate the node to the left.
- The balance factor of the node is negative, but that of its child is positive.
  - > Rotate the child node to the left, then rotate the node to the right.

The latter two solutions are also called "right-left" and "left-right" rotations. What follows is an example of a "left-right" rotation and how it keeps the BST valid while neuralising the balance factor and reducing the overall height of the tree:
```
    b                b                d
   / \              / \              / \
  a   e            a   d            b   e
     / \    ->        / \    ->    / \   \
    d   f            c   e        a   c   f
   /                      \
  c                        f
```
After an insertion or deletion, all the nodes whose height may have changed will have to be checked for whether they need to be rebalanced. The convenience of using a recursive algorithm is then that all possibly affected nodes will be reached through backtracking. By running a rebalancing subroutine after every recursion, the whole tree will be rebalanced by the time the backtracking returns to the root.

## V. Iterator

MySet's iterator works as a pointer that can browse through all the data stored in the set in order. The iterator has the properties of a "bidirectional constant iterator". This means the following:
1. It is in canonical form
2. Two iterators can be compared (`==` and `!=` operators)
3. An iterator can be dereferenced as an rvalue: information about what the iterator points to can be extracted (`*` and `->` operators)
4. An iterator can **NOT** be dereferenced as an lvalue: the information an iterator points to can not be modified
5. An iterator can be incremented to point to the next element of a set (`++` operator)
6. An iterator can be decremented to point to the previous element of a set (`--` operator)

Point 4 is what distinguishes a constant iterator from a regular iterator, but it is a necessary property in case of the set. Reassigning a node's data would mean that it belongs elsewhere in the BST, otherwise one could no longer retrieve a sorted order using inorder traversal. However, there is no way to adjust the behavior of a pointer in C++ so that modifying a pointer content will instead result in a removal and consequent insertion of new data. The `std` library specifically makes the node data read-only. A constant iterator has basically the same effect.

Incrementing an iterator means finding the successor of a node. For nodes that have right children, as we've seen before, this is trivial, but otherwise the only option is to retrace steps. Consider the following: In order for a node with a right child to find its successor, all one has to do is go to its right child and then keep going left as far as possible. Likewise, if a node has a left child, one can find it's predecessor by taking its left child and moving right as far as possible, until a node is encountered that does not have a right child. While this does not directly help us, it shows one thing: The successor of a node without a right child will certainly be between the node itself and the root of the tree. In order to find it, one has to follow the same path through the tree as one would doing a lookup of the target node. One of the nodes along this path will be the successor, specifically the lowest node that is still higher than the target node. Note that it is only necessary to keep track of the nodes where one is moving left, since these nodes are higher than the target node. Already knowing how to find the successor for any node, the method can be used symmetrically to find the predecessor of any node as well. 

One thing to mention is that the successor of the highest, rightmost node does not technically exist. When an iterator pointing at this node is incremented, its node will point to NULL. Further increments will loop around to the leftmost element of the BST. Likewise, decrements will reach NULL before the beginning, so that `begin()-- == end()`. This behavior is consistent with the iterator for the standard library set, with the only exception being that `end()` does not point at NULL.

## VI. Testing

MySet comes with two testing modules to verify that all its functionalities work properly: The first is a functional test, the other a performance test. The functional test is split into 6 sections that each showcase different features:
1. Copying: Demonstrates how to insert, lookup and remove elements, copy their data from one set to a new one using a constructor and the assignment overload.
2. Heap Allocation: Demonstrates how the features mentioned in Copying can be used for heap-allocated set objects.
3. Iterator: Demonstrates the functionality of the iterator and how all its operator overloads function.
5. Other Datatypes: The other tests focus on use with sets of `std::string`. This part demonstrates how it functions with other datatypes such as integers and classes.
6. Polymorphism: Demonstrates how derived classes of the set can be used with polymorphism, functioning as valid MySet objects.

The other test, the performance test, runs four different sub-tests or tasks on both MySet and the standard library set object. Each task involves inserting a large amount of data in a predefined order into the sets, which will be found in the `lorem.txt` file, and measures the time elapsed for each task to be completed. Their goal is the see how well MySet handles larger data sets and how its performance compares to the standard library set. These tasks are:
1. Insertion: The entire dataset is inserted into the set using the `add()` method.
2. Lookup: Each word in the dataset is verified to be in the set using the `contains()` method.
3. Iterator: An iterator browses through every single entry in the set by means if increment (the `operator++()` method).
4. Removal: Each word in the dataset is removed from an already filled set.
