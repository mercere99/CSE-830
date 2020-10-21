#include <iostream>
#include <unordered_set>
#include <string>
#include <sstream>
#include <vector>

struct MiddleSquare {
  size_t seed;

  MiddleSquare(size_t in_seed) : seed(in_seed) { }  
  
  size_t Get() {
    seed *= seed;                     // Square seed.
    seed =  (seed / 1000) % 1000000;  // Return middle six digits.
    return seed;
  }

  using hash_t = size_t;
  size_t GetHash() { return seed; }
};


struct LCG {
  size_t seed;

  size_t a = 21;
  size_t c = 91;
  size_t m = 1000000;
  
  LCG(size_t in_seed) : seed(in_seed) { }

  size_t Get() {
    seed = (a * seed + c) % m;
    return seed;
  }

  using hash_t = size_t;
  size_t GetHash() { return seed; }
};


template <typename T>
std::string GetValues(size_t seed, size_t cap=10, size_t range=1048576) {
  std::stringstream ss;
  T rng(seed);
  for (size_t i = 0; i < cap; i++) {
    if (i) ss << " ";
    ss << (rng.Get() % range);
  }
  return ss.str();
}

// Measure how long we go until the first repeated value.
template <typename T>
size_t TestRepeat(size_t seed) {
  T rng(seed);
  std::unordered_set<size_t> found;

  size_t val = rng.Get();
  while (found.count(val) == 0) {
    found.insert(val);
    val = rng.Get();
  }

  return found.size();
}

// Similar to TestRepeat, but accounts for full internal state.
template <typename T>
size_t TestCycle(size_t seed) {
  using hash_t = typename T::hash_t;
  T rng(seed);
  std::unordered_set<hash_t> found;

  size_t val = rng.Get();
  hash_t hash = rng.GetHash();
  while (found.count(hash) == 0 && found.size() < 1000000) {
    found.insert(hash);
    val = rng.Get();
    hash = rng.GetHash();
  }

  return val;
}

template <typename T>
std::string TestDice(size_t seed) {
  std::vector<int> rolls(6, 0);
  T rng(seed);
  for (size_t i = 0; i < 1000000; i++) {
    int val = rng.Get() % 6;
    rolls[val]++;
  }

  std::stringstream ss;
  for (size_t i = 0; i < 6; i++) {
    if (i) ss << " ";
    ss << i << ":" << rolls[i];
  }

  return ss.str();
}


template <typename T>
void Test(const std::string & name, size_t seed) {
  std::cout << name << ":" << std::endl;
  std::cout << "  Example Vals: " << GetValues<T>(seed) << std::endl;
  std::cout << "  First Repeat: " << TestRepeat<T>(seed) << std::endl;
  std::cout << "  Cycle Start:  " << TestCycle<T>(seed) << std::endl;
  std::cout << "  Example Dice: " << GetValues<T>(seed, 30, 6) << std::endl;
  std::cout << "  Dice Summary: " << TestDice<T>(seed) << std::endl;
}

int main()
{
  // size_t seed = 675248;
  size_t seed = 123456;

  Test<MiddleSquare>("MiddleSquare", seed);
  Test<LCG>("LCG", seed);
}
