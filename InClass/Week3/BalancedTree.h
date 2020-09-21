#ifndef BALANCED_TREE_H
#define BALANCED_TREE_H

#include <vector>

#include "BaseContainer.h"

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

#endif
