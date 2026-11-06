// C++ in 199 Pages - Project 6: Personal Expense Tracker
// Uses Chapter 6 ideas: file streams, appending, reading line by line,
// stringstream parsing, CSV, iomanip formatting, std::filesystem.
//
// Expenses are saved in data/expenses.csv and budgets in data/budgets.csv,
// so they are still there the next time you run the program.
//
// Commands (one per line):
//   ADD <yyyy-mm-dd> <category> <amount> <note words...>
//   LIST [yyyy-mm]            SUMMARY <yyyy-mm>
//   BUDGET <category> <amount>
//   EXPORT <yyyy-mm>          BACKUP
//   QUIT
//
// Build: make        Run: make run        Test: make test

#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

const fs::path kDataDir = "data";
const fs::path kExpensesFile = kDataDir / "expenses.csv";
const fs::path kBudgetsFile = kDataDir / "budgets.csv";

struct Expense {
    std::string date;       // yyyy-mm-dd
    std::string category;
    long long paise = 0;    // money as whole paise, never as double
    std::string note;
};

// ---- Money helpers -------------------------------------------------------------
// "249.5" -> 24950. Returns nothing if the text is not a valid amount.
std::optional<long long> parseAmount(const std::string& text) {
    std::istringstream in(text);
    double rupees = 0.0;
    char extra = 0;
    if (!(in >> rupees) || (in >> extra) || rupees <= 0) {
        return std::nullopt;
    }
    return static_cast<long long>(rupees * 100 + 0.5);
}

std::string formatMoney(long long paise) {
    std::ostringstream out;
    out << paise / 100 << "." << std::setw(2) << std::setfill('0') << paise % 100;
    return out.str();
}

// ---- Storage: CSV files ----------------------------------------------------------
void ensureStorage() {
    fs::create_directories(kDataDir);
    if (!fs::exists(kExpensesFile)) {
        std::ofstream(kExpensesFile) << "date,category,paise,note\n";
    }
    if (!fs::exists(kBudgetsFile)) {
        std::ofstream(kBudgetsFile) << "category,paise\n";
    }
}

std::vector<Expense> loadExpenses() {
    std::vector<Expense> all;
    std::ifstream in(kExpensesFile);
    std::string line;
    std::getline(in, line);                          // header
    while (std::getline(in, line)) {
        std::istringstream fields(line);
        Expense e;
        std::string paiseText;
        std::getline(fields, e.date, ',');
        std::getline(fields, e.category, ',');
        std::getline(fields, paiseText, ',');
        std::getline(fields, e.note);                // the rest of the line
        try {
            e.paise = std::stoll(paiseText);
            all.push_back(e);
        } catch (const std::exception&) {
            std::cerr << "warning: skipped damaged line: " << line << "\n";
        }
    }
    return all;
}

void appendExpense(const Expense& e) {
    std::ofstream out(kExpensesFile, std::ios::app);
    out << e.date << ',' << e.category << ',' << e.paise << ',' << e.note << '\n';
}

std::map<std::string, long long> loadBudgets() {
    std::map<std::string, long long> budgets;
    std::ifstream in(kBudgetsFile);
    std::string line;
    std::getline(in, line);
    while (std::getline(in, line)) {
        std::istringstream fields(line);
        std::string category, paiseText;
        std::getline(fields, category, ',');
        std::getline(fields, paiseText);
        budgets[category] = std::stoll(paiseText);
    }
    return budgets;
}

void saveBudgets(const std::map<std::string, long long>& budgets) {
    std::ofstream out(kBudgetsFile);                 // rewrite the whole file
    out << "category,paise\n";
    for (const auto& [category, paise] : budgets) {
        out << category << ',' << paise << '\n';
    }
}

// ---- Reports ------------------------------------------------------------------------
bool inMonth(const Expense& e, const std::string& month) {
    return month.empty() || e.date.compare(0, month.size(), month) == 0;
}

void writeList(std::ostream& out, const std::vector<Expense>& all, const std::string& month) {
    long long total = 0;
    int count = 0;
    for (const Expense& e : all) {
        if (!inMonth(e, month)) continue;
        out << "  " << e.date << "  " << std::left << std::setw(10) << e.category
            << std::right << std::setw(10) << formatMoney(e.paise) << "  " << e.note << "\n";
        total += e.paise;
        ++count;
    }
    out << "  " << count << " expense(s), total " << formatMoney(total) << "\n";
}

void writeSummary(std::ostream& out, const std::vector<Expense>& all, const std::string& month,
                  const std::map<std::string, long long>& budgets) {
    std::map<std::string, long long> byCategory;
    long long total = 0;
    for (const Expense& e : all) {
        if (inMonth(e, month)) {
            byCategory[e.category] += e.paise;
            total += e.paise;
        }
    }
    out << "Summary for " << month << " (total " << formatMoney(total) << ")\n";
    out << "  " << std::left << std::setw(10) << "Category" << std::right << std::setw(10)
        << "Spent" << std::setw(7) << "Share" << std::setw(10) << "Budget" << "  Chart\n";
    for (const auto& [category, paise] : byCategory) {
        double share = total > 0 ? 100.0 * paise / total : 0.0;
        auto budget = budgets.find(category);
        std::string budgetText = budget == budgets.end() ? "-" : formatMoney(budget->second);
        out << "  " << std::left << std::setw(10) << category << std::right << std::setw(10)
            << formatMoney(paise) << std::setw(6) << std::fixed << std::setprecision(1) << share
            << "%" << std::setw(10) << budgetText << "  "
            << std::string(static_cast<std::size_t>(share / 5), '#');
        if (budget != budgets.end() && paise > budget->second) {
            out << "  OVER by " << formatMoney(paise - budget->second);
        }
        out << "\n";
    }
}

// ---- Commands --------------------------------------------------------------------------
void addCommand(std::istringstream& args) {
    Expense e;
    std::string amountText;
    args >> e.date >> e.category >> amountText;
    std::getline(args >> std::ws, e.note);
    for (char& c : e.note) {
        if (c == ',') c = ';';                       // keep the CSV columns intact
    }
    auto paise = parseAmount(amountText);
    if (e.date.size() != 10 || e.category.empty() || !paise) {
        std::cout << "! Usage: ADD yyyy-mm-dd category amount note\n";
        return;
    }
    e.paise = *paise;
    appendExpense(e);
    std::cout << "Saved " << formatMoney(e.paise) << " for " << e.category << "\n";
}

void exportCommand(const std::string& month) {
    fs::path reportPath = kDataDir / ("report-" + month + ".txt");
    std::ofstream out(reportPath);
    std::vector<Expense> all = loadExpenses();
    out << "EXPENSE REPORT " << month << "\n\n";
    writeList(out, all, month);
    out << "\n";
    writeSummary(out, all, month, loadBudgets());
    out.close();
    std::cout << "Report written to " << reportPath.generic_string() << " ("
              << fs::file_size(reportPath) << " bytes)\n";
}

void backupCommand() {
    fs::path backupDir = kDataDir / "backup";
    fs::create_directories(backupDir);
    for (const fs::path& file : {kExpensesFile, kBudgetsFile}) {
        fs::copy_file(file, backupDir / file.filename(), fs::copy_options::overwrite_existing);
    }
    std::cout << "Backed up 2 files to " << backupDir.generic_string() << "\n";
}

int main() {
    ensureStorage();
    std::cout << "Expense tracker: " << loadExpenses().size() << " saved expense(s) loaded.\n";

    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;
        std::cout << "> " << line << "\n";
        std::istringstream args(line);
        std::string command;
        args >> command;

        if (command == "ADD") {
            addCommand(args);
        } else if (command == "LIST") {
            std::string month;
            args >> month;
            writeList(std::cout, loadExpenses(), month);
        } else if (command == "SUMMARY") {
            std::string month;
            args >> month;
            writeSummary(std::cout, loadExpenses(), month, loadBudgets());
        } else if (command == "BUDGET") {
            std::string category, amountText;
            args >> category >> amountText;
            auto paise = parseAmount(amountText);
            if (category.empty() || !paise) {
                std::cout << "! Usage: BUDGET category amount\n";
                continue;
            }
            auto budgets = loadBudgets();
            budgets[category] = *paise;
            saveBudgets(budgets);
            std::cout << "Budget for " << category << " set to " << formatMoney(*paise) << "\n";
        } else if (command == "EXPORT") {
            std::string month;
            args >> month;
            exportCommand(month);
        } else if (command == "BACKUP") {
            backupCommand();
        } else if (command == "QUIT") {
            break;
        } else {
            std::cout << "! Unknown command\n";
        }
    }
    return 0;
}
