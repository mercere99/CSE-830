#include <iostream>
#include <vector>

double ProbWinning(int num_people, int num_scratches) {
    if (num_people <= num_scratches) return 1.0;

    // Probability of FIRST person finding their name.
    double p_everyone = 0.0;
    for (int cycle_size = 1; cycle_size <= num_scratches; cycle_size++) {
        double p1 = 1.0 / (double) num_people;
        double p_everyone_else = ProbWinning(num_people - cycle_size, num_scratches);
        p_everyone += p1 * p_everyone_else;
    }
    return p_everyone;
}

double ProbWinningDP(int total_people, int num_scratches) {
    std::vector<double> probs(total_people+1);

    for (int num_people = 0; num_people <= total_people; num_people++) {
        if (num_people <= num_scratches) {
            probs[num_people] = 1.0;
            continue;
        }

        // Probability of FIRST person finding their name.
        double p_everyone = 0.0;
        for (int cycle_size = 1; cycle_size <= num_scratches; cycle_size++) {
            double p1 = 1.0 / (double) num_people;
            double p_everyone_else = probs[num_people - cycle_size];
            p_everyone += p1 * p_everyone_else;
        }

        probs[num_people] = p_everyone;
    }

    return probs.back();
}

int main()
{
    // N people.
    // p_self = 1/N <= cycle with 1 node.
    // p cycle size 2 = (N-1) / N  * 1/(N-1)  = 1/N
    // p cycle size 3 = (N-1)/N * (N-2)/(N-1) * 1/(N-2) = 1/N
    // p cycle size 30 = 1/N
    // p cycle size k = 1/N

    std::cout << "Probability of winning = " << ProbWinningDP(100,50) << std::endl;
}