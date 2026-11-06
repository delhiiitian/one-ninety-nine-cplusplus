// C++ in 199 Pages - 8.9 Move semantics: transfer instead of copy
// Build: g++ -std=c++17 09_move_semantics.cpp -o move && ./move

#include <iostream>
#include <string>
#include <utility>
#include <vector>

// A class that reports when it is copied or moved, so we can watch.
class Video {
public:
    explicit Video(std::string name) : name_(std::move(name)), frames_(1'000'000, 0) {}

    Video(const Video& other) : name_(other.name_), frames_(other.frames_) {
        std::cout << "  COPY " << name_ << " (1,000,000 frames duplicated)\n";
    }
    Video(Video&& other) noexcept
        : name_(std::move(other.name_)), frames_(std::move(other.frames_)) {
        std::cout << "  MOVE " << name_ << " (just a pointer handed over)\n";
    }
    Video& operator=(const Video&) = default;
    Video& operator=(Video&&) noexcept = default;

    std::size_t frameCount() const { return frames_.size(); }
    const std::string& name() const { return name_; }

private:
    std::string name_;
    std::vector<int> frames_;
};

Video record(const std::string& name) {
    Video v(name);
    return v;            // returned objects are moved (or the copy is skipped entirely)
}

int main() {
    std::vector<Video> library;
    library.reserve(4);                              // avoid moves caused by regrowth

    Video holiday("holiday.mp4");
    std::cout << "push_back(holiday):\n";
    library.push_back(holiday);                      // copy: we still use holiday later

    std::cout << "push_back(std::move(birthday)):\n";
    Video birthday("birthday.mp4");
    library.push_back(std::move(birthday));          // move: we are done with birthday
    std::cout << "  birthday now has " << birthday.frameCount() << " frames (moved-from)\n";

    std::cout << "push_back(record(...)):\n";
    library.push_back(record("wedding.mp4"));        // a temporary is moved automatically

    std::cout << "Library holds " << library.size() << " videos; holiday still has "
              << holiday.frameCount() << " frames\n";
    return 0;
}
