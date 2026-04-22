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

    Board b2;
    MoveResult r = b2.makeMove(0, Player::P1);
    std::cout << "Extra-turn test (P1 plays K0):\n";
    std::cout << "  extraTurn: " << r.extraTurn << " (expect true)\n";
    std::cout << "  capture: " << r.capture << " (expect false)\n";

    Board b3;
    b3._setSlot(5, 1);
    b3._setSlot(6, 0);
    MoveResult r2 = b3.makeMove(5, Player::P1);
    std::cout << "Capture test (P1 plays K5 with 1 seed):\n";
    std::cout << "  extraTurn: " << r2.extraTurn << " (expect false)\n";
    std::cout << "  capture: " << r2.capture << " (expect true)\n";
    std::cout << "  K5: " << b3.getKampung(5) << " (expect 0)\n";
    std::cout << "  K6: " << b3.getKampung(6) << " (expect 0)\n";
    std::cout << "  K8: " << b3.getKampung(8) << " (expect 0)\n";
    std::cout << "  P1 rumah: " << b3.getRumah(Player::P1) << " (expect 8)\n";
    std::cout << "  Total: " << b3.getTotalSeeds() << " (expect 85)\n";
    return 0;
}
