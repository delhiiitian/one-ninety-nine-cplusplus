# Project 8: Parking Garage Manager

Runs a small car park: vehicles enter and get the smallest free
spot that fits them, leave and get a fee, and the attendant can see live
status and a revenue report. Motorbikes, cars, electric cars and trucks each
have their own size and pricing rules.

It uses Chapter 8 ideas: classes, constructors, encapsulation, inheritance,
virtual functions, operator overloading, a class template, `std::unique_ptr`
and move semantics.

## Pricing rules

| Vehicle | Spot | Per started hour | Extra |
| --- | --- | --- | --- |
| Motorbike | small (or bigger if full) | Rs 20 | |
| Car | regular (or large) | Rs 40 | |
| Electric car | regular (or large) | Rs 40 | Rs 150 charging |
| Truck | large only | Rs 100 | |

The first 15 minutes are free, and no stay is charged for more than 8 hours.

## Commands

```
ENTER <BIKE|CAR|EV|TRUCK> <plate> <hh:mm>
EXIT <plate> <hh:mm>
STATUS
REPORT
QUIT
```

## Files

| File | What it is |
| --- | --- |
| `src/money.h` | `Money` class with `+`, `*`, `+=`, `<` and `<<` |
| `src/vehicle.h`, `src/vehicle.cpp` | abstract `Vehicle` and four vehicle classes, plus the `makeVehicle` factory |
| `src/garage.h`, `src/garage.cpp` | `Spot`, `Receipt`, the `Tally<Key>` template and the `Garage` class |
| `src/main.cpp` | command loop |
| `sample_input.txt`, `expected_output.txt` | a full day, including every error message |
| `Makefile`, `CMakeLists.txt` | build with Make or CMake |

## Run it

```sh
make run
make test     # replays a day at the garage and compares the output
```
