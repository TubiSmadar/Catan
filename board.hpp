// Tuvia Smadar
// gunslokij@gmail.com
#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include "hextile.hpp"
#include "land.hpp"
#include "road.hpp"
#include "player.hpp"
#include "developmentCard.hpp"

using namespace std;
class Player;

class Board {
public:
    // Constructor to initialize the board with hextiles, lands, and roads
    Board();

    // Assignment operator for Board class
    Board &operator=(const Board&);

    // Getter for the vector of hextiles
    vector<Hextile>& getHextiles();
    // Getter for the vector of lands
    vector<Land>& getLands();

    // Function to print the current configuration of the board
    void printBoard() const;

    // Check if a settlement placement is valid on a specific land for a given player
    bool isSettlementValidOnLand(int playerId, size_t landIndex);

    // Check if a road placement is valid between two specific lands for a given player
    bool isRoadValidBetweenLands(int playerId, size_t landIndex1, size_t landIndex2);

    // Check if upgrading to a city is valid on a specific land for a given player
    bool isCityValidOnLand(int playerId, size_t landIndex);

    // Function to get the index of a road between two lands
    int getRoadByLandIndex(size_t landIndex1, size_t landIndex2);

    // Check if a player can place initial settlements and roads on specified lands
    bool canPlaceInitialSettlementAndRoad(Player& player, size_t landIndex, size_t landIndex2);

private:
    // Vector to hold hextile objects representing the hexagonal tiles on the board
    vector<Hextile> hextiles;

    // Vector to hold land objects representing the vertices where settlements/cities can be placed
    vector<Land> lands;

    // Vector to hold road objects representing the edges where roads can be built
    vector<Road> roads;
};

#endif // BOARD_HPP
