// Tuvia Smadar
// gunslokij@gmail.com
#include "player.hpp"
#include "board.hpp"
#include "developmentCard.hpp"
#include <iostream>

// Constructor for Player class
Player::Player(int id, const string &name)
    : id(id), name(name), turn(false)
{
    resources.resize(5);
    resources[0] = make_pair("Wood", 0);
    resources[1] = make_pair("Brick", 0);
    resources[2] = make_pair("Wool", 0);
    resources[3] = make_pair("Wheat", 0);
    resources[4] = make_pair("Ore", 0);
    points = 2;
    knightsPlayed = 0;
    winner = -1;
}

// Getter for player ID
int Player::getId() const
{
    return id;
}

// Getter for player points
int Player::getPoints() const {
    return points;
}

// Getter for player name
const string &Player::getName() const
{
    return name;
}

// Check if player can buy a settlement
bool Player::canbuySettlement()
{
    // Check if player have enough resources
    if (resources[0].second >= 1 && resources[1].second >= 1 && resources[2].second >= 1 && resources[3].second >= 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Check if player can buy a city
bool Player::canbuyCity()
{
    if (resources[3].second >= 2 && resources[4].second >= 3)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Check if player can buy a road
bool Player::canbuyRoad()
{
    if (resources[0].second >= 1 && resources[1].second >= 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Roll dice and handle the result
void Player::rollDice(Catan &catan)
{
    int diceRoll = rand() % 6 + 1 + rand() % 6 + 1;
    if (diceRoll == 7)
    {
        cout << "Player " << this->getName() << " rolled a 7" << endl;
        // every player with more than 7 resources will have to discard half of his resources
        discardResources(catan);
    }
    else
    {
        cout << "Player " << this->getName() << " rolled a " << diceRoll << endl;

        catan.giveResources(diceRoll);
    }
}

// Handle resource discarding when a 7 is rolled
void Player::discardResources(Catan &catan)
{
    for (int i = 0; i < 3; i++)
    {
        // check if the player has more than 7 resources
        int totalResources = catan.players[i]->resources[0].second 
                            +catan.players[i]->resources[1].second 
                            +catan.players[i]->resources[2].second 
                            +catan.players[i]->resources[3].second 
                            +catan.players[i]->resources[4].second;
        if (totalResources > 7)
        {
            // calculate the number of resources to discard
            int resourcesToDiscard = totalResources / 2;

            // first, discard half of each resource type (rounded down)
            for (int j = 0; j < 5; j++)
            {
                int discardFromThisResource = catan.players[i]->resources[j].second / 2;
                catan.players[i]->resources[j].second -= discardFromThisResource;
                resourcesToDiscard -= discardFromThisResource;
            }

            // if there are still resources to discard, continue discarding one by one from each resource type
            int j = 0;
            while (resourcesToDiscard > 0)
            {
                if (catan.players[i]->resources[j].second > 0)
                {
                    catan.players[i]->resources[j].second--;
                    resourcesToDiscard--;
                }
                j = (j + 1) % 5; // move to the next resource type, wrap around to the first one if necessary
            }

            // print the resources that the player has after discarding
            cout << "Player " << catan.players[i]->getName() << " now has resources: Wood: " << catan.players[i]->resources[0].second << ", Brick: " << catan.players[i]->resources[1].second << ", Wool: " << catan.players[i]->resources[2].second << ", Wheat: " << catan.players[i]->resources[3].second << ", Ore: " << catan.players[i]->resources[4].second << endl;
        }
    }
}

// Place initial settlement and road
void Player::placeInitialSettlementAndRoad(int landIndex, int landIndex2, Board &board)
{
    if (this->turn == false) {
        cout<<"This is not your turn!"<<endl;
        return;
    }
    if (board.canPlaceInitialSettlementAndRoad(*this, landIndex, landIndex2))
    {
        settlements.push_back(landIndex);
        roads.push_back(board.getRoadByLandIndex(landIndex, landIndex2));
        cout << this->getName() << " placed an initial settlement on land " << landIndex << " and a road between land " << landIndex << " and " << landIndex2 << "\n"
             << endl;
        points++;
    }
    else
    {
        cout << this->getName() << " cannot place an initial settlement on land " << landIndex << " and a road between lands " << landIndex << " and " << landIndex2 << endl;
    }
}

// Place a settlement
void Player::placeSettlement(int landIndex, Board &board, Catan &catan)
{    
    if (this->turn == false) {
        cout<<"This is not your turn!"<<endl;
        return;
    }

    if (!canbuySettlement())
    {
        cerr << "Insufficient resources: " << this->getName() << " cannot place a settlement." << endl;        return;
    }

    if (board.isSettlementValidOnLand(this->getId(), landIndex))
    {
        settlements.push_back(landIndex);
        cout << "Player " << this->getName() << " placed a settlement on land " << landIndex << endl;
        for (int i = 0; i < 4; i++)
        {
            resources[i].second -= 1;
        }
        points += 1;
        // print the resources that the player has after placing the settlement
        cout << "Player " << this->getName() << " now has resources: Wood: " << resources[0].second << ", Brick: " << resources[1].second << ", Wool: " << resources[2].second << ", Wheat: " << resources[3].second << ", Ore: " << resources[4].second << endl;
        // print the points that the player has after placing the settlement
        cout << "Player " << this->getName() << " now has " << points << " points \n"
             << endl;
        // check if the player won the game
        if (points >= 10)
        {
            // make sure no one else won the game
            if (catan.winnerIndex == -1)
            {
                catan.winnerIndex = this->getId();
                cout << "Player " << this->getName() << " won the game!" << endl;
            }
        }
    }
    else
    {
        cout << "Player " << this->getName() << " cannot place a settlement on land " << landIndex << endl;
    }
}

// Upgrade settlement to city
void Player::upgradeToCity(int landIndex, Board &board, Catan &catan)
{

    if (this->turn == false) {
        cout<<"This is not your turn!"<<endl;
        return;
    }
    if (!canbuyCity())
    {
cerr << "Insufficient resources: " << this->getName() << " cannot upgrade settlement to city on land " << landIndex << endl;        return;
    }
    if (board.isCityValidOnLand(this->getId(), landIndex))
    {
        cities.push_back(landIndex);
        cout << "Player " << this->getName() << " upgraded a settlement to a city on land " << landIndex << endl;
        resources[3].second -= 2;
        resources[4].second -= 3;
        points += 1;
        // print the resources that the player has after upgrading the settlement to a city
        cout << "Player " << this->getName() << " now has resources: Wood: " << resources[0].second << ", Brick: " << resources[1].second << ", Wool: " << resources[2].second << ", Wheat: " << resources[3].second << ", Ore: " << resources[4].second << endl;
        // print the points that the player has after upgrading the settlement to a city
        cout << "Player " << this->getName() << " now has " << points << " points \n"
             << endl;
        if (points >= 10)
        {
            // make sure no one else won the game
            if (catan.winnerIndex == -1)
            {
                catan.winnerIndex = this->getId();
                cout << "Player " << this->getName() << " won the game!" << endl;
            }
        }
    }
    else
    {
        cout << "Player " << this->getName() << " cannot upgrade a settlement to a city on vertex " << landIndex << endl;
    }
}

// Place a road
void Player::placeRoad(int landIndex1, int landIndex2, Board &board, int devCard = 0)
{
    if (this->turn == false) {
        cout<<"This is not your turn!"<<endl;
        return;
    }
    if (!devCard) {
        if (!canbuyRoad())
        {
            cerr << "Insufficient resources: " << this->getName() << " cannot place road between lands " << landIndex1 << " and " << landIndex2 << endl;            return;
        }
    }

    if (board.isRoadValidBetweenLands(this->getId(), landIndex1, landIndex2))
    {
        roads.push_back(board.getRoadByLandIndex(landIndex1, landIndex2));
        cout << "Player " << this->getName() << " placed a road between lands " << landIndex1 << " and " << landIndex2 << endl;
        resources[0].second -= 1;
        resources[1].second -= 1;
        // print the resources that the player has after placing the road
        cout << "Player " << this->getName() << " now has resources: Wood: " << resources[0].second << ", Brick: " << resources[1].second << ", Wool: " << resources[2].second << ", Wheat: " << resources[3].second << ", Ore: " << resources[4].second << endl;
    }
    else
    {
        cout << "Player " << this->getName() << " cannot place a road between lands " << landIndex1 << " and " << landIndex2 << endl;
    }
}

// Check if player can buy a development card
void Player::canBuyDevelopmentCard()
{
    if (resources[2].second >= 1 && resources[3].second >= 1 && resources[4].second >= 1)
    {
        resources[2].second -= 1;
        resources[3].second -= 1;
        resources[4].second -= 1;
        cout << "Player " << this->getName() << " bought a development card" << endl;
        // print the resources that the player has after buying the development card
        cout << "Player " << this->getName() << " now has resources: Wood: " << resources[0].second << ", Brick: " << resources[1].second << ", Wool: " << resources[2].second << ", Wheat: " << resources[3].second << ", Ore: " << resources[4].second << endl;
    }
    else
    {
        cerr << "Insufficient resources: " << this->getName() << " cannot buy a development card." << endl;    }
}

// Print player's settlements
void Player::getSettlements() const
{
    cout << "Player " << this->getName() << " has settlements on lands: ";
    for (int i = 0; i < (int)settlements.size(); i++)
    {
        cout << settlements[i] << ", ";
    }
    cout << endl;
}

// Print player's Cities
void Player::getCities() const
{
    cout << "Player " << this->getName() << " has cities on lands+: ";
    for (int i = 0; i < (int)cities.size(); i++)
    {
        cout << cities[i] << " ";
    }
}

// Getter for cities vector
const vector<int> &Player::getCitiesVector() const
{
    return cities;
}

// Getter for settlements vector
const vector<int> &Player::getSettlementsVector() const
{
    return settlements;
}

// Getter for roads vector
const vector<int> &Player::getRoads() const
{
    return roads;
}

// Print player resources
void Player::getResources() const
{
    cout << "Player " << this->getName() << " has: \n";
    for (int i = 0; i < 5; i++)
    {
        cout << resources[i].first << ": " << resources[i].second << " \n";
    }
}

// Add resource to player
void Player::addResource(const string &resource, int amount)
{
    for (int i = 0; i < 5; i++)
    {
        if (resources[i].first == resource)
        {
            cout << "Player " << this->getName() << " got " << amount << " " << resource << endl;
            resources[i].second += amount;
            cout << "Player " << this->getName() << " now has " << resources[i].second << " " << resource << endl;
        }
    }
    // print the resources that the player got:
    cout << "Player " << this->getName() << " got the next resources: Wood: " << resources[0].second << ", Brick: " << resources[1].second << ", Wool: " << resources[2].second << ", Wheat: " << resources[3].second << ", Ore: " << resources[4].second << endl;
}

// Player takes development card
void Player::chooseDevelopmentCard(Catan &catan)
{
    if (this->turn == false) {
        cout<<"This is not your turn!"<<endl;
        return;
    }
    if (catan.developmentCards.size() == 0)
    {
        cout << "No more development cards in the deck" << endl;
        return;
    }
    // check if the player has the resources to buy a development card
    if (resources[2].second < 1 || resources[3].second < 1 || resources[4].second < 1)
    {
        cerr << "Insufficient resources: " << this->getName() << " cannot buy a development card." << endl;        return;
    }
    catan.takeDevelopmentCard(this->getId());
    string card = this->developmentCards.back();
    // print the development card that the player got
    cout << "Player " << this->getName() << " bought a development card, and got a: " << card << " card" << endl;
    // subtract the resources that the player used to buy the development card
    resources[2].second -= 1;
    resources[3].second -= 1;
    resources[4].second -= 1;

    // print the resources that the player has after buying the development card
    cout << "Player " << this->getName() << " now has resources: Wood: " << resources[0].second << ", Brick: " << resources[1].second << ", Wool: " << resources[2].second << ", Wheat: " << resources[3].second << ", Ore: " << resources[4].second << endl;

    if (card == "Victory Point")
    {
        this->points += 1;
        // print the points that the player has after buying the development card
        cout << "Player " << this->getName() << " now has " << points << " points \n"
             << endl;
        if (points >= 10)
        {
            // make sure no one else won the game
            if (catan.winnerIndex == -1)
            {
                catan.winnerIndex = this->getId();
                cout << "Player " << this->getName() << " won the game!" << endl;
            }
        }
    }
}

// Use knight development card
void Player::useKnight(Catan &catan)
{
    if (this->turn == false) {
        cout<<"This is not your turn!"<<endl;
        return;
    }
    // check if the player has a knight card
    for (size_t i = 0; i < developmentCards.size(); i++)
    {
        if (developmentCards[i] == "Knight")
        {
            knightsPlayed++;
            // print that the player played a knight card
            cout << "Player " << this->getName() << " played a knight card" << endl;
            // print the number of knights played by the player
            cout << "Player " << this->getName() << " played " << knightsPlayed << " knights" << endl;
            // check the number of knights played for the largest army
            if (knightsPlayed > catan.biggestArmy)
            {
                if (catan.biggestArmyIndex != -1 && catan.biggestArmyIndex != this->getId())
                {
                    catan.players[catan.biggestArmyIndex]->points -= 2;
                    catan.biggestArmy = knightsPlayed;
                    catan.biggestArmyIndex = this->getId();
                    points += 2;
                    if (points >= 10)
                    {
                        // make sure no one else won the game
                        if (catan.winnerIndex == -1)
                        {
                            catan.winnerIndex = this->getId();
                            cout << "Player " << this->getName() << " won the game!" << endl;
                        }
                    }
                }
                else if (catan.biggestArmyIndex == -1)
                {
                    catan.biggestArmy = knightsPlayed;
                    catan.biggestArmyIndex = this->getId();
                    points += 2;
                    if (points >= 10)
                    {
                        // make sure no one else won the game
                        if (catan.winnerIndex == -1)
                        {
                            catan.winnerIndex = this->getId();
                            cout << "Player " << this->getName() << " won the game!" << endl;
                        }
                    }
                }
            }
            // delete the knight card from the player's deck
            developmentCards.erase(developmentCards.begin() + i);
            return;
        }
    }
    cout << "Player " << this->getName() << " does not have a knight card" << endl;
}

// Use 2 roads building development card
void Player::useRoadBuilding(Board &board, int landIndex1, int landIndex2, int landIndex3, int landIndex4)
{
    if (this->turn == false) {
        cout<<"This is not your turn!"<<endl;
        return;
    }
    // check if the player has a road building card
    for (size_t i = 0; i < developmentCards.size(); i++)
    {
        if (developmentCards[i] == "2 Roads Placement")
        {
            // check if the player can place the roads
            if (board.isRoadValidBetweenLands(this->getId(), landIndex1, landIndex2) && board.isRoadValidBetweenLands(this->getId(), landIndex3, landIndex4))
            {
                placeRoad(landIndex1, landIndex2, board,1);
                placeRoad(landIndex3, landIndex4, board,1);
                // delete the road building card from the player's deck
                developmentCards.erase(developmentCards.begin() + i);
                return;
            }
        }
    }
    cout << "Player " << this->getName() << " does not have a road building card" << endl;
}

// Use year of plenty development card
void Player::useYearOfPlenty(string resource1, string resource2)
{
    if (this->turn == false) {
        cout<<"This is not your turn!"<<endl;
        return;
    }
    // check if the player has a year of plenty card
    for (size_t i = 0; i < (developmentCards.size()); i++)
    {
        if (developmentCards[i] == "Year Of Plenty")
        {
            // check if the player can get the resources
            
            addResource(resource1, 1);
            addResource(resource2, 1);
            // delete the year of plenty card from the player's deck
            developmentCards.erase(developmentCards.begin() + i);
            // developmentCards.shrink_to_fit();
            return;
        }
    }
    cout << "Player " << this->getName() << " does not have a year of plenty card" << endl;
}

// Use monopoly develoment card
void Player::useMonopoly(Catan &catan, string resource)
{
    if (this->turn == false) {
        cout<<"This is not your turn!"<<endl;
        return;
    }
    // check if the player has a monopoly card
    for (size_t i = 0; i < developmentCards.size(); i++)
    {
        if (developmentCards[i] == "Monopoly")
        {
            // check if the player can get the resources
            for (int j = 0; j < 3; j++)
            {
                if (catan.players[j]->getId() != this->getId())
                {
                    for (int k = 0; (long unsigned int)k < catan.players[j]->resources.size(); k++)
                    {
                        if (catan.players[j]->resources[k].first == resource)
                        {
                            addResource(resource, catan.players[j]->resources[k].second);
                            catan.players[j]->resources[k].second = 0;
                        }
                    }
                }
            }
            // delete the monopoly card from the player's deck
            developmentCards.erase(developmentCards.begin() + i);
            return;
        }
    }
    cout << "Player " << this->getName() << " does not have a monopoly card" << endl;
}

// Trade resources with another player
void Player::tradeResources(Catan &catan, int player, string resource1, int amount, string resource2, int amount2)
{
    if (this->turn == false) {
        cout<<"This is not your turn!"<<endl;
        return;
    }
    // check if the player has the resources
    for (int i = 0; i < 5; i++)
    {
        if (resources[i].first == resource2 && resources[i].second >= amount2)
        {
            // check if the other player has the resources
            for (int j = 0; j < 5; j++)
            {
                if (catan.players[player - 1]->resources[j].first == resource1 && catan.players[player - 1]->resources[j].second >= amount)
                {
                    // trade the resources
                    resources[j].second += amount2;
                    resources[i].second -= amount2;
                    catan.players[player - 1]->resources[i].second += amount;
                    catan.players[player - 1]->resources[j].second -= amount;
                    cout << "Player " << this->getName() << " traded " << amount << " " << resource1 << " with player " << catan.players[player - 1]->getName() << " for " << amount2 << " " << resource2 << endl;
                    // print the resources that the player has after trading
                    cout << "Player " << this->getName() << " now has resources: Wood: " << resources[0].second << ", Brick: " << resources[1].second << ", Wool: " << resources[2].second << ", Wheat: " << resources[3].second << ", Ore: " << resources[4].second << endl;
                    // print the resources that the other player has after trading
                    cout << "Player " << catan.players[player - 1]->getName() << " now has resources: Wood: " << catan.players[player - 1]->resources[0].second << ", Brick: " << catan.players[player - 1]->resources[1].second << ", Wool: " << catan.players[player - 1]->resources[2].second << ", Wheat: " << catan.players[player - 1]->resources[3].second << ", Ore: " << catan.players[player - 1]->resources[4].second << endl;
                    return;
                }
            }
        }
    }
    // print that the trade was not successful
    cout << "Player " << this->getName() << " cannot trade " << amount << " " << resource1 << " with player " << catan.players[player - 1]->getName() << " for " << amount2 << " " << resource2 << endl;
}