#pragma once
#include "board.hpp"
class Game {
public:
    Game();

    bool playMove(int hole);
    Player currentPlayer() const;
    bool isGameOver() const;
    const Board& board() const;
    Board& _board();

private:
    void flipPlayer();
    bool isSideEmpty(Player p) const;

    Board board_;
    Player currentPlayer_;
};
