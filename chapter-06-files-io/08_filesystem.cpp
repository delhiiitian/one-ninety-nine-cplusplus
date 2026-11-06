// C++ in 199 Pages - 6.8 std::filesystem: folders, paths and file info
// Build: g++ -std=c++17 08_filesystem.cpp -o fs && ./fs

#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

namespace fs = std::filesystem;

int main() {
    fs::path base = "photos_demo";
    fs::remove_all(base);                               // clean start
    fs::create_directories(base / "2026" / "goa");      // '/' joins paths safely

    for (const char* name : {"beach.jpg", "sunset.jpg", "notes.txt"}) {
        std::ofstream(base / "2026" / "goa" / name) << "fake data for " << name;
    }

    std::cout << "Exists? " << std::boolalpha << fs::exists(base / "2026") << "\n";

    std::vector<std::string> found;
    std::uintmax_t totalBytes = 0;
    for (const auto& entry : fs::recursive_directory_iterator(base)) {
        if (entry.is_regular_file()) {
            found.push_back(entry.path().filename().string() + " (" +
                            entry.path().extension().string() + ", " +
                            std::to_string(entry.file_size()) + " bytes)");
            totalBytes += entry.file_size();
        }
    }
    std::sort(found.begin(), found.end());        // directory order is not guaranteed
    for (const auto& f : found) std::cout << "  " << f << "\n";
    std::cout << "Total: " << totalBytes << " bytes\n";

    fs::path p = base / "2026" / "goa" / "beach.jpg";
    std::cout << "stem=" << p.stem() << " parent=" << p.parent_path() << "\n";

    fs::rename(p, base / "2026" / "goa" / "beach_day1.jpg");
    std::cout << "Renamed: " << fs::exists(base / "2026" / "goa" / "beach_day1.jpg") << "\n";

    fs::remove_all(base);                              // tidy up
    return 0;
}
