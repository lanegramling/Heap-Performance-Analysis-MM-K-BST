
#include "BinaryNode.h"

template <typename T>
BinaryNode<T>::BinaryNode(T value, BinaryNode<T>* left, BinaryNode<T>* right)
{
  m_value = value;
  m_leftChild = left;
  m_rightChild = right;
}

template <typename T>
void BinaryNode<T>::setValue(T value)
{m_value = value;}

template <typename T>
T BinaryNode<T>::getValue()
{return m_value;}

template <typename T>
bool BinaryNode<T>::isLeaf()
{return ((m_leftChild == nullptr) && (m_rightChild == nullptr));}

template <typename T>
void BinaryNode<T>::setLeftChild(BinaryNode<T>* left)
{m_leftChild = left;}

template <typename T>
void BinaryNode<T>::setRightChild(BinaryNode<T>* right)
{m_rightChild = right;}

template <typename T>
BinaryNode<T>* BinaryNode<T>::getLeftChild()
{return m_leftChild;}

template <typename T>
BinaryNode<T>* BinaryNode<T>::getRightChild()
{return m_rightChild;}
