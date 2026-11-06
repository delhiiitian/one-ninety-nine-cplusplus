// C++ in 199 Pages - Project 8: Parking Garage
// money.h - an exact money type with natural operators (lesson 8.6).
#pragma once

#include <iomanip>
#include <ostream>

class Money {
public:
    constexpr explicit Money(long long paise = 0) : paise_(paise) {}
    static constexpr Money rupees(long long r) { return Money(r * 100); }

    Money operator+(const Money& o) const { return Money(paise_ + o.paise_); }
    Money operator*(long long n) const { return Money(paise_ * n); }
    Money& operator+=(const Money& o) { paise_ += o.paise_; return *this; }
    bool operator<(const Money& o) const { return paise_ < o.paise_; }
    long long paise() const { return paise_; }

private:
    long long paise_;
};

inline std::ostream& operator<<(std::ostream& out, const Money& m) {
    return out << "Rs " << m.paise() / 100 << "." << std::setw(2) << std::setfill('0')
               << m.paise() % 100 << std::setfill(' ');
}
