// C++ in 199 Pages - 7.9 Using a library: include its header, link its archive.
// Build: make && ./report
//   (manually: g++ -std=c++17 -c stats/stats.cpp -o stats.o
//              ar rcs libstats.a stats.o
//              g++ -std=c++17 main.cpp -Istats -L. -lstats -o report)

#include <iostream>
#include <vector>
#include "stats/stats.h"

int main() {
    std::vector<double> deliveryMinutes = {28, 35, 22, 41, 30, 26, 95, 33};
    std::cout << "Deliveries: " << deliveryMinutes.size() << "\n";
    std::cout << "Mean:   " << stats::mean(deliveryMinutes) << " min\n";
    std::cout << "Median: " << stats::median(deliveryMinutes) << " min\n";
    std::cout << "Std dev: " << stats::standardDeviation(deliveryMinutes) << " min\n";
    std::cout << "(The one 95-minute delivery pulls the mean above the median.)\n";
    return 0;
}
