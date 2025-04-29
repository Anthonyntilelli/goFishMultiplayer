#!/bin/bash

EXCLUDE_DIRS=("third_party" "_dep" "external")   # Add or remove dirs here
ORIGINAL_DB="./build/compile_commands.json"
FILTERED_DIR="./build/filtered_db"
FILTERED_DB="$FILTERED_DIR/compile_commands.json"
THREADS=2


PATTERN=$(printf "|%s" "${EXCLUDE_DIRS[@]}")
PATTERN="${PATTERN:1}"  # Remove leading '|'
echo "[*] Excluding directories: ${EXCLUDE_DIRS[*]}"
echo "[*] Filtering $ORIGINAL_DB -> $FILTERED_DB"

mkdir -p "$FILTERED_DIR"
jq "[.[] | select(.file | test(\"^(?!.*($PATTERN)).*\"))]" "$ORIGINAL_DB" > "$FILTERED_DB"
if [ $? -ne 0 ]; then
    echo "[!] Failed to filter compile_commands.json"
    exit 1
fi

echo "[*] Running run-clang-tidy-19 with $FILTERED_DB"
run-clang-tidy-19 -p="$FILTERED_DIR" -j "$THREADS" | tee clang-tidy.log
rm -r "$FILTERED_DIR"