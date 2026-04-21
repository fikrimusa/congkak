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

    b.makeMove(2, Player::P1);
    std::cout << "After P1 plays K2:\n";
    std::cout << "  K2: " << b.getKampung(2) << " (expect 0)\n";
    std::cout << "  K3: " << b.getKampung(3) << " (expect 8)\n";
    std::cout << "  K6: " << b.getKampung(6) << " (expect 8)\n";
    std::cout << "  P1 rumah: " << b.getRumah(Player::P1) << " (expect 1)\n";
    std::cout << "  K8: " << b.getKampung(8) << " (expect 8)\n";
    std::cout << "  K9: " << b.getKampung(9) << " (expect 8)\n";
    std::cout << "  Total: " << b.getTotalSeeds() << " (expect 98)\n";
    return 0;
}
