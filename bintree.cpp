/*
* Student: Audrey Nguyen
* Professor: Christopher Esposito
* Assignment #2: BinTree
* Description: Cpp file for a representation of a Binary Search Tree
*/

#include "bintree.h"

// Global Constant
const int ARRAYSIZE = 100;

// Default Constructor
// Makes a tree with a null root
BinTree::BinTree()
{
	root = nullptr;
}

// Copy Constructor
BinTree::BinTree(const BinTree& other)
{
	// If the other tree is empty, set root to be null
	if (other.isEmpty())
	{
		root = nullptr;
	}

	// Otherwise, set the root and copy elements to the tree recursively
	else
	{
		Node* newRoot = new Node;
		NodeData* newData = new NodeData(*other.root->data);
		newRoot->data = newData;
		newRoot->left = nullptr;
		newRoot->right = nullptr;

		root = newRoot;

		copy(root, other.root);
	}
}

// Helper method for copy constructor
void BinTree::copy(Node* lhs, Node* rhs)
{
	// If the node we are copying is not null, copy elements
	if (rhs != nullptr)
	{
		// Copy left node
		if (rhs->left != nullptr)
		{
			Node* newLeft = new Node;
			NodeData* newLeftData = new NodeData(*rhs->left->data);
			newLeft->data = newLeftData;
			newLeft->left = nullptr;
			newLeft->right = nullptr;
			lhs->left = newLeft;

			copy(lhs->left, rhs->left);
		}

		// Copy right node
		if (rhs->right != nullptr)
		{
			Node* newRight = new Node;
			NodeData* newRightData = new NodeData(*rhs->right->data);
			newRight->data = newRightData;
			newRight->left = nullptr;
			newRight->right = nullptr;
			lhs->right = newRight;

			copy(lhs->right, rhs->right);
		}

	}
}

// Destructor
BinTree::~BinTree()
{
	makeEmpty();
}

// Inserts a node into the tree
// If succesfully inserted, return true. Otherwise return false.
bool BinTree::insert(NodeData* data)
{
	// If nothing is in the tree, assign the data to the root
	if (isEmpty())
	{
		Node* newRoot = new Node;
		newRoot->data = data;
		newRoot->left = nullptr;
		newRoot->right = nullptr;
		root = newRoot;
		return true;
	}

	// Checks if the element already exists in the tree
	NodeData *checkData;
	bool exists = retrieve(*data, checkData);

	// If the item exists, don't insert the item into the tree
	if (exists)
	{
		return false;
	}

	// Inserts the item into the tree
	else 
	{
		insert(root, data);
		return true;
	}
}

// Helper method for insert
BinTree::Node* BinTree::insert(Node* node, NodeData* key)
{
	// If the node passed in is null, insert the data
	if (node == nullptr)
	{
		Node* newNode = new Node;
		newNode->data = key;
		newNode->left = nullptr;
		newNode->right = nullptr;
		return newNode;
	}

	// If the key is less than the current node's data, insert left
	if (*key < *(node->data))
	{
		node->left = insert(node->left, key);
	}

	// If the key is less than the current node's data, insert right
	else if (*key > *(node->data))
	{
		node->right = insert(node->right, key);
	}

	return node;
}

// Searches the tree for the target NodeData
// If it is found, retrieves the value through the retVal reference and return true
// Otherwise returns false
bool BinTree::retrieve(const NodeData& target, NodeData*& retVal) const
{
	// Return false if the tree is empty 
	if (isEmpty())
	{
		retVal = nullptr;
		return false;
	}

	// Searches the tree for the target
	// If target is found, set the reference to the found nodedata in retVal
	// and return true
	Node* temp = find(root, target);
	if (temp != nullptr)
	{
		retVal = temp->data;
		return true;
	}

	// If it is not found, return false
	retVal = nullptr;
	return false;
}

// Helper method for Retrieve
BinTree::Node* BinTree::find(Node* node, NodeData key) const
{
	// If the node is null, return null 
	if (node == nullptr) 
	{
		return nullptr;
	}

	// If the node's data is equal to the key, return the node
	if (*(node->data) == key)
	{
		return node;
	}

	// If the node's data is less than the key, search left
	if (*(node->data) < key)
	{
		return find(node->right, key);
	}

	// If the node's data is greater than the key, search right
	if (*(node->data) > key)
	{
		return find(node->left, key);
	}

	return nullptr;
}

// Checks if the tree is empty
bool BinTree::isEmpty() const
{
	return root == nullptr;
}

// Gets the target's height
// Does not assume the tree is a binary search tree (as per instruction requirements)
int BinTree::getHeight(const NodeData& target) const
{
	// Checks if the target exists in the tree
	// Returns 0 if it is not in the tree
	Node* checkData = nullptr;
	if (!foundNode(target, root, checkData))
	{
		return 0;
	}

	// If the target exists, return the height
	return getHeightHelper(checkData);
}

// Helper fucntion for getHeight
// Searches for a node
// Does not assume the tree is a binary search tree as per assignment requirements
bool BinTree::foundNode(const NodeData& target, Node* current, Node*& retVal) const
{
	// If the current node is null, return false
	if (current == nullptr)
	{
		return false;
	}

	// If the current node's data matches the target, 
	// pass current to retVal by reference
	// and return true
	if (*current->data == target)
	{
		retVal = current;
		return true;
	}

	// Recursively searches left and right
	// If target is found on either side, returns true
	return foundNode(target, current->left, retVal) || foundNode(target, current->right, retVal);
}

// Helper function for getHeight
// Calculates the height of a node
int BinTree::getHeightHelper(const Node* node) const
{
	// If the node is null, return 0
	if (node == nullptr)
	{
		return 0;
	}

	// If the node's left and rights are null, return 1
	if (node->left == nullptr && node->right == nullptr)
	{
		return 1;
	}

	// Return sum of heights
	return 1 + getMax(getHeightHelper(node->left), getHeightHelper(node->right));
}

// Finds the tree's total height
// Does not assume the tree is a binary search tree
int BinTree::getTreeHeight() const
{
	return getTreeHeight(root);
}

// Helper function for getHeight
// Helps recursively find the tree's height
int BinTree::getTreeHeight(Node* currentNode) const
{
	// If the node is null, return 0;
	if (currentNode == nullptr)
	{
		return 0;
	}

	// Otherwise return 1 + the maximum of the recusrive calls to the nodes children
	return 1 + getMax(getTreeHeight(currentNode->left), getTreeHeight(currentNode->right));
}

// Returns the maximum integer out of two provided
int BinTree::getMax(int left, int right) const
{
	// If the left integer is less than the right, return right
	if (left < right)
	{
		return right;
	}

	// If the left integer is less than or equal to the right, return left
	return left;
}

// Assignment Overload Operator
BinTree& BinTree::operator = (const BinTree& other)
{
	// If the trees are equal, return this without modifying anything
	if (*this == other)
	{
		return *this;
	}

	// Deletes everything
	makeEmpty();

	// If the other tree is empty, make this tree's root null
	if (other.isEmpty())
	{
		root = nullptr;
	}

	// Copies the other tree
	else
	{
		// Sets root's data to be equal to the other tree
		Node* newRoot = new Node;
		NodeData* newData = new NodeData(*other.root->data);
		newRoot->data = newData;
		newRoot->left = nullptr;
		newRoot->right = nullptr;
		root = newRoot;

		// Recursively copies the nodes from the other tree to this tree
		copy(root, other.root);
	}

	return *this;
}

// Empties the tree
void BinTree::makeEmpty()
{
	// If the tree is already empty, don't do anything
	if (isEmpty())
	{
		return;
	}
	// Otherwise, free the nodes recursively
	free(root);
	root = nullptr;
}

// Helper function for makeEmpty
// Recursively deletes the nodes
void BinTree::free(Node* node)
{
	if (isEmpty())
	{
		return;
	}

	if (node->left != nullptr)
	{
		free(node->left);
	}

	if (node->right != nullptr)
	{
		free(node->right);
	}

	// Deletes the data of the nodes
	delete node->data;
	delete node;
}

// Fills a NodeData array with bsTree values while emptying the tree
// Assumes the array is statically allocated and has 100 NULL elements as per assignment requirements
// No size checking as per assignment requirements
void BinTree::bstreeToArray(NodeData* array[])
{
	//If the tree is empty, there is nothing to add to the array
	if (isEmpty())
	{
		return;
	}

	// Adds elements to the array
	int index = 0;
	addElements(array, root, index);

	//Empties the tree
	makeEmpty();
}

// Helper method for bstreeToArray
// Inserts elements recursively
void BinTree::addElements(NodeData* array[], Node* currentNode, int& index)
{
	// Checks if the node is null
	if (currentNode == nullptr)
	{
		return;
	}

	// Checks if index is beyond bounds
	if (index >= ARRAYSIZE)
	{
		return;
	}
	
	// Adds the elements to the array recursively inOrder
	addElements(array, currentNode->left, index);
	array[index++] = new NodeData(*currentNode->data);
	addElements(array, currentNode->right, index);
}

// Overload Operators: testing equality
bool BinTree::operator==(const BinTree& other) const
{
	// Checks if both sides are empty
	if (isEmpty() && other.isEmpty())
	{
		return true;
	}

	// Recursively checks for equality
	return equals(root, other.root);
}

// Helper method to help test equality
bool BinTree::equals(Node* thisNode, Node* otherNode) const
{
	// Checks if the nodes are both null, if so return true
	if ((thisNode == nullptr) && (otherNode == nullptr))
	{
		return true;
	}

	// Checks if one of the nodes are null, if so, return false
	else if ((thisNode == nullptr) || (otherNode == nullptr))
	{
		return false;
	}

	// Otherwise if the nodes are equal, recursively check their left and right nodes
	else if (*thisNode->data == *otherNode->data)
	{
		return equals(thisNode->left, otherNode->left)
			&& equals(thisNode->right, otherNode->right);
	}

	// Return false if nodes are not equal to each other
	return false;
}

// Checks for inequality
bool BinTree::operator!=(const BinTree& other) const
{
	return !(*this == other);
}

// Helper function for an in order traversal of the tree
// Studen chose not to use it as a helper method for this assignment
/*
void BinTree::inorderHelper(Node* root) const
{
	if (root == nullptr)
	{
		return;
	}

	// Visit Left
	inorderHelper(root->left);

	// Do something at Root

	// Visit Right
	inorderHelper(root->right);
}
*/

// Outstream Overload
ostream& operator<<(ostream& outStream, const BinTree& thisBin)
{
	// Recursively adds elements to outstream
	thisBin.inOrderPrint(outStream, thisBin.root);
	outStream << endl;
	return outStream;
}


// Helper method for outstream overload
ostream& BinTree::inOrderPrint(ostream& outStream, Node* node) const
{
	// Returns outStream without adding anything if node is null
	if (node == nullptr)
	{
		return outStream;
	}

	// Recursivley calls left, executes root, calls right
	inOrderPrint(outStream, node->left);
	outStream << *node->data << " ";
	inOrderPrint(outStream, node->right);

	// returns outStream
	return outStream;
}



// The functions displaySidewats and sideways were provided by the instructor
// Originally located in bintree.h but moved to bintree.cpp by student

//------------------------- displaySideways ---------------------------------
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::displaySideways() const {
	sideways(root, 0);
}

//---------------------------- Sideways -------------------------------------
// Helper method for displaySideways
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::sideways(Node* current, int level) const {
	if (current != NULL) {
		level++;
		sideways(current->right, level);

		// indent for readability, 4 spaces per depth level 
		for (int i = level; i >= 0; i--) {
			cout << "    ";
		}

		cout << *current->data << endl;        // display information of object
		sideways(current->left, level);
	}
};

