#ifndef SORTED_LIST_H
#define SORTED_LIST_H

#include <vector>

#include "BaseContainer.h"

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

#endif
