// C++ in 199 Pages - 3.7 Recursion
// Build: g++ -std=c++17 07_recursion.cpp -o recursion && ./recursion

#include <iostream>
#include <string>

// n! = n * (n-1)!   with the base case 0! = 1
long long factorial(int n) {
    if (n <= 1) {
        return 1;                      // base case: stops the recursion
    }
    return n * factorial(n - 1);       // recursive case: a smaller problem
}

// Sum of the digits of a number: 4096 -> 4+0+9+6 = 19
int digitSum(int n) {
    if (n < 10) {
        return n;
    }
    return n % 10 + digitSum(n / 10);
}

// Russian dolls: open each doll until the smallest one.
void openDoll(int size) {
    std::string indent(static_cast<std::size_t>(5 - size) * 2, ' ');
    if (size == 1) {
        std::cout << indent << "Smallest doll found!\n";
        return;
    }
    std::cout << indent << "Opening doll " << size << "\n";
    openDoll(size - 1);
    std::cout << indent << "Closing doll " << size << "\n";
}

int main() {
    std::cout << "5! = " << factorial(5) << "\n";
    std::cout << "20! = " << factorial(20) << "\n";
    std::cout << "Digit sum of 4096 = " << digitSum(4096) << "\n";
    openDoll(4);
    return 0;
}
