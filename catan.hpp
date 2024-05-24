#ifndef CATAN_HPP
#define CATAN_HPP
#include "player.hpp"
#include "board.hpp"
using namespace std;
namespace ariel {
    class Catan {
        private:
            Player player1;
            Player player2;
            Player player3;
            Board board;
            int startingPlayer;

        public:
            Catan(Player,Player,Player);
            Catan();
            void ChooseStartingPlayer();
            Board getBoard();
    };

}

#endif