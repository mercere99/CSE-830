#include <ctime>
#include <fstream>
#include <functional>
#include <iostream>
#include <random>
#include <string>
#include <vector>

// A standard implementation of Insertion Sort
void InsertionSort(std::vector<double> & v) { // N is v.size()
    for (size_t i = 1; i < v.size(); i++) {   // Run N-1 + 1 times
        double key = v[i];                    // Run N-1 times
        size_t j = i - 1;                     // Run N-1 times
        while (j < v.size() && v[j] > key) {  // Run N-1 to N(N-1)/2 + N-1 times
            v[j+1] = v[j];                    // Run 0 to N(N-1)/2 times
            --j;                              // Run 0 to N(N-1)/2 times
        }
        v[j+1] = key;                         // Run N-1 times
    }
}

// A quick function to print a vector of doubles.
void Print(const std::vector<double> & v, size_t max=(size_t)-1) {
    for (size_t i=0; i < max && i < v.size(); i++) {
        if (i) std::cout << ',';
        std::cout << v[i];
    }
}

// Time a sorting function and return answer in seconds.
double TimeSortFun(std::function<void(std::vector<double>&)> fun,
                   std::vector<double> v) {
    std::clock_t start_time = std::clock();
    fun(v);
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

        // Finish this line of the output file.
        out_file << std::endl;
    }
}