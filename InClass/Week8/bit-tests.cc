#include <iostream>
#include <vector>
#include <bitset>
#include <ctime>

int main()
{
    constexpr size_t N = 10000000;

    std::clock_t start_time = std::clock();

    std::vector<bool> bits_vb(N);
    for (size_t i = 0; i < bits_vb.size(); i++) {
        if (i%3 == 0 || i%5 == 0) bits_vb[i] = true;
        else bits_vb[i] = false;
    }

    size_t count = 0;
    for (auto x : bits_vb) if (x) count++;

    std::clock_t tot_time = std::clock() - start_time;

    std::cout << "std::vector<bool>\n"
              << "count = " << count << std::endl
              << "Time: "
              << ((double) tot_time) / (double) CLOCKS_PER_SEC
              << " seconds.\n";



    // VECTOR OF CHAR
    start_time = std::clock();

    std::vector<char> bits_vc(N);
    for (size_t i = 0; i < bits_vc.size(); i++) {
        if (i%3 == 0 || i%5 == 0) bits_vc[i] = true;
        else bits_vc[i] = false;
    }

    count = 0;
    for (auto x : bits_vc) if (x) count++;

    tot_time = std::clock() - start_time;

    std::cout << "\nstd::vector<char>\n"
              << "count = " << count << std::endl
              << "Time: "
              << ((double) tot_time) / (double) CLOCKS_PER_SEC
              << " seconds.\n";




    // BITSET
    start_time = std::clock();

    std::bitset<N> bits;
    for (size_t i = 0; i < bits.size(); i++) {
        if (i%3 == 0 || i%5 == 0) bits[i] = true;
        else bits[i] = false;
    }

    count = 0;
    for (size_t i = 0; i < bits.size(); i++) {
        if (bits[i]) count++;
    }

    tot_time = std::clock() - start_time;

    std::cout << "\nstd::bitset\n"
              << "count = " << count << std::endl
              << "Time: "
              << ((double) tot_time) / (double) CLOCKS_PER_SEC
              << " seconds.\n";
}