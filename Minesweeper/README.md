# C++ Minesweeper Project with SFML

This project is an implementation of the Minesweeper game, built using C++ and the SFML (Simple and Fast Multimedia Library) library for graphics and user input handling.

## Features

- Graphical user interface with a game board and controls
- Left-click to reveal a cell, right-click to mark/unmark a cell as a potential mine
- Automatic mine detection and game over/win conditions
- Ability to restart the game at any time
- Test Cases & Mine Visibility Mode

## Requirements

- C++ compiler (e.g., GCC, Clang, MSVC)
- SFML library (version 2.5 or later)

## Building the Project

1. Clone the repository or download the source code.
2. Install the SFML library on your system if not already installed.
3. Open a terminal or command prompt and navigate to the project directory.
4. Compile the source code using your preferred C++ compiler and linker, including the SFML libraries.

For example, on Linux/macOS with GCC:

```
g++ -c *.cpp
g++ *.o -o minesweeper -lsfml-graphics -lsfml-window -lsfml-system
```

On Windows with MinGW:

```
g++ -c *.cpp
g++ *.o -o minesweeper.exe -lsfml-graphics -lsfml-window -lsfml-system
```
