#include "Tree.h"

pNode Tree::sharedPointerHelper(Node* n)
{
	return std::shared_ptr<Node>(n);
}

bool Tree::insertHelper(pNode node, int value, pNode parent)
{
	if (node->getValue() > value)
	{
		if (node->hasLeft())
			return insertHelper(node->getLeft(), value, node);
		else
		{
			node->setLeft(sharedPointerHelper(new Node(value)));
			balance(parent);
			return true;
		}
	}
	else
	{
		if (node->hasRight())
			return insertHelper(node->getRight(), value, node);
		else
		{
			node->setRight(sharedPointerHelper(new Node(value)));
			balance(parent);
			return true;
		}
	}
}
bool Tree::insert(int value)
{
	if (root == nullptr)
	{
		root = sharedPointerHelper(new Node(value));
		return true;
	}
	else
	{
		return insertHelper(root, value, nullptr);
	}
}

bool Tree::containsHelper(pNode node, int value)
{
	if (node == nullptr) return false;
	if (node->getValue() == value) return true;
	else if (node->getValue() > value) return containsHelper(node->getLeft(), value);
	else return containsHelper(node->getRight(), value);
}
bool Tree::contains(int value)
{
	return containsHelper(root, value);
}

int Tree::removeHelper(pNode node, int value, pNode parent)
{
	if (node == nullptr)
	{
		std::cout << "Node not found!" << std::endl;
		return -1;
	}
	else if (node->getValue() > value && node->hasLeft())
	{
		pNode leftNode = node->getLeft();
		if (leftNode->getValue() == value)
		{
			if (leftNode->hasRight())
			{
				node->setLeft(leftNode->getRight());
				balance(parent);
				return value;
			}
			else if (leftNode->hasLeft())
			{
				node->setLeft(leftNode->getLeft());
				balance(parent);
				return value;
			}
			else
			{
				node->setLeft(nullptr);
				balance(parent);
				return value;
			}
		}
		else
		{
			return removeHelper(leftNode, value, parent);
		}
	}
	else if (node->hasRight())
	{
		pNode rightNode = node->getRight();
		if (rightNode->getValue() == value)
		{
			if (rightNode->hasRight())
			{
				node->setRight(rightNode->getRight());
				balance(parent);
				return value;
			}
			else if (rightNode->hasLeft())
			{
				node->setRight(rightNode->getLeft());
				balance(parent);
				return value;
			}
			else
			{
				node->setRight(nullptr);
				balance(parent);
				return value;
			}
		}
		else
		{
			return removeHelper(rightNode, value, parent);
		}
	}
	else
	{
		std::cout << "Node not found!" << std::endl;
		return -1;
	}
}
int Tree::remove(int value)
{
	if (root == nullptr) return INT_MIN;
	if (root->getValue() == value)
	{
		if (root->hasRight())
		{
			int newValue = remove(getMin(root->getRight()));
			root->setValue(newValue);
			balance(root);
			return value;
		}
		else if (root->hasLeft())
		{
			int newValue = remove(getMax(root->getLeft()));
			root->setValue(newValue);
			balance(root);
			return value;
		}
		else
		{
			root = nullptr;
			balance(root);
			return value;
		}
	}
	else return removeHelper(root, value, nullptr);
}

int Tree::getMax() const
{
	pNode temp = root;
	if (temp == nullptr) return INT_MIN;
	//Get most right guy
	while (temp->getRight()) temp = temp->getRight();
	return temp->getValue();
}

int Tree::getMin() const
{
	pNode temp = root;
	if (temp == nullptr) return INT_MIN;
	//Get most left guy
	while (temp->getLeft()) temp = temp->getLeft();
	return temp->getValue();
}

int Tree::getMax(pNode node) const
{
	//Get most right guy 
	while (node->getRight()) node = node->getRight();
	return node->getValue();
}

int Tree::getMin(pNode node) const
{
	//Get most left guy
	while (node->getLeft()) node = node->getLeft();
	return node->getValue();
}

void Tree::preOrderHelper(pNode node)
{
	if (node == nullptr) return;
	std::cout << node->getValue() << " ";
	preOrderHelper(node->getLeft());
	preOrderHelper(node->getRight());
}
void Tree::traversePreOrder()
{
	std::cout << "PreOrder: ";
	return preOrderHelper(root);
}

void Tree::inOrderHelper(pNode node)
{
	if (node == nullptr) return;
	inOrderHelper(node->getLeft());
	std::cout << node->getValue() << " ";
	inOrderHelper(node->getRight());
}
void Tree::traverseInOrder()
{
	std::cout << "InOrder: ";
	return inOrderHelper(root);
}

void Tree::postOrderHelper(pNode node)
{
	if (node == nullptr) return;
	postOrderHelper(node->getLeft());
	postOrderHelper(node->getRight());
	std::cout << node->getValue() << " ";
}
void Tree::traversePostOrder()
{
	std::cout << "PostOrder: ";
	return postOrderHelper(root);
}

int Tree::getHeight(pNode node)
{
	int leftHeight = 1;
	int rightHeight = 1;
	if (node->hasLeft())
		leftHeight = getHeight(node->getLeft()) + 1;
	if (node->hasRight())
		rightHeight = getHeight(node->getRight()) + 1;

	return (leftHeight > rightHeight) ? leftHeight : rightHeight;
}

int Tree::calcBalance(pNode node)
{
	int balance = 0;
	if (node->hasLeft())
		balance -= getHeight(node->getLeft());
	if (node->hasRight())
		balance += getHeight(node->getRight());

	return balance;
}

void Tree::balance(pNode node)
{
	if (node == nullptr) return;

	if (node->hasLeft())
		balance(node->getLeft());
	if (node->hasRight())
		balance(node->getRight());

	int bal = calcBalance(node);
	if (bal == 2)
	{
		//left rot?
		if (node->hasRight() && node->getRight()->hasRight())
			rotateLeft(node, node->getRight());
		//right left rot?
		if (node->hasLeft() && node->getLeft()->hasRight())
			rotateLeftRight(node, node->getLeft());
	}
	else if (bal == -2)
	{
		//right rot?
		if (node->hasLeft() && node->getLeft()->hasLeft())
			rotateRight(node, node->getLeft());
		//left right rot?
		if (node->hasLeft() && node->getLeft()->hasRight())
			rotateLeftRight(node, node->getLeft());
	}
}

void Tree::rotateRight(pNode parent, pNode left)
{
	parent->setRight(sharedPointerHelper(new Node(parent->getValue())));
	parent->setValue(left->getValue());
	parent->setLeft(left->getLeft());
}
void Tree::rotateLeft(pNode parent, pNode right)
{
	parent->setLeft(sharedPointerHelper(new Node(parent->getValue())));
	parent->setValue(right->getValue());
	parent->setRight(right->getRight());
}
void Tree::rotateRightLeft(pNode parent, pNode right)
{
	right->setRight(sharedPointerHelper(new Node(right->getLeft()->getValue())));
	right->setValue(right->getLeft()->getValue());
	right->setLeft(nullptr);
	rotateLeft(parent, right);
}
void Tree::rotateLeftRight(pNode parent, pNode left)
{
	left->setLeft(sharedPointerHelper(new Node(left->getRight()->getValue())));
	left->setValue(left->getRight()->getValue());
	left->setRight(nullptr);
	rotateRight(parent, left);
}

