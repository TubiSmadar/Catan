// Tuvia Smadar
// gunslokij@gmail.com


// Defines the Board class for managing the game board in Catan

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
    // Initializes the board with hextiles, lands, and roads
    Board();

    // Assigns values from another Board object
    Board &operator=(const Board&);

    // Returns a reference to the vector of hextiles
    vector<Hextile>& getHextiles();

    // Returns a reference to the vector of lands
    vector<Land>& getLands();

    // Displays the current board configuration
    void printBoard() const;

    // Validates settlement placement for a player on a specific land
    bool isSettlementValidOnLand(int playerId, size_t landIndex);

    // Validates road placement for a player between two lands
    bool isRoadValidBetweenLands(int playerId, size_t landIndex1, size_t landIndex2);

    // Validates city upgrade for a player on a specific land
    bool isCityValidOnLand(int playerId, size_t landIndex);

    // Retrieves the index of a road connecting two lands
    int getRoadByLandIndex(size_t landIndex1, size_t landIndex2);

    // Checks if a player can place initial settlements and roads
    bool canPlaceInitialSettlementAndRoad(Player& player, size_t landIndex, size_t landIndex2);

private:
    // Stores the hexagonal tiles of the board
    vector<Hextile> hextiles;

    // Stores the land vertices where settlements/cities can be built
    vector<Land> lands;

    // Stores the edges where roads can be constructed
    vector<Road> roads;
};

#endif // BOARD_HPP