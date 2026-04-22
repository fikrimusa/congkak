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

MoveResult Board::makeMove(int hole, Player p) {

    MoveResult result;

    int seeds = slots_[hole];
    slots_[hole] = 0;

    const auto& sowTable = (p == Player::P1) ? SOW_P1 : SOW_P2;

    int pos = 0;
    for (int i = 0; i < 15; ++i) {
        if (sowTable[i] == hole) {
            pos = i;
            break;
        }
    }

    int lastSlot = -1;

    while (seeds > 0) {
        pos = (pos + 1) % 15;
        int slot = sowTable[pos];
        slots_[slot] += 1;
        lastSlot = slot;
        seeds -= 1;
    }

    if ((p == Player::P1 && lastSlot == P1_RUMAH_INDEX) ||
        (p == Player::P2 && lastSlot == P2_RUMAH_INDEX)) {
        result.extraTurn = true;
    }

    bool onOwnSide = (p == Player::P1 && lastSlot >= 0 && lastSlot <= 6) ||
                     (p == Player::P2 && lastSlot >= 8 && lastSlot <= 14);

    bool wasEmpty = slots_[lastSlot] == 1;
    bool oppHasSeeds = slots_[14 - lastSlot] > 0;

    if (onOwnSide && wasEmpty && oppHasSeeds) {
        int ownRumah = (p == Player::P1) ? P1_RUMAH_INDEX : P2_RUMAH_INDEX;

        slots_[ownRumah] += slots_[lastSlot] + slots_[14 - lastSlot];
        slots_[lastSlot] = 0;
        slots_[14 - lastSlot] = 0;

        result.capture = true;
    }

    return result;
}

void Board::_setSlot(int i, int v) {
    slots_[i] = v;
}
