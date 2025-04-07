# GoFishMultiplayer - Multiplayer game of GOfish built in C++

## Table of Contents

1. [Description](#Description)
2. [Parameters](#Parameters)
3. [Examples](#Examples)
4. [Build](#Build)
5. [Mic](#Mic)
6. [Authors](#Authors)

## Description <a name= "Description"></a>

## Parameters: <a name="Parameters"></a>

## Examples: <a name="Examples"></a>

## Build <a name="Build"></a>


### Dependencies

### Compile

### Testing build

## Mic <a name="Mic"></a>

### Manual Build (No ASan)

### Leak testing

### Static Analysis

`cppcheck --enable=all --check-config --inconclusive --suppress=missingIncludeSystem src/`

### Formatting
`find src -type f \( -name "*.cpp" -o -name "*.hpp" -o -name "*.c" -o -name "*.h" \) -exec clang-format -i {} \;`

## Authors: <a name="Authors"></a>

- Anthony Tilelli
