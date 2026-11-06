#include "vehicle.h"

#include <stdexcept>

namespace {
constexpr int kFreeMinutes = 15;
constexpr long long kDailyCapHours = 8;   // never charge more than 8 hours per stay
}  // namespace

std::string toString(SpotSize size) {
    switch (size) {
        case SpotSize::Small:   return "small";
        case SpotSize::Regular: return "regular";
        case SpotSize::Large:   return "large";
    }
    return "?";
}

Vehicle::Vehicle(std::string plate) : plate_(std::move(plate)) {
    if (plate_.empty()) {
        throw std::invalid_argument("number plate cannot be empty");
    }
}

Money Vehicle::fee(int minutesParked) const {
    if (minutesParked <= kFreeMinutes) {
        return Money(0);
    }
    long long startedHours = (minutesParked + 59) / 60;   // every started hour counts
    if (startedHours > kDailyCapHours) startedHours = kDailyCapHours;
    return hourlyRate() * startedHours;
}

Money ElectricCar::fee(int minutesParked) const {
    return Car::fee(minutesParked) + Money::rupees(150);   // the base rule, plus charging
}

std::unique_ptr<Vehicle> makeVehicle(const std::string& type, const std::string& plate) {
    if (type == "BIKE")  return std::make_unique<Motorbike>(plate);
    if (type == "CAR")   return std::make_unique<Car>(plate);
    if (type == "EV")    return std::make_unique<ElectricCar>(plate);
    if (type == "TRUCK") return std::make_unique<Truck>(plate);
    throw std::invalid_argument("unknown vehicle type '" + type + "'");
}
