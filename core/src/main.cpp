#include "board.hpp"

#include <iostream>

int main() {
    Board b;
    std::cout << "Board created!\n";
    std::cout << "Seeds in kampung 3: " << b.getKampung(3) << "\n";
    std::cout << "P1 rumah: " << b.getRumah(Player::P1) << "\n";
    std::cout << "Total seeds: " << b.getTotalSeeds() << "\n";
    std::cout << std::boolalpha; // makes bools print as "true"/"false" instead of 1/0
    std::cout << "Game over? " << b.isGameOver() << "\n";
    return 0;
}
