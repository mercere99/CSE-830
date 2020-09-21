#ifndef BASE_CONTAINER_H
#define BASE_CONTAINER_H

#include <vector>

// A container object that hold integer values
class BaseContainer {
public:
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

  // Take a vector of values and insert them all (one at a time).
  virtual void InsertMany(const std::vector<int> & values) {
    for (int v : values) Insert(v);
  }

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

#endif
