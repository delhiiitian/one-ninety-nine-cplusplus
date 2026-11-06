# Project 2: Number Guessing Game

The computer picks a secret number and you guess it. After each guess it says
"higher" or "lower" and how close you are (cold, warm, very hot). Three
difficulty levels, a play-again loop, and a running best score.

It uses Chapter 2 ideas: `if`/`else`, `switch`, the ternary operator, `while`,
`do`-`while`, `for`, `break` and `continue`.

## Files

| File | What it is |
| --- | --- |
| `main.cpp` | The game, in four labelled sections |
| `sample_input.txt` | Two full rounds of answers: one win, one loss |
| `expected_output.txt` | What the game prints for those answers with seed 42 |
| `Makefile` | `make`, `make run`, `make test`, `make clean` |

## Run it

```sh
make run              # a new random number every time
./guessing_game 42    # fixed seed: the secrets are always 43, then 18
make test             # replays sample_input.txt with seed 42 and compares output
```

## Ideas to extend

- Keep the best score per difficulty level instead of one overall.
- Add a "reverse" mode where you pick the number and the computer guesses.
