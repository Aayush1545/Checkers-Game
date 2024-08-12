#ifndef CHECKERSGAME_H
#define CHECKERSGAME_H

#include <iostream>
#include <vector>
#include <cstdlib> // For std::abs
#include <string>
#include <iomanip>
#include <limits>
#include <fstream> // For file handling
#include <sstream> // For std::stringstream
#include "Piece.h"
#include "Constants.h"

class CheckersGame {
public:
    CheckersGame(const std::string& player1Name, const std::string& player2Name);
    void run();

private:
    std::vector<std::vector<Piece>> board;
    Player currentPlayer;
    std::string player1Name;
    std::string player2Name;
    bool quitRequested;

    void setupBoard();
    void printBoard() const;
    bool isValidMove(int startRow, int startCol, int endRow, int endCol) const;
    bool makeMove(int startRow, int startCol, int endRow, int endCol);
    bool isValidPosition(int row, int col) const;
    bool parsePosition(const std::string& pos, int& row, int& col) const;
    std::string getCurrentPlayerName() const;
    bool checkVictory() const;
    void saveGame() const;
    void loadGame();
    void displayThankYouMessage() const;
    void handleCommand(const std::string& command);
};

#endif // CHECKERSGAME_H
