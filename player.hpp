// Tuvia Smadar
// gunslokij@gmail.com
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>
#include "land.hpp"
#include "road.hpp"
#include "hextile.hpp"
#include "board.hpp"
#include "catan.hpp"

// Forward declaration of Board class
class Board;
class Catan;

using namespace std;

class Player
{
public:
    Player(int id, const string &name);

    int getId() const;
    const string &getName() const;
    int getPoints() const;

    void placeInitialSettlementAndRoad(int landIndex, int landIndex2, Board &board);
    void placeSettlement(int landIndex, Board &board, Catan &catan);
    void upgradeToCity(int landIndex, Board &board, Catan &catan);
    void placeRoad(int landIndex1, int landIndex2, Board &board, int devCard);
    void canBuyDevelopmentCard();
    void getSettlements() const;
    void getCities() const;
    const vector<int> &getRoads() const;

    const vector<int> &getCitiesVector() const;

    const vector<int> &getSettlementsVector() const;

    void getResources() const;
    void addResource(const string &resource, int amount);

    bool canbuySettlement();
    bool canbuyCity();
    bool canbuyRoad();

    void rollDice(Catan &catan);

    void chooseDevelopmentCard(Catan &catan);

    // Vector to hold the development cards
    vector<string> developmentCards;

    // Function to trade resources with other players
    void tradeResources(Catan &catan, int player, string resource1, int amount, string resource2, int amount2);

    // Function to use Knight Development Card
    void useKnight(Catan &catan);

    // Function to use Road Building Development Card
    void useRoadBuilding(Board &board, int landIndex1, int landIndex2, int landIndex3, int landIndex4);

    // Function to use Year of Plenty Development Card
    void useYearOfPlenty(string resource1, string resource2);

    // Function to use Monopoly Development Card
    void useMonopoly(Catan &catan, string resource);

    // Function to discard half of the resources of a player
    void discardResources(Catan &catan);

    // Vector to hold the resources
    vector<pair<string, int>> resources;

    // int to get the winner of the game
    int winner;

    // int for the number of knights played
    int knightsPlayed = 0;

    // bool for the trun
    bool turn;

private:
    int id;

    // Name of the player
    string name;
    // Number of points the player has
    int points;
    // Vector to hold the settlements
    vector<int> settlements;
    // Vector to hold the cities
    vector<int> cities;
    // Vector to hold the roads
    vector<int> roads;

    // int to keep track of the number of development cards
    int developmentCardCount = 0;
};

#endif // PLAYER_HPP
