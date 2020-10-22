#include <iostream>
#include <math.h>

int main()
{
    // double result = 0.0;
    // for (int c = 0;  c < 1000; ++c) {
    //     double sqrtc = sqrt(c);
    //     for (int a = 0; a < 1000; ++a) {
    //         for (int b = 0; b < 1000; ++b) {
    //             result += a * b + sqrtc;
    //         }
    //     }
    // }

    double result = 0.0;
    for (int c = 0;  c < 1000; ++c) {
        for (int a = 0; a < 1000; ++a) {
            for (int b = 0; b < 1000; ++b) {
                result += a * b + sqrt(c);
            }
        }
    }

    std::cout << "result = " << result << std::endl;
}