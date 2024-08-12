#ifndef PIECE_H
#define PIECE_H

enum class Player { NONE, PLAYER1, PLAYER2 };

struct Piece {
    Player owner;
    bool isKing;

    Piece(Player owner = Player::NONE, bool isKing = false);
};

#endif // PIECE_H
