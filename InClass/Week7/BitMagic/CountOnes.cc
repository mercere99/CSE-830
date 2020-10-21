#include <ctime>
#include <functional>
#include <iostream>
#include <random>
#include <vector>


int CountOnes(uint32_t val) {
    int count = 0;
    for (int i = 0; i  < 32; i++) {
        if (val & (1 << i)) count++;
    }

    return count;
}

int CountOnes2(uint32_t val) {
    int count = 0;
    while (val) {
        val &= val - 1;  // Remove the last 1.
        count++;
    }

    return count;
}

int CountOnes3(uint32_t val) {
  val = (val & 0x55555555) + ((val>>1)  & 0x55555555);
  val = (val & 0x33333333) + ((val>>2)  & 0x33333333);
  val = (val & 0x0f0f0f0f) + ((val>>4)  & 0x0f0f0f0f);
  val = (val & 0x00ff00ff) + ((val>>8)  & 0x00ff00ff);
  val = (val & 0x0000ffff) + ((val>>16) & 0x0000ffff);
  return val;
}

static const unsigned char BitsSetTable256[] = {
  0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8 };

int CountOnes4(uint32_t val) {
    return BitsSetTable256[val & 0xff]
        + BitsSetTable256[(val >> 8) & 0xff]
        + BitsSetTable256[(val >> 16) & 0xff]
        + BitsSetTable256[(val >> 24) & 0xff];
}

// Time how long it takes to count bits in all values passed in.
double TimeCount(std::function<int(uint32_t val)> fun,
                 const std::vector<uint32_t> & vals,
                 std::vector<uint32_t> & results)
{
    std::clock_t start_time = std::clock();

    for (size_t i = 0; i < vals.size(); i++) {
        results[i] = fun( vals[i] );
    }

    std::clock_t total_time = std::clock() - start_time;
    return ((double) total_time) / (double) CLOCKS_PER_SEC;
}


int main() {
    uint32_t bits = 0b01100100101011010100001010101111;

    std::cout << "bits value = " << bits << std::endl;
    std::cout << "CountOnes  = " << CountOnes(bits) << std::endl;
    std::cout << "CountOnes2 = " << CountOnes2(bits) << std::endl;
    std::cout << "CountOnes3 = " << CountOnes3(bits) << std::endl;
    std::cout << "CountOnes4 = " << CountOnes4(bits) << std::endl;

     // Build a random-number generator for input values.
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib;

    size_t N = 10000000;
    std::vector<uint32_t> values(N);
    std::vector<uint32_t> results(N);

    for (size_t i = 0; i < N; i++) {
        values[i] = distrib(gen);
    }

    double time1 = TimeCount(CountOnes, values, results);
    std::cout << "time 1 = " << time1 << std::endl;
   
    double time2 = TimeCount(CountOnes2, values, results);
    std::cout << "time 2 = " << time2 << std::endl;

    double time3 = TimeCount(CountOnes3, values, results);
    std::cout << "time 3 = " << time3 << std::endl;
   
    double time4 = TimeCount(CountOnes4, values, results);
    std::cout << "time 4 = " << time4 << std::endl;
   
   
}
