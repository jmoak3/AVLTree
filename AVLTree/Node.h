#pragma once
#include "Util.h"

class Node {
public:
	Node() : value(0), left(nullptr), right(nullptr) {}
	Node(int value) : value(value), left(nullptr), right(nullptr) {}
	Node(int value, pNode newLeft, pNode newRight) : value(value), left(newLeft), right(newRight) {}
	~Node() {}

	pNode getLeft() const { return left; }
	pNode getRight() const { return right; }
	int getValue() const { return value; }
	bool hasLeft() const { return left!=nullptr; }
	bool hasRight() const { return right!=nullptr; }

	bool setLeft(pNode newLeft) { left = newLeft; return true; }
	bool setRight(pNode newRight) { right = newRight; return true; }
	bool setValue(int newValue) { value = newValue; return true; }

private:
	int value;
	pNode left;
	pNode right;
};
