#include <iostream>
#include "SBST.h"

int main() {
	SBST<int> tree;
	tree.insert(10);
	tree.insert(15);
	tree.insert(20);
	if (tree.search(20))
		cout << "found" << endl;

	tree.remove(20);
	if (!tree.search(20))
		cout << "not found" << endl;
	
	tree.clear();
	if (!tree.search(10))
		cout << "not found" << endl;

	return 0;
}