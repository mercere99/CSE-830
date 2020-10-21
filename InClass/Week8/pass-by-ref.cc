#include <iostream>
#include <vector>

int SumVec(const std::vector<int> & v, int start, int end) {
    if (start >= end) return 0;
    int total = v[start] + SumVec(v, start+1, end);
    return total;
}

int main()
{
    constexpr size_t N = 30000;
    std::vector<int> v(N);
    for (int i = 0; i < N; i++) {
        v[i] = i;
    }

    std::cout << "sum = " << SumVec(v, 0, v.size()) << std::endl;
}