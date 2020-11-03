// A memoization version of our coin recursion.

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

size_t num_coins;                // N coin types
std::vector<int> coins;          // Values of each coin type.
size_t test_cases;               // Number of test cases to figure out.
std::vector<int> target_values;  // Target value for each test case.

int FindMinCoins(int value) {
    std::vector<int> min_coins(value+1);

    min_coins[0] = 0;
    for (int v = 1; v <= value; v++) {
        int min_coin_count = v;
        for (auto coin : coins) {
            if (coin > v) continue;  // If the coin is too big, skip it.
            int use_coin_count = 1 + min_coins[v - coin];
            if (use_coin_count < min_coin_count) min_coin_count = use_coin_count;
        }        
        min_coins[v] = min_coin_count;
    }

    return min_coins[value];
}

int main()
{
    /* Example input file....
     * 6
     * 30 24 12 6 3 1
     * 3
     * 2
     * 24
     * 48
     */

    std::cin >> num_coins;
    coins.resize(num_coins);
    for (auto & coin : coins) {
        std::cin >> coin;
    }

    if (coins.back() != 1) {
        std::cerr << "Oh no!  The last coin is not a 1!" << std::endl;
        exit(1);
    }
    coins.pop_back();

    std::cin >> test_cases;
    target_values.resize(test_cases);
    for (auto & target : target_values) {
        std::cin >> target;

        std::cout << target << " : " << FindMinCoins(target) << std::endl;
    }


}