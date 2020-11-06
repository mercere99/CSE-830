// Bin Packing Problem - Brute force

#include <algorithm>
#include <iostream>
#include <vector>

class BinPacking {
private:
    int N;
    double T;
    std::vector<double> vals;

    double best_total = 0.0;
    std::vector<double> best_vals;

public:
    BinPacking(std::istream & is=std::cin) {
        // File Format:
        // N and T on the first line (Number of values and Target value)
        // N values on next N lines.

        is >> N >> T;
        vals.resize(N);
        for (double & x : vals) is >> x;
 
        std::sort(vals.begin(), vals.end());
   }

    void Print(std::ostream & os=std::cout) {
        os << N << " " << T << "\n";
        for (double x : vals) os << x << std::endl;
    }

    void PrintBest(std::ostream & os=std::cout) {
        for (double x : best_vals) os << " " << x;
        os << std::endl;
    }

    double Solve(std::vector<double> included,
                 std::vector<double> excluded,
                 std::vector<double> undecided,
                 double included_total,
                 double undecided_total)
    {
        if (included_total > T) return 0.0;  // BACKTRACK IF ALREADY ILLEGAL!!
        if (included_total + undecided_total < best_total) return 0.0; // BOUND!
        if (undecided.size() == 0) {
            if (included_total > best_total) {
                best_total = included_total;
                best_vals = included;
            }
            return included_total;
        }

        double next_val = undecided.back();
        undecided.pop_back();
        undecided_total -= next_val;

        included.push_back(next_val);
        double val1 = Solve(included, excluded, undecided,
                            included_total + next_val, undecided_total);

        included.pop_back();
        excluded.push_back(next_val);
        double val2 = Solve(included, excluded, undecided,
                            included_total, undecided_total);

        return std::max(val1, val2);
    }

    double Solve() {
        std::vector<double> included;
        std::vector<double> excluded;
        std::vector<double> undecided(vals);
        double un_total = 0.0;
        for (double x : undecided) un_total += x;
        return Solve(included, excluded, undecided, 0.0, un_total);
    }
};

int main()
{
    BinPacking bp;

    bp.Print();

    std::cout << "\nResult: " << bp.Solve() << std::endl;

    bp.PrintBest();
}