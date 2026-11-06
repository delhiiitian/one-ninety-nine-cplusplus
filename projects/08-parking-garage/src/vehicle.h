// C++ in 199 Pages - Project 8: Parking Garage
// vehicle.h - the vehicle class hierarchy (lessons 8.4 and 8.5).
#pragma once

#include <memory>
#include <string>

#include "money.h"

enum class SpotSize { Small = 0, Regular = 1, Large = 2 };

std::string toString(SpotSize size);

// Abstract base class: every vehicle has a plate, a size and a pricing rule.
class Vehicle {
public:
    explicit Vehicle(std::string plate);
    virtual ~Vehicle() = default;

    const std::string& plate() const { return plate_; }
    virtual std::string kind() const = 0;
    virtual SpotSize size() const = 0;
    virtual Money hourlyRate() const = 0;

    // Shared rule for every vehicle; derived classes may add to it.
    virtual Money fee(int minutesParked) const;

private:
    std::string plate_;
};

class Motorbike : public Vehicle {
public:
    using Vehicle::Vehicle;
    std::string kind() const override { return "Motorbike"; }
    SpotSize size() const override { return SpotSize::Small; }
    Money hourlyRate() const override { return Money::rupees(20); }
};

class Car : public Vehicle {
public:
    using Vehicle::Vehicle;
    std::string kind() const override { return "Car"; }
    SpotSize size() const override { return SpotSize::Regular; }
    Money hourlyRate() const override { return Money::rupees(40); }
};

// An electric car IS a car, plus a flat charging fee.
class ElectricCar : public Car {
public:
    using Car::Car;
    std::string kind() const override { return "Electric car"; }
    Money fee(int minutesParked) const override;
};

class Truck : public Vehicle {
public:
    using Vehicle::Vehicle;
    std::string kind() const override { return "Truck"; }
    SpotSize size() const override { return SpotSize::Large; }
    Money hourlyRate() const override { return Money::rupees(100); }
};

// Factory: turns the word typed by the attendant into the right object.
std::unique_ptr<Vehicle> makeVehicle(const std::string& type, const std::string& plate);
