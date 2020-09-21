#ifndef MAX_HEAP_H
#define MAX_HEAP_H

#include <vector>

#include "BaseContainer.h"

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

  void InsertMany(const std::vector<int> & in_vals) override {
    vals.insert(vals.end(), in_vals.begin(), in_vals.end());
    std::make_heap(vals.begin(), vals.end());
  }
};

#endif
