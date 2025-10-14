# Minesweeper (Terminal Game in C)

## Overview
This is a terminal-based implementation of the classic **Minesweeper** game in C.  
The objective is to uncover all non-mined cells. Each revealed cell displays a number (1–8) indicating how many neighboring cells contain mines. Empty cells (0) have no neighboring mines. Revealing a mine ends the game.

## Build

This project uses a `Makefile` to simplify building the game and tests.

### Building the game

To build the main Minesweeper program:

```bash
make
```
### Building and running tests
To compile and run the tests:

```bash
make test
./test
```
### Cleaning up
```bash
make clean
```
Removes all compiled files and executables.

## Usage

### Standard Mode
Run the game with:
```bash
./Minesweeper <path_to_file>
```
1. Select a difficulty level (easy, medium, hard) or create a custom board.  
2. During the game, enter commands to reveal cells or place flags.  
3. After finishing, enter your name to save your score if it qualifies for the **Top 5 players**. The program will display the leaderboard.

### File Mode
Run the game with:
```bash
./Minesweeper -f <path_to_file>
```
- The program reads a board and a sequence of commands from a file.  
- Commands are executed automatically, updating the board after each step.  
- The final outcome (win/lose) and the number of successful moves are displayed.

## Commands
- `r <x> <y>` – reveal the cell at row `x`, column `y`. Revealing a mine ends the game.  
- `f <x> <y>` – place or remove a flag at cell `x, y` to mark suspected mines.  

**File format example:**
```
1 * * 1 0 1 1 1 0
1 1 1 1 0 1 * 1 0
0 1 1 1 0 1 2 2 1
0 2 * 3 0 0 1 * 1
0 2 * * 2 1 2 2 2
1 2 3 3 * 1 1 * 1
1 * 1 1 1 1 1 1 1
1 1 1 0 0 0 0 0 0
r 1 1
f 1 2
r 1 4
r 1 5
```
- Numbers indicate the count of neighboring mines; `*` indicates a mine.  
- Commands are listed directly below the board.

## Implementation Details

### Modules

#### `main.c`
- Controls program flow and selects the mode (standard or file-based).  

#### `board.c`
- **`choose_difficulty`** – prompts user for difficulty and sets board size and number of mines.  
- **`generate_board`** – allocates memory for the board and initializes all cells.  
- **`generate_mines`** – randomly places mines and updates neighboring counts.  
- **`print_board`** – displays the board in the terminal with points, flags, and optional mine locations; uses colored numbers.  
- **`load_board`** – reads a board from a file.  
- **`free_board`** – releases allocated memory.  

#### `game.c`
- **`are_all_read`** – checks if all non-mine cells have been revealed.  
- **`read_fields`** – reveals a cell; recursively reveals neighbors if the cell is empty.  
- **`execute_commands`** – handles user input in standard mode, generating mines after the first move to avoid instant loss.  
- **`execute_commands_from_file`** – executes commands from a file, updating the board automatically.  

#### `results.c`
- **`load_result`** – loads top players from a file.  
- **`add_new_result`** – adds a new score to the top 5 list, sorting with `qsort`.  
- **`save_result`** – writes updated scores to a file.  

### Data Structures
- **`Field`** – stores cell info: number of neighboring mines, whether it is revealed, mined, or flagged.  
- **`Difficulty`** – stores board size, number of mines, and point multiplier.  
- **`Player`** – stores player name and score.  

## Testing
Basic testing is done using C and assert.h.
```c
#include <assert.h>
#include "../include/board.h"

void test_generate_mines() {
    // ... test code
    assert(mines == expected);
}
```
## Summary
The game meets all project requirements:
- Functional Minesweeper logic.  
- Two modes: interactive and file-driven.  
- Persistent Top 5 leaderboard.  
- Recursive empty cell revealing implemented as in the original game.  
  

**Author:** Daniel Kaźmierczak

