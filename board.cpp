// Tuvia Smadar
// gunslokij@gmail.com

#include <iostream>
#include <vector>
#include <tuple>
#include <iomanip>
#include <algorithm>
#include <random>
#include <chrono>
#include <unordered_map>

#include "board.hpp"

// Initializes the game board with terrains, numbers, and structures
Board::Board()
{
    cout << "Creating board!" << endl;


    // Define terrain types for the game
    vector<string> terrains = {"Mountains" , "Pasture", "Forest", 
                               "Agricultural", "Hills", "Pasture", 
                               "Hills", "Agricultural", "Forest", 
                               "Forest", "Mountains", "Forest", 
                               "Mountains", "Agricultural", "Pasture",
                               "Hills", "Agricultural", "Pasture"};

    // Define vector for terrains numbers
    vector<int> numbers = {2,3,3,
                           4,4,5,
                           5,6,6,
                           8,8,9,
                           9,10,10,
                           11,11,12};

    // Shuffle the hextileData vector
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(terrains.begin(), terrains.end(), g);
    std::shuffle(numbers.begin(),numbers.end(),g);

    int randomIndex = rand() % 18;
    // Inesert desert in random position
    terrains.insert(terrains.begin() + randomIndex, "Desert");
    numbers.insert(numbers.begin() + randomIndex, 7);

    // Initialize the board
    for (size_t i = 0; i < 19; i++){
        hextiles.emplace_back(Hextile(terrains[i],numbers[i],i));
    }


    // Initialize lands for settelments (54)
    lands.reserve(54);
    for (size_t i = 0; i < 54; ++i)
    {
        lands.emplace_back(Land(i));
    }

    // Define connections for each land site based on specific order
    vector<vector<size_t>> hextileLandMap = {
        {0, 1, 2, 10, 9, 8},
        {2, 3, 4, 12, 11, 10}, 
        {4, 5, 6, 14, 13, 12}, 
        {7, 8, 9, 19, 18, 17}, 
        {9, 10, 11, 21, 20, 19}, 
        {11, 12, 13, 23, 22, 21}, 
        {13, 14, 15, 25, 24, 22}, 
        {16, 17, 18, 29, 28, 27}, 
        {18, 19, 20, 31, 30, 29}, 
        {20, 21, 22, 33, 32, 31}, 
        {22, 23, 24, 35, 34, 33}, 
        {24, 25, 26, 37, 36, 35}, 
        {28, 29, 30, 40, 39, 38}, 
        {30, 31, 32, 42, 41, 40}, 
        {32, 33, 34, 44, 43, 42}, 
        {34, 35, 36, 46, 45, 44}, 
        {39, 40, 41, 49, 48, 47}, 
        {41, 42, 43, 51, 50, 49}, 
        {43, 44, 45, 53, 52, 51}};
    
    // Set the lands for each hextile based on landMapping declared before
    for (size_t i = 0; i < 19; i++)
    {
        for (size_t j = 0; j < 6; j++)
        {
            hextiles[i].setLand(lands[hextileLandMap[i][j]]);
        }
    }

    // Set the neightbors for each land in game (can be 2 or 3 neighbors)
    lands[0].setNeighbor(&lands[1]);
    lands[0].setNeighbor(&lands[8]);
    lands[1].setNeighbor(&lands[0]);
    lands[1].setNeighbor(&lands[2]);
    lands[2].setNeighbor(&lands[1]);
    lands[2].setNeighbor(&lands[3]);
    lands[2].setNeighbor(&lands[10]);
    lands[3].setNeighbor(&lands[2]);
    lands[3].setNeighbor(&lands[4]);
    lands[4].setNeighbor(&lands[3]);
    lands[4].setNeighbor(&lands[5]);
    lands[4].setNeighbor(&lands[12]);
    lands[5].setNeighbor(&lands[4]);
    lands[5].setNeighbor(&lands[6]);
    lands[6].setNeighbor(&lands[5]);
    lands[6].setNeighbor(&lands[14]);
    lands[7].setNeighbor(&lands[8]);
    lands[8].setNeighbor(&lands[7]);
    lands[8].setNeighbor(&lands[9]);
    lands[8].setNeighbor(&lands[0]);
    lands[9].setNeighbor(&lands[8]);
    lands[9].setNeighbor(&lands[10]);
    lands[9].setNeighbor(&lands[19]);
    lands[10].setNeighbor(&lands[9]);
    lands[10].setNeighbor(&lands[2]);
    lands[10].setNeighbor(&lands[11]);
    lands[11].setNeighbor(&lands[10]);
    lands[11].setNeighbor(&lands[12]);
    lands[11].setNeighbor(&lands[21]);
    lands[12].setNeighbor(&lands[11]);
    lands[12].setNeighbor(&lands[4]);
    lands[12].setNeighbor(&lands[13]);
    lands[13].setNeighbor(&lands[12]);
    lands[13].setNeighbor(&lands[14]);
    lands[13].setNeighbor(&lands[23]);
    lands[14].setNeighbor(&lands[13]);
    lands[14].setNeighbor(&lands[6]);
    lands[14].setNeighbor(&lands[15]);
    lands[15].setNeighbor(&lands[14]);
    lands[15].setNeighbor(&lands[25]);
    lands[16].setNeighbor(&lands[17]);
    lands[17].setNeighbor(&lands[16]);
    lands[17].setNeighbor(&lands[18]);
    lands[17].setNeighbor(&lands[7]);
    lands[18].setNeighbor(&lands[17]);
    lands[18].setNeighbor(&lands[19]);
    lands[18].setNeighbor(&lands[29]);
    lands[19].setNeighbor(&lands[18]);
    lands[19].setNeighbor(&lands[9]);
    lands[19].setNeighbor(&lands[20]);
    lands[20].setNeighbor(&lands[19]);
    lands[20].setNeighbor(&lands[21]);
    lands[20].setNeighbor(&lands[31]);
    lands[21].setNeighbor(&lands[20]);
    lands[21].setNeighbor(&lands[11]);
    lands[21].setNeighbor(&lands[22]);
    lands[22].setNeighbor(&lands[21]);
    lands[22].setNeighbor(&lands[23]);
    lands[22].setNeighbor(&lands[33]);
    lands[23].setNeighbor(&lands[22]);
    lands[23].setNeighbor(&lands[13]);
    lands[23].setNeighbor(&lands[24]);
    lands[24].setNeighbor(&lands[23]);
    lands[24].setNeighbor(&lands[25]);
    lands[24].setNeighbor(&lands[35]);
    lands[25].setNeighbor(&lands[24]);
    lands[25].setNeighbor(&lands[15]);
    lands[25].setNeighbor(&lands[26]);
    lands[26].setNeighbor(&lands[25]);
    lands[26].setNeighbor(&lands[37]);
    lands[27].setNeighbor(&lands[28]);
    lands[28].setNeighbor(&lands[27]);
    lands[28].setNeighbor(&lands[29]);
    lands[28].setNeighbor(&lands[16]);
    lands[29].setNeighbor(&lands[28]);
    lands[29].setNeighbor(&lands[18]);
    lands[29].setNeighbor(&lands[30]);
    lands[30].setNeighbor(&lands[29]);
    lands[30].setNeighbor(&lands[31]);
    lands[30].setNeighbor(&lands[40]);
    lands[31].setNeighbor(&lands[30]);
    lands[31].setNeighbor(&lands[20]);
    lands[31].setNeighbor(&lands[32]);
    lands[32].setNeighbor(&lands[31]);
    lands[32].setNeighbor(&lands[33]);
    lands[32].setNeighbor(&lands[42]);
    lands[33].setNeighbor(&lands[32]);
    lands[33].setNeighbor(&lands[22]);
    lands[33].setNeighbor(&lands[34]);
    lands[34].setNeighbor(&lands[33]);
    lands[34].setNeighbor(&lands[35]);
    lands[34].setNeighbor(&lands[44]);
    lands[35].setNeighbor(&lands[34]);
    lands[35].setNeighbor(&lands[24]);
    lands[35].setNeighbor(&lands[36]);
    lands[36].setNeighbor(&lands[35]);
    lands[36].setNeighbor(&lands[37]);
    lands[36].setNeighbor(&lands[46]);
    lands[37].setNeighbor(&lands[36]);
    lands[37].setNeighbor(&lands[26]);
    lands[37].setNeighbor(&lands[38]);
    lands[38].setNeighbor(&lands[37]);
    lands[38].setNeighbor(&lands[39]);
    lands[39].setNeighbor(&lands[38]);
    lands[39].setNeighbor(&lands[28]);
    lands[39].setNeighbor(&lands[40]);
    lands[40].setNeighbor(&lands[39]);
    lands[40].setNeighbor(&lands[30]);
    lands[40].setNeighbor(&lands[41]);
    lands[41].setNeighbor(&lands[40]);
    lands[41].setNeighbor(&lands[42]);
    lands[41].setNeighbor(&lands[49]);
    lands[42].setNeighbor(&lands[41]);
    lands[42].setNeighbor(&lands[32]);
    lands[42].setNeighbor(&lands[43]);
    lands[43].setNeighbor(&lands[42]);
    lands[43].setNeighbor(&lands[44]);
    lands[43].setNeighbor(&lands[51]);
    lands[44].setNeighbor(&lands[43]);
    lands[44].setNeighbor(&lands[34]);
    lands[44].setNeighbor(&lands[45]);
    lands[45].setNeighbor(&lands[44]);
    lands[45].setNeighbor(&lands[46]);
    lands[45].setNeighbor(&lands[53]);
    lands[46].setNeighbor(&lands[45]);
    lands[46].setNeighbor(&lands[36]);
    lands[47].setNeighbor(&lands[48]);
    lands[48].setNeighbor(&lands[47]);
    lands[48].setNeighbor(&lands[49]);
    lands[49].setNeighbor(&lands[48]);
    lands[49].setNeighbor(&lands[41]);
    lands[49].setNeighbor(&lands[50]);
    lands[50].setNeighbor(&lands[49]);
    lands[50].setNeighbor(&lands[51]);
    lands[51].setNeighbor(&lands[50]);
    lands[51].setNeighbor(&lands[43]);
    lands[51].setNeighbor(&lands[52]);
    lands[52].setNeighbor(&lands[51]);
    lands[52].setNeighbor(&lands[53]);
    lands[53].setNeighbor(&lands[52]);
    lands[53].setNeighbor(&lands[45]);

    // Reserve 72 spots in the roads vector 
    roads.reserve(72);
    // Initialize each spot with numbered road index
    for (size_t i = 0; i < 72; ++i)
    {
        roads.emplace_back(Road(i));
    }

    // Road mapping (each index contains 2 land indexes for the road)
    vector<vector<size_t>> roadMapping = {
        {0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {0, 8}, {2, 10}, {4, 12}, {6, 14}, {7, 8}, {8, 9}, {9, 10}, {10, 11}, {11, 12}, {12, 13}, {13, 14}, {14, 15}, {7, 17}, {9, 19}, {11, 21}, {13, 23}, {15, 25}, {16, 17}, {17, 18}, {18, 19}, {19, 20}, {20, 21}, {21, 22}, {22, 23}, {23, 24}, {24, 25}, {25, 26}, {16, 27}, {18, 29}, {20, 31}, {22, 33}, {24, 35}, {26, 37}, {27, 28}, {28, 29}, {29, 30}, {30, 31}, {31, 32}, {32, 33}, {33, 34}, {34, 35}, {35, 36}, {36, 37}, {28, 38}, {30, 40}, {32, 42}, {34, 44}, {36, 46}, {38, 39}, {39, 40}, {40, 41}, {41, 42}, {42, 43}, {43, 44}, {44, 45}, {45, 46}, {39, 47}, {41, 49}, {43, 51}, {45, 53}, {47, 48}, {48, 49}, {49, 50}, {50, 51}, {51, 52}, {52, 53}};

    // Set the lands for each road
    for (size_t i = 0; i < roads.size(); ++i)
    {
        roads[i].setLands(&lands[roadMapping[i][0]], &lands[roadMapping[i][1]]);
        lands[roadMapping[i][0]].setRoad(&roads[i]);
        lands[roadMapping[i][1]].setRoad(&roads[i]);
    }

    cout << "Board is ready!" << endl;
}

// Displays the current board configuration
void Board::printBoard() const {
    auto formatHex = [](const Hextile &hex) {
        return hex.getResource().substr(0, 3) + "(" + std::to_string(hex.getNumber()) + ")";
    };

    // Construct the layout for a Catan board
    std::vector<std::vector<int>> layout = {
        { -1, -1, 0,  1,  2, -1,-1},
        { -1,  3,  4,  5, 6, -1},
        { 7, 8, 9, 10, 11},
        { -1, 12, 13, 14, 15, -1},
        { -1, -1, 16, 17, 18,  -1,-1}
    };

    for (const auto& row : layout) {
        std::string line;
        for (const auto& index : row) {
            if (index == -1) {
                line += "       ";
            } else {
                line += " " + formatHex(hextiles[index]) + " ";
            }
        }
        std::cout << line << std::endl;
    }
}

// Copy assignment operator for the Board class
Board& Board::operator=(const Board& other) {
    if (this != &other) {
        this->hextiles = other.hextiles;
        this->lands = other.lands;
        this->roads = other.roads;
    }
    return *this; 
}

// Return the Hextiles
vector<Hextile> &Board::getHextiles()
{
    return hextiles;
}

// Returns the lands
vector<Land> &Board::getLands()
{
    return lands;
}

// Returns road index
int Board::getRoadByLandIndex(size_t index1, size_t index2) {
    if (index1 > index2) {
        size_t temp = index1;
        index1 = index2;
        index2 = temp;
    }

    for (int i = 0; i < 72; ++i) {
        // Check road connectivity
        if (roads[i].getLand1().getIndex() == index1 && roads[i].getLand2().getIndex() == index2) {
            return i; // Return road index if found
        }
    }

    return -1; // Not found
}


// Function to check if a player can place an initial settlement and road
bool Board::canPlaceInitialSettlementAndRoad(Player &player, size_t index1, size_t index2)
{
    // Check if the land indices are valid
    if (index1 >= lands.size() || index1 < 0 || index2 >= lands.size() || index2 < 0)
    {
        cerr << "Invalid index." << endl;
        return false;
    }

    // Get the land at the specified index
    Land &land = lands[index1];

    // Check if the land is already taken by a settlement or city
    if (land.getOwner() != -1)
    {
        cerr << "Land is already taken." << endl;
        return false;
    }

    // Check if the land is adjacent to any land that is already taken by a settlement or city
    bool validRoad = false;
    const vector<Land *> &adjacentLands = land.getNeighbors();
    for (const Land *adjacentLand : adjacentLands)
    {
        if (adjacentLand->getOwner() != -1)
        {
            cerr << "Adjacent land " << adjacentLand->getIndex() << " already taken." << endl;
            return false;
        }
        if (adjacentLand->getIndex() == index2) {
            validRoad = true;
        }

    }

    if (!validRoad) {
        cerr << "Road is not valid!" <<endl;
        return false;
    }

    // Check if the road we are trying to place is already taken
    int roadIndex = getRoadByLandIndex(index1, index2);
    if (roadIndex != -1)
    {
        if (roads[roadIndex].getOwner() != -1)
        {
            cerr << "Road is already taken." << endl;
            return false;
        }
    }

    // Set the owner of the land to the player's ID
    land.setOwner(player.getId());
    
    // Set the owner of the road to the player's ID
    roads[roadIndex].setOwner(player.getId());

    // Map to associate hextile resource types with player resource types
    std::unordered_map<std::string, std::string> resourceMap = {
        {"Mountains", "Ore"},
        {"Pasture", "Wool"},
        {"Forest", "Wood"},
        {"Agricultural", "Wheat"},
        {"Hills", "Brick"}
    };

    // Give the player the resources that the land sits on
    for (int i = 0; i < 19; i++)
    {
        const vector<Land *> &lands = hextiles[i].getLands();
        for (Land *v : lands)
        {
            if (v->getIndex() == index1)
            {
                std::string resourceType = hextiles[i].getResource();
                if (resourceMap.find(resourceType) != resourceMap.end())
                {
                    player.addResource(resourceMap[resourceType], 1);
                }
            }
        }
    }

    return true;
}

// Function to check if a player can place a settelment on land
bool Board::isSettlementValidOnLand(int playerId, size_t landIndex)
{
    // Check if the land index is valid
    if (landIndex >= lands.size() || landIndex < 0)
    {
        cerr << "Invalid land index." << endl;
        return false;
    }

    // Get the land at the specified index
    Land &land = lands[landIndex];

    // Check if the land is already taken
    if (land.getOwner() != -1)
    {
        cerr << "Land is already taken." << endl;
        return false;
    }

    // Check if any adjacent land is taken
    for (const auto& adjacentLand : land.getNeighbors())
    {
        if (adjacentLand->getOwner() != -1)
        {
            cerr << "Adjacent land " << adjacentLand->getIndex() << " is already taken." << endl;
            return false;
        }
    }

    // Check if any adjacent road belongs to the player
    for (const auto& road : land.getRoads())
    {
        if (road->getOwner() == playerId)
        {
            land.setOwner(playerId);
            return true;
        }
    }

    // No adjacent roads belong to the player
    cerr << "No adjacent roads belong to the player." << endl;
    return false;
}

// Function to check if a player can place a road
bool Board::isRoadValidBetweenLands(int playerId, size_t index1, size_t index2)
{
    // Check if land indices are valid
    if (index1 >= lands.size() || index2 >= lands.size() || index1 == index2 || index1 < 0 || index2 < 0)
    {
        cerr << "Invalid index." << endl;
        return false;
    }

    // Get the lands at the specified indices
    const Land &land1 = lands[index1];
    const Land &land2 = lands[index2];

    // Check if the lands are neighbors
    if (!land1.isNeighbor(land2))
    {
        cerr << "Lands are not neighbors." << endl;
        return false;
    }

    // Check if the road between the lands is already taken
    for (Road* road1 : land1.getRoads())
    {
        for (Road* road2 : land2.getRoads())
        {
            if (road1 == road2 && road1->getOwner() > -1)
            {
                // cout << "Road " << road1->getIndex()<< " owner "<<road1->getOwner()<<endl;
                cerr << "Road is already taken." << endl;
                return false;
            }
        }
    }

    // Check if the player owns a settlement or city on either land
    if (land1.getOwner() == playerId || land2.getOwner() == playerId)
    {
        int roadIndex = getRoadByLandIndex(index1, index2);
        if (roadIndex != -1)
        {
            roads[roadIndex].setOwner(playerId);
        }
        return true;
    }

    // Check if the player owns an adjacent road on either land
    for (const auto& road : land1.getRoads())
    {
            if (road->getOwner() == playerId)
            {
                int roadIndex = getRoadByLandIndex(index1, index2);
                if (roadIndex != -1)
                {
                    roads[roadIndex].setOwner(playerId);
                    return true;
                }
            }  
    }    
    
    for (const auto& road : land2.getRoads())
    {
            if (road->getOwner() == playerId)
            {
                int roadIndex = getRoadByLandIndex(index1, index2);
                if (roadIndex != -1)
                {
                    roads[roadIndex].setOwner(playerId);
                    return true;
                }
            }  
    }
    // int roadIndex = getRoadByLandIndex(index1, index2);
    // if (roadIndex != -1)
    //     {
    //         roads[roadIndex].setOwner(playerId);
    //         return true;
    //     }

    cerr << "No adjacent roads belong to the player." << endl;
    return false;
}

// Function to check if a player can upgrade settelment to city
bool Board::isCityValidOnLand(int playerId, size_t landIndex)
{
    // Check if landIndex is valid
    if (landIndex >= lands.size() || landIndex < 0)
    {
        cerr << "Invalid land index." << endl;
        return false;
    }

    // Get the land at the specified index
    Land &land = lands[landIndex];

    // Check if the land is occupied by the player
    if (land.getOwner() != playerId)
    {
        cerr << "Land is not taken by the player." << endl;
        return false;
    }

    // Check if the land is already occupied by a city
    if (land.getCity() == 1)
    {
        cerr << "Land is already taken by a city." << endl;
        return false;
    }

    // Set the land to be occupied by a city
    land.setCity(1);
    return true;
}
