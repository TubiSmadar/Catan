#include "board.hpp"
#include <algorithm>
#include <random>
using namespace std;
namespace ariel {
    // Define the terrain distribution
    std::vector<TerrainType> terrains = {
        FOREST, FOREST, FOREST,
        FIELD, FIELD, FIELD, FIELD,
        PASTURE, PASTURE, PASTURE, PASTURE,
        MOUNTAIN, MOUNTAIN, MOUNTAIN,
        HILL, HILL, HILL,
        DESERT
    };

    // Define the number distribution (excluding the desert)
    std::vector<int> numbers = {2, 
                                3, 3, 
                                4, 4, 
                                5, 5, 
                                6, 6, 
                                8, 8, 
                                9, 9, 
                                10, 10, 
                                11, 11, 
                                12};

    std::vector<Hextile> Board::generateBoard() {
        // Shuffle the terrains
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(terrains.begin(), terrains.end(), g);

        // Create the board with shuffled terrains
        std::vector<Hextile> board;
        for (const auto& terrain : terrains) {
            if (terrain == DESERT) {
                board.emplace_back(Hextile(terrain, 0));
            } else {
                board.emplace_back(Hextile(terrain));
            }
        }

        // Shuffle the numbers and assign them to the non-desert tiles
        std::shuffle(numbers.begin(), numbers.end(), g);
        int numberIndex = 0;
        for (auto& tile : board) {
            if (tile.terrain != DESERT) {
                tile.number = numbers[numberIndex++];
            }
        }
        return board;
    }
    
    Board::Board() {
        this->board = generateBoard();
    }

    Board::~Board() {

    }

}