#include "catan.hpp"
using namespace std;
namespace ariel {
    Catan::Catan(Player player1, Player player2,Player player3) {
        this->player1 = player1;
        this->player2 = player2;
        this->player3 = player3;
    }

    Catan::Catan() {}

    Board Catan::getBoard() {
        return this->board;
    }

    void Catan::ChooseStartingPlayer() {
      //TODO errors
        int pid1 = player1.rollDice();
        int pid2 = player2.rollDice();
        int pid3 = player3.rollDice();

        int pid = max(pid1,pid2,pid3);
    }


}