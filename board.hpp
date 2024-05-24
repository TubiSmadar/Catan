#ifndef BOARD_HPP
#define BOARD_HPP
#include "hextile.hpp"
#include <vector>
using namespace std;
namespace ariel {

    class Board
    {
        private:
            vector<Hextile> board;
        public:
            Board(/* args */);
            ~Board();
            std::vector<Hextile> generateBoard();

    };
}

#endif