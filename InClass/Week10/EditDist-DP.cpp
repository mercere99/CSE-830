/*
 *  Edit Distance: Compare two strings and report the minimum number of insertions, deletions
 *  and substitutions for going from one string to the other.
 * 
 *  NOW USING DYNAMIC PROGRAMMING!!!
 * 
 *  Compare:  PEAR  and  PARE
 * 
 *   P E A R _
 *   P _ A R E
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

int EditDist(std::string_view string1, std::string_view string2) {
    // Build an empty matrix for our results.
    std::vector< std::vector<int> > results(string1.size()+1);
    for (auto & row : results) row.resize(string2.size()+1);

    // *_pos is the substring size we are consider at each moment.
    for (size_t s1_pos = 0; s1_pos <= string1.size(); ++s1_pos) {
        for (size_t s2_pos = 0; s2_pos <= string2.size(); ++s2_pos) {
            // Base case: If either string is zero, all insertions or deletions to get to other string.
            if (s1_pos == 0) { results[s1_pos][s2_pos] = s2_pos; continue; }
            if (s2_pos == 0) { results[s1_pos][s2_pos] = s1_pos; continue; }

            // If the last characters match, call on one-smaller version.
            if (string1[s1_pos] == string2[s2_pos]) {
                results[s1_pos][s2_pos] = results[s1_pos-1][s2_pos-1];
                continue;
            }

            // Consider three options for how the end can be different!
            const int end_delete = results[s1_pos-1][s2_pos] + 1;
            const int end_insert = results[s1_pos][s2_pos-1] + 1;
            const int end_sub    = results[s1_pos-1][s2_pos-1] + 1;

            // Return the minimum of all three options.
            results[s1_pos][s2_pos] = std::min({end_delete, end_insert, end_sub});
        }
    }

    return results[string1.size()][string2.size()];

}

int main()
{
    std::string string1, string2;

    // Input format - two string to compare.
    std::cin >> string1 >> string2;

    int result = EditDist(string1, string2);

    std::cout << "String1: " << string1 << std::endl;
    std::cout << "String2: " << string2 << std::endl;
    std::cout << "Result = " << result << std::endl;
}