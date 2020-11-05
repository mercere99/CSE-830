/*
 *  Edit Distance: Compare two strings and report the minimum number of insertions, deletions
 *  and substitutions for going from one string to the other.
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

int EditDist(std::string_view string1, std::string_view string2) {
    // Base case: If either string is zero, all insertions or deletions to get to other string.
    if (string1.size() == 0) return string2.size();
    if (string2.size() == 0) return string1.size();

    std::string_view string1_shorter = string1;
    string1_shorter.remove_suffix(1);

    std::string_view string2_shorter = string2;
    string2_shorter.remove_suffix(1);

    // If the last characters match, call on one-smaller version.
    if (string1.back() == string2.back()) {
        return EditDist( string1_shorter, string2_shorter );
    }

    // Consider three options for how the end can be different!
    int end_delete = EditDist(string1_shorter, string2) + 1;
    int end_insert = EditDist(string1,         string2_shorter) + 1;
    int end_sub    = EditDist(string1_shorter, string2_shorter) + 1;

    // Return the minimum of all three options.
    return std::min({end_delete, end_insert, end_sub});
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