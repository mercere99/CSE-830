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

    std::vector< std::vector<double> > inc_vectors;
    std::vector< std::vector<double> > und_vectors;

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

    double Solve(int depth,
                 double included_total,
                 double undecided_total)
    {
        if (included_total > T) return 0.0;  // BACKTRACK IF ALREADY ILLEGAL!!
        if (included_total + undecided_total < best_total) return 0.0; // BOUND!
        if (und_vectors[depth].size() == 0) {
            if (included_total > best_total) {
                best_total = included_total;
                best_vals = inc_vectors[depth];
            }
            return included_total;
        }

        double next_val = und_vectors[depth].back();
        und_vectors[depth].pop_back();
        undecided_total -= next_val;

        inc_vectors[depth].push_back(next_val);
        if (inc_vectors.size() == depth+1) inc_vectors.resize(depth+2);
        if (und_vectors.size() == depth+1) und_vectors.resize(depth+2);
        inc_vectors[depth+1] = inc_vectors[depth];
        und_vectors[depth+1] = und_vectors[depth];
        double val1 = Solve(depth+1, included_total + next_val, undecided_total);

        inc_vectors[depth].pop_back();
        inc_vectors[depth+1] = inc_vectors[depth];
        und_vectors[depth+1] = und_vectors[depth];
        double val2 = Solve(depth+1, included_total, undecided_total);

        return std::max(val1, val2);
    }

    double Solve() {
        std::vector<double> included;
        std::vector<double> undecided(vals);
        double un_total = 0.0;
        for (double x : undecided) un_total += x;

        inc_vectors.push_back(included);
        und_vectors.push_back(undecided);
        return Solve(0, 0.0, un_total);
    }
};

int main()
{
    BinPacking bp;

    bp.Print();

    std::cout << "\nResult: " << bp.Solve() << std::endl;

    bp.PrintBest();
}