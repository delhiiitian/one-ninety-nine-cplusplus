// C++ in 199 Pages - 6.6 Reading CSV data into structs
// Build: g++ -std=c++17 06_csv.cpp -o csv && ./csv

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Employee {
    std::string name;
    std::string department;
    double salary = 0.0;
};

std::vector<Employee> loadCsv(const std::string& path) {
    std::vector<Employee> rows;
    std::ifstream in(path);
    std::string line;
    std::getline(in, line);                       // skip the header row
    while (std::getline(in, line)) {
        std::istringstream fields(line);
        Employee e;
        std::string salaryText;
        std::getline(fields, e.name, ',');
        std::getline(fields, e.department, ',');
        std::getline(fields, salaryText, ',');
        try {
            e.salary = std::stod(salaryText);
            rows.push_back(e);
        } catch (const std::exception&) {
            std::cerr << "Skipping bad row: " << line << "\n";
        }
    }
    return rows;
}

int main() {
    {
        std::ofstream setup("staff.csv");
        setup << "name,department,salary\n"
              << "Asha,Engineering,92000\n"
              << "Ben,Sales,61000\n"
              << "Chitra,Engineering,105000\n"
              << "Dev,Sales,not-a-number\n"
              << "Esha,HR,58000\n";
    }

    std::vector<Employee> staff = loadCsv("staff.csv");
    double engTotal = 0.0;
    int engCount = 0;
    for (const Employee& e : staff) {
        std::cout << e.name << " (" << e.department << "): " << e.salary << "\n";
        if (e.department == "Engineering") {
            engTotal += e.salary;
            ++engCount;
        }
    }
    std::cout << "Loaded " << staff.size() << " rows. Engineering average: "
              << engTotal / engCount << "\n";
    return 0;
}
