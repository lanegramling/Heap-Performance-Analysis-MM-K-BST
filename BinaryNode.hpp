#include "BinaryNode.h"

//Constructor
template <class T>
BinaryNode<T>::BinaryNode(T value, BinaryNode<T>* leftChild, BinaryNode<T>* rightChild)
{
    m_value = value;
    m_leftChild = leftChild;
    m_rightChild = rightChild;
}

//Set the value of a child of this FiveNode, given index of the child.
template <class T>
void BinaryNode<T>::setChild(int child, T value)
{m_children[child] = value;}

//Get the value of a child of this FiveNode, given index of the child.
template <class T>
T BinaryNode<T>::getChild(int child)
{return m_children[child];}
