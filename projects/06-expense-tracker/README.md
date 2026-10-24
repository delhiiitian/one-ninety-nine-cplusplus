# Project 6: Personal Expense Tracker

Record your spending, set monthly budgets per category, and get a summary with
percentages, a text bar chart and "over budget" warnings. Everything is saved
in CSV files under `data/`, so it is still there next time you run it. Reports
can be exported to a text file, and the data can be backed up.

It uses Chapter 6 ideas: `std::ifstream`/`std::ofstream`, appending, reading
line by line, `std::stringstream`, CSV parsing, `<iomanip>` formatting and
`std::filesystem`.

## Commands

| Command | Example |
| --- | --- |
| `ADD date category amount note` | `ADD 2026-10-02 Food 420.50 Groceries` |
| `LIST [yyyy-mm]` | `LIST 2026-10` (no month = everything) |
| `SUMMARY yyyy-mm` | `SUMMARY 2026-10` |
| `BUDGET category amount` | `BUDGET Food 3000` |
| `EXPORT yyyy-mm` | writes `data/report-2026-10.txt` |
| `BACKUP` | copies the CSV files to `data/backup/` |
| `QUIT` | exit |

## Files

| File | What it is |
| --- | --- |
| `main.cpp` | Money helpers, CSV storage, reports, commands, `main` |
| `session1.txt` | First run: adds expenses (one with a typo) and sets two budgets |
| `session2.txt` | Second run: adds one more, then lists, summarises, exports, backs up |
| `expected_output.txt` | Both runs' output followed by the exported report |
| `Makefile` | `make`, `make run`, `make test`, `make clean` |

## Run it

```sh
make run      # your data goes to data/expenses.csv and data/budgets.csv
make test     # runs two sessions from a clean data folder and compares output
```
