#include <algorithm>
#include <ctime>
#include <functional>
#include <iostream>
#include <list>
#include <random>
#include <set>
#include <unordered_set>
#include <vector>

// A container object that hold integer values
struct BaseContainer {
  virtual bool Search(int) = 0;  // Find a value; make current if found; return success
  virtual void Insert(int) = 0;  // Insert a new value an make it current.
  virtual void Delete() = 0;     // Remove the current value.

  virtual int Min() = 0;         // Return the smalest value (make current)
  virtual int Max() = 0;         // Return the largest value (make current)

  virtual int Next() = 0;        // Return the successor to the current value (and make current)
  virtual int Prev() = 0;        // Return the predecessor to the current value (and make current)

  virtual bool HasCurrent() = 0; // Is the current value valid?
  virtual int Current() = 0;     // Return the current value.
  virtual int GetSize() = 0;     // Return number of values in the container.

protected:
  // Helper functions

  // Brute-force search through a container.
  template <typename VALS_T, typename IT_T>
  bool BFSearch(VALS_T & vals, IT_T & it, int test_val) {
    // Check every value for a match.
    for (it = vals.begin(); it != vals.end(); it++) {
      if (*it == test_val) return true;
    }
    return false;
  }

  // Brute-force search for minimum value.
  template <typename VALS_T, typename IT_T>
  int BFMin(VALS_T & vals, IT_T & min_it) {
    min_it = std::min_element(vals.begin(), vals.end());
    if (vals.size() == 0) return 0;    // Return 0 be default (error?)
    return *min_it;
  }

  // Brute-force search for maximum value.
  template <typename VALS_T, typename IT_T>
  int BFMax(VALS_T & vals, IT_T & max_it) {
    max_it = std::max_element(vals.begin(), vals.end());
    if (vals.size() == 0) return 0;    // Return 0 be default (error?)
    return *max_it;
  }

  // Brute-force finding of the next entry in sorted order.
  template <typename VALS_T, typename IT_T>
  int BFNext(VALS_T & vals, IT_T & cur_it) {
    if (cur_it == vals.end()) return BFMin(vals, cur_it);
    auto next_it = vals.end();
    // Search BEFORE cur_it for the smallest value greater than current.
    IT_T test_it;
    for (test_it = vals.begin(); test_it != cur_it; test_it++) {
      if (*test_it > *cur_it &&
	        (next_it == vals.end() || *test_it < *next_it)) { next_it = test_it; }
    }
    // Search AFTER cur_it for the smallest value greater OR EQUAL to current.
    for (++test_it; test_it != vals.end(); test_it++) {
      if (*test_it >= *cur_it &&
    	    (next_it == vals.end() || *test_it < *next_it)) { next_it = test_it; }
    }
    cur_it = next_it;
    return cur_it == vals.end() ? 0 : *cur_it;
  }
  
  // Brute-force finding of the previous entry in sorted order.
  template <typename VALS_T, typename IT_T>
  int BFPrev(VALS_T & vals, IT_T & cur_it) {
    if (cur_it == vals.end()) return BFMax(vals, cur_it);
    auto prev_it = vals.end();
    // Search BEFORE cur_it for the largest value less than OR EQUAL to current.
    IT_T test_it;
    for (test_it = vals.begin(); test_it != cur_it; test_it++) {
      if (*test_it <= *cur_it &&
	        (prev_it == vals.end() || *test_it >= *prev_it)) { prev_it = test_it; }
    }
    // Search AFTER cur_it for the largest value less than current.
    for (++test_it; test_it != vals.end(); test_it++) {
      if (*test_it < *cur_it &&
    	    (prev_it == vals.end() || *test_it > *prev_it)) { prev_it = test_it; }
    }
    cur_it = prev_it;
    return prev_it == vals.end() ? 0 : *cur_it;
  }
};

class UnsortedArray : public BaseContainer {
private:
  std::vector<int> vals;
  std::vector<int>::iterator cur_it;
  
public:
  bool Search(int test_val) override { return BFSearch(vals, cur_it, test_val); }
  void Insert(int in_val) override { vals.push_back(in_val); }
  
  void Delete() override {
    if (cur_it == vals.end()) return;  // If we don't have a position, do nothing (error?)
    *cur_it = vals[vals.size()-1];     // Replace removed value with final value.
    vals.resize(vals.size()-1);        // Remove final position.
  }

  int Min() override { return BFMin(vals, cur_it); }
  int Max() override { return BFMax(vals, cur_it); }
  
  int Next() override { return BFNext(vals, cur_it); }
  int Prev() override { return BFPrev(vals, cur_it); }
  
  bool HasCurrent() override { return cur_it != vals.end(); }
  int Current() override { return HasCurrent() ? *cur_it : 0; }
  int GetSize() override { return vals.size(); }
};

class SortedArray : public BaseContainer {
private:
  std::vector<int> vals;
  std::vector<int>::iterator cur_it;
  
public:
  bool Search(int test_val) override {
    // Do a binary search.
    int first=0, last=vals.size();
    int cur_pos = last/2;
    while (cur_pos < last && vals[cur_pos] != test_val) {
      if (vals[cur_pos] > test_val) last = cur_pos;  // Search left
      else first = cur_pos+1;                        // Search right
      cur_pos = (first + last)/2;
    }
    cur_it = vals.begin() + cur_pos;
    
    return cur_it != vals.end() && *cur_it == test_val;
  }
  
  void Insert(int in_val) override {
    Search(in_val);                   // Find the closest position to in_val.
    // Make sure we have the spot AFTER it goes.
    if (cur_it != vals.end() && *cur_it < in_val) cur_it++;   
    vals.insert(cur_it, in_val);
  }
  
  void Delete() override { cur_it = vals.erase(cur_it); }

  int Min() override {
    if (vals.size() == 0) return 0;
    cur_it = vals.begin();
    return *cur_it;
  }
  
  int Max() override {
    if (vals.size() == 0) return 0;
    cur_it = vals.end()-1;
    return *cur_it;
  }
  
  int Next() override {
    if (cur_it == vals.end()) return Min();
    return *(++cur_it);
  }
  
  int Prev() override {
    if (cur_it == vals.end()) return Max();
    return *(--cur_it);
  }

  bool HasCurrent() override { return cur_it != vals.end(); }
  int Current() override { return HasCurrent() ? *cur_it : 0; }
  int GetSize() override { return vals.size(); }

  const std::vector<int> & GetVals() const { return vals; }
};

class UnsortedList : public BaseContainer {
private:
  std::list<int> vals;
  std::list<int>::iterator cur_it;
  
public:
  bool Search(int test_val) override { return BFSearch(vals, cur_it, test_val); }
  void Insert(int in_val) override { vals.push_back(in_val); }
  void Delete() override { cur_it = vals.erase(cur_it); }

  int Min() override { return BFMin(vals, cur_it); }
  int Max() override { return BFMax(vals, cur_it); }
    
  int Next() override { return BFNext(vals, cur_it); }
  int Prev() override { return BFPrev(vals, cur_it); }
  
  bool HasCurrent() override { return cur_it != vals.end(); }
  int Current() override { return HasCurrent() ? *cur_it : 0; }
  int GetSize() override { return vals.size(); }
};


class SortedList : public BaseContainer {
private:
  std::list<int> vals;
  std::list<int>::iterator cur_it;
  
public:
  bool Search(int test_val) override {
    // Check every value for a match, stopping when they get too high.
    for (cur_it = vals.begin();
         cur_it != vals.end() && *cur_it < test_val;
         cur_it++);
    return *cur_it == test_val;
  }
  void Insert(int in_val) override {
    Search(in_val);                 // Find the closest position to in_val.
    vals.insert(cur_it, in_val);    // And insert it there.
  }
  void Delete() override { cur_it = vals.erase(cur_it); }

  int Min() override { cur_it = vals.begin(); return *cur_it; }
  int Max() override { cur_it = --vals.end(); return *cur_it; }
    
  int Next() override { return *(++cur_it); }
  int Prev() override { return *(--cur_it); }
  
  bool HasCurrent() override { return cur_it != vals.end(); }
  int Current() override { return HasCurrent() ? *cur_it : 0; }
  int GetSize() override { return vals.size(); }
};

class BalancedTree : public BaseContainer {
private:
  std::multiset<int> vals;
  std::multiset<int>::iterator cur_it;
  
public:
  bool Search(int test_val) override {
    cur_it = vals.find(test_val);
    return cur_it != vals.end();
  }
  void Insert(int in_val) override {
    cur_it = vals.insert(in_val);    // And insert it there.
  }
  void Delete() override { cur_it = vals.erase(cur_it); }

  int Min() override { cur_it = vals.begin(); return *cur_it; }
  int Max() override { cur_it = --vals.end(); return *cur_it; }
    
  int Next() override { return *(++cur_it); }
  int Prev() override { return *(--cur_it); }
  
  bool HasCurrent() override { return cur_it != vals.end(); }
  int Current() override { return HasCurrent() ? *cur_it : 0; }
  int GetSize() override { return vals.size(); }
};

class HashTable : public BaseContainer {
private:
  std::unordered_multiset<int> vals;
  std::unordered_multiset<int>::iterator cur_it;
  
public:
  bool Search(int test_val) override {
    cur_it = vals.find(test_val);
    return cur_it != vals.end();
  }
  void Insert(int in_val) override {
    cur_it = vals.insert(in_val);    // And insert it there.
  }
  void Delete() override { cur_it = vals.erase(cur_it); }

  int Min() override { return BFMin(vals, cur_it); }
  int Max() override { return BFMax(vals, cur_it); }
  int Next() override { return BFNext(vals, cur_it); }
  int Prev() override { return BFPrev(vals, cur_it); }
  
  bool HasCurrent() override { return cur_it != vals.end(); }
  int Current() override { return HasCurrent() ? *cur_it : 0; }
  int GetSize() override { return vals.size(); }
};

class MaxHeap : public BaseContainer {
private:
  using iterator = std::vector<int>::iterator;
  
  std::vector<int> vals;
  iterator cur_it;
  
  // Helper functions
  int ToID(iterator it) { return it - vals.begin(); }
  iterator Left(iterator it) {
    int id = ToID(it)*2 + 1;
    return (id >= vals.size()) ? vals.end() : vals.begin() + id;
  }
  iterator Right(iterator it) {
    int id = ToID(it)*2 + 2;
    return (id >= vals.size()) ? vals.end() : vals.begin() + id;
  }
  iterator Parent(iterator it) {
    int id = (ToID(it) - 1) / 2;
    return vals.begin() + id;
  }
public:
  bool Search(int test_val) override { return BFSearch(vals, cur_it, test_val); }
  void Insert(int in_val) override {
    vals.push_back(in_val);
    push_heap(vals.begin(), vals.end());
  }
  
  void Delete() override {
    if (cur_it == vals.end()) return;  // If we don't have a position, do nothing (error?)

    // If we are removing the max, use built-in functionaloity.
    if (cur_it == vals.begin()) {
      std::pop_heap(vals.begin(), vals.end());
      vals.pop_back();
      return;
    }

    // Otherwise handle this manually.
    *cur_it = vals[vals.size()-1];     // Replace removed value with final value.
    vals.resize(vals.size()-1);        // Remove final position.

    // Now we need to manually make this a heap again.  Start by checking if we move up.
    while (cur_it != vals.begin() && *cur_it > *Parent(cur_it)) {
      std::swap(*cur_it, *Parent(cur_it));
      cur_it = Parent(cur_it);
    }

    // Then check if we need to move down...
    auto left = Left(cur_it), right = Right(cur_it);
    while (left != vals.end()) {
      auto max_child = (right == vals.end() || *right < *left) ? left : right;
      if (*cur_it > *max_child) break;
      std::swap(*cur_it, *max_child);
      left = Left(cur_it), right = Right(cur_it);
    }
  }

  int Min() override { return BFMin(vals, cur_it); }
  int Max() override { return BFMax(vals, cur_it); }
  
  int Next() override { return BFNext(vals, cur_it); }
  int Prev() override { return BFPrev(vals, cur_it); }
  
  bool HasCurrent() override { return cur_it != vals.end(); }
  int Current() override { return HasCurrent() ? *cur_it : 0; }
  int GetSize() override { return vals.size(); }
};

// Function to measure the time (in seconds) that it takes for another container to run.
double TimeFun( std::function<void()> fun ) {
  std::clock_t start_time = std::clock();
  fun();
  std::clock_t total_time = std::clock() - start_time;
  return ((double) total_time) / (double) CLOCKS_PER_SEC;
}

// Take a vector of values and insert them all (one at a time) into a container.
template <typename T>
void InsertMany(T & container, const std::vector<int> & values) {
  for (int v : values) container.Insert(v);
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
  InsertMany(container, vals);
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
