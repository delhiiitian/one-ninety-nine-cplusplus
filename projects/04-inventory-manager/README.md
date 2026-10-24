# Project 4: Shop Inventory Manager

A command-driven stock system for a small shop. Add products, sell, restock,
look items up, list everything, see what is running low, find the best sellers,
and get stock value per category with revenue so far.

It uses Chapter 4 ideas: `struct`, `std::vector`, `std::unordered_map`,
`std::map`, `std::set`, `std::pair` and the standard algorithms.

## Commands

| Command | Example | Does |
| --- | --- | --- |
| `ADD code name category qty price` | `ADD R100 Basmati-Rice Grocery 40 120` | Add a new product |
| `SELL code qty` | `SELL R100 15` | Sell units, if enough are in stock |
| `RESTOCK code qty` | `RESTOCK T200 15` | Add units to a product |
| `FIND code` | `FIND C400` | Show one product |
| `LIST` | | All products sorted by name, with totals |
| `LOW threshold` | `LOW 15` | Products with quantity at or below the threshold |
| `TOP n` | `TOP 3` | Best sellers by units sold |
| `REPORT` | | Stock value per category and revenue |
| `QUIT` | | Exit |

Names are single words; use hyphens instead of spaces (`Green-Tea`).

## Run it

```sh
make run      # type commands yourself
make test     # replays sample_input.txt and compares with expected_output.txt
```

## Ideas to extend

- Add a `DELETE code` command.
- Add a `DISCOUNT category percent` command that lowers every price in a category.
