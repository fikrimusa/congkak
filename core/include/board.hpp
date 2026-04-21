#pragma once
#include <array>

class Board {
public:
    Board() {
        slots_.fill(STARTING_SEEDS);
        slots_[P1_RUMAH_INDEX] = 0;
        slots_[P2_RUMAH_INDEX] = 0;
    }

private:
    std::array<int, 16> slots_{};
    static constexpr int P1_RUMAH_INDEX = 7;
    static constexpr int P2_RUMAH_INDEX = 15;
    static constexpr int STARTING_SEEDS = 7;
};
