#include "greeting.h"

std::string greet(const std::string& name, int hour) {
    std::string part = hour < 12 ? "morning" : hour < 17 ? "afternoon" : "evening";
    return "Good " + part + ", " + name + "!";
}
