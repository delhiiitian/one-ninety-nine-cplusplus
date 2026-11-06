// C++ in 199 Pages - Project 8: Parking Garage
// garage.h - spots, tickets and the garage itself.
#pragma once

#include <array>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "money.h"
#include "vehicle.h"

// A small template (lesson 8.7): counts things by any key type.
template <typename Key>
class Tally {
public:
    void add(const Key& key, long long amount = 1) { counts_[key] += amount; }
    long long get(const Key& key) const {
        auto it = counts_.find(key);
        return it == counts_.end() ? 0 : it->second;
    }
    const std::map<Key, long long>& all() const { return counts_; }
private:
    std::map<Key, long long> counts_;
};

struct Spot {
    std::string id;                      // e.g. "R03"
    SpotSize size;
    std::unique_ptr<Vehicle> vehicle;    // empty when the spot is free
    int enteredAt = 0;                   // minutes since midnight
};

struct Receipt {
    std::string plate;
    std::string kind;
    std::string spotId;
    int minutes = 0;
    Money fee;
};

class Garage {
public:
    Garage(int small, int regular, int large);

    // Returns the spot id, or nothing if no suitable spot is free.
    std::optional<std::string> park(std::unique_ptr<Vehicle> vehicle, int time);
    std::optional<Receipt> leave(const std::string& plate, int time);

    void printStatus() const;
    void printReport() const;

private:
    Spot* findFreeSpot(SpotSize needed);
    Spot* findByPlate(const std::string& plate);

    std::vector<Spot> spots_;
    Money revenue_;
    Tally<std::string> visitsByKind_;
    Tally<std::string> revenueByKind_;   // in paise
};
