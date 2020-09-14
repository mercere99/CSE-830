#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

// A container object that hold integer values
struct ActiveContainer {
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
};

class UnsortedArray : public ActiveContainer {
private:
  std::vector<int> vals;
  std::vector<int>::iterator cur_it;
  
public:
  bool Search(int test_val) override {
    // Check every value for a match.
    for (cur_it = vals.begin(); cur_it != vals.end(); cur_it++) {
      if (*cur_it == test_val) return true;
    }
    return false;
  }
  
  void Insert(int in_val) override {
    vals.push_back(in_val);
  }
  
  void Delete() override {
    if (cur_it == vals.end()) return;  // If we don't have a position, do nothing (error?)
    *cur_it = vals[vals.size()-1];     // Replace removed value with final value.
    vals.resize(vals.size()-1);        // Remove final position.
  }

  int Min() override {
    if (vals.size() == 0) return 0;    // Return 0 be default (error?)
    std::vector<int>::iterator min_it = vals.begin();
    for (auto it = vals.begin()+1; it != vals.end(); it++) {
      if (*it < *min_it) min_it = it;
    }
    cur_it = min_it;
    return *min_it;
  }
  
  int Max() override {
    if (vals.size() == 0) return 0;    // Return 0 be default (error?)
    std::vector<int>::iterator max_it = vals.begin();
    for (auto it = vals.begin()+1; it != vals.end(); it++) {
      if (*it >= *max_it) max_it = it;
    }
    cur_it = max_it;
    return *max_it;
  }
  
  int Next() override {
    if (cur_it == vals.end()) return Min();
    auto next_it = vals.end();
    // Search BEFORE cur_pos for the smallest value greater than current.
    for (auto test_it = vals.begin(); test_it != cur_it; test_it++) {
      if (*test_it > *cur_it &&
	        (next_it == vals.end() || *test_it < *next_it)) { next_it = test_it; }
    }
    // Search AFTER cur_pos for the smallest value greater OR EQUAL to current.
    for (auto test_it = cur_it+1; test_it != vals.end(); test_it++) {
      if (*test_it >= *cur_it &&
    	    (next_it == vals.end() || *test_it < *next_it)) { next_it = test_it; }
    }
    cur_it = next_it;
    return cur_it == vals.end() ? 0 : *cur_it;
  }
  
  int Prev() override {
    if (cur_it == vals.end()) return Max();
    auto prev_it = vals.end();
    // Search BEFORE cur_pos for the largest value less than OR EQUAL to current.
    for (auto test_it = vals.begin(); test_it != cur_it; test_it++) {
      if (*test_it <= *cur_it &&
	        (prev_it == vals.end() || *test_it >= *prev_it)) { prev_it = test_it; }
    }
    // Search AFTER cur_pos for the largest value less than current.
    for (auto test_it = cur_it+1; test_it != vals.end(); test_it++) {
      if (*test_it < *cur_it &&
    	    (prev_it == vals.end() || *test_it > *prev_it)) { prev_it = test_it; }
    }
    cur_it = prev_it;
    return prev_it == vals.end() ? 0 : *cur_it;
  }
  
  bool HasCurrent() override { return cur_it != vals.end(); }

  int Current() override { return HasCurrent() ? *cur_it : 0; }

  int GetSize() override { return vals.size(); }
};

class SortedArray : public ActiveContainer {
private:
  std::vector<int> vals;
  std::vector<int>::iterator cur_it;
  
public:
  bool Search(int test_val) override {
    // Do a binary search.
    int first=0, last=vals.size();
    int cur_pos = last/2;
    while (cur_pos < last && vals[cur_pos] == test_val) {
      if (vals[cur_pos] > test_val) last = cur_pos;  // Search left
      else first = cur_pos+1;                        // Search right
      cur_pos = (first + last)/2;
    }
    cur_it = vals.begin() + cur_pos;
    
    return *cur_it == test_val;
  }
  
  void Insert(int in_val) override {
    Search(in_val);                   // Find the closest position to in_val.
    if (*cur_it < in_val) in_val++;   // Make sure we have the spot AFTER it goes.
    vals.insert(cur_it, in_val);
  }
  
  void Delete() override { vals.erase(cur_it); }

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
};



template <typename T>
void InsertMany(T & container, const std::vector<int> & values) {
  for (int v : values) container.Insert(v);
}

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

int main(int argc, char *argv[])
{
  // Build a random-number generator for input values.
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0.0,1000);

  // Build a vector of random ints.
  constexpr int N = 20;
  std::vector<int> vals(N);
  for (auto & v : vals) v = dis(gen);

  Print(vals);

  UnsortedArray container;
  InsertMany(container, vals);
  Sort(container, vals);

  Print(vals);

}
