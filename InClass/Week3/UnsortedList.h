#ifndef UNSORTED_LIST_H
#define UNSORTED_LIST_H

#include <vector>

#include "BaseContainer.h"

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

#endif
