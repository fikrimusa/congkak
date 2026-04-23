#include "game.hpp"

Game::Game() : currentPlayer_(Player::P1) {}

bool Game::playMove(int hole) {
    if (currentPlayer_ == Player::P1 && (hole < 0 || hole > 6)) {
        return false;
    }
    if (currentPlayer_ == Player::P2 && (hole < 8 || hole > 14)) {
        return false;
    }
    if (board_.getKampung(hole) == 0) {
        return false;
    }

    MoveResult result = board_.makeMove(hole, currentPlayer_);

    if (!result.extraTurn) {
        flipPlayer();
    }
    while (!board_.isGameOver() && isSideEmpty(currentPlayer_)) {
        flipPlayer();
    }
    return true;
}

Player Game::currentPlayer() const {
    return currentPlayer_;
}

const Board& Game::board() const {
    return board_;
}

bool Game::isGameOver() const {
    return board_.isGameOver();
}

void Game::flipPlayer() {
    if (currentPlayer_ == Player::P1) {
        currentPlayer_ = Player::P2;
    } else {
        currentPlayer_ = Player::P1;
    }
}

bool Game::isSideEmpty(Player p) const {
    int start = (p == Player::P1) ? 0 : 8;
    int end = (p == Player::P1) ? 6 : 14;
    for (int i = start; i <= end; ++i) {
        if (board_.getKampung(i) != 0) {
            return false;
        }
    }
    return true;
}
