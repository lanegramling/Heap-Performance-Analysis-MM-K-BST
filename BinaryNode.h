#ifndef BINARYNODE_H
#define BINARYNODE_H

template<typename T>
class BinaryNode
{
private:
    T m_value;
    BinaryNode<T>* m_leftChild;
    BinaryNode<T>* m_rightChild;

public:
    //Constructor
    BinaryNode(T value=T(), BinaryNode<T>* left=nullptr, BinaryNode<T>* right=nullptr);

    //Sets & Gets
    void setValue(T value);
    T getValue();

    void setLeftChild(BinaryNode<T>* left);
    BinaryNode<T>* getLeftChild();

    void setRightChild(BinaryNode<T>* right);
    BinaryNode<T>* getRightChild();

    bool isLeaf();
};

#include "BinaryNode.cpp"

#endif
