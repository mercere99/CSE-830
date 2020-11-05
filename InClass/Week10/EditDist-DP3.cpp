/*
 *  Edit Distance: Compare two strings and report the minimum number of insertions, deletions
 *  and substitutions for going from one string to the other.
 * 
 *  CLEANED UP INTO A PROPER OBJECT.
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

class StringCompare {
private:
    std::string string1;
    std::string string2;

    enum class DIR { UP=1, LEFT=2, UPLEFT=3 };
    std::vector< std::vector<int> > results;
    std::vector< std::vector<DIR> > direction;

public:
    StringCompare(const std::string & s1, const std::string & s2)
        : string1(s1), string2(s2)
        , results(string2.size()+1)
        , direction(string2.size()+1)
    {
        // Build an empty matrix for our results.
        for (auto & row : results) row.resize(string2.size()+1);

        // Direction will indicate which value each result is built off of.
        for (auto & row : direction) row.resize(string2.size()+1);
    }

    int EditDist() {
        // *_pos is the substring size we are consider at each moment.
        for (size_t s1_size = 0; s1_size <= string1.size(); ++s1_size) {
            for (size_t s2_size = 0; s2_size <= string2.size(); ++s2_size) {
                // Base case: If either string is zero, use only insertions or
                //            deletions to get to other string.
                if (s1_size == 0) {
                    results[s1_size][s2_size] = s2_size;
                    direction[s1_size][s2_size] = DIR::LEFT;
                    continue;
                }
                if (s2_size == 0) {
                    results[s1_size][s2_size] = s1_size;
                    direction[s1_size][s2_size] = DIR::UP;
                    continue;
                }

                // If the last characters match, call on one-smaller version.
                if (string1[s1_size-1] == string2[s2_size-1]) {
                    results[s1_size][s2_size] = results[s1_size-1][s2_size-1];
                    direction[s1_size][s2_size] = DIR::UPLEFT;
                    continue;
                }

                // Consider three options for how the end can be different!
                const int end_delete = results[s1_size-1][s2_size] + 1;
                const int end_insert = results[s1_size][s2_size-1] + 1;
                const int end_sub    = results[s1_size-1][s2_size-1] + 1;
                const int min_val    = std::min({end_delete, end_insert, end_sub});

                // Figure out direction.
                if (end_delete == min_val) direction[s1_size][s2_size] = DIR::UP;
                else if (end_insert == min_val) direction[s1_size][s2_size] = DIR::LEFT;
                else direction[s1_size][s2_size] = DIR::UPLEFT;

                // Return the minimum of all three options.
                results[s1_size][s2_size] = min_val;
            }
        }

        return results[string1.size()][string2.size()];
    }

    void PrintDirections(std::ostream & os=std::cout) {
        for (size_t s1_size = 0; s1_size <= string1.size(); ++s1_size) {
            for (size_t s2_size = 0; s2_size <= string2.size(); ++s2_size) {
                switch (direction[s1_size][s2_size]) {
                case DIR::UP:
                    std::cout << " |";
                    break;
                case DIR::LEFT:
                    std::cout << " -";
                    break;
                case DIR::UPLEFT:
                    std::cout << " \\";
                    break;
                default:
                    break;
                    std::cout << "!!";
                }
            }
            std::cout << std::endl;
        }
    }

    void PrintAlignment(std::ostream & os=std::cout) {
        std::string align1, align2;

        // Identify the first positions to consider.
        size_t s1_size = string1.size();
        size_t s2_size = string2.size();

        while (s1_size > 0 && s2_size > 0) {
            switch (direction[s1_size][s2_size]) {
            case DIR::UP:
                align1.insert(align1.begin(), string1[--s1_size]);
                align2.insert(align2.begin(), '_');
                continue;
            case DIR::LEFT:
                align1.insert(align1.begin(), '_');
                align2.insert(align2.begin(), string2[--s2_size]);
                continue;
            case DIR::UPLEFT:
                align1.insert(align1.begin(), string1[--s1_size]);
                align2.insert(align2.begin(), string2[--s2_size]);
                continue;
            default:
                std::cout << "ERROR!" << std::endl;
            }
        }

        // align1.insert(align1.begin(), '*');
        // align2.insert(align2.begin(), '*');

        // By here, one side or the other must be zero.  Fill out other side.
        while (s1_size > 0) {
            align1.insert(align1.begin(), string1[--s1_size]);
            align2.insert(align2.begin(), '_');
        }
        while (s2_size > 0) {
            align1.insert(align1.begin(), '_');
            align2.insert(align2.begin(), string2[--s2_size]);
        }

        os << "Alignment:\n" << align1 << "\n" << align2 << std::endl;
    }
};

int main()
{
    std::string string1, string2;

    // Input format - two string to compare.
    std::cin >> string1 >> string2;

    StringCompare compare(string1, string2);

    int result = compare.EditDist();

    std::cout << "String1: " << string1 << std::endl;
    std::cout << "String2: " << string2 << std::endl;
    std::cout << "Result = " << result << std::endl;

    compare.PrintDirections();
    
    std::cout << std::endl;

    compare.PrintAlignment();
}