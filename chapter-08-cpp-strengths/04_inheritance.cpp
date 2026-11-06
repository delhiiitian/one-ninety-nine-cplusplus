// C++ in 199 Pages - 8.4 Inheritance: building on an existing class
// Build: g++ -std=c++17 04_inheritance.cpp -o inherit && ./inherit

#include <iomanip>
#include <iostream>
#include <string>

class Employee {
public:
    Employee(const std::string& name, double monthlySalary)
        : name_(name), monthlySalary_(monthlySalary) {}

    const std::string& name() const { return name_; }
    double annualPay() const { return monthlySalary_ * 12; }

private:
    std::string name_;

protected:                              // visible to derived classes, hidden from others
    double monthlySalary_;
};

// A Manager IS an Employee, plus a team and a bonus.
class Manager : public Employee {
public:
    Manager(const std::string& name, double monthlySalary, int teamSize)
        : Employee(name, monthlySalary), teamSize_(teamSize) {}   // build the base part first

    double bonus() const { return monthlySalary_ * 0.5 * teamSize_ / 5.0; }
    int teamSize() const { return teamSize_; }

private:
    int teamSize_;
};

void printPay(const Employee& e) {      // accepts Employees AND Managers
    std::cout << e.name() << ": annual pay " << e.annualPay() << "\n";
}

int main() {
    std::cout << std::fixed << std::setprecision(0);
    Employee dev("Kavya", 90000);
    Manager lead("Rohit", 140000, 10);

    printPay(dev);
    printPay(lead);                                       // a Manager works where an Employee is expected
    std::cout << lead.name() << " leads " << lead.teamSize()
              << " people, bonus " << lead.bonus() << "\n";
    return 0;
}
