# Checkers game
# Team Members:
# Aayush Rauniyar(@Aayush1545)
# Bipin Khatiwada(@BipinKhatiwada)
# Abbal Adhikari(@AbbalAdhikari)
# Dhiraj Shah(@dhiraj-7x7x)

This project is a console-based implementation of the classic Checkers game written in C++. The game features a fully interactive board, supports two-player gameplay, and allows for saving and loading game states. It's designed with a focus on clean, modular code and uses several C++ Standard Library features, including std::vector, std::string, and file I/O operations.

# Features
Two-Player Mode: Play the game with a friend on the same computer.
Board Representation: The game board is represented using a 2D vector of custom Piece objects.
Move Validation: Ensures that only valid moves are allowed, including support for regular and capture moves.
King Pieces: Pieces are promoted to kings when they reach the opposite side of the board, gaining additional movement capabilities.
Saving and Loading: Save your game to a file and load it later to continue playing.
Formatted Board Output: The board is displayed with column and row labels, using colored pieces to distinguish between players.

# Getting Started
To compile and run the project, ensure you have a C++ compiler installed (e.g., g++, clang). Clone the repository and build the project using the provided Makefile or compile manually.

```
git clone https://github.com/yourusername/checkers-game.git
cd checkers-game
g++ -o checkers main.cpp CheckersGame.cpp Piece.cpp -std=c++11
./checkers ```
 
