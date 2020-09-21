#ifndef UNSORTED_ARRAY_H
#define UNSORTED_ARRAY_H

#include <vector>

#include "BaseContainer.h"

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

  void InsertMany(const std::vector<int> & in_vals) override {
    vals.insert(vals.end(), in_vals.begin(), in_vals.end());
  }
};

#endif
