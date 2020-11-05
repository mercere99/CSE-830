/*
 *  Edit Distance: Compare two strings and report the minimum number of insertions, deletions
 *  and substitutions for going from one string to the other.
 * 
 *  NOW PRINTING THE DIFFERENCES!!
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

enum class DIR { UP=1, LEFT=2, UPLEFT=3 };

std::vector< std::vector<DIR> > direction;

int EditDist(std::string_view string1, std::string_view string2) {
    // Build an empty matrix for our results.
    std::vector< std::vector<int> > results(string1.size()+1);
    for (auto & row : results) row.resize(string2.size()+1);

    // Direction will indicate which value each result is built off of.
    direction.resize(string1.size()+1);
    for (auto & row : direction) row.resize(string2.size()+1);


    // *_pos is the substring size we are consider at each moment.
    for (size_t s1_pos = 0; s1_pos <= string1.size(); ++s1_pos) {
        for (size_t s2_pos = 0; s2_pos <= string2.size(); ++s2_pos) {
            // Base case: If either string is zero, all insertions or deletions to get to other string.
            if (s1_pos == 0) {
                results[s1_pos][s2_pos] = s2_pos;
                direction[s1_pos][s2_pos] = DIR::LEFT;
                continue;
            }
            if (s2_pos == 0) {
                results[s1_pos][s2_pos] = s1_pos;
                direction[s1_pos][s2_pos] = DIR::UP;
                continue;
            }

            // If the last characters match, call on one-smaller version.
            if (string1[s1_pos] == string2[s2_pos]) {
                results[s1_pos][s2_pos] = results[s1_pos-1][s2_pos-1];
                direction[s1_pos][s2_pos] = DIR::UPLEFT;
                continue;
            }

            // Consider three options for how the end can be different!
            const int end_delete = results[s1_pos-1][s2_pos] + 1;
            const int end_insert = results[s1_pos][s2_pos-1] + 1;
            const int end_sub    = results[s1_pos-1][s2_pos-1] + 1;
            const int min_val    = std::min({end_delete, end_insert, end_sub});

            // Figure out direction.
            if (end_delete == min_val) direction[s1_pos][s2_pos] = DIR::UP;
            else if (end_insert == min_val) direction[s1_pos][s2_pos] = DIR::LEFT;
            else direction[s1_pos][s2_pos] = DIR::UPLEFT;

            // Return the minimum of all three options.
            results[s1_pos][s2_pos] = min_val;
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

    // Now let's determine alignment.
    std::string align1, align2;

    size_t pos1 = string1.size();
    size_t pos2 = string2.size();

    while (pos1 > 0 || pos2 > 0) {
        if (direction[pos1][pos2] == DIR::UP) {
            align1.insert(align1.begin(), string1[pos1--]);
            align2.insert(align2.begin(), '_');
            continue;
        }
        else if (direction[pos1][pos2] == DIR::LEFT) {
            align1.insert(align1.begin(), '_');
            align2.insert(align2.begin(), string2[pos2--]);
            continue;
        }
        else {
            align1.insert(align1.begin(), string1[pos1--]);
            align2.insert(align2.begin(), string2[pos2--]);
            continue;
        }
    }

    std::cout << "Alignment:\n" << align1 << "\n" << align2 << std::endl;
}