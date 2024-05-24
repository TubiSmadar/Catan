#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>
#include <set>
using namespace std;
namespace ariel {
    enum Cards {WOOD, ROCK, BRICK, WHEAT, SHEEP};
    enum DevelopmentCards {VICTORY_POINT};
    class Player {
        private:
            string name;
            int points;
            vector<set<Cards,int>> resourceCards;
            vector<DevelopmentCards> developmentCards;


        public:
            Player(string);
            Player();
            int rollDice();

    };

}


#endif
