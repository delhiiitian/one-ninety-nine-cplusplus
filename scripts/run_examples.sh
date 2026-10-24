#!/usr/bin/env bash
# Compiles and runs every chapter example. Usage: scripts/run_examples.sh [chapter-folder]
# An example that reads input gets it from a matching .input file next to it.
set -u
cd "$(dirname "$0")/.."
CXX="${CXX:-g++}"
FLAGS="-std=c++17 -Wall -Wextra -pedantic -Werror -pthread"
OUT="$(mktemp -d)"
pass=0; fail=0
dirs="${1:-chapter-*}"
for src in $dirs/*.cpp; do
  name="$(basename "$src" .cpp)"
  dir="$(dirname "$src")"
  bin="$OUT/$name"
  if ! $CXX $FLAGS "$src" -o "$bin" 2>"$OUT/err"; then
    echo "FAIL (compile) $src"; cat "$OUT/err"; fail=$((fail+1)); continue
  fi
  input="$PWD/$dir/$name.input"; [ -f "$input" ] || input=/dev/null
  if (cd "$OUT" && timeout 20 "$bin" < "$input" > "$OUT/$name.out" 2>&1); then
    pass=$((pass+1))
  else
    echo "FAIL (run) $src"; cat "$OUT/$name.out"; fail=$((fail+1))
  fi
done
# Multi-file lessons live in their own folder: compile every .cpp in it together.
for lesson in $dirs/*/; do
  [ -d "$lesson" ] || continue
  name="$(basename "$lesson")"
  bin="$OUT/$name"
  sources=$(find "$lesson" -name '*.cpp' | sort)
  if ! $CXX $FLAGS -I"$lesson" $sources -o "$bin" 2>"$OUT/err"; then
    echo "FAIL (compile) $lesson"; cat "$OUT/err"; fail=$((fail+1)); continue
  fi
  if (cd "$OUT" && timeout 20 "$bin" < /dev/null > "$OUT/$name.out" 2>&1); then
    pass=$((pass+1))
  else
    echo "FAIL (run) $lesson"; cat "$OUT/$name.out"; fail=$((fail+1))
  fi
done
echo "Examples passed: $pass, failed: $fail"
rm -rf "$OUT"
[ "$fail" -eq 0 ]
