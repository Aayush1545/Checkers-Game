#include <iostream>
#include "CheckersGame.h"
#include "Constants.h"

int main() {
    std::string player1Name, player2Name;

    // Print welcome message
    std::cout << "\n\n\n\n\n"; // Add vertical space for centering
    std::cout << "\033[2J\033[H"; // Clear screen
    int terminalWidth = 130; // Adjust based on your terminal's width
    int rightMargin = terminalWidth - 40; // Centering the welcome message to the right
    std::cout << std::setw(rightMargin) << std::right << "        =============================" << std::endl;
    std::cout << std::setw(80) << std::right << "          Welcome to" << std::endl;
    std::cout << std::setw(80) << std::right << "           Checkers!" << std::endl;
    std::cout << std::setw(rightMargin) << std::right << "        =============================" << std::endl;

    // Get player names
    std::cout << "\n\n\n";
    std::cout << "\033[1;31mEnter name for Player 1 (Red): \033[0m";
    std::getline(std::cin, player1Name);
    std::cout << "\033[1;34mEnter name for Player 2 (Blue): \033[0m";
    std::getline(std::cin, player2Name);

    // Start the game
    CheckersGame game(player1Name, player2Name);
    game.run();

    return 0;
}
