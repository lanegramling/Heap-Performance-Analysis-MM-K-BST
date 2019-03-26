#ifndef HEAPMAX_H
#define HEAPMAX_H

#include <iostream>
#include <string>

//This Class is an implementation of an Integer K-MaxHeap using an array.
//K defaults to a 5-Heap.

class HeapMax
{
private:

  //Heap(Min/Max) Structure:
  int m_K = 5;                    //Children per Node
  int MAX_SIZE = 500;             //Maximum size allocated for K-Heap.
  int* heap;                      //K-Heap contents.
  int insertPoint;                //Tracks the last position in the tree.
  std::string m_type = "max";     //Type ('min' or 'max') - defaults to 'max'

  //Get the chosen child (given childID 1-K) for a given parent index.
  //Returns -1 if not found.
  int getChild(int childID, int parentIndex);

  //Get the parent value of a child, given the child's index
  //Returns -1 if not found.
  int getParent(int childIndex);

public:
  //Constructor
  HeapMax(std::string m_heapType = "max", int k_heap = 5, int maxSize=500);

  //Destructor
  ~HeapMax();

  //Build the K-Heap
  void buildHeap(int swapPoint);

  //Compares - returns true if arg1.priority > arg2.priority
  //cmp delegates comparison between the two functions depending on m_type
  bool cmp(int i, int j);
  bool minCompare(int i, int j);
  bool maxCompare(int i, int j);

  //Swap heap[i] with heap[j].
  void swap(int i, int j);

  //Sink the given node down the heap.
  void sink(int swapPoint);

  //Insert a given value to the K-Heap
  void insert(int value);

  //Delete minimum/maximum values from K-Heap
  void deleteMin();
  void deleteMax();
  void deleteIndex(int deletePoint);

  //Find minimum/maximum values in K-Heap
  int findMin();
  int findMax();

  //Return value from the found index for convenient outputting
  int getMin();
  int getMax();

  //Get the current size of the heap
  int getSize();

  //Return the type of the heap ('min' or 'max')
  std::string getType();

  //Level-Order Traversal
  void levelorder();

};

#include "HeapMax.hpp"

#endif
