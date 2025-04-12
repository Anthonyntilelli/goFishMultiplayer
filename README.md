# GoFishMultiplayer - Multiplayer Go Fish server and clients written in C++

## Table of Contents

1. [Description](#Description)
2. [Parameters](#Parameters)
3. [Examples](#Examples)
4. [Build](#Build)
5. [Mic](#Mic)
6. [Authors](#Authors)

## Description

## Parameters

## Examples

## Build


### Dependencies

### Compile

### Testing build

## Mic

### Generating Documentation

Doxygen is used to automatically generate the documentation. Rum the command from the project root directory.

`doxygen`

### Static Analysis

`cppcheck --enable=all --check-config --inconclusive --suppress=missingIncludeSystem src/`

### Formatting

`find src -type f \( -name "*.cpp" -o -name "*.hpp" -o -name "*.c" -o -name "*.h" \) -exec clang-format -i {} \;`

## Authors

- Anthony Tilelli
