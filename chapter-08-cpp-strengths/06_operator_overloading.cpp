// C++ in 199 Pages - 8.6 Operator overloading
// Build: g++ -std=c++17 06_operator_overloading.cpp -o operators && ./operators

#include <iomanip>
#include <iostream>

// Money stored as whole paise, with natural operators.
class Money {
public:
    explicit Money(long long paise = 0) : paise_(paise) {}
    static Money rupees(double r) { return Money(static_cast<long long>(r * 100 + 0.5)); }

    Money operator+(const Money& other) const { return Money(paise_ + other.paise_); }
    Money operator-(const Money& other) const { return Money(paise_ - other.paise_); }
    Money operator*(int times) const { return Money(paise_ * times); }
    Money& operator+=(const Money& other) { paise_ += other.paise_; return *this; }

    bool operator==(const Money& other) const { return paise_ == other.paise_; }
    bool operator<(const Money& other) const { return paise_ < other.paise_; }

    long long paise() const { return paise_; }

private:
    long long paise_;
};

// << is overloaded as a free function so it works as: std::cout << money
std::ostream& operator<<(std::ostream& out, const Money& m) {
    return out << "Rs " << m.paise() / 100 << "." << std::setw(2) << std::setfill('0')
               << m.paise() % 100 << std::setfill(' ');
}

int main() {
    Money coffee = Money::rupees(149.50);
    Money sandwich = Money::rupees(220);
    Money bill = coffee * 2 + sandwich;             // reads like maths
    std::cout << "Bill: " << bill << "\n";

    Money paid = Money::rupees(600);
    std::cout << "Change: " << paid - bill << "\n";

    Money tips;
    tips += Money::rupees(20);
    tips += Money::rupees(30.25);
    std::cout << "Tips: " << tips << "\n";

    std::cout << std::boolalpha << "Coffee cheaper than sandwich? " << (coffee < sandwich) << "\n";
    std::cout << "0.10 + 0.20 == 0.30? " << (Money::rupees(0.10) + Money::rupees(0.20) == Money::rupees(0.30))
              << " (exact, because we store paise)\n";
    return 0;
}
