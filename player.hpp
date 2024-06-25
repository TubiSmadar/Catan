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
// Forward declaration of Board and Catan classes
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
// Store development cards
vector<string> developmentCards;
// Trade resources with other players
void tradeResources(Catan &catan, int player, string resource1, int amount, string resource2, int amount2);
// Use Knight Development Card
void useKnight(Catan &catan);
// Use Road Building Development Card
void useRoadBuilding(Board &board, int landIndex1, int landIndex2, int landIndex3, int landIndex4);
// Use Year of Plenty Development Card
void useYearOfPlenty(string resource1, string resource2);
// Use Monopoly Development Card
void useMonopoly(Catan &catan, string resource);
// Discard half of the player's resources
void discardResources(Catan &catan);
// Store player's resources
vector<pair<string, int>> resources;
// Track the winner of the game
int winner;
// Count of knights played
int knightsPlayed = 0;
// Indicate if it's the player's turn
bool turn;
private:
int id;
// Player's name
string name;
// Player's score
int points;
// Store settlement locations
vector<int> settlements;
// Store city locations
vector<int> cities;
// Store road locations
vector<int> roads;
};
#endif // PLAYER_HPP