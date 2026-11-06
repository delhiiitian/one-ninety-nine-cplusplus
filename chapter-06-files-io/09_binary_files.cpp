// C++ in 199 Pages - 6.9 Binary files: saving raw bytes
// Build: g++ -std=c++17 09_binary_files.cpp -o binary && ./binary

#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

// A fixed-size record: easy to write and read as raw bytes.
struct SensorReading {
    std::int32_t sensorId;
    std::int32_t timestamp;
    double value;
};

int main() {
    std::vector<SensorReading> readings = {
        {7, 1000, 21.5}, {7, 1060, 21.9}, {9, 1060, 64.0}, {7, 1120, 22.4}};

    {
        std::ofstream out("readings.bin", std::ios::binary);
        std::int32_t count = static_cast<std::int32_t>(readings.size());
        out.write(reinterpret_cast<const char*>(&count), sizeof(count));
        out.write(reinterpret_cast<const char*>(readings.data()),
                  static_cast<std::streamsize>(readings.size() * sizeof(SensorReading)));
    }

    std::ifstream in("readings.bin", std::ios::binary);
    std::int32_t count = 0;
    in.read(reinterpret_cast<char*>(&count), sizeof(count));
    std::vector<SensorReading> loaded(static_cast<std::size_t>(count));
    in.read(reinterpret_cast<char*>(loaded.data()),
            static_cast<std::streamsize>(loaded.size() * sizeof(SensorReading)));

    std::cout << "Read back " << loaded.size() << " readings (" << sizeof(SensorReading)
              << " bytes each)\n";
    for (const SensorReading& r : loaded) {
        std::cout << "  sensor " << r.sensorId << " at t=" << r.timestamp << ": " << r.value << "\n";
    }

    // Jump straight to record 3 without reading the others: seekg.
    std::ifstream again("readings.bin", std::ios::binary);
    again.seekg(static_cast<std::streamoff>(sizeof(std::int32_t) + 2 * sizeof(SensorReading)));
    SensorReading third{};
    again.read(reinterpret_cast<char*>(&third), sizeof(third));
    std::cout << "Record 3 directly: sensor " << third.sensorId << ", value " << third.value << "\n";
    return 0;
}
