#include <algorithm>
#include <ctime>
#include <functional>
#include <iostream>
#include <list>
#include <random>
#include <set>
#include <unordered_set>
#include <vector>

#include "BaseContainer.h"

#include "BalancedTree.h"
#include "HashTable.h"
#include "MaxHeap.h"
#include "SortedArray.h"
#include "SortedList.h"
#include "UnsortedArray.h"
#include "UnsortedList.h"

// Function to measure the time (in seconds) that it takes for another container to run.
double TimeFun( std::function<void()> fun ) {
  std::clock_t start_time = std::clock();
  fun();
  std::clock_t total_time = std::clock() - start_time;
  return ((double) total_time) / (double) CLOCKS_PER_SEC;
}

// Use a combination of Min() and a linear number of calls to Current() and Next() to
// sort a set of values.
template <typename T>
void Sort(T & container, std::vector<int> & out_values) {
  out_values.resize(container.GetSize());
  container.Min();
  for (int pos = 0; pos < container.GetSize(); pos++) {
    out_values[pos] = container.Current();
    container.Next();
  }
}

// A quick function to print a vector of doubles.
template <typename T>
void Print(const std::vector<T> & v, size_t max=(size_t)-1) {
    for (size_t i=0; i < max && i < v.size(); i++) {
        if (i) std::cout << ", ";
        std::cout << v[i];
    }
    std::cout << std::endl;
}

// Run some simple tests on a container, printing as we go.
template <typename T>
void TestContainer(std::vector<int> vals, const std::string & name)
{
  std::cout << "\n" << name << std::endl;
  T container;
  container.InsertMany(vals);
  Sort(container, vals);

  Print(vals, 40);
}

int main(int argc, char *argv[])
{
  // Build a random-number generator for input values.
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0.0,1000);

  // Build a vector of random ints.
  constexpr int N = 40;
  std::vector<int> vals(N);
  for (auto & v : vals) v = dis(gen);

  std::cout << "Initial:\n";
  Print(vals, 40);

  TestContainer<UnsortedArray>(vals, "UnsortedArray");
  TestContainer<SortedArray>  (vals, "SortedArray");
  TestContainer<UnsortedList> (vals, "UnsortedList");
  TestContainer<SortedList>   (vals, "SortedList");
  TestContainer<BalancedTree> (vals, "BalancedTree");
  TestContainer<HashTable>    (vals, "HashTable");
  TestContainer<MaxHeap>      (vals, "MaxHeap");
}
