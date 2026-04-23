#include "board.hpp"
#include "game.hpp"

#include <iostream>

int main() {
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

    // Test 1: fresh Game state
    {
        Game g;
        std::cout << "Fresh Game:\n";
        std::cout << "  currentPlayer P1? " << (g.currentPlayer() == Player::P1)
                  << " (expect true)\n";
        std::cout << "  isGameOver: " << g.isGameOver() << " (expect false)\n";
        std::cout << "  K0 seeds: " << g.board().getKampung(0) << " (expect 7)\n";
    }

    // Test 2: valid move, no extra turn → flip to P2
    // P1 plays K2 (7 seeds) → sows K3..K6,R1,K8,K9; last slot K9 (kampung, not rumah)
    {
        Game g;
        bool ok = g.playMove(2);
        std::cout << "P1 plays K2 (no extra turn):\n";
        std::cout << "  playMove: " << ok << " (expect true)\n";
        std::cout << "  currentPlayer P2? " << (g.currentPlayer() == Player::P2)
                  << " (expect true)\n";
    }

    // Test 3: extra turn → player stays P1
    // P1 plays K0 (7 seeds) → last slot lands in R1
    {
        Game g;
        bool ok = g.playMove(0);
        std::cout << "P1 plays K0 (extra turn):\n";
        std::cout << "  playMove: " << ok << " (expect true)\n";
        std::cout << "  currentPlayer P1? " << (g.currentPlayer() == Player::P1)
                  << " (expect true)\n";
    }

    // Test 4: invalid — opponent's side
    {
        Game g;
        bool ok = g.playMove(8);
        std::cout << "P1 plays K8 (opponent's side):\n";
        std::cout << "  playMove: " << ok << " (expect false)\n";
        std::cout << "  currentPlayer P1? " << (g.currentPlayer() == Player::P1)
                  << " (expect true, unchanged)\n";
    }

    // Test 5: invalid — rumah indices and out-of-range
    {
        Game g;
        std::cout << "P1 plays rumah/out-of-range:\n";
        std::cout << "  playMove(7): " << g.playMove(7) << " (expect false)\n";
        std::cout << "  playMove(15): " << g.playMove(15) << " (expect false)\n";
        std::cout << "  playMove(-1): " << g.playMove(-1) << " (expect false)\n";
        std::cout << "  playMove(99): " << g.playMove(99) << " (expect false)\n";
        std::cout << "  currentPlayer P1? " << (g.currentPlayer() == Player::P1)
                  << " (expect true, unchanged)\n";
    }

    // Test 6: invalid — empty kampung
    {
        Game g;
        g._board()._setSlot(0, 0);
        bool ok = g.playMove(0);
        std::cout << "P1 plays empty K0:\n";
        std::cout << "  playMove: " << ok << " (expect false)\n";
        std::cout << "  currentPlayer P1? " << (g.currentPlayer() == Player::P1)
                  << " (expect true, unchanged)\n";
    }

    // Test 7: revival skip
    // Craft: only K0 has 1 seed; P1 K1..K6 empty; P2 side empty; rumahs 0.
    // P1 plays K0 → sows 1 seed to K1. No extra turn.
    // Phase 3a flips to P2. Phase 3b: P2 side empty, game not over → flip back to P1.
    {
        Game g;
        for (int i = 0; i < 16; ++i) g._board()._setSlot(i, 0);
        g._board()._setSlot(0, 1);

        bool ok = g.playMove(0);
        std::cout << "Revival skip (P2 side empty, P1 plays K0):\n";
        std::cout << "  playMove: " << ok << " (expect true)\n";
        std::cout << "  currentPlayer P1? " << (g.currentPlayer() == Player::P1)
                  << " (expect true, revival fired)\n";
        std::cout << "  K0: " << g.board().getKampung(0) << " (expect 0)\n";
        std::cout << "  K1: " << g.board().getKampung(1) << " (expect 1)\n";
    }

    return 0;
}
