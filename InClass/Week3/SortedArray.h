#ifndef SORTED_ARRAY_H
#define SORTED_ARRAY_H

#include <vector>

#include "BaseContainer.h"

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

  void InsertMany(const std::vector<int> & in_vals) override {
    // If the new values will dominate, insert them all and THEN sort.
    if (in_vals.size() > vals.size()) {
      vals.insert(vals.end(), in_vals.begin(), in_vals.end());
      std::sort(vals.begin(), vals.end());
    }

    // Otherwise keep sorted and just insert one at a time.
    else {
      for (int v : in_vals) Insert(v);
    }
  }
};

#endif