// C++ in 199 Pages - 7.2 Source file: the "kitchen" where the work happens.
#include "temperature.h"

double celsiusToFahrenheit(double c) {
    return c * 9.0 / 5.0 + 32.0;
}

double fahrenheitToCelsius(double f) {
    return (f - 32.0) * 5.0 / 9.0;
}

std::string describe(double celsius) {
    if (celsius < 10) return "cold";
    if (celsius < 25) return "mild";
    if (celsius < 35) return "warm";
    return "hot";
}
