#include "board.hpp"
#include "game.hpp"

#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

namespace {

std::string playerName(Player p) {
    return (p == Player::P1) ? "P1" : "P2";
}

// Mirror mapping: user types 1-7 meaning "my kampung in sowing order, first to last".
//   P1: 1 -> slot 0, 7 -> slot 6
//   P2: 1 -> slot 14, 7 -> slot 8
int toSlot(Player p, int input) {
    if (p == Player::P1) return input - 1;
    return 15 - input;
}

void renderBoard(const Board& b) {
    std::cout << "\n";

    // P2 row (top): slots 14..8 left-to-right
    std::cout << "          ";
    for (int i = 14; i >= 8; --i) {
        std::cout << "[" << std::setw(2) << b.getKampung(i) << "] ";
    }
    std::cout << "\n";

    // P2 labels 1..7 (left-to-right matches P2's sowing order from their seat)
    std::cout << "          ";
    for (int n = 1; n <= 7; ++n) {
        std::cout << "  " << n << "  ";
    }
    std::cout << "\n";

    // Rumah row: P2's rumah on the left (west), P1's on the right (east)
    std::cout << "P2: " << std::setw(2) << b.getRumah(Player::P2);
    std::cout << "                                   ";
    std::cout << std::setw(2) << b.getRumah(Player::P1) << " :P1\n";

    // P1 labels 1..7
    std::cout << "          ";
    for (int n = 1; n <= 7; ++n) {
        std::cout << "  " << n << "  ";
    }
    std::cout << "\n";

    // P1 row (bottom): slots 0..6 left-to-right
    std::cout << "          ";
    for (int i = 0; i <= 6; ++i) {
        std::cout << "[" << std::setw(2) << b.getKampung(i) << "] ";
    }
    std::cout << "\n\n";
}

void announceWinner(const Board& b) {
    int p1 = b.getRumah(Player::P1);
    int p2 = b.getRumah(Player::P2);
    std::cout << "=== Game Over ===\n";
    std::cout << "P1 rumah: " << p1 << "\n";
    std::cout << "P2 rumah: " << p2 << "\n";
    if (p1 > p2)      std::cout << "P1 wins!\n";
    else if (p2 > p1) std::cout << "P2 wins!\n";
    else              std::cout << "Draw.\n";
}

void runGame() {
    Game game;
    std::cout << "=== Congkak ===\n";
    std::cout << "Each turn, pick 1-7 (1 = your first kampung in sowing order).\n";

    while (!game.isGameOver()) {
        renderBoard(game.board());
        Player p = game.currentPlayer();
        std::cout << playerName(p) << "'s turn. Pick hole (1-7): ";

        int input;
        if (!(std::cin >> input)) {
            if (std::cin.eof()) {
                std::cout << "\nEOF - exiting.\n";
                return;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Not a number. Try again.\n";
            continue;
        }
        if (input < 1 || input > 7) {
            std::cout << "Out of range. Pick 1-7.\n";
            continue;
        }

        int slot = toSlot(p, input);
        if (!game.playMove(slot)) {
            std::cout << "Invalid move (empty kampung). Try again.\n";
            continue;
        }
    }

    renderBoard(game.board());
    announceWinner(game.board());
}

void runSmokeTests() {
    std::cout << std::boolalpha;

    // ===== Board smoke tests =====

    Board b;
    std::cout << "Board created!\n";
    std::cout << "Seeds in kampung 3: " << b.getKampung(3) << "\n";
    std::cout << "P1 rumah: " << b.getRumah(Player::P1) << "\n";
    std::cout << "Total seeds: " << b.getTotalSeeds() << "\n";
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

    // ===== Game smoke tests =====
    std::cout << "\n--- Game smoke tests ---\n";

    {
        Game g;
        std::cout << "Fresh Game:\n";
        std::cout << "  currentPlayer P1? " << (g.currentPlayer() == Player::P1) << " (expect true)\n";
        std::cout << "  isGameOver: " << g.isGameOver() << " (expect false)\n";
        std::cout << "  K0 seeds: " << g.board().getKampung(0) << " (expect 7)\n";
    }
    {
        Game g;
        bool ok = g.playMove(2);
        std::cout << "P1 plays K2 (no extra turn):\n";
        std::cout << "  playMove: " << ok << " (expect true)\n";
        std::cout << "  currentPlayer P2? " << (g.currentPlayer() == Player::P2) << " (expect true)\n";
    }
    {
        Game g;
        bool ok = g.playMove(0);
        std::cout << "P1 plays K0 (extra turn):\n";
        std::cout << "  playMove: " << ok << " (expect true)\n";
        std::cout << "  currentPlayer P1? " << (g.currentPlayer() == Player::P1) << " (expect true)\n";
    }
    {
        Game g;
        bool ok = g.playMove(8);
        std::cout << "P1 plays K8 (opponent's side):\n";
        std::cout << "  playMove: " << ok << " (expect false)\n";
        std::cout << "  currentPlayer P1? " << (g.currentPlayer() == Player::P1) << " (expect true, unchanged)\n";
    }
    {
        Game g;
        std::cout << "P1 plays rumah/out-of-range:\n";
        std::cout << "  playMove(7): " << g.playMove(7) << " (expect false)\n";
        std::cout << "  playMove(15): " << g.playMove(15) << " (expect false)\n";
        std::cout << "  playMove(-1): " << g.playMove(-1) << " (expect false)\n";
        std::cout << "  playMove(99): " << g.playMove(99) << " (expect false)\n";
        std::cout << "  currentPlayer P1? " << (g.currentPlayer() == Player::P1) << " (expect true, unchanged)\n";
    }
    {
        Game g;
        g._board()._setSlot(0, 0);
        bool ok = g.playMove(0);
        std::cout << "P1 plays empty K0:\n";
        std::cout << "  playMove: " << ok << " (expect false)\n";
        std::cout << "  currentPlayer P1? " << (g.currentPlayer() == Player::P1) << " (expect true, unchanged)\n";
    }
    {
        Game g;
        for (int i = 0; i < 16; ++i) g._board()._setSlot(i, 0);
        g._board()._setSlot(0, 1);
        bool ok = g.playMove(0);
        std::cout << "Revival skip (P2 side empty, P1 plays K0):\n";
        std::cout << "  playMove: " << ok << " (expect true)\n";
        std::cout << "  currentPlayer P1? " << (g.currentPlayer() == Player::P1) << " (expect true, revival fired)\n";
        std::cout << "  K0: " << g.board().getKampung(0) << " (expect 0)\n";
        std::cout << "  K1: " << g.board().getKampung(1) << " (expect 1)\n";
    }
}

}  // namespace

int main(int argc, char** argv) {
    if (argc > 1 && std::string(argv[1]) == "--test") {
        runSmokeTests();
        return 0;
    }
    runGame();
    return 0;
}
