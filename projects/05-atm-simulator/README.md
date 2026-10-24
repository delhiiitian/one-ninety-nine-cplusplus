# Project 5: ATM Simulator

A cash machine for an imaginary bank. Insert a card, enter a PIN (three
tries, then the card is blocked), and check your balance, withdraw, deposit,
transfer, or print a mini statement. Every bank rule is enforced: notes of 100
only, no overdrafts, and a daily withdrawal limit of 20,000.

It uses Chapter 5 ideas: return values, exceptions, a custom exception
hierarchy, `std::optional`, input validation, `assert` and RAII cleanup.

## Test accounts

| Card | PIN | Holder | Balance |
| --- | --- | --- | --- |
| 4001 | 1234 | Anil Kumar | 25,000 |
| 4002 | 8080 | Fatima Sheikh | 3,200 |

## Files

| File | What it is |
| --- | --- |
| `main.cpp` | Rules, error classes, operations, login, session, `main` |
| `sample_input.txt` | Two customers: every operation, every error, and a blocked card |
| `expected_output.txt` | What the ATM must print for that input |
| `Makefile` | `make`, `make run`, `make test`, `make clean` |

## Run it

```sh
make run      # use the ATM yourself; press Ctrl+D to shut it down
make test     # replays sample_input.txt and compares with expected_output.txt
```

## Ideas to extend

- Add a "change PIN" option that asks for the old PIN first.
- Add a `CardBlocked` exception and throw it from `login` instead of printing.
