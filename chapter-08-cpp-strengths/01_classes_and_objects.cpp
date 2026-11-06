// C++ in 199 Pages - 8.1 Classes and objects
// Build: g++ -std=c++17 01_classes_and_objects.cpp -o classes && ./classes

#include <iostream>
#include <string>

// A class bundles data (members) AND the actions on that data (member functions).
class Smartphone {
public:
    std::string model;
    int batteryPercent = 100;

    void useApp(const std::string& app, int drain) {
        batteryPercent -= drain;
        if (batteryPercent < 0) batteryPercent = 0;
        std::cout << model << ": used " << app << ", battery " << batteryPercent << "%\n";
    }

    void charge() {
        batteryPercent = 100;
        std::cout << model << ": fully charged\n";
    }

    bool needsCharging() const {          // const: promises not to change the object
        return batteryPercent < 20;
    }
};

int main() {
    Smartphone mine;                       // an object: one actual phone
    mine.model = "Pixel";
    Smartphone yours;                      // a second, independent object
    yours.model = "Galaxy";

    mine.useApp("Maps", 45);
    mine.useApp("Camera", 40);
    yours.useApp("Music", 10);

    std::cout << mine.model << " needs charging? " << std::boolalpha << mine.needsCharging() << "\n";
    std::cout << yours.model << " needs charging? " << yours.needsCharging() << "\n";
    mine.charge();
    return 0;
}
