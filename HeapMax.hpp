
#include "math.h"
#include "HeapMax.h"

//Constructor
HeapMax::HeapMax(std::string type, int k_heap, int maxSize)
{
  //Set initial values
  m_type = (type == "min" || type == "max") ? type : "max";
  if (type != "min" && m_type != "max") std::cout << "\nWarning: Heap type '" << type << "' unrecognized. Defaulting to max-heap.";
  m_K = (k_heap <= 5 && k_heap >= 2) ? k_heap : 5;
  if (k_heap > 5 || k_heap < 2) std::cout << "\nWarning: K value of " << k_heap << " is too "<< ((k_heap > 5) ? "large" : "small") << " - K can be in the range [2,5]. Defaulting to a K value of 5.";
  MAX_SIZE = maxSize;

  //Initialization
  std::cout << "\nCreating a new " << m_K << "-" << m_type << "Heap...";
  heap = new int[MAX_SIZE];
  for (int i = 0; i < MAX_SIZE; i++) heap[i] = -1;
  insertPoint = 0;
}

//Destructor
HeapMax::~HeapMax()
{
  delete[] heap;
}

//Build the K-Heap (Bottom-up approach)
//swapPoint marks the child index to check if swapping is necessary
void HeapMax::buildHeap(int swapPoint)
{
    if (cmp(swapPoint, getParent(swapPoint))) {
      swap(swapPoint, getParent(swapPoint));
      buildHeap(getParent(swapPoint));
    }
}

//Sink the value down the tree
//Swaps node (a parent) with the highest priority node not satisfying
//the heap-ordered tree property.
void HeapMax::sink(int swapPoint)
{
  int i_highestPriorityChild = getChild(1, swapPoint);
  for (int i = 1; i <= m_K; i++)
    if (cmp(getChild(i, swapPoint), swapPoint))
      i_highestPriorityChild = getChild(i, swapPoint);
  if (i_highestPriorityChild == -1) return;
  swap(swapPoint, i_highestPriorityChild);
  sink(i_highestPriorityChild); //Recurse with child as swap point
}


//Compare Priority - returns true if arg1.priority higher than arg2.priority
//respective to 'min' or 'max' type. Convenient abstraction.
bool HeapMax::cmp(int i, int j)
{return (m_type == "max") ? maxCompare(i, j) : minCompare(i, j);}
bool HeapMax::maxCompare(int i, int j)
{return (heap[i] > heap[j]) && (heap[j] != -1) && (heap[j] != -1);}
bool HeapMax::minCompare(int i, int j)
{return (heap[i] < heap[j]) && (heap[j] != -1) && (heap[j] != -1);}

//Swaps heap[i] with heap[j]. Typically used with a child and its parent.
void HeapMax::swap(int i, int j)
{
  int temp = heap[j];  //Temporarily store j
  heap[j] = heap[i];   //Place i into j
  heap[i] = temp;      //Place j where i was
}

//Insert a given value to the K-Heap (Bottom-up approach)
void HeapMax::insert(int value)
{
    heap[insertPoint] = value;
    buildHeap(insertPoint);
    insertPoint++;
}

//Delete Lowest Priority value from K-Heap
void HeapMax::deleteMin()
{
  int minIndex = (m_type == "max") ? findMin() : 0;
  deleteIndex(minIndex);
}

//Delete Highest Priority value from K-Heap
void HeapMax::deleteMax()
{
  int maxIndex = (m_type == "min") ? findMax() : 0;
  deleteIndex(maxIndex);
}

//Delete the value at the point
void HeapMax::deleteIndex(int deletePoint)
{
  insertPoint--;
  heap[deletePoint] = heap[insertPoint];
  heap[insertPoint] = -1;
  sink(heap[deletePoint]);
}

//Find minimum/maximum values in K-Heap
//Return - index of the located int, or -1 if not found.
int HeapMax::findMin()
{
  int minIndex = 0;
  if (m_type == "min") return 0;
  for (int i = 0; i < MAX_SIZE; i++)
    if ((heap[i] != -1) && (heap[i] < heap[minIndex])) minIndex = i;
  return minIndex;
}
int HeapMax::findMax()
{
  int maxIndex = 0;
  if (m_type == "max") return 0;
  for (int i = 0; i < MAX_SIZE; i++)
    if ((heap[i] != -1) && (heap[i] > heap[maxIndex])) maxIndex = i;
  return maxIndex;
}

//Return value from the found index for convenient outputting
int HeapMax::getMin()
{ return heap[findMin()];}

int HeapMax::getMax()
{ return heap[findMax()];}

//Level-Order Traversal
void HeapMax::levelorder()
{
    for (int i=1 ; i < getSize(); i++) {
      if ((log(i)/log(m_K)) == floor((log(i)/log(m_K)))) std::cout << "\n";
      else if (i % m_K == 0) std::cout << "- ";
      std::cout << heap[i] << " ";
    }

    //Flat Traversal
    //for (int i = 0; i < getSize(); i++) std::cout << ((heap[i] != -1) ? (std::to_string(heap[i]) + " ") : "");
}


//Get the chosen child (given childID 1-K) for a given parent index.
//Returns -1 if not found.
int HeapMax::getChild(int childID, int parentIndex)
{ return ((m_K * parentIndex) + childID); }

//Get the parent index of a child, given the child's index
//Returns -1 if not found.
int HeapMax::getParent(int childIndex)
{ return ((childIndex-1) / m_K); }

int HeapMax::getSize()
{
  for (int i = 1; i < MAX_SIZE; i++) if (heap[i] == -1) return i;
  return MAX_SIZE;
}

std::string HeapMax::getType()
{ return m_type; }
