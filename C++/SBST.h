// SBST.h
#ifndef SBST_H
#define SBST_H

//#include <iostream>
#include <vector>
using namespace std;

template <typename T>
/* A simple, balanced, binary search tree.
Use a K value in (0, 1). */
class SBST{
public:
	SBST() { root = NULL; k = 0.9; } //Any k in (0, 1) is fine.
	SBST(double K) { root = NULL; k = K; }
	~SBST() { _clear(root); }

	bool search(T v) { return _search(root, v) != NULL; }
	bool insert(T v) {
		bool result = false;
		_insert(root, v, result);
		return result;
	}
	bool remove(T v) {
		bool result = false;
		_delete(root, v, result);
		return result;
	}

	void clear() { _clear(root); root = NULL; }
	//void debug() { _debug(root, 0); }

private:
	struct NODE {
		NODE *left, *right;
		T key;
		int timer;

		NODE(T v) {
			left = right = NULL;
			key = v;
			timer = 1;
		}
	};
	NODE *root;
	double k;

	NODE* _search(NODE* t, T &v) {
		if (t == NULL) return NULL;
		else if (v == t->key) return t;
		else if (v < t->key) return _search(t->left, v);
		else return _search(t->right, v);
	}

	void _insert(NODE* & t, T &v, bool &result) {
		if (t == NULL) {  //Create a new node
			result = true;
			t = new NODE(v);
			return;
		}
		else if (v < t->key) _insert(t->left, v, result);
		else if (v > t->key) _insert(t->right, v, result);
		else result = false;

		if (result) _update(t);
	}

	void _delete(NODE* & t, T &v, bool &result) {
		if (t == NULL) result = false;
		else if (v < t->key) _delete(t->left, v, result);
		else if (v > t->key) _delete(t->right, v, result);
		else {									  //Node found
			if (t->left && t->right) {			  //Both child nodes exist.
				t->key = _getMax(t->left)->key;	  //Find the inorder predecessor of t and copy its key.
				_delete(t->left, t->key, result); //Delete the inorder predecessor. Note that it always has 0 or 1 child nodes.
			}
			else {							      //0 or 1 child nodes exist.
				NODE* successor = NULL;		      //If t is a leaf, its successor is NULL. Otherwise, its successor is its sole child node.
				if (t->left) successor = t->left;
				else successor = t->right;
				delete t;
				t = successor;
				result = true;
				return;
			}
		}
		if (result) _update(t);
	}

	/* Auxillary function used in _delete */
	NODE* _getMax(NODE* t) {
		while (t->right != NULL) t = t->right;
		return t;
	}

	void _update(NODE* &t) {
		t->timer -= 1;
		if (t->timer <= 0) {	//now rebuild the subtree
			vector<NODE*> nodeArr;
			_getCopy(t, nodeArr);
			t = _buildTree(nodeArr, 0, nodeArr.size() - 1);
		}
	}

	/* Auxillary function used in _update for rebuilds */
	void _getCopy(NODE* t, vector<NODE*> &nodeArr) {
		if (t == NULL) return;
		_getCopy(t->left, nodeArr);
		nodeArr.push_back(t);
		_getCopy(t->right, nodeArr);
	}

	/* Auxillary function used in _update for rebuilds */
	NODE* _buildTree(vector<NODE*> &nodeArr, int s, int f) {
		if (s > f) return NULL;
		int m = (s + f + 1) / 2;
		NODE* t = nodeArr[m];
		t->left = _buildTree(nodeArr, s, m - 1);
		t->right = _buildTree(nodeArr, m + 1, f);
		t->timer = int(k*(f - s + 1));
		if (t->timer < 1) t->timer = 1;
		return t;
	}

	void _clear(NODE *t) {
		if (t == NULL) return;
		_clear(t->left);
		_clear(t->right);
		delete t;
	}

	/*
	void _debug(NODE *t, int depth) {
		if (t == NULL) return;
		_debug(t->left, depth + 1);
		cout << "key : " << t->key << ", depth : " << depth << ", timer : " << t->timer << endl;
		_debug(t->right, depth + 1);
	}
	*/
};
#endif
