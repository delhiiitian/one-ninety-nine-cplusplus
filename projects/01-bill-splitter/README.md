# Project 1: Restaurant Bill Splitter

A console program that takes a restaurant bill, adds 5% service tax and a tip,
splits the total between friends, and rounds each share up to a whole amount.
It uses only Chapter 1 ideas: variables, constants, arithmetic, strings, type
conversion and `cin`/`cout`.

## Files

| File | What it is |
| --- | --- |
| `main.cpp` | The whole program, in four labelled sections |
| `sample_input.txt` | Answers to the four questions, for a repeatable run |
| `expected_output.txt` | What the program must print for the sample input |
| `Makefile` | `make`, `make run`, `make test`, `make clean` |

## Run it

```sh
make run            # answer the questions yourself
make test           # feed sample_input.txt and compare with expected_output.txt
```

Without `make`: `g++ -std=c++17 main.cpp -o bill_splitter && ./bill_splitter`

## Ideas to extend

- Ask for a discount coupon percentage and subtract it before tax.
- Print each share in a second currency using a constant exchange rate.
