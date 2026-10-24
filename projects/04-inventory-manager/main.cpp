// C++ in 199 Pages - Project 4: Shop Inventory Manager
// Uses Chapter 4 ideas: struct, vector, unordered_map, map, set, pair,
// and the standard algorithms.
//
// The program reads one command per line (see sample_input.txt):
//   ADD <code> <name> <category> <qty> <price>
//   SELL <code> <qty>          RESTOCK <code> <qty>
//   FIND <code>                LIST
//   LOW <threshold>            REPORT
//   TOP <n>                    QUIT
//
// Build: make        Run: make run        Test: make test

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>    // std::istringstream, to split a line into words (Chapter 6)
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

// ---- Data -------------------------------------------------------------------
struct Item {
    std::string code;
    std::string name;
    std::string category;
    int quantity = 0;
    double price = 0.0;
    int unitsSold = 0;
};

struct Shop {
    std::unordered_map<std::string, Item> items;   // code -> item, fast lookup
    std::set<std::string> categories;              // unique, sorted
    double revenue = 0.0;
};

// ---- Helpers ----------------------------------------------------------------
void printItem(const Item& it) {
    std::cout << "  " << std::left << std::setw(8) << it.code << std::setw(16) << it.name
              << std::setw(11) << it.category << std::right << std::setw(5) << it.quantity
              << std::setw(10) << std::fixed << std::setprecision(2) << it.price << "\n";
}

// Items sorted by name, so LIST output is stable and easy to read.
std::vector<Item> sortedByName(const Shop& shop) {
    std::vector<Item> list;
    for (const auto& [code, item] : shop.items) {
        list.push_back(item);
    }
    std::sort(list.begin(), list.end(),
              [](const Item& a, const Item& b) { return a.name < b.name; });
    return list;
}

// Returns {number of units, total value} for the whole stock.
std::pair<int, double> stockTotals(const Shop& shop) {
    int units = 0;
    double value = 0.0;
    for (const auto& [code, item] : shop.items) {
        units += item.quantity;
        value += item.quantity * item.price;
    }
    return {units, value};
}

// ---- Commands ---------------------------------------------------------------
void addItem(Shop& shop, const Item& item) {
    if (shop.items.count(item.code) > 0) {
        std::cout << "! " << item.code << " already exists, use RESTOCK\n";
        return;
    }
    shop.items[item.code] = item;
    shop.categories.insert(item.category);
    std::cout << "Added " << item.name << "\n";
}

void sell(Shop& shop, const std::string& code, int qty) {
    auto it = shop.items.find(code);
    if (it == shop.items.end()) {
        std::cout << "! No item " << code << "\n";
        return;
    }
    Item& item = it->second;                   // reference: change the real item
    if (qty > item.quantity) {
        std::cout << "! Only " << item.quantity << " " << item.name << " left\n";
        return;
    }
    item.quantity -= qty;
    item.unitsSold += qty;
    double amount = qty * item.price;
    shop.revenue += amount;
    std::cout << "Sold " << qty << " x " << item.name << " = " << std::fixed
              << std::setprecision(2) << amount << "\n";
}

void restock(Shop& shop, const std::string& code, int qty) {
    auto it = shop.items.find(code);
    if (it == shop.items.end()) {
        std::cout << "! No item " << code << "\n";
        return;
    }
    it->second.quantity += qty;
    std::cout << "Restocked " << it->second.name << " to " << it->second.quantity << "\n";
}

void find(const Shop& shop, const std::string& code) {
    auto it = shop.items.find(code);
    if (it == shop.items.end()) {
        std::cout << "! No item " << code << "\n";
    } else {
        printItem(it->second);
    }
}

void list(const Shop& shop) {
    std::cout << "  " << std::left << std::setw(8) << "CODE" << std::setw(16) << "NAME"
              << std::setw(11) << "CATEGORY" << std::right << std::setw(5) << "QTY"
              << std::setw(10) << "PRICE" << "\n";
    for (const Item& item : sortedByName(shop)) {
        printItem(item);
    }
    auto [units, value] = stockTotals(shop);
    std::cout << "  " << shop.items.size() << " products, " << units
              << " units, stock value " << std::fixed << std::setprecision(2) << value << "\n";
}

void lowStock(const Shop& shop, int threshold) {
    std::vector<Item> all = sortedByName(shop);
    std::vector<Item> low;
    std::copy_if(all.begin(), all.end(), std::back_inserter(low),
                 [threshold](const Item& it) { return it.quantity <= threshold; });
    std::cout << "Low stock (<= " << threshold << "): " << low.size() << " item(s)\n";
    for (const Item& item : low) {
        printItem(item);
    }
}

void report(const Shop& shop) {
    std::map<std::string, double> valueByCategory;   // sorted by category
    for (const auto& [code, item] : shop.items) {
        valueByCategory[item.category] += item.quantity * item.price;
    }
    std::cout << "Stock value by category:\n";
    for (const std::string& cat : shop.categories) {
        std::cout << "  " << std::left << std::setw(11) << cat << std::right
                  << std::setw(10) << std::fixed << std::setprecision(2)
                  << valueByCategory[cat] << "\n";
    }
    std::cout << "Revenue so far: " << shop.revenue << "\n";
}

void topSellers(const Shop& shop, int n) {
    std::vector<Item> all = sortedByName(shop);
    std::stable_sort(all.begin(), all.end(), [](const Item& a, const Item& b) {
        return a.unitsSold > b.unitsSold;
    });
    std::cout << "Top " << n << " sellers:\n";
    for (int i = 0; i < n && i < static_cast<int>(all.size()); ++i) {
        std::cout << "  " << i + 1 << ". " << all[i].name << " (" << all[i].unitsSold
                  << " sold)\n";
    }
}

// ---- main: read and dispatch commands ----------------------------------------
int main() {
    Shop shop;
    std::string command;
    std::cout << "Inventory ready. Type commands (QUIT to exit).\n";

    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;
        std::cout << "> " << line << "\n";            // echo, so the output reads like a log
        std::istringstream in(line);
        in >> command;
        if (command == "ADD") {
            Item item;
            in >> item.code >> item.name >> item.category >> item.quantity >> item.price;
            addItem(shop, item);
        } else if (command == "SELL" || command == "RESTOCK") {
            std::string code;
            int qty = 0;
            in >> code >> qty;
            if (command == "SELL") sell(shop, code, qty);
            else restock(shop, code, qty);
        } else if (command == "FIND") {
            std::string code;
            in >> code;
            find(shop, code);
        } else if (command == "LIST") {
            list(shop);
        } else if (command == "LOW") {
            int threshold = 0;
            in >> threshold;
            lowStock(shop, threshold);
        } else if (command == "REPORT") {
            report(shop);
        } else if (command == "TOP") {
            int n = 0;
            in >> n;
            topSellers(shop, n);
        } else if (command == "QUIT") {
            break;
        } else {
            std::cout << "! Unknown command\n";
        }
    }
    std::cout << "Goodbye.\n";
    return 0;
}
