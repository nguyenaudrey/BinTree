/*
* Student: Audrey Nguyen
* Professor: Christopher Esposito
* Assignment #2: BinTree
* Description: Header file for a representation of a Binary Search Tree
* Code was provided by the professor and modified by the student
*/

#ifndef BINTREE_H
#define BINTREE_H

#include <iostream>
#include <string>
#include "nodedata.h"

using namespace std;

class BinTree {				
public:
	BinTree();								// constructor
	BinTree(const BinTree&);				// copy constructor
	~BinTree();								// destructor, calls makeEmpty	
	bool isEmpty() const;					// true if tree is empty, otherwise false
	void makeEmpty();						// make the tree empty so isEmpty returns true
	BinTree& operator=(const BinTree&);
	bool operator==(const BinTree&) const;
	bool operator!=(const BinTree&) const;
	bool insert(NodeData*);
	bool retrieve(const NodeData& target, NodeData*& retVal) const;
	void displaySideways() const;			// provided in cpp file, displays the tree sideways

	// Back and Forth to An Array
	void bstreeToArray(NodeData* array[]);

	// Gets the trees & element's height
	int getHeight(const NodeData& target) const;
	int getTreeHeight() const;

	// Prints out the tree
	friend ostream& operator<<(ostream& outStream, const BinTree& tree);

private:
	struct Node {
		NodeData* data;						// pointer to data object
		Node* left;							// left subtree pointer
		Node* right;						// right subtree pointer
	};
	Node* root;								// root of the tree

// utility functions
	void inorderHelper(Node* root) const;
	void sideways(Node*, int) const;			// provided below, helper for displaySideways()

// helper functions
	// Recursive helper functions
	Node* insert(Node* node, NodeData* key);

	// Looks for a node
	Node* find(Node* node, NodeData key) const;

	// Copies nodes
	void copy(Node* lhs, Node* rhs);

	// Frees nodes
	void free(Node* node);

	// Checks equality of nodes
	bool equals(Node* thisNode, Node* otherNode) const;

	// Returns the maximum integer out of two provided
	int getMax(int left, int right) const;

	// Helper functions for getHeight
	bool foundNode(const NodeData& target, Node* current, Node*& retVal) const;
	int getHeightHelper(const Node* node) const;

	// Helper function overload for getTreeHeight
	int getTreeHeight(Node* currentNode) const;

	// Helper function for outStream overload
	ostream& inOrderPrint(ostream& outStream, Node* node) const;

	// Helper function for bstreeToArray
	void addElements(NodeData* array[], Node* currentNode, int& index);
};

#endif