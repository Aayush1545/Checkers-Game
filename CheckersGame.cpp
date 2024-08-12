#include "CheckersGame.h"
#include "Constants.h"

CheckersGame::CheckersGame(const std::string& player1Name, const std::string& player2Name)
    : board(BOARD_SIZE, std::vector<Piece>(BOARD_SIZE)), currentPlayer(Player::PLAYER1),
      player1Name(player1Name), player2Name(player2Name), quitRequested(false) {
    setupBoard();
}

void CheckersGame::run() {
    while (!quitRequested) {
        printBoard();
        std::cout << "\n" << getCurrentPlayerName() << "'s turn." << std::endl;

        std::string input;

        // Change prompt color based on the current player
        if (currentPlayer == Player::PLAYER1) {
            std::cout << "\033[1;31mEnter move (e.g., a3 b4) or command (save, load, exit): \033[0m";
        } else {
            std::cout << "\033[1;34mEnter move (e.g., a3 b4) or command (save, load, exit): \033[0m";
        }

        std::getline(std::cin, input);

        if (input == "save" || input == "load" || input == "exit") {
            handleCommand(input);
        } else {
            std::stringstream ss(input);
            std::string startPos, endPos;
            ss >> startPos >> endPos;

            // Parse positions
            int startRow, startCol, endRow, endCol;
            if (parsePosition(startPos, startRow, startCol) && parsePosition(endPos, endRow, endCol)) {
                if (!makeMove(startRow, startCol, endRow, endCol)) {
                    std::cout << "Invalid move. Try again." << std::endl;
                } else {
                    // Switch player
                    currentPlayer = (currentPlayer == Player::PLAYER1 ? Player::PLAYER2 : Player::PLAYER1);
                }
            } else {
                std::cout << "Invalid move format. Please try again." << std::endl;
            }
        }

        if (checkVictory()) {
            std::cout << getCurrentPlayerName() << " wins!" << std::endl;
            break;
        }
    }

    // Display thank you message
    displayThankYouMessage();
}

void CheckersGame::setupBoard() {
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            if ((row + col) % 2 == 1) {
                if (row < 3) board[row][col] = Piece(Player::PLAYER1);
                else if (row > 4) board[row][col] = Piece(Player::PLAYER2);
            }
        }
    }
}

void CheckersGame::printBoard() const {
    // Clear screen
    std::cout << "\033[2J\033[H";

    // Calculate terminal width
    int terminalWidth = 130; // Adjust based on your terminal's width
    int boardWidth = 37; // Width of the board without borders

    // Calculate left margin for centering the board
    int leftMargin = (terminalWidth - boardWidth) / 2;

    // Print the centered board
    std::cout << std::setw(leftMargin) << "" << "    a   b   c   d   e   f   g   h" << std::endl; // Column headers
    std::cout << std::setw(leftMargin) << "" << "  +---+---+---+---+---+---+---+---+" << std::endl;
    for (int row = BOARD_SIZE - 1; row >= 0; --row) {
        std::cout << std::setw(leftMargin) << "" << row + 1 << " |"; // Row header
        for (int col = 0; col < BOARD_SIZE; ++col) {
            char cellChar = ' ';
            if (board[row][col].owner != Player::NONE) {
                if (board[row][col].isKing) {
                    cellChar = (board[row][col].owner == Player::PLAYER1 ? 'K' : 'Q'); // King symbols
                } else {
                    cellChar = (board[row][col].owner == Player::PLAYER1 ? 'O' : 'X'); // Regular symbols
                }
            }
            // Add color codes for better visibility
            if (board[row][col].owner == Player::PLAYER1) {
                std::cout << " \033[1;31m" << cellChar << "\033[0m |"; // Red color for PLAYER1
            } else if (board[row][col].owner == Player::PLAYER2) {
                std::cout << " \033[1;34m" << cellChar << "\033[0m |"; // Blue color for PLAYER2
            } else {
                std::cout << " " << cellChar << " |";
            }
        }
        std::cout << " " << row + 1 << std::endl;
        std::cout << std::setw(leftMargin) << "" << "  +---+---+---+---+---+---+---+---+" << std::endl;
    }
    std::cout << std::setw(leftMargin) << "" << "    a   b   c   d   e   f   g   h" << std::endl; // Column headers

    // Print current player's turn indication
    std::cout << std::endl;
    std::cout << std::setw(leftMargin) << "" << (currentPlayer == Player::PLAYER1 ? "\033[1;31mRed's turn (Player 1)\033[0m" : "\033[1;34mBlue's turn (Player 2)\033[0m") << std::endl;
}

bool CheckersGame::isValidMove(int startRow, int startCol, int endRow, int endCol) const {
    if (!isValidPosition(startRow, startCol) || !isValidPosition(endRow, endCol)) return false;
    if (board[startRow][startCol].owner != currentPlayer) return false;
    if (board[endRow][endCol].owner != Player::NONE) return false;

    int rowDiff = endRow - startRow;
    int colDiff = std::abs(endCol - startCol);

    if (std::abs(rowDiff) == 1 && colDiff == 1) {
        // Regular move
        return (currentPlayer == Player::PLAYER1 && rowDiff == 1) ||
               (currentPlayer == Player::PLAYER2 && rowDiff == -1) ||
               board[startRow][startCol].isKing;
    } else if (std::abs(rowDiff) == 2 && colDiff == 2) {
        // Capture move
        int midRow = (startRow + endRow) / 2;
        int midCol = (startCol + endCol) / 2;
        return board[midRow][midCol].owner != Player::NONE && board[midRow][midCol].owner != currentPlayer;
    }

    return false;
}

bool CheckersGame::makeMove(int startRow, int startCol, int endRow, int endCol) {
    if (!isValidMove(startRow, startCol, endRow, endCol)) return false;

    int rowDiff = endRow - startRow;
    if (std::abs(rowDiff) == 2) {
        int midRow = (startRow + endRow) / 2;
        int midCol = (startCol + endCol) / 2;
        board[midRow][midCol] = Piece(Player::NONE);
    }

    board[endRow][endCol] = board[startRow][startCol];
    board[startRow][startCol] = Piece(Player::NONE);

    if ((currentPlayer == Player::PLAYER1 && endRow == BOARD_SIZE - 1) ||
        (currentPlayer == Player::PLAYER2 && endRow == 0)) {
        board[endRow][endCol].isKing = true;
    }

    return true;
}

bool CheckersGame::isValidPosition(int row, int col) const {
    return row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE;
}

bool CheckersGame::parsePosition(const std::string& pos, int& row, int& col) const {
    if (pos.size() != 2) return false;

    col = pos[0] - 'a';
    row = pos[1] - '1';

    return isValidPosition(row, col);
}

std::string CheckersGame::getCurrentPlayerName() const {
    return currentPlayer == Player::PLAYER1 ? player1Name : player2Name;
}

bool CheckersGame::checkVictory() const {
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            if (board[row][col].owner != currentPlayer && board[row][col].owner != Player::NONE) {
                return false;
            }
        }
    }
    return true;
}

void CheckersGame::saveGame() const {
    std::ofstream outFile("checkers_save.txt");
    if (outFile) {
        outFile << static_cast<int>(currentPlayer) << '\n';
        for (const auto& row : board) {
            for (const auto& piece : row) {
                outFile << static_cast<int>(piece.owner) << ' ' << piece.isKing << ' ';
            }
            outFile << '\n';
        }
        outFile << player1Name << '\n' << player2Name << '\n';
        outFile.close();
        std::cout << "Game saved successfully." << std::endl;
    } else {
        std::cout << "Failed to save game." << std::endl;
    }
}

void CheckersGame::loadGame() {
    std::ifstream inFile("checkers_save.txt");
    if (inFile) {
        int player;
        inFile >> player;
        currentPlayer = static_cast<Player>(player);

        for (auto& row : board) {
            for (auto& piece : row) {
                int owner;
                bool isKing;
                inFile >> owner >> isKing;
                piece = Piece(static_cast<Player>(owner), isKing);
            }
        }

        inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Skip to the next line
        std::getline(inFile, player1Name);
        std::getline(inFile, player2Name);

        inFile.close();
        std::cout << "Game loaded successfully." << std::endl;
    } else {
        std::cout << "Failed to load game." << std::endl;
    }
}

void CheckersGame::displayThankYouMessage() const {
    std::cout << "\033[2J\033[H"; // Clear screen

    // Adjust these values based on your terminal's width
    const int terminalWidth = 130;

    // Calculate left padding for each line
    const int line1Padding = (terminalWidth - 29) / 2;
    const int line2Padding = (terminalWidth - 35) / 2;
    const int line3Padding = (terminalWidth - 29) / 2;
    const int line4Padding = (terminalWidth - 18) / 2;
    const int line5Padding = (terminalWidth - 14) / 2;
    const int line6Padding = (terminalWidth - 18) / 2;
    const int line7Padding = (terminalWidth - 15) / 2;
    const int line8Padding = (terminalWidth - 14) / 2;
    const int line9Padding = (terminalWidth - 12) / 2;

    std::cout << std::setw(line1Padding) << "" << "=============================" << std::endl;
    std::cout << std::setw(line2Padding) << "" << "Thank you for playing Checkers!" << std::endl;
    std::cout << std::setw(line3Padding) << "" << "=============================" << std::endl;
    std::cout << std::setw(line4Padding) << "" << "Created by\n\n" << std::endl;
    std::cout << std::setw(line5Padding) << "" << "TEAM CHECKERS\n\n" << std::endl;
    std::cout << std::setw(line6Padding) << "" << "Aayush Rauniyar\n\n" << std::endl;
    std::cout << std::setw(line7Padding) << "" << "Bipin Khatiwada\n\n" << std::endl;
    std::cout << std::setw(line8Padding) << "" << "Abal Adhikari\n\n" << std::endl;
    std::cout << std::setw(line9Padding) << "" << "Dhiraj Shah\n\n" << std::endl;
}

void CheckersGame::handleCommand(const std::string& command) {
    if (command == "save") {
        saveGame();
    } else if (command == "load") {
        loadGame();
    } else if (command == "exit") {
        quitRequested = true;
    }
}
