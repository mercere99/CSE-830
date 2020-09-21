#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <vector>

#include "BaseContainer.h"

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

#endif