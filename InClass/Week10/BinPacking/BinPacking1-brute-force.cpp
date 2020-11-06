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
                 std::vector<double> undecided)
    {
        if (undecided.size() == 0) {
            double total = 0.0;
            for (double x : included) total += x;
            if (total > T) return 0.0;
            return total;
        }

        double next_val = undecided.back();
        undecided.pop_back();

        included.push_back(next_val);
        double val1 = Solve(included, excluded, undecided);

        included.pop_back();
        excluded.push_back(next_val);
        double val2 = Solve(included, excluded, undecided);

        return std::max(val1, val2);
    }

    double Solve() {
        std::vector<double> included;
        std::vector<double> excluded;
        std::vector<double> undecided(vals);
        return Solve(included, excluded, undecided);
    }
};

int main()
{
    BinPacking bp;

    bp.Print();

    std::cout << "\nResult: " << bp.Solve() << std::endl;
}