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

  virtual int Current() = 0;     // Return the current value.
  virtual int GetSize() = 0;     // Return number of values in the container.
  virtual bool HasCurrent() = 0; // Is the current value valid?
};

class UnsortedArray : public ActiveContainer {
private:
  std::vector<int> vals;
  int cur_pos = -1;
  
public:
  bool Search(int test_val) override {
    // Check every value for a match.
    for (int i = 0; i < vals.size(); i++) {
      if (vals[i] == test_val) {
	cur_pos = i;
	return true;
      }
    }
    return false;
  }
  
  void Insert(int in_val) override {
    vals.push_back(in_val);
  }
  
  void Delete() override {
    if (cur_pos == -1) return;            // If we don't have a position, do nothing.
    vals[cur_pos] = vals[vals.size()-1];  // Replace removed value with final value.
    vals.resize(vals.size()-1);           // Remove final position.
  }

  int Min() override {
    if (vals.size() == 0) return 0;
    int min_pos = 0;
    for (int i = 1; i < vals.size(); i++) {
      if (vals[i] < vals[min_pos]) min_pos = i;
    }
    cur_pos = min_pos;
    return vals[min_pos];
  }
  
  int Max() override {
    if (vals.size() == 0) return 0;
    int max_pos = 0;
    for (int i = 1; i < vals.size(); i++) {
      if (vals[i] >= vals[max_pos]) max_pos = i;
    }
    cur_pos = max_pos;
    return vals[max_pos];
  }
  
  int Next() override {
    if (cur_pos == -1) return Min();
    int next_pos = -1;
    // Search BEFORE cur_pos for the smallest value greater than current.
    for (int i = 0; i < cur_pos; i++) {
      if (vals[i] > vals[cur_pos] &&
	        (next_pos == -1 || vals[i] < vals[next_pos])) { next_pos = i; }
    }
    // Search AFTER cur_pos for the smallest value greater OR EQUAL to current.
    for (int i = cur_pos+1; i < vals.size(); i++) {
      if (vals[i] >= vals[cur_pos] &&
    	    (next_pos == -1 || vals[i] < vals[next_pos])) { next_pos = i; }
    }
    cur_pos = next_pos;
    return next_pos == -1 ? 0 : vals[next_pos];
  }
  
  int Prev() override {
    if (cur_pos == -1) return Max();
    int prev_pos = -1;
    // Search BEFORE cur_pos for the largest value less than OR EQUAL to current.
    for (int i = 0; i < cur_pos; i++) {
      if (vals[i] <= vals[cur_pos] &&
      	  (prev_pos == -1 || vals[i] >= vals[prev_pos])) { prev_pos = i; }
    }
    // Search AFTER cur_pos for the largest value less than current.
    for (int i = cur_pos+1; i < vals.size(); i++) {
      if (vals[i] < vals[cur_pos] &&
     	    (prev_pos == -1 || vals[i] > vals[prev_pos])) { prev_pos = i; }
    }
    cur_pos = prev_pos;
    return prev_pos == -1 ? 0 : vals[prev_pos];
  }
  
  int Current() override {
    if (cur_pos == -1) return Min();
    return vals[cur_pos];
  }

  int GetSize() override { return vals.size(); }

  bool HasCurrent() override { return cur_pos != -1; }
};

class SortedArray : public ActiveContainer {
private:
  std::vector<int> vals;
  int cur_pos = -1;
  
public:
  bool Search(int test_val) override {
    // Do a binary search.
    int first=0, last=vals.size();
    cur_pos = last/2;
    while (cur_pos < last) {
      if (vals[cur_pos] == test_val) return true;    // Found it!
      if (vals[cur_pos] > test_val) last = cur_pos;  // Search left
      else first = cur_pos+1;                        // Search right
      cur_pos = (first + last)/2;
    }
    
    return false;
  }
  
  void Insert(int in_val) override {
    Search(in_val);                       // Find the closest position to in_val.
    if (vals[cur_pos] < in_val) in_val++; // Make sure we have the spot AFTER it goes.
    vals.insert(vals.begin()+cur_pos, in_val);
  }
  
  void Delete() override {
    if (cur_pos == -1) return;            // If we don't have a position, do nothing.
    vals.erase(vals.begin()+cur_pos)
  }

  int Min() override {
    if (vals.size() == 0) return 0;
    cur_pos = 0;
    return vals[0];
  }
  
  int Max() override {
    if (vals.size() == 0) return 0;
    cur_pos = vals.size()-1;
    return vals[cur_pos];
  }
  
  int Next() override {
    if (cur_pos < 0) return Min();
    if (vals.size() == 0 || ++cur_pos >= vals.size()) { cur_pos = -1; return 0; }
    return vals[cur_pos];
  }
  
  int Prev() override {
    if (cur_pos < 0) return Max();
    if (vals.size() == 0 || cur_pos == 0) { cur_pos = -1; return 0; }
    return vals[--cur_pos]
  }
  
  int Current() override {
    if (cur_pos == -1) return Min();
    return vals[cur_pos];
  }

  int GetSize() override { return vals.size(); }

  bool HasCurrent() override { return cur_pos != -1; }
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
