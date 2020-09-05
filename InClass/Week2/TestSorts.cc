#include <algorithm>
#include <ctime>
#include <fstream>
#include <functional>
#include <iostream>
#include <random>
#include <string>
#include <vector>

// Create a type for storing sort functions.  Parameters are the vector to
// be sorted, the first position to sort, and the last position to sort+1.
using sort_fun_t = std::function<void(std::vector<double>&, int, int)>;

// A standard implementation of Insertion Sort
void InsertionSort(std::vector<double> & v, int start=0, int end=-1)
{                                             // N is end - start
    if (end == -1) end = v.size();

    for (int i = start+1; i < end; i++) {     // Run N-1 + 1 times
        double key = v[i];                    // Run N-1 times
        int j = i - 1;                        // Run N-1 times
        while (j >= start && v[j] > key) {    // Run N-1 to N(N-1)/2 + N-1 times
            v[j+1] = v[j];                    // Run 0 to N(N-1)/2 times
            --j;                              // Run 0 to N(N-1)/2 times
        }
        v[j+1] = key;                         // Run N-1 times
    }
}

void Merge(std::vector<double> & v, int start, int midpoint, int end) {
    std::vector<double> merged;
    int p1 = start;
    int p2 = midpoint;
    while (p1 < midpoint && p2 < end) {
        if (v[p1] < v[p2]) { merged.push_back(v[p1++]); }
        else { merged.push_back(v[p2++]); }
    }
    while (p1 < midpoint) merged.push_back(v[p1++]);
    while (p2 < end) merged.push_back(v[p2++]);

    std::copy_n(merged.begin(), merged.size(), v.begin()+start);
}

void DividedInsertionSort(std::vector<double> & v, int start=0, int end=-1)
{
    if (end == -1) end = v.size();
    if (end - start < 2) return;

    int midpoint = start + end / 2;
    InsertionSort(v, start, midpoint);
    InsertionSort(v, midpoint, end);

    Merge(v, start, midpoint, end);
}


// A quick function to print a vector of doubles.
void Print(const std::vector<double> & v, size_t max=(size_t)-1) {
    for (size_t i=0; i < max && i < v.size(); i++) {
        if (i) std::cout << ", ";
        std::cout << v[i];
    }
}

// Time a sorting function and return answer in seconds.
double TimeSortFun(sort_fun_t fun,
                   std::vector<double> v) {
    std::clock_t start_time = std::clock();
    fun(v, 0, v.size());
    std::clock_t total_time = std::clock() - start_time;
    return ((double) total_time) / (double) CLOCKS_PER_SEC;
}

int main(int argc, char *argv[])
{
    // Ensure that we received the correct command-line arguments.
    if (argc != 4) {
        std::cerr << "Error: expected exactly three arguments.  Format:\n"
                  << "  " << argv[0] << " [min_N] [max_N] [step]"
                  << std::endl;
        exit(1);
    }

    // Convert command line arguments from strings to useful values.
    size_t min_N = atoi(argv[1]);
    size_t max_N = atoi(argv[2]);
    size_t step = atoi(argv[3]);

    // Build a random-number generator for input values.
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0,1000.0);

    // Setup an output file for graphing.
    std::ofstream out_file("output.csv");

    // Loop through the specified input sizes and test each.
    for (size_t N = min_N; N <= max_N; N += step) {
        // The input size should be the first column of the CSV.
        out_file << N;

        // Generate a vector of the correct size.
        std::vector<double> v(N);
        for (auto & val : v) {
            val = dis(gen);
        }

        // Collect data on using InsertionSort.
        double run_time = TimeSortFun(InsertionSort, v);
        std::cout << "InsertionSort(N=" << N << ") Total time = " << run_time << " seconds." << std::endl;
        out_file << ", " << run_time;

        // Collect data on using InsertionSort.
        run_time = TimeSortFun(DividedInsertionSort, v);
        std::cout << "DividedInsertionSort(N=" << N << ") Total time = " << run_time << " seconds." << std::endl;
        out_file << ", " << run_time;

        // std::cout << "Unsorted: ";
        // Print(v);
        // std::cout << std::endl;

        // DividedInsertionSort(v);

        // std::cout << "Sorted:   ";
        // Print(v);
        // std::cout << std::endl;

        // Finish this line of the output file.
        out_file << std::endl;
    }
}