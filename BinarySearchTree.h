#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

#include <iostream>

#include "BinaryNode.h"

template <class T>
class BinarySearchTree
{

public:

  //Constructor - initializes a root node to nullptr.
  BinarySearchTree();

  //Destructor
  ~BinarySearchTree();

  //Destroy a subtree
  void destroyTree(BinaryNode<T>* subtree);

  //Insert a given value to the tree
  void insert(T value, BinaryNode<T>* subtree=nullptr);

  //Delete the minimum value from the tree.
  BinaryNode<T>* deleteMin(BinaryNode<T>* subtree=nullptr, bool verbose=true);

  //Delete the maximum value from the tree.
  BinaryNode<T>* deleteMax(BinaryNode<T>* subtree=nullptr, bool verbose=true);

  //Entry to erase() for convenience
  void eraseValue(T value);

  //Delete a given value from the tree.
  //Recurses until it is the parent of the Node to delete.
  //Then Deploys eraseNode on the child, setting the parent's
  //child pointer with eraseNode's returned Node.
  void erase(T value, BinaryNode<T>* subtree=nullptr);

  //Delete a given Node from the tree.
  BinaryNode<T>* eraseNode(BinaryNode<T>* subtree);

  //Find the minimum value in the tree.
  BinaryNode<T>* findMin(BinaryNode<T>* subtree=nullptr, bool verbose=true);

  //Find the maximum value in the tree.
  BinaryNode<T>* findMax(BinaryNode<T>* subtree=nullptr, bool verbose=true);

  //Print out all elements using preorder.
  void preorder(BinaryNode<T>* subtree=nullptr);

  //Print out all elements using inorder.
  void inorder(BinaryNode<T>* subtree=nullptr);

  //Print out all elements using postorder.
  void postorder(BinaryNode<T>* subtree=nullptr);

private:

  BinaryNode<T>* m_root;

};

#include "BinarySearchTree.hpp"

#endif
