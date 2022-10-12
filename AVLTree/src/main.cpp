#include <iostream>
#include "avl_tree.h"

int main() {
	AVLTree<int> tree;
	tree.Insert(5);
	tree.Insert(4);
	tree.Insert(6);
	tree.Insert(1);
	tree.Insert(2);
	std::cout << tree.HasValue(2) << '\n';
	std::cout << tree.IsEmpty() << '\n';
	tree.Remove(1);
	tree.PrintAll();
    return 0;
}
