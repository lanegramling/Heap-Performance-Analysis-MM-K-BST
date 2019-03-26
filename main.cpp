#include <iostream>   //I/O
#include <fstream>    //File Input handling
#include <string>     //String convenience
#include <iomanip>    //I/O formatting convenience
#include <stdlib.h>   //srand, rand
#include <time.h>     //time

#include "Timer.h"    //Provided Timer Class

#include "HeapK.h"    //Max 5-Heap, Min 5-Heap
#include "BinarySearchTree.h"

typedef struct _PerformanceTable
{
  double     buildTimes[5] = {0, 0, 0, 0, 0};
  double deleteMinTimes[5] = {0, 0, 0, 0, 0};
  double deleteMaxTimes[5] = {0, 0, 0, 0, 0};
} PerformanceTable;

//Load a HeapK from a (.txt) file (DEBUG)
HeapK* loadHeap(std::string fName, std::string heapType) {
  std::ifstream file(fName);
  int num;
  std::cout << "\n\nAttempting to create a 5-heap from table from file " << fName << "...";
  if (file.is_open()) {
    HeapK* heap = new HeapK(heapType);
    while(file >> num) heap->insert(num); //Load numbers to table.
    file.close();
    return heap;
  } else return new HeapK();
}

//Main function
int main(int argc, char* argv[])
{
  std::cout << "\n\n................................................................"
            << "\nGenerating performance analysis with randomized test data...";

  int M = 1000000;

  //Initialize structures
  Timer t;
  HeapK* minHeap = new HeapK("min", 5, 10 * M);
  HeapK* maxHeap = new HeapK("max", 5, 10 * M);
  BinarySearchTree<int>* bst = new BinarySearchTree<int>();
  PerformanceTable minTable, maxTable, bstTable;


  //Generate performance analysis - MIN 5-HEAP
  std::cout << "\n\n-----------------------Performance - Min-5-Heap-------------------------";
  std::cout << "\n___________|  100,000  |  200,000  |  300,000  |  400,000  |  500,000  |";
  for(int loadScale = 1; loadScale <= 5; loadScale++){                           //Cycle through heap sizes
      delete minHeap;
      minHeap = new HeapK("min", 5, 10 * M);
      for (int run = 0; run < 5; run++) {
          srand(time(NULL));                                                                  //(Re)Seed random generator

          t.start();                                                                      //Timer start .
          for (int i = 0; i < (loadScale * M); i++) minHeap->insert(rand() % (500000));   //Insertions  .
          minTable.buildTimes[loadScale - 1] += t.stop();

          for (int i = 0; i < ((0.001) * M); i++) {                                            //Perform 0.001 * M number of deleteMins
              if (i % 50 == 0) std::cout << "\nDeleteMin - " << i << "/" << ((0.001) * M) << " on run " << run+1 << "/5 for m=" << M;
              t.start();                                                                      //Timer start .
              minHeap->deleteMin();
              minTable.deleteMinTimes[loadScale - 1] += t.stop();
          }
          for (int i = 0; i < ((0.001) * M); i++) {                                            //Perform 0.001 * M number of deleteMaxes
              if (i % 50 == 0) std::cout << "\nDeleteMax - " << i << "/" << ((0.001) * M) << " on run " << run+1 << "/5 for m=" << M;
              t.start();                                                                      //Timer start .
              minHeap->deleteMax();
              minTable.deleteMaxTimes[loadScale - 1] += t.stop();
          }
      }
      for (int i = 0; i < 5; i++) {           //Average over 5 passes
          minTable.buildTimes[i] /= 5;
          minTable.deleteMinTimes[i] /= 5;
          minTable.deleteMaxTimes[i] /= 5;
      }
  }

  std::cout << "\nBuild      |";
  for (int i = 0; i < 5; i++) std::cout << " " << std::setprecision(6) << std::fixed << minTable.buildTimes[i] << "s |";        //Output CPU time to cell
  std::cout << "\nDeleteMin  |";
  for (int i = 0; i < 5; i++) std::cout << " " << std::setprecision(6) << std::fixed << minTable.deleteMinTimes[i] << "s |";        //Output CPU time to cell
  std::cout << "\nDeleteMax  |";
  for (int i = 0; i < 5; i++) std::cout << " " << std::setprecision(6) << std::fixed << minTable.deleteMaxTimes[i] << "s |";        //Output CPU time to cell

  //Generate performance analysis - HASHING WITH QUADRATIC PROBING
  std::cout << "\n\n-----------------------Performance - Max-5-Heap-------------------------";
  std::cout << "\n___________|  100,000  |  200,000  |  300,000  |  400,000  |  500,000  |";
  for(int loadScale = 1; loadScale <= 5; loadScale++){                           //Cycle through heap sizes
      delete maxHeap;
      maxHeap = new HeapK("max", 5, M * 10);
      for (int run = 0; run < 5; run++) {
          srand(time(NULL));                                                                  //(Re)Seed random generator
          t.start();                                                                          //Timer start .
          for (int i = 0; i < (loadScale * M); i++) maxHeap->insert(rand() % (5 * M));   //Insertions  .
          maxTable.buildTimes[loadScale - 1] += t.stop();

          for (int i = 0; i < ((0.001) * M); i++) {                                            //Perform 0.001 * M number of deleteMins
              if (i % 50 == 0) std::cout << "\nDeleteMin - " << i << "/" << ((0.001) * M) << " on run " << run+1 << "/5 for m=" << M;
              t.start();                                                                      //Timer start .
              maxHeap->deleteMin();
              maxTable.deleteMinTimes[loadScale - 1] += t.stop();
          }
          for (int i = 0; i < ((0.001) * M); i++) {                                            //Perform 0.001 * M number of deleteMaxes
              if (i % 50 == 0) std::cout << "\nDeleteMax - " << i << "/" << ((0.001) * M) << " on run " << run+1 << "/5 for m=" << M;
              t.start();                                                                      //Timer start .
              maxHeap->deleteMax();
              maxTable.deleteMaxTimes[loadScale - 1] += t.stop();
          }

      }
      for (int i = 0; i < 5; i++) {           //Average over 5 passes
          maxTable.buildTimes[i] /= 5;
          maxTable.deleteMinTimes[i] /= 5;
          maxTable.deleteMaxTimes[i] /= 5;
      }
  }

  std::cout << "\nBuild      |";
  for (int i = 0; i < 5; i++) std::cout << " " << std::setprecision(6) << std::fixed << maxTable.buildTimes[i] << "s |";        //Output CPU time to cell
  std::cout << "\nDeleteMin  |";
  for (int i = 0; i < 5; i++) std::cout << " " << std::setprecision(6) << std::fixed << maxTable.deleteMinTimes[i] << "s |";        //Output CPU time to cell
  std::cout << "\nDeleteMax  |";
  for (int i = 0; i < 5; i++) std::cout << " " << std::setprecision(6) << std::fixed << maxTable.deleteMaxTimes[i] << "s |";        //Output CPU time to cell


  //Generate performance analysis - HASHING WITH DOUBLE HASHING
  std::cout << "\n\n----------------Performance - Binary Search Tree------------------------";
  std::cout << "\n___________|  100,000  |  200,000  |  300,000  |  400,000  |  500,000  |";
  for(int loadScale = 1; loadScale <= 5; loadScale++){                           //Cycle through table sizes
      while(bst->deleteMin());  //Unload
      for (int run = 0; run < 5; run++) {                                                               //Refresh hash table for next pass
          srand(time(NULL));                                                                  //(Re)Seed random generator
          t.start();                                                                          //Timer start .
          for (int i = 0; i < (((double)loadScale / 10) * M); i++) bst->insert(rand() % (5 * M));   //Insertions  .
          bstTable.buildTimes[loadScale - 1] += t.stop();

          for (int i = 0; i < ((0.001) * M); i++) {                                            //Perform 0.001 * M number of deleteMins
              t.start();                                                                      //Timer start .
              bst->deleteMin();
              bstTable.deleteMinTimes[loadScale - 1] += t.stop();
          }
          for (int i = 0; i < ((0.001) * M); i++) {                                            //Perform 0.001 * M number of deleteMaxes
              t.start();                                                                      //Timer start .
              bst->deleteMax();
              bstTable.deleteMaxTimes[loadScale - 1] += t.stop();
          }
      }
      for (int i = 0; i < 5; i++) {           //Average over 5 passes
          bstTable.buildTimes[i] /= 5;
          bstTable.deleteMinTimes[i] /= 5;
          bstTable.deleteMaxTimes[i] /= 5;
      }
  }

  std::cout << "\nBuild      |";
  for (int i = 0; i < 5; i++) std::cout << " " << std::setprecision(6) << std::fixed << bstTable.buildTimes[i] << "s |";        //Output CPU time to cell
  std::cout << "\nDeleteMin  |";
  for (int i = 0; i < 5; i++) std::cout << " " << std::setprecision(6) << std::fixed << bstTable.deleteMinTimes[i] << "s |";        //Output CPU time to cell
  std::cout << "\nDeleteMax  |";
  for (int i = 0; i < 5; i++) std::cout << " " << std::setprecision(6) << std::fixed << bstTable.deleteMaxTimes[i] << "s |";        //Output CPU time to cell


  //Unload tables
  for (int i=0; i < minHeap->getSize(); i++) minHeap->deleteMin();
  for (int i=0; i < maxHeap->getSize(); i++) maxHeap->deleteMax();
  while(bst->deleteMin());

}
