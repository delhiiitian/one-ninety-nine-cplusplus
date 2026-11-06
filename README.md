# C++ in 199 Pages

Code for the book *C++ in 199 Pages*, part of the 199 series of beginner
programming books. Every lesson in the book has a runnable file here, and
every chapter ends with a larger project.

## What is inside

| Chapter | Folder | Project |
| --- | --- | --- |
| 1. Basics | [chapter-01-basics](chapter-01-basics) | [Bill Splitter](projects/01-bill-splitter) |
| 2. Control flow | [chapter-02-control-flow](chapter-02-control-flow) | [Number Guessing Game](projects/02-guessing-game) |
| 3. Functions | [chapter-03-functions](chapter-03-functions) | [Report Card Generator](projects/03-report-card) |
| 4. Data structures | [chapter-04-data-structures](chapter-04-data-structures) | [Inventory Manager](projects/04-inventory-manager) |
| 5. Error handling | [chapter-05-error-handling](chapter-05-error-handling) | [ATM Simulator](projects/05-atm-simulator) |
| 6. Files and I/O | [chapter-06-files-io](chapter-06-files-io) | [Expense Tracker](projects/06-expense-tracker) |
| 7. Modules and tooling | [chapter-07-modules-tooling](chapter-07-modules-tooling) | [Geometry Library with Tests](projects/07-geometry-library) |
| 8. C++ strengths | [chapter-08-cpp-strengths](chapter-08-cpp-strengths) | [Parking Garage Manager](projects/08-parking-garage) |
| 9. Real-world C++ | [chapter-09-real-world](chapter-09-real-world) | [Parallel Log Analyzer](projects/09-log-analyzer) |

Each chapter folder has nine lessons named `NN_topic.cpp`. A few Chapter 7
and 9 lessons use several files, so they have their own folder.

## What you need

A C++17 compiler (g++ 9 or newer, clang 10 or newer, or Visual Studio 2019 or
newer), plus `make`. CMake 3.16 or newer is optional, for projects 7 to 9.

## Run a lesson

```sh
cd chapter-01-basics
g++ -std=c++17 -Wall 01_hello_world.cpp -o hello
./hello
```

The build line for every lesson is in the comment at the top of its file.

## Run a project

```sh
cd projects/04-inventory-manager
make run      # build and start the program
make test     # run it on sample input and compare with the expected output
```

## Check everything

```sh
bash scripts/run_examples.sh                      # compiles and runs all 81 lessons
for p in projects/*/; do make -C "$p" test; done  # tests all 9 projects
```

The same checks run on every push in GitHub Actions
(`.github/workflows/ci.yml`).
