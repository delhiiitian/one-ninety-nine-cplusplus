# Project 3: Student Report Card

Reads a class's marks in five subjects and prints a formatted report card:
total, average, grade, pass or fail and a remark for every student, then the
class topper and a star chart of subject averages.

It is built entirely from small functions (Chapter 3): parameters and return
values, references, const references, default arguments, overloading,
recursion, lambdas, and declarations at the top of the file.

## Files

| File | What it is |
| --- | --- |
| `main.cpp` | Declarations, then `main`, then the function definitions |
| `sample_input.txt` | Five students with five marks each |
| `expected_output.txt` | The report card the program must print |
| `Makefile` | `make`, `make run`, `make test`, `make clean` |

## Input format

```
5                         <- number of students
Asha  92 88 79 85 95      <- name, then Maths Science English History Computer
...
```

## Run it

```sh
make run      # prints the report for sample_input.txt
make test     # compares with expected_output.txt
./report_card < my_class.txt
```

## Ideas to extend

- Add a rank column (sort students by average with a lambda).
- Make the pass mark a command-line option and pass it to `passedAll`.
