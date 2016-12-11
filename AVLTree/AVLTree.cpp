#include "Util.h"
#include "Tree.h"

int main()
{
	std::cout << "AVL TREE !" << std::endl;

	std::cout << "Making AVL Tree with root 5" << std::endl;
	Tree tree(5);
	tree.traverseInOrder();
	std::cout << std::endl;

	std::cout << "Adding a node of 4" << std::endl;
	tree.insert(4);
	tree.traversePostOrder();
	std::cout << std::endl;

	std::cout << "Getting Smallest node value (4): " << std::endl;
	std::cout << tree.getMin() << std::endl;

	std::cout << "Adding 1, 7, 8, 3. InOrder should be 1 3 4 5 7 8, PostOrder should be  3 1 5 8 7 4" << std::endl;
	tree.insert(1); tree.insert(7); tree.insert(8); tree.insert(3);
	tree.traverseInOrder();
	tree.traversePostOrder();
	std::cout << std::endl;

	std::cout << "Getting largest Node (8) " << std::endl;
	std::cout << tree.getMax() << std::endl;

	std::cout << "removing 5. In order should be 1 3 4 7 8 " << std::endl;
	if (tree.contains(5)) tree.remove(5);
	tree.traverseInOrder();
	std::cout << std::endl;

	std::cout << "PostOrder should be  3 1 8 7 4" << std::endl;
	tree.traversePostOrder();
	std::cout << std::endl;

	std::cout << "Removing 4. PostOrder should be 3 1 8 7" << std::endl;
	if (tree.contains(4)) tree.remove(4);
	tree.traversePostOrder();
	std::cout << std::endl;

	std::cout << "In order should be 1 3 7 8 " << std::endl;
	tree.traverseInOrder();
	std::cout << std::endl;

	std::cout << "Adding 5. Postorder should be 1 5 3 8 7 " << std::endl;
	tree.insert(5);
	tree.traversePostOrder();
	std::cout << std::endl;
	
	std::cin.get();
	return 0;
}