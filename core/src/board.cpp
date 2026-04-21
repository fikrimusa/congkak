#include "board.hpp"

#include <numeric>

int Board::getKampung(int i) const {
    return slots_[i];
}

int Board::getRumah(Player p) const {
    if (p == Player::P1) {
        return slots_[P1_RUMAH_INDEX];
    }
    return slots_[P2_RUMAH_INDEX];
}

int Board::getTotalSeeds() const {
    return std::accumulate(slots_.begin(), slots_.end(), 0);
}

bool Board::isGameOver() const {
    for (int i = 0; i < 16; ++i) {
        if (i == P1_RUMAH_INDEX || i == P2_RUMAH_INDEX)
            continue;
        if (slots_[i] != 0)
            return false;
    }
    return true;
}
