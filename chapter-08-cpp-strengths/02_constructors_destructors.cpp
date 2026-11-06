// C++ in 199 Pages - 8.2 Constructors and destructors
// Build: g++ -std=c++17 02_constructors_destructors.cpp -o ctors && ./ctors

#include <iostream>
#include <stdexcept>
#include <string>

class HotelBooking {
public:
    // Constructor: runs when the object is created. The member initializer
    // list (after the colon) sets each member before the body runs.
    HotelBooking(const std::string& guest, int nights)
        : guest_(guest), nights_(nights) {
        if (nights <= 0) {
            throw std::invalid_argument("a booking needs at least one night");
        }
        std::cout << "  Booked: " << guest_ << " for " << nights_ << " night(s)\n";
    }

    // A second constructor (overloaded) that delegates to the first.
    explicit HotelBooking(const std::string& guest) : HotelBooking(guest, 1) {}

    // Destructor: runs automatically when the object is destroyed.
    ~HotelBooking() {
        std::cout << "  Checked out: " << guest_ << "\n";
    }

    int bill(int ratePerNight) const { return nights_ * ratePerNight; }

private:
    std::string guest_;
    int nights_;
};

int main() {
    std::cout << "Start of main\n";
    HotelBooking a("Meena", 3);
    {
        HotelBooking b("Tom");                     // one night, via the second constructor
        std::cout << "  Tom owes " << b.bill(2500) << "\n";
    }                                              // b is destroyed here
    try {
        HotelBooking bad("Nobody", 0);
    } catch (const std::invalid_argument& e) {
        std::cout << "  Rejected: " << e.what() << "\n";
    }
    std::cout << "  Meena owes " << a.bill(2500) << "\n";
    std::cout << "End of main\n";
    return 0;                                      // a is destroyed here
}
