A-simple-balanced-search-tree
=============

This is a C++ and python implementation of a simple, balanced, binary search tree that I made as a personal project to make implementing balanced BSTs simpler. It's based on the Scapegoat tree, so its kinda similar to it.

The balancing method is explained as, <br/>
**"Every subtree has a timer, and we decrease it by 1 each time we insert or delete a node in the subtree. If a subtree’s timer reaches 0, we simply rebuild it and reset its timer to a fraction of its size."**


In more details, tree operations are done as following.
- **Insert**
  1. Insert a leaf node (just as in an ordinary BST).
  2. Go back up the trail from the leaf node to the root, and for each node t, do Update(t).
- **Delete**
    1. Delete a leaf node.
    2. Go back up the trail from the leaf node to the root, and for each node t, do Update(t).
- **Update(t)**
    1. Decrease t.timer by 1.
    2. If t.timer is now 0, *rebuild* the subtree rooted by t.
        - "An example way to rebuild" :
        1. Move all nodes to an array in increasing order, such as by using an inorder traversal.
        2. Use a divide-and-conquer method to make a perfectly balanced tree from the array. Don't forget to reset the timer for every subtree.
  
Compared to an implementation of an ordinatry BST, <strong>Search</strong> operations remain the same, and for **Insert** and **Delete** operations, everything we additionally need can be encapsulated inside a single **Update(t)** function.
  
Details or a proof can be found in the source files or the included draft.
