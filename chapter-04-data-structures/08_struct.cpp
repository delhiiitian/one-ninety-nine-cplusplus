// C++ in 199 Pages - 4.8 struct: your own data type
// Build: g++ -std=c++17 08_struct.cpp -o struct && ./struct

#include <iostream>
#include <string>
#include <vector>

struct Book {
    std::string title;
    std::string author;
    int year = 0;
    double rating = 0.0;
    bool available = true;
};

void printBook(const Book& b) {
    std::cout << b.title << " by " << b.author << " (" << b.year << "), "
              << b.rating << "/5, " << (b.available ? "on shelf" : "borrowed") << "\n";
}

int main() {
    Book first{"The Guide", "R. K. Narayan", 1958, 4.3, true};
    Book second;                         // uses the default values
    second.title = "Wings of Fire";
    second.author = "A. P. J. Abdul Kalam";
    second.year = 1999;
    second.rating = 4.6;

    std::vector<Book> library = {first, second,
                                 {"Malgudi Days", "R. K. Narayan", 1943, 4.4, false}};
    for (const Book& b : library) {
        printBook(b);
    }

    library[0].available = false;        // change one field of one book
    int onShelf = 0;
    for (const Book& b : library) {
        if (b.available) ++onShelf;
    }
    std::cout << "Books on shelf: " << onShelf << " of " << library.size() << "\n";
    return 0;
}
