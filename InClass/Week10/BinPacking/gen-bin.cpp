#include <iostream>
#include <random>

int main(int argc, char * argv[]) {
    // Args: num_values  threshold_value   max_value

    if (argc != 4) {
        std::cerr << "Format: " << argv[0] << "  num_values threshold_value max_value\n";
        exit(1);
    }

    int num_values = atoi(argv[1]);
    double threshold = atof(argv[2]);
    double max_value = atof(argv[3]);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, max_value);

    std::cout << num_values << " " << threshold << "\n";
    for (int i = 0; i < num_values; i++) {
        std::cout << dis(gen) << std::endl;
    }
}