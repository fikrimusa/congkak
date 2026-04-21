#pragma once
#include <array>

enum class Player { P1, P2 };

class Board {
public:
    Board() {
        slots_.fill(STARTING_SEEDS);
        slots_[P1_RUMAH_INDEX] = 0;
        slots_[P2_RUMAH_INDEX] = 0;
    }

    int getKampung(int i) const;
    int getRumah(Player p) const;
    int getTotalSeeds() const;
    bool isGameOver() const;
    void makeMove(int hole, Player p);

private:
    std::array<int, 16> slots_{};
    static constexpr int P1_RUMAH_INDEX = 7;
    static constexpr int P2_RUMAH_INDEX = 15;
    static constexpr int STARTING_SEEDS = 7;
    static constexpr std::array<int, 15> SOW_P1 = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    static constexpr std::array<int, 15> SOW_P2 = {
        14, 13, 12, 11, 10, 9, 8, 15, 6, 5, 4, 3, 2, 1, 0};
};
