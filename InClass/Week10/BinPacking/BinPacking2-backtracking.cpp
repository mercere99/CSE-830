// Bin Packing Problem - Brute force

#include <algorithm>
#include <iostream>
#include <vector>

class BinPacking {
private:
    int N;
    double T;
    std::vector<double> vals;

public:
    BinPacking(std::istream & is=std::cin) {
        // File Format:
        // N and T on the first line (Number of values and Target value)
        // N values on next N lines.

        is >> N >> T;
        vals.resize(N);
        for (double & x : vals) is >> x;
    }

    void Print(std::ostream & os=std::cout) {
        os << N << " " << T << "\n";
        for (double x : vals) os << x << std::endl;
    }

    double Solve(std::vector<double> included,
                 std::vector<double> excluded,
                 std::vector<double> undecided,
                 double included_total)
    {
        if (included_total > T) return 0.0;  // BACKTRACK IF ALREADY ILLEGAL!!
        if (undecided.size() == 0) return included_total;

        double next_val = undecided.back();
        undecided.pop_back();

        included.push_back(next_val);
        double val1 = Solve(included, excluded, undecided, included_total + next_val);

        included.pop_back();
        excluded.push_back(next_val);
        double val2 = Solve(included, excluded, undecided, included_total);

        return std::max(val1, val2);
    }

    double Solve() {
        std::vector<double> included;
        std::vector<double> excluded;
        std::vector<double> undecided(vals);
        return Solve(included, excluded, undecided, 0.0);
    }
};

int main()
{
    BinPacking bp;

    bp.Print();

    std::cout << "\nResult: " << bp.Solve() << std::endl;
}