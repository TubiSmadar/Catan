// Tuvia Smadar
// gunslokij@gmail.com

#include "catan.hpp"
#include <unordered_map>
#include <iomanip>
#include <algorithm>
#include <random>
#include <chrono>
#include <iostream>

using namespace std;

Catan::Catan(Player &player1, Player &player2, Player &player3, Board &board) : board(board){
    // Add players to the players vector
    players.push_back(&player1);
    players.push_back(&player2);
    players.push_back(&player3);
    

    // Create the development card deck
    for (int i = 0; i < 14; i++)
    {
        developmentCards.push_back(DevelopmentCard("Knight"));
    }
    
    for (int i = 0; i < 5; i++)
    {
        developmentCards.push_back(DevelopmentCard("Victory Point"));
    }

    for (int i = 0; i < 2; i++)
    {
        developmentCards.push_back(DevelopmentCard("2 Roads Placement"));
    }

    for (int i = 0; i < 2; i++)
    {
        developmentCards.push_back(DevelopmentCard("Year Of Plenty"));
    }

    for (int i = 0; i < 2; i++)
    {
        developmentCards.push_back(DevelopmentCard("Monopoly"));
    }

    default_random_engine eng(chrono::system_clock::now().time_since_epoch().count());
    shuffle(developmentCards.begin(), developmentCards.end(), eng);

}

void Catan::playTurn(Player &player) {
    for (Player* player1 : players) {
        if (player.getId() != player1->getId()) {
            if (player1->turn) {
                cerr<< "Another player is playing his turn" << endl;
                return;
            }
        }
    }
    player.turn = true;
}

void Catan::endTurn(Player &player) {
    if (player.turn == false) {
        cerr << "This is not your turn" <<endl;
        return;
    }
    for (Player* player1 : players) {
        if (player.getId() != player1->getId()) {
            if (player1->turn == true) {
                cerr<< "Another player is playing his turn" << endl;
                return;
            }

        }
    }
    player.turn = false;
}


// Function to distribute resources to players based on the dice roll
void Catan::giveResources(int dice)
{
    // Map to associate hextile resource types with player resource types
    std::unordered_map<std::string, std::string> resourceMap = {
        {"Mountains", "Ore"},
        {"Pasture", "Wool"},
        {"Forest", "Wood"},
        {"Agricultural", "Wheat"},
        {"Hills", "Brick"}
    };

    // Iterate through all hextiles
    for (int i = 0; i < 19; i++)
    {
        // Check if the hextile's number matches the dice roll
        if (board.getHextiles()[i].getNumber() == dice)
        {
            // Get the lands associated with this hextile
            const vector<Land *> &lands = board.getHextiles()[i].getLands();
            
            // Iterate through each land
            for (Land *land : lands)
            {
                // Get the player ID who owns the land
                int playerId = land->getOwner();
                
                // Check if the land is owned by a player
                if (playerId != -1)
                {
                    // Determine the amount of resources based on whether the land has a city
                    int resourceAmount = (land->getCity() == 1) ? 2 : 1;

                    // Get the resource type of the hextile
                    std::string resourceType = board.getHextiles()[i].getResource();

                    // Check if the resource type exists in the map and allocate resources
                    if (resourceMap.find(resourceType) != resourceMap.end())
                    {
                        // Add resources to the player
                        players[playerId - 1]->addResource(resourceMap[resourceType], resourceAmount);
                    }
                }
            }
        }
    }
}

// Gives development card to player by playerID
void Catan::takeDevelopmentCard(int player)
{
    for (auto &playerID : players) {
        if (playerID->getId() == player && !playerID->turn) {
            cerr << "It is not your turn!" << endl;
            return;
        }
    }
    player = player-1;
    players[player]->developmentCards.push_back(developmentCards.back().getType());
    developmentCards.erase(developmentCards.end());

}

// Prints the winner
void Catan::printWinner()
{
    if(winnerIndex != -1)
    {
        cout << "Player " << winnerIndex << " has won the game!" << endl;
        return;
    }

    cout << "No winner yet." << endl;
}