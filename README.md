A simple balanced search tree
=============

This is a C++ and python implementation of a simple, balanced, binary search tree that I made as a personal project to make implementing balanced BSTs simpler. It's based on the Scapegoat tree, so it's kinda similar to it.

# How to use
Just copy the SBST.h or sbst.py file and put it in your project file.

In your C++ source code, to make a SBST that stores int keys, for example, use
```
SBST<int> bst;
```
and to search, insert, or delete a key, you can do something like
```
bst.search(10); //bool type, O(logn)
bst.insert(20); //bool type, amortized O(logn)
bst.delete(20); //bool type, amortized O(logn)
```

# Balancing method
The balancing method can be explained as, <br/>
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
        - (An example way to rebuild) :
        1. Move all nodes to an array in increasing order, such as by using an inorder traversal.
        2. Use a divide-and-conquer method to make a perfectly balanced tree from the array. Don't forget to reset the timer for each subtree.
  
Compared to an implementation of an ordinatry BST, <strong>Search</strong> operations remain the same, and for **Insert** and **Delete** operations, everything we additionally need is encapsulated inside a single **Update(t)** function.
  
Details or a proof can be found in the source files or the included pdf file.
