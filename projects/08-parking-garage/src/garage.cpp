#include "garage.h"

#include <iomanip>
#include <iostream>
#include <sstream>

namespace {
std::string makeId(char prefix, int number) {
    std::ostringstream id;
    id << prefix << std::setw(2) << std::setfill('0') << number;
    return id.str();
}

std::string clock(int minutes) {
    std::ostringstream out;
    out << std::setw(2) << std::setfill('0') << minutes / 60 << ":"
        << std::setw(2) << minutes % 60;
    return out.str();
}
}  // namespace

Garage::Garage(int small, int regular, int large) {
    for (int i = 1; i <= small; ++i)   spots_.push_back({makeId('S', i), SpotSize::Small, nullptr, 0});
    for (int i = 1; i <= regular; ++i) spots_.push_back({makeId('R', i), SpotSize::Regular, nullptr, 0});
    for (int i = 1; i <= large; ++i)   spots_.push_back({makeId('L', i), SpotSize::Large, nullptr, 0});
}

// Smallest free spot that is big enough: a bike may use a regular spot if
// all small ones are taken, but a truck can only use a large spot.
Spot* Garage::findFreeSpot(SpotSize needed) {
    for (int size = static_cast<int>(needed); size <= static_cast<int>(SpotSize::Large); ++size) {
        for (Spot& spot : spots_) {
            if (!spot.vehicle && static_cast<int>(spot.size) == size) {
                return &spot;
            }
        }
    }
    return nullptr;
}

Spot* Garage::findByPlate(const std::string& plate) {
    for (Spot& spot : spots_) {
        if (spot.vehicle && spot.vehicle->plate() == plate) {
            return &spot;
        }
    }
    return nullptr;
}

std::optional<std::string> Garage::park(std::unique_ptr<Vehicle> vehicle, int time) {
    if (findByPlate(vehicle->plate())) {
        throw std::invalid_argument(vehicle->plate() + " is already parked");
    }
    Spot* spot = findFreeSpot(vehicle->size());
    if (!spot) {
        return std::nullopt;
    }
    visitsByKind_.add(vehicle->kind());
    spot->vehicle = std::move(vehicle);      // the garage now owns the vehicle
    spot->enteredAt = time;
    return spot->id;
}

std::optional<Receipt> Garage::leave(const std::string& plate, int time) {
    Spot* spot = findByPlate(plate);
    if (!spot) {
        return std::nullopt;
    }
    int minutes = time - spot->enteredAt;
    if (minutes < 0) minutes += 24 * 60;     // parked overnight
    Receipt r{plate, spot->vehicle->kind(), spot->id, minutes, spot->vehicle->fee(minutes)};
    revenue_ += r.fee;
    revenueByKind_.add(r.kind, r.fee.paise());
    spot->vehicle.reset();                   // the vehicle object is destroyed here
    return r;
}

void Garage::printStatus() const {
    int used = 0;
    for (const Spot& spot : spots_) {
        std::cout << "  " << spot.id << " ";
        if (spot.vehicle) {
            std::cout << std::left << std::setw(13) << spot.vehicle->kind() << std::right
                      << spot.vehicle->plate() << " since " << clock(spot.enteredAt) << "\n";
            ++used;
        } else {
            std::cout << "free (" << toString(spot.size) << ")\n";
        }
    }
    std::cout << "  " << used << "/" << spots_.size() << " spots in use\n";
}

void Garage::printReport() const {
    std::cout << "  " << std::left << std::setw(14) << "Vehicle" << std::right << std::setw(7)
              << "Visits" << std::setw(14) << "Revenue" << "\n";
    for (const auto& [kind, visits] : visitsByKind_.all()) {
        std::cout << "  " << std::left << std::setw(14) << kind << std::right << std::setw(7)
                  << visits << std::setw(14);
        std::ostringstream money;
        money << Money(revenueByKind_.get(kind));
        std::cout << money.str() << "\n";
    }
    std::cout << "  Total revenue: " << revenue_ << "\n";
}
