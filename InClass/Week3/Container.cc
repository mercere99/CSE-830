#include <algorithm>
#include <iostream>
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
};

class Test_UnsortedArray : public ActiveContainer {
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
};

//    int first=0, last=vals.size();

int main(int argc, char *argv[])
{
}
