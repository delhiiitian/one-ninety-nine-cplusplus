// C++ in 199 Pages - 9.2 Environment variables
// Build: g++ -std=c++17 02_environment_variables.cpp -o env
// Run:   APP_MODE=production APP_PORT=9090 ./env

#include <cstdlib>
#include <iostream>
#include <optional>
#include <string>

// std::getenv returns a null pointer when the variable is not set.
std::optional<std::string> readEnv(const char* name) {
    const char* value = std::getenv(name);
    if (value == nullptr) return std::nullopt;
    return std::string(value);
}

std::string envOr(const char* name, const std::string& fallback) {
    return readEnv(name).value_or(fallback);
}

int main() {
    std::string mode = envOr("APP_MODE", "development");
    int port = std::stoi(envOr("APP_PORT", "8080"));
    bool hasKey = readEnv("APP_API_KEY").has_value();

    std::cout << "Mode:    " << mode << "\n";
    std::cout << "Port:    " << port << "\n";
    std::cout << "API key: " << (hasKey ? "set (hidden)" : "not set") << "\n";

    if (auto home = readEnv("HOME")) {
        std::cout << "HOME is set (" << home->size() << " characters)\n";
    } else {
        std::cout << "HOME is not set\n";
    }
    return 0;
}
