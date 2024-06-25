// Tuvia Smadar
// gunslokij@gmail.com
#ifndef LAND_HPP
#define LAND_HPP

#include <vector>
#include <cstddef>

#include "hextile.hpp"
#include "road.hpp"
class Hextile; // Forward declaration of the Hextile class
class Road; // Forward declaration of the Road class

using namespace std;

class Land {
public:
    // Constructor to initialize the land with an index
    Land(size_t index);

    bool operator==(const Land&) const;

    // Getters and setters for index, owner, roads, adjacent hextiles and land neighbors
    size_t getIndex() const;
    void setOwner(int playerId);
    void setCity(int cityId);
    int getOwner() const;
    int getCity() const;
    void setNeighbor(Land*);
    const vector<Land*>& getNeighbors() const;
    void setRoad(Road*);
    const vector<Road*>& getRoads() const;
    void setAdjacentHextiles(Hextile*);
    const vector<Hextile*>& getAdjacentHextiles() const;


    // Check if a land is a neighbor
    bool isNeighbor(const Land&) const;



private:
    size_t index;
    int owner;
    int city; 
    vector<Hextile*> adjacentHextiles;
    vector<Land*> neighbors;
    vector<Road*> roads;
};

#endif //LAND_HPP
