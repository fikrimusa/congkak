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
