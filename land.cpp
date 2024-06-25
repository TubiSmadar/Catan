// Tuvia Smadar
// gunslokij@gmail.com
#include "land.hpp"
#include "hextile.hpp"
#include "road.hpp"

// Constructor 
Land::Land(size_t index) : index(index), owner(-1), city(-1) {}

// Index getter
size_t Land::getIndex() const {
    return index;
}

// Owner setter
void Land::setOwner(int playerId) {
    owner = playerId;
}

// Owner getter
int Land::getOwner() const {
    return owner;
}

// Adjacent hextiles setter
void Land::setAdjacentHextiles(Hextile* hextile) {
    adjacentHextiles.push_back(hextile);
}

// Adjacent hextiles getter
const vector<Hextile*>& Land::getAdjacentHextiles() const {
    return adjacentHextiles;
}

// Neighbor setter
void Land::setNeighbor(Land* land) {
    neighbors.push_back(land);
}

// Neighbor getter
const vector<Land*>& Land::getNeighbors() const {
    return neighbors;
}

// Check if a land is a neighbor
bool Land::isNeighbor(const Land& land) const {
    for (const Land* neighbor : neighbors) {
        if (neighbor->getIndex() == land.getIndex()) {
            return true;
        }
    }
    return false;
}


// Road setter
void Land::setRoad(Road* road) {
    roads.push_back(road);
}

// Road getter
const vector<Road*>& Land::getRoads() const {
    return roads;
}

// City setter
void Land::setCity(int cityId) {
    city = cityId;
}

// City getter
int Land::getCity() const {
    return city;
}

bool Land::operator==(const Land& other)const{
    if (this->getIndex() == other.getIndex() && this->getOwner() == other.getOwner())
    {
        return true;
    }
    return false;
}