// Fibinacci numbers: 0 1 1 2 3 5 8 13 21 34 ...

#include <iostream>

constexpr uint64_t Fib(int id) {
    if (id < 2) return id;
    return Fib(id - 1) + Fib(id - 2);
}

int main()
{
    constexpr uint64_t result = Fib(43);
    std::cout << "Fib(43) = " << result << std::endl;
}