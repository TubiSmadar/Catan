// Tuvia Smadar
// gunslokij@gmail.com

#ifndef CATAN_HPP
#define CATAN_HPP

#include <vector>
#include <cstddef>

#include "hextile.hpp"
#include "road.hpp"
#include "board.hpp"
#include "developmentCard.hpp"
#include "player.hpp"
#include "land.hpp"

using namespace std;
class Player;
class Board;

class Catan {
    public:
    
        // Constructor
        Catan(Player&, Player&, Player&, Board&);

        // Vector to hold players
        vector<Player*> players;
        
        // Gives resources to players based on dice roll
        void giveResources(int dice);
        
        // Vector to hold development cards
        vector<DevelopmentCard> developmentCards;

        // Function to draw a random development card for a player
        void takeDevelopmentCard(int playerId);

        // Index of the player with the largest army
        int biggestArmyIndex = -1;

        // Number of knights played by the player with the largest army
        int biggestArmy = 2;
        
        // Index of the winner
        int winnerIndex = -1;

        // Function to determine and print the winner
        void printWinner();

        void playTurn(Player &);

        void endTurn(Player &);

    private:
        Board& board;

};


#endif // CATAN_HPP