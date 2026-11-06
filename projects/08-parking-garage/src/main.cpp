// C++ in 199 Pages - Project 8: Parking Garage Manager
// Uses Chapter 8 ideas: classes, constructors, encapsulation, inheritance,
// polymorphism, operator overloading, templates, smart pointers and moves.
//
// Commands (one per line):
//   ENTER <BIKE|CAR|EV|TRUCK> <plate> <hh:mm>
//   EXIT <plate> <hh:mm>
//   STATUS        REPORT        QUIT
//
// Build: make        Run: make run        Test: make test

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "garage.h"

int parseTime(const std::string& text) {
    int h = 0, m = 0;
    char colon = 0;
    std::istringstream in(text);
    if (!(in >> h >> colon >> m) || colon != ':' || h < 0 || h > 23 || m < 0 || m > 59) {
        throw std::invalid_argument("time must look like 09:30");
    }
    return h * 60 + m;
}

int main() {
    Garage garage(2, 3, 1);           // 2 small, 3 regular, 1 large spot
    std::cout << "Garage open: 2 small, 3 regular, 1 large spot.\n";

    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;
        std::cout << "> " << line << "\n";
        std::istringstream args(line);
        std::string command;
        args >> command;
        try {
            if (command == "ENTER") {
                std::string type, plate, time;
                args >> type >> plate >> time;
                auto vehicle = makeVehicle(type, plate);
                std::string kind = vehicle->kind();
                auto spot = garage.park(std::move(vehicle), parseTime(time));
                if (spot) {
                    std::cout << "  " << kind << " " << plate << " -> spot " << *spot << "\n";
                } else {
                    std::cout << "  Sorry, no free spot for a " << kind << "\n";
                }
            } else if (command == "EXIT") {
                std::string plate, time;
                args >> plate >> time;
                auto receipt = garage.leave(plate, parseTime(time));
                if (receipt) {
                    std::cout << "  " << receipt->kind << " " << receipt->plate << " left "
                              << receipt->spotId << " after " << receipt->minutes
                              << " min. Fee: " << receipt->fee << "\n";
                } else {
                    std::cout << "  No vehicle with plate " << plate << "\n";
                }
            } else if (command == "STATUS") {
                garage.printStatus();
            } else if (command == "REPORT") {
                garage.printReport();
            } else if (command == "QUIT") {
                break;
            } else {
                std::cout << "  Unknown command\n";
            }
        } catch (const std::exception& e) {
            std::cout << "  Error: " << e.what() << "\n";
        }
    }
    std::cout << "Garage closed.\n";
    return 0;
}
