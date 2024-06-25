// Tuvia Smadar
// gunslokij@gmail.com

#include "hextile.hpp"

// Constructor: Initializes a Hextile with given resource, number, and index
Hextile::Hextile(const string& resource, int number, size_t index)
    : resource(resource), number(number), index(index), lands{}, roads{} {}

// Adds a land vertex to this Hextile
void Hextile::setLand(Land& land) {
    lands.push_back(&land);
}

// Sets a road at a specific position around this Hextile
// Position should be between 0 and 5 (inclusive)
void Hextile::setRoad(int position, const Road& road) {
    if (position >= 0 && position < 6) {
        roads[position] = road;
    }
}

// Returns the resource type of this Hextile
string Hextile::getResource() const {
    return resource;
}

// Returns the number token of this Hextile
int Hextile::getNumber() const {
    return number;
}

// Returns the index of this Hextile on the board
size_t Hextile::getIndex() const {
    return index;
}

// Returns a reference to the vector of Land pointers associated with this Hextile
vector<Land*>& Hextile::getLands() {
    return lands;
}

// Returns a const reference to the vector of Roads associated with this Hextile
const vector<Road>& Hextile::getRoads() const {
    return roads;
}