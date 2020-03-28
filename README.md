A-simple-balanced-search-tree
=============

This is an implementation of a simple, balanced, binary search tree that I made as a personal project to make implementing balanced BSTs simpler. It's a lot similar to the Scapegoat tree since this was based on it.

The balancing method is, <br/>
<strong>"Every subtree has a timer, and we decrease it by 1 each time we insert or delete a node in the subtree. If a subtree’s timer reaches 0, we rebuild it and reset its timer to a fraction of its size."</strong>


In more details, tree operations are done as following.
* Insert
  1. Insert a leaf node (like in a basic BST).
  2. Re-follow the trail from the leaf node to the root. For each node t, do Update(t).
* Delete
  1. Delete a leaf node.
  2. Re-follow the trail from the leaf node to the root. For each node t, do Update(t).
* Update(t)
  1. Decrease t.timer by 1.
  2. If t.timer is now 0, rebuild the subtree rooted by t.
* Rebuild
  1. GetCopy: Using an inorder traversal, copy all nodes of the subtree to an array.
  2. BuildTree: Make a perfectly balanced subtree using this array in a divide-and-conquer sense. We also reset each subtree’s timer.
  
Details or proof can be found in the included draft.
