# Min Heap

## Overview

##### Basic Operations

* Insert O(log<sub>2</sub>n)
* Deletemin O(log<sub>2</sub>n)

This is an array implementation of a traditional Minimum Priority Queue. Using an array to simulate a tree structure, smaller values are "floated" to the top while larger values make their way down. The tree structure of a binary heap achieves a complexity O(log<sub>2</sub>n). The Binary Heap is actually a special case of a d-ary Heap, which is bound by O(log<sub>d</sub>n) where d is the maximum number of children per node.

##### Key Properties

* Shape property: A binary heap is a complete binary tree; that is, all levels of the tree, except possibly the last one (deepest) are fully filled, and, if the last level of the tree is not complete, the nodes of that level are filled from left to right.

* Heap property: All nodes are either greater than or equal to or less than or equal to each of its children, according to a comparison predicate defined for the heap.


### Implementation Details

Entirely done in C. Because access to familiar tools like the C++ STL are not available, the heap is constructed with a statically allocated array whose size is arbitrarily defined by a Macro. The rational for this choice is to avoid the complication of resizing the array upon reaching max capacity, which is not the point of this implementation. After every operation, the heap ensures integrity by evaluating each of its the elements follows the heap property.

Using Valgrind, the data structure has been confirmed to avoid memory leaks of any kind. 

In addition, the repo comes with a test generation executable that can create a variety of scenarios. 
