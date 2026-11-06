// C++ in 199 Pages - Project 3: Student Report Card
// Uses Chapter 3 ideas: functions, parameters and return values, references,
// const references, default arguments, overloading, recursion, lambdas and
// declarations.
//
// Input format (see sample_input.txt):
//   first line : number of students
//   each line  : name followed by 5 marks out of 100
//                (Maths, Science, English, History, Computer)
//
// Build: make        Run: make run        Test: make test

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

// ---- Declarations: the table of contents for this file ----------------------
constexpr int kSubjects = 5;
const std::vector<std::string> kSubjectNames = {"Maths", "Science", "English",
                                                "History", "Computer"};

std::vector<int> readMarks();
int total(const std::vector<int>& marks);
double average(const std::vector<int>& marks);
char grade(double avg);
std::string remark(char g);
bool passedAll(const std::vector<int>& marks, int passMark = 35);
void printLine(char symbol = '-', int width = 76);
void printLine(const std::string& title);
void printStudentRow(const std::string& name, const std::vector<int>& marks);
std::string stars(int count);

// ---- main: reads like a summary of the whole program -------------------------
int main() {
    int studentCount = 0;
    std::cin >> studentCount;

    std::vector<std::string> names;
    std::vector<double> averages;
    std::vector<int> subjectTotals(kSubjects, 0);

    printLine("CLASS 8-B REPORT CARD");
    std::cout << std::left << std::setw(10) << "Name";
    for (const std::string& subject : kSubjectNames) {
        std::cout << std::right << std::setw(5) << subject.substr(0, 4);
    }
    std::cout << std::setw(7) << "Total" << std::setw(7) << "Avg"
              << std::setw(7) << "Grade" << "  Result\n";
    printLine();

    for (int i = 0; i < studentCount; ++i) {
        std::string name;
        std::cin >> name;
        std::vector<int> marks = readMarks();

        printStudentRow(name, marks);
        names.push_back(name);
        averages.push_back(average(marks));
        for (int s = 0; s < kSubjects; ++s) {
            subjectTotals[s] += marks[s];
        }
    }
    printLine();

    // Class topper: the lambda tells max_element how to compare two averages.
    auto best = std::max_element(averages.begin(), averages.end(),
                                 [](double a, double b) { return a < b; });
    std::size_t topIndex = static_cast<std::size_t>(best - averages.begin());
    std::cout << "Class topper: " << names[topIndex] << " with "
              << std::fixed << std::setprecision(1) << *best << "%\n\n";

    std::cout << "Subject averages (one star = 5 marks):\n";
    for (int s = 0; s < kSubjects; ++s) {
        double subjectAvg = static_cast<double>(subjectTotals[s]) / studentCount;
        std::cout << "  " << std::left << std::setw(9) << kSubjectNames[s]
                  << std::right << std::setw(6) << subjectAvg << "  "
                  << stars(static_cast<int>(subjectAvg / 5)) << "\n";
    }
    printLine('=');
    return 0;
}

// ---- Definitions -------------------------------------------------------------
std::vector<int> readMarks() {
    std::vector<int> marks(kSubjects);
    for (int& m : marks) {          // reference: fill the real elements
        std::cin >> m;
    }
    return marks;
}

int total(const std::vector<int>& marks) {
    int sum = 0;
    for (int m : marks) {
        sum += m;
    }
    return sum;
}

double average(const std::vector<int>& marks) {
    return static_cast<double>(total(marks)) / marks.size();
}

char grade(double avg) {
    if (avg >= 90) return 'A';
    if (avg >= 75) return 'B';
    if (avg >= 60) return 'C';
    if (avg >= 45) return 'D';
    return 'E';
}

std::string remark(char g) {
    switch (g) {
        case 'A': return "Outstanding";
        case 'B': return "Very good";
        case 'C': return "Good";
        case 'D': return "Needs work";
        default:  return "See teacher";
    }
}

bool passedAll(const std::vector<int>& marks, int passMark) {
    return std::all_of(marks.begin(), marks.end(),
                       [passMark](int m) { return m >= passMark; });
}

void printLine(char symbol, int width) {
    std::cout << std::string(static_cast<std::size_t>(width), symbol) << "\n";
}

void printLine(const std::string& title) {
    printLine('=');
    int padding = (76 - static_cast<int>(title.size())) / 2;
    std::cout << std::string(static_cast<std::size_t>(padding), ' ') << title << "\n";
    printLine('=');
}

void printStudentRow(const std::string& name, const std::vector<int>& marks) {
    double avg = average(marks);
    char g = grade(avg);
    std::cout << std::left << std::setw(10) << name << std::right;
    for (int m : marks) {
        std::cout << std::setw(5) << m;
    }
    std::cout << std::setw(7) << total(marks)
              << std::setw(7) << std::fixed << std::setprecision(1) << avg
              << std::setw(7) << g << "  "
              << (passedAll(marks) ? "PASS" : "FAIL") << " (" << remark(g) << ")\n";
}

// Recursion: a row of n stars is one star followed by a row of n - 1 stars.
std::string stars(int count) {
    if (count <= 0) {
        return "";
    }
    return "*" + stars(count - 1);
}
