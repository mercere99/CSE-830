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

//    int first=0, last=vals.size();

int main(int argc, char *argv[])
{
}
